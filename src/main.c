// Ai Project
// Genetic ALgorithm for Musical Accompaniment

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "fitness.h"
#include "genetic.h"

#include <jack/jack.h>
#include <jack/midiport.h>

#define CLIENT_NAME "Genegle"

/**

   GenegleBot - CS471 AI Semester Project
   Gregory Hughes
   Mardigon Toler

   This file registers a client on the JACK server and handles
   memory allocation for the inidividuals that will participate
   in the genetic algorithm.

   As of the time of the in-class presentation,
   the genetic algorithm goes through 3 generations
   every half-beat after the user enters "start" at the
   command line. Then, the current best individual is used to
   generate and output a note.

   The queue implementation is found in queue.c
   The genetic algorithm is contained in genetic.c
   Our fitness function is in fitness.c

**/


// create MIDI ports as global variables
jack_port_t *midi_input_port;
jack_port_t *midi_output_port;
jack_client_t *client;

// array of the MIDI values for the notes getting sequenced
unsigned char *note_freqs;

// array of note beginnings and lengths
jack_nframes_t *note_starts;
jack_nframes_t *note_lengths;

// other global information for sequencing the AI's output
jack_nframes_t num_notes;
jack_nframes_t loop_nsamp = 44100;

int currentNumClockPulses = 0;
long currentQuarterNote = 0;
int shouldSimulate = 0;

// For sequencing output, we need to know how many of JACK's callbacks
// will occur per ouur smallest possible division of rhythm (i.e. 32nd note)
// Listen for two successive MIDI clock signals, count how many frames in-between them.
size_t framesPerSmallNote;

// Pointers to the population and working population for copying
// as well as a pointer to the queu for user input and "bad" notes
NoteQueue* currentPopulation;
NoteQueue* workingPopulation;
NoteQueue* currentPopulationOriginal;
NoteQueue* workingPopulationOriginal;
NoteQueue* userInputQueue;
NoteQueue* badNotesQueue;

unsigned char note = 0; // gets updated in the process callback from MIDI messages or CLI input

void jack_shutdown(void *arg){
    exit(1);
}



// callback function for whenever the soundcard is ready for more output
// This program does not actually output any audio, but this can be good
// in conjunction with knowing the sampling rate to do accurate timing
// nframes is not how many "chunks," it is how many samples.
// Our AI uses this callback function to update the user input
// as well as to determine when to simulate more generations.
int process(jack_nframes_t nframes, void *arg){

    // monophonic, remembers the current note so it can be turned off in the next callback
    static unsigned char currentNote = 0;
    void* input_port_buffer = jack_port_get_buffer(midi_input_port, nframes);

    void* output_port_buffer = jack_port_get_buffer(midi_output_port, nframes);
    unsigned char* buffer;

    jack_midi_event_t input_event;
    jack_nframes_t event_count = jack_midi_get_event_count(input_port_buffer);
    jack_nframes_t event_index = 0; // for looping over all midi events

    jack_midi_event_get(&input_event, input_port_buffer, 0);
    jack_midi_clear_buffer(output_port_buffer);
    for(int i=0; i<nframes; i++)
    {

        if((input_event.time == i) && (event_index < event_count))
        {
            // MIDI Beat Clock messages are sent 24 times per quater note.
            // As a temporary solution to having the genetic algorithm
            // output MIDI notes, we will play random notes from
            // an individual with a random probability after, say, every
            // 8th note (24/2 = 12 clock pulses per eight note)
            // The NOTEOFF message will not come until this program attempts to
            // output another NOTEON message

            if(*(input_event.buffer) == 0xf8){

                currentNumClockPulses++;
                currentNumClockPulses %= 24;
                if(currentNumClockPulses == 0){
                    currentQuarterNote++;
                    shouldSimulate = 1;
                }
                if(currentNumClockPulses % 12 == 0 && ((double)rand())/RAND_MAX < 0.5){
                    // random eigth notes

                    buffer = jack_midi_event_reserve(output_port_buffer, 0, 3);
                    // turn off the last note played here
                    buffer[2] = 64;
                    buffer[1] = currentNote + 60;
                    buffer[0] = 0x80; // NOTE OFF message
                    // write a note from the current best individual
                    buffer = jack_midi_event_reserve(output_port_buffer, 0, 3);
                    currentNote = GetFitNote(currentPopulation);
                    buffer[2] = 64; // velocity
                    buffer[1] = currentNote + 60;
                    buffer[0] = 0x90;
                }
            }
            // mask with 11110000
            // A note on message is 10010000
            // The next byte will be the note value
            if( ((*(input_event.buffer) & 0xf0)) == 0x90 )
            {
                /* note on */
                note = *(input_event.buffer + 1);
                Note* noteObj = SetupNote(note%12);
                if(noteObj == NULL){
                    printf("ERROR: Could not set up note object.\n");
                }
                PushNoteIntoQueue(noteObj, userInputQueue);
                // printf("%d\n", note);
            }
        }
    }

    return 0;
}

// callback for when sampling rate gets changed
int srate(jack_nframes_t nframes, void *arg)
{
    printf("the sample rate is now %" PRIu32 "/sec\n", nframes);
    return 0;
}

int main(void){
    // seed rng
    srand(time(0));

    client = jack_client_open(CLIENT_NAME, JackNullOption, NULL);
    if(client == 0){
        printf("\nCould not start as a JACK client. Make sure the jack server is running.\n");
        return 1;
    }
    jack_on_shutdown(client, jack_shutdown, 0);

    midi_input_port = jack_port_register(client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
    midi_output_port = jack_port_register(client, "midi_out", JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

    jack_set_process_callback (client, process, 0);
    jack_set_sample_rate_callback (client, srate, 0);

    // allocate space for the population along with
    // duplicate space for use in generating new generations
    currentPopulation = calloc(POP_SIZE, sizeof(NoteQueue));
    workingPopulation = calloc(POP_SIZE, sizeof(NoteQueue));
    currentPopulationOriginal = currentPopulation;
    workingPopulationOriginal = workingPopulation;
    userInputQueue = calloc(1, sizeof(NoteQueue));
    badNotesQueue = calloc(1, sizeof(NoteQueue));

    // initialize note queues. the working memory can stay blank
    for(int i = 0; i < POP_SIZE; i++){
        initNoteQueue(currentPopulation + i);
        initNoteQueue(workingPopulation + i);
        currentPopulation[i].histogram[0] = 1;
    }
    initNoteQueue(userInputQueue);
    initNoteQueue(badNotesQueue);


    if(jack_activate(client) != 0){
        printf("\nERROR: Can't activate the JACK client.\n");
    }

    int running = 1;
    char *command = NULL;
    size_t lineLength = 0;
    ssize_t nread;
    int readInt;
    while(running){
        nread = getline(&command, &lineLength, stdin);
        //printf("%s\n", command);
        if(strncmp(command,"exit",4)== 0){
            running = 0;
            break;
        }
        else if(strncmp(command,"start",5) == 0){
            printf("Now performing genetic algorithm every 4 quarter notes.\n");
            printf("Terminating command line interactions...\n");
            while(1){
                if(shouldSimulate == 1){
                    shouldSimulate = 0;
                    currentPopulation = simulate(currentPopulation,
                             workingPopulation, userInputQueue, badNotesQueue);
                    if(currentPopulation != currentPopulationOriginal){
                        workingPopulation = currentPopulationOriginal;
                    }

                }
                sleep(0.1);
            }
        }
        // Accept input from stdin to make it easier to test
        // Try to interpret each line as a midi note value
        else if((sscanf(command, "%3d", &readInt)) == 1){
            //printf("Got the integer: %d\n", readInt);
            if(readInt >= 0 && readInt <= 127){
                note = (unsigned char)readInt;
                Note* noteObj = SetupNote(note);
                PushNoteIntoQueue(noteObj, currentPopulation);
                //PrintHistogram(currentPopulation);
            }
        }
        else{
            printf("Error parsing input.\n");
        }
    }

    free(command); // allocated in getline


    // Close connectoins to the JACK servre and free up memory
    jack_client_close(client);

    while(QueueEmpty(currentPopulation) == QUEUE_NOT_EMPTY){
        RemoveNote(currentPopulation);
    }
    while(QueueEmpty(workingPopulation) == QUEUE_NOT_EMPTY){
        RemoveNote(workingPopulation);
    }

    free(currentPopulation);
    free(workingPopulation);
    free(userInputQueue);
    free(badNotesQueue);

    exit(0);

}

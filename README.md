## Gregory Hughes
## Mardigon Toler
## CS 472

# AI Project : A Genetic Algorithm for Musical Accompaniment


Depends on the JACK audio connection kit.
When compiling, link with the JACK library.
For example:
gcc *.c -ljack

## Abstract as presented for WVU Undergraduate Research Day at the Capitol:
Generating Concurrent Musical Accompaniment using Artificial Intelligence


One of the most impressive feats of musical performance is improvising while
playing with another musician. We present an Artificial Intelligence (AI) agent that
emulates this feat by playing music alongside a real musician as if it were also
another musician.

While a simple melody is being played in a predetermined key and time signature,
the AI agent generates a simple melody in the same key and time signature using a
genetic algorithm.  The notes from the melody are stored in a custom data structure
that reaches full capacity after approximately around 12 notes. Once the structure
is full, several possible accompaniments, called individuals, of the same size are
randomly generated and then merged based on an evaluation of how well they
sound when contrasted with the input melody.  Using the genetic algorithm, the
best-sounding individuals that synchronize with the input melody are more likely
to be created. The best individual to emerge from multiple rounds of merging and
the occasional mutation is then played while next notes are being recorded.  The
result is a computer-generated melody that plays with the accompanying tune in
harmony.

There are existing programs that generate musical accompaniment, but the
significance of this approach is its ability to generate music in real time during a
musical performance, making it an interesting tool for use in both practice and
performance.


## Info
This AI agent is designed to be used with the JACK Audio Connection Kit:
https://http://jackaudio.org/
To perform, it requires a MIDI clock input as well as MIDI note messages.
As the genetic algorithm searches for "good" accompaniments, it outputs
the current best accompaniments as MIDI note messages, routable with JACK.

If ALSA is installed, MIDI files can be used for input rather than
realtime human input. Find this AI's MIDI port with:

For synchronization, this program relies on MIDI Clock input.
It was tested by using JACK to route the MIDI Clock output from Ardour
into its input.

This agent was developed partly in parallel with the project at:
https://github.com/fifostack/vic

Some requirements for operation are a source of MIDI input, a destination for MIDI output,
and a source for MIDI clock. The Genegle AI agent has been tested with a hardware keyboard
for input, a hardware synthesizer for output, and Ardour (https://ardour.org/)
as a source of MIDI clock input.
It has also been tested with the Virtual Midi Piano Keyboard (http://vmpk.sourceforge.net/)
for input and Qsynth (https://qsynth.sourceforge.io/) for output.

## Instructions
After compiling and running the executable, it will appear in the JACK server as "Genegle."
You must first use software like qjackctrl to connect your source of MIDI input to Genegle's
input port. Then, connect a source of MIDI Clock to Genegle's Input. Next, connect Genegle's
MIDI output to a synthesizer or some other MIDI input port.

To begin the genetic algorithm, enter the word "start" to Genegle. At the moment, after the genetic 
algorithm starts, it can only be stopped by killing or interrupting the process.
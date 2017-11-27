##Gregory Hughes
##Mardigon Toler
##CS 472

#AI Project : A Genetic Algorithm for Musical Accompaniment


Depends on the JACK audio connection kit.
When compiling, link with the JACK library.
For example:
gcc *.c -ljack

##Abstract as presented for WVU Undergraduate Research Day at the Capitol:

###


## Info
This AI agent is designed to be used with the JACK Audio Connection Kit.
To perform, it requires a MIDI clock input as well as MIDI note messages.
As the genetic algorithm searches for "good" accompaniments, it outputs
the current best accompaniments as MIDI note messages, routable with JACK.

If ALSA is installed, MIDI files can be used for input rather than
realtime human input. Find this AI's MIDI port with:

aplaymidi --list

and send a MIDI file to the AI with:

aplaymidi --port <port>

This agent was developed partly in parallel with the project at:
https://github.com/fifostack/vic

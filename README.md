# myuzik
Simple music programming language for Carnatic Classical Music using C++ and VS 2013
Used the MIDI wrapper library for windows API (http://www.codeproject.com/Articles/2771/Wrapper-Library-for-Windows-MIDI-API) to develop the below mentioned classes. Also contains a simple parser to read sheet music and play the same.

Note - Basic set/get of note levels

Octave - Set a default/user defined octave

Raga - Skeleton of the class with only 3 ragas set, along with their scale

Track - main function where you can set the above params, parse and play

Sample files - contain the various ways to play the notes.

Todo:

1) Since this is a simplistic version, Janya ragas are not tested.

2) Ragas with scales having variation of the same note or asymmetric ragam (say, Yadukulakamboji) need to be supported.

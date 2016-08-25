#include "Note.h"
#include <string>
#include <map>

//declaring the basic notes
const std::string Note::basicNotes[7] = { "S", "R", "G", "M", "P", "D", "N" };

//Name: setNoteLevels()
//Set values according to the order in a particular octave, in MIDI, according to the mapping to Western Music
//Ref : http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm
//Ref : http://www.hitxp.com/keyboard-music-notes/western-notations-guide-convert-classical-indian-carnatic/
void Note::setNoteLevels(){
	noteLevels["S"] = 0;
	noteLevels["R1"] = 1;
	noteLevels["R2"] = 2;
	noteLevels["G1"] = 2;
	noteLevels["R3"] = 3;
	noteLevels["G2"] = 3;
	noteLevels["G3"] = 4;
	noteLevels["M1"] = 5;
	noteLevels["M2"] = 6;
	noteLevels["P"] = 7;
	noteLevels["D1"] = 8;
	noteLevels["D2"] = 9;
	noteLevels["N1"] = 9;
	noteLevels["D3"] = 9;
	noteLevels["N2"] = 10;
	noteLevels["N3"] = 11;
}

//Constructor Function
//Basic Notes declared and a default note is set
Note::Note(void){
	if (noteLevels.size() == 0){
		setNoteLevels();
	}
	newNote = "S"; //default
}

//Name: setNote(note)
//The note object is set to a particular note 
void Note::setNote(std::string note){
	newNote = note;
}

//Name: getNote()
//Return the note set in a note object
std::string Note::getNote(){
	return newNote;
}

//Name: getNoteLevel(note)
//Returns the MIDI level of a particular note in a general octave
int Note::getNoteLevel(std::string note){
	if (noteLevels.count(note))
		return noteLevels[note];
	else
		return 0;
}


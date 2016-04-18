#include "Note.h"
#include <string>
#include <map>

const std::string Note::basicNotes[7] = { "S", "R", "G", "M", "P", "D", "N" };

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


Note::Note(void){
	if (noteLevels.size() == 0){
		setNoteLevels();
	}
	newNote = "S"; //default
}

void Note::setNote(std::string note){
	newNote = note;
}

std::string Note::getNote(){
	return newNote;
}

int Note::getNoteLevel(std::string note){
	if (noteLevels.count(note))
		return noteLevels[note];
	else
		return 0;
}


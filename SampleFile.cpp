#include<iostream>
#include "Track.h"


int main(){
	
	Track newTrack;
	Note newNote;
	std::string noteString("S P S+ P S P- S");
	newNote.setNote("S");
	newTrack.setOctave(5);
	
	//newTrack.appendNote(newNote);
	newTrack.appendNotes(noteString);
	newTrack.playTrack();

	return 0;
}

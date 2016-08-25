#include <iostream>
#include "Track.h"


int main(){

	Track newTrack;
	newTrack.extractNotesFromFile("SampleMusicSheet1.txt");
	newTrack.playTrack();

	return 0;
}
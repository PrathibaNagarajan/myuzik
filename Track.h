#include <iostream>
#include <string>
#include <sstream>
#include "Note.h"
#include "Raga.h"


class Track {
	std::string newTrack;
	int midOctaveLevel;
	std::vector<int> noteLevels;
	int channelNum;
public:
	Track();
	void setOctave(int);
	void appendNote(Note);
	void appendNotes(std::string);
	void playTrack();
private:
	std::vector<std::string> splitNotes(std::string);
};
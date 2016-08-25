#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Note.h"
#include "Raga.h"

//Class that defines a track along with the notes, octaves and ragas and plays it by extracting the MIDI levels of the same.
class Track {
	std::string newTrack;
	int midOctaveLevel;
	int rhythmLevel;
	std::vector<int> noteLevels;
	int channelNum;
	std::map<std::string, int> ragaNoteLevels;
public:
	Track();
	void setOctave(int);
	void setRhythm(int);
	void setRaga(std::string);
	void appendNote(Note);
	void appendNotes(std::string);
	void extractNotesFromFile(std::string);
	void playTrack();
private:
	void setDefaultRaga(std::string);
	std::vector<std::string> splitNotes(std::string);
};
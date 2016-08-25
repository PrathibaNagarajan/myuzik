#include <iostream>
#include <string>
#include <map>

//Class to set a Note, return a note and return the MIDI level of the note in a general octave
class Note {
	static const std::string basicNotes[7];
	std::map<std::string, int> noteLevels;
	std::string newNote;
public:
	void setNote(std::string);
	std::string getNote();
	int getNoteLevel(std::string);
	Note();
private:
	void setNoteLevels();
	char getNoteVariation();
};
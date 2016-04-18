#include <iostream>
#include <string>
#include <map>

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
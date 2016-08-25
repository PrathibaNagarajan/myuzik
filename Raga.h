#include <iostream>
#include <vector>
#include <string>
#include <map>

//Class that set ragas, return the MIDI levels and notes of a particular raga
class Raga{
public :
	Raga();
	std::vector<std::string> getNotesForRaga(std::string);
	std::map<std::string, int> getNoteLevelsForRaga(std::string);
private:
	std::string raga;
	std::map<std::string, std::vector<std::string> > ragas;
	void setNoteLevels();
	void setRagas();
};
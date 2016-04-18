#include <iostream>
#include <vector>
#include <string>
#include <map>

class Raga{
public :
	Raga();
	std::vector<std::string> getNotesForRaga(std::string);
	std::map<std::string, int> getNoteLevelsForRaga(std::string);

private:
	std::map<std::string, std::vector<std::string> > ragas;
	void setNoteLevels();
	void setRagas();
};
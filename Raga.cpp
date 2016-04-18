#include "Raga.h"

//Ref :: https://en.wikipedia.org/wiki/Melakarta

void Raga::setRagas(){
	ragas["None"] = { "S", "R1", "R2", "G1","G2","G3", "M1", "M2","P", "D1","D2","D3","N1","N2","N3","S+" };
	ragas["Shankarabharana"] = { "S", "R2", "G3", "M1", "P", "D2", "N3", "S+" };
	ragas["Mayamalavagoula"] = { "S", "R1", "G3", "M1", "P", "D1", "N3", "S+" };
	ragas["Natabhairavi"] = {"S", "R2", "G2", "M1", "P", "D1", "N2", "S+"};
}
Raga::Raga(){
	setRagas();
}

std::vector<std::string> Raga::getNotesForRaga(std::string currentRaga){
	if (ragas.count(currentRaga) > 0)
		return ragas[currentRaga];
	else
		return ragas["None"];
	
}

std::map<std::string, int> Raga::getNoteLevelsForRaga(std::string currentRaga){
	std::vector<std::string> ragaNotes;
	std::map<std::string, int> ragaNoteLevels;

	ragaNotes = getNotesForRaga(currentRaga);
	
	for (int count = 0; count < sizeof(ragaNotes); count++){
		ragaNoteLevels[ragaNotes[count]] = 0; //shall be set in Note.cpp
	}

	return ragaNoteLevels;
}
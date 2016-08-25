#include "Track.h"
#include "midi.h"
#include "MIDIOutDevice.h"
#include "ShortMsg.h"
#include "LongMsg.h"

//Constructor function
//default octave, channel rhythm and raga set
Track::Track(void){
	midOctaveLevel = 5; //default
	channelNum = 0; //default
	rhythmLevel = 8; //default
	std::string defaultRaga("");
	setDefaultRaga(defaultRaga);
}

//Name: setOctave(int)
//Sets the mid level octave for the composition
void Track::setOctave(int oct){
	if (oct <= 10 || oct >= 0){
		midOctaveLevel = oct;
	}
}

//Name: setRhythm(int)
//Sets the rhythm for the composition
void Track::setRhythm(int rhythm) {
	rhythmLevel = rhythm;
}

//Name: setDefaultRaga(raga)
//sets the deafultraga in the constructor of the function
void Track::setDefaultRaga(std::string raga){
	Raga newRaga;
	std::vector<std::string> ragaNotes = newRaga.getNotesForRaga(raga);
	for (int count = 0; count < ragaNotes.size(); count++){
		Note noteObj;
		ragaNoteLevels[ragaNotes[count]] = noteObj.getNoteLevel(ragaNotes[count]);
	}
}

//Name: setRaga(raga)
//sets the raga for a particular track containing a particular composition
void Track::setRaga(std::string raga){
	Raga newRaga;
	Note noteObj;
	ragaNoteLevels.clear();
	std::vector<std::string> ragaNotes = newRaga.getNotesForRaga(raga);
	for (int count = 0; count < ragaNotes.size(); count++){
		std::string majorNote;
		majorNote.push_back(ragaNotes[count].at(0));
		ragaNoteLevels[majorNote] = noteObj.getNoteLevel(ragaNotes[count]);
	}
}

//Name: appendNote(noteObj)
//sets the note for the object. If the note is accompanied by a '+' - it is played in a higher octave.
//If the note is accompanied by a '-' - it is played in a lower octave. The MIDI level of the note is then
//found in that particular octave. Refer below site for the details.
//Ref : http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm
void Track::appendNote(Note noteObj){
	std::string currentNote = noteObj.getNote();
	int currentNoteLevel = ragaNoteLevels[currentNote];
	if (currentNote.find("+") != std::string::npos) 
		currentNoteLevel = 12 * (midOctaveLevel + 1) + currentNoteLevel;
	else if (currentNote.find("-") != std::string::npos)
		currentNoteLevel = 12 * (midOctaveLevel - 1) + currentNoteLevel;
	else
		currentNoteLevel = 12 * midOctaveLevel + currentNoteLevel;
	noteLevels.push_back(currentNoteLevel);
}

//Name: appendNotes(noteObj)
//appends a string of notes separated by spaces
void Track::appendNotes(std::string notes){
	std::vector<std::string> noteString = splitNotes(notes);
	for (int count = 0; count < noteString.size(); count++){
		Note tempNote;
		tempNote.setNote(noteString[count]);
		appendNote(tempNote);
	}
}

//Name: extractNotesFromFile(filePath)
//parses through a file of parameters and notes to create a track object. A sample file is provided.
void Track::extractNotesFromFile(std::string filePath){
	std::ifstream infile(filePath);
	if (infile.is_open())
	{
		std::string line;
		std::string inputToken;
		std::string rhythmKey("@Rhythm");
		std::string notesKey("@Notes");
		std::string ragaKey("@Raga");
		std::string octaveKey("@Octave");
		std::string commentKey("#");
		std::string valueTokenStr;
		int valueTokenInt = 0;
		bool noteDefn = false;
		
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			if (iss >> inputToken >> valueTokenStr) {
				if (inputToken == rhythmKey || inputToken == octaveKey){
					std::stringstream convert(valueTokenStr);
					convert >> valueTokenInt;
					if (inputToken == rhythmKey)
						this->setRhythm(valueTokenInt);
					else 
						this->setOctave(valueTokenInt);
				}
				else if (inputToken == ragaKey)
					this->setRaga(valueTokenStr);
				else if (inputToken.find(commentKey) != std::string::npos)
					continue;
				else if (noteDefn)
					this->appendNotes(line);
			}
			else if (inputToken == notesKey)
				noteDefn = true;
			iss.clear();
		}
		infile.close();
	}
}

//Name : splitNotes(string)
//Splits a string according to spaces and returns a vector
//Ref: http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> Track::splitNotes(std::string notesString){
	std::string buf; // Have a buffer string
	std::stringstream ss(notesString); // Insert the string into a stream

	std::vector<std::string> tokens; // Create vector to hold our notes

	while (ss >> buf)
		tokens.push_back(buf);
	return tokens;
}

//Name: playTrack()
//Plays the track using the MIDI wrapper library
//Ref : http://www.codeproject.com/Articles/2771/Wrapper-Library-for-Windows-MIDI-API
void Track::playTrack(){
	try
	{
		// Make sure there is an output device present
		if (midi::CMIDIOutDevice::GetNumDevs() > 0)
		{
			midi::CMIDIOutDevice OutDevice;
			// Use the first device
			OutDevice.Open(0);
			int noteTime = ceil(3000 / rhythmLevel);
			for (int count = 0; count < noteLevels.size(); count++){
				// Create note-on message
				midi::CShortMsg NoteOnMsg(midi::NOTE_ON, channelNum, noteLevels[count], 127, 0);
				// Turn note on
				NoteOnMsg.SendMsg(OutDevice);
				// Wait a bit
				::Sleep(noteTime);
				// Create note-off message
				midi::CShortMsg NoteOffMsg(midi::NOTE_OFF, channelNum, noteLevels[count], 0, 0);
				// Turn note off
				NoteOffMsg.SendMsg(OutDevice);
			}
			//sleep again to avoid closing the device before the final note finishes playing
			::Sleep(noteTime);
			// Close device
			OutDevice.Close();
		}
		else
		{
			std::cout << "No MIDI output devices present!\n";
		}
	}
	catch (const std::exception &Err)
	{
		std::cout << "Error";
	}
}

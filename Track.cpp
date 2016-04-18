#include "Track.h"
#include "midi.h"
#include "MIDIOutDevice.h"
#include "ShortMsg.h"
#include "LongMsg.h"

Track::Track(void){
	midOctaveLevel = 5; //default
	channelNum = 0; //default
}

void Track::setOctave(int oct){
	if (oct <= 10 || oct >= 0){
		midOctaveLevel = oct;
	}
}

void Track::appendNote(Note noteObj){
	std::string currentNote = noteObj.getNote();
	int currentNoteLevel = noteObj.getNoteLevel(currentNote);
	if (currentNote.find("+") != std::string::npos) 
		currentNoteLevel = 12 * (midOctaveLevel + 1) + currentNoteLevel;
	else if (currentNote.find("-") != std::string::npos)
		currentNoteLevel = 12 * (midOctaveLevel - 1) + currentNoteLevel;
	else
		currentNoteLevel = 12 * midOctaveLevel + currentNoteLevel;
	noteLevels.push_back(currentNoteLevel);
}

void Track::appendNotes(std::string notes){
	std::vector<std::string> noteString = splitNotes(notes);
	for (int count = 0; count < noteString.size(); count++){
		Note tempNote;
		tempNote.setNote(noteString[count]);
		appendNote(tempNote);
	}
}

void Track::playTrack(){
	try
	{
		// Make sure there is an output device present
		if (midi::CMIDIOutDevice::GetNumDevs() > 0)
		{
			midi::CMIDIOutDevice OutDevice;
			// Use the first device
			OutDevice.Open(0);
			for (int count = 0; count < noteLevels.size(); count++){
				// Create note-on message
				midi::CShortMsg NoteOnMsg(midi::NOTE_ON, channelNum, noteLevels[count], 127, 0);
				// Turn note on
				NoteOnMsg.SendMsg(OutDevice);
				// Wait a bit
				::Sleep(2500);
				// Create note-off message
				midi::CShortMsg NoteOffMsg(midi::NOTE_OFF, channelNum, noteLevels[count], 0, 0);
				// Turn note off
				NoteOffMsg.SendMsg(OutDevice);
			}
			
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

//Ref: http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> Track::splitNotes(std::string notesString){
	std::string buf; // Have a buffer string
	std::stringstream ss(notesString); // Insert the string into a stream

	std::vector<std::string> tokens; // Create vector to hold our notes

	while (ss >> buf)
		tokens.push_back(buf);
	return tokens;
}
#include "Octave.h"

Octave::Octave(void){
	octave = 5; //default
}

void Octave::set(int oct){
	if (oct <= 10 || oct >= 0){
		octave = oct;
	}
}
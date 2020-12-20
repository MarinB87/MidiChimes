#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include <vector>
#include <list>
#include "midiout.h"

class AMidiInterface
{
	std::vector<MidiOutputInterface*> list;

public:
	void add(MidiOutputInterface *chimes);
    void remove(MidiOutputInterface *chimes);
	void notify(unsigned char note, unsigned char velocity); 
};

#endif //_OBSERVABLE_H_

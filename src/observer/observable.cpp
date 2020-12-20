#include "observable.h"
#include <algorithm>

using namespace std;

void AMidiInterface::add(MidiOutputInterface *chimes)
{
	list.push_back(chimes);
}
void AMidiInterface::remove(MidiOutputInterface *chimes)
{	
	list.erase(std::remove(list.begin(), list.end(), chimes), list.end());	
}

void AMidiInterface::notify(unsigned char note, unsigned char velocity)
{
	for(vector<MidiOutputInterface*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if(*iter != 0)
		{
			(*iter)->update(note, velocity);
		}
	}
}

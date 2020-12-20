#ifndef _MIDIOUT_H_
#define _MIDIOUT_H_

#include <iostream>
#include <string>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include "observer.h"
#include "sysfswrapper.h"

using namespace std::chrono;

class HoldOutput
{
public:
    void makeOutputThread();
    static std::mutex noteMutex;
    static std::queue<std::pair<milliseconds, int>> noteTimeQueue;
    static PwmDriverWrapper driver;
private:
    std::thread outputThread;
    void taskFunction();
};

class MidiOutputInterface : IObserver
{
public:
	MidiOutputInterface(std::string n); 
    void update(unsigned char note, unsigned char velocity);
private:
	std::string name;
    unsigned char note, velocity;
    HoldOutput noteOutputThreadObject;          
};

#endif //_MIDIOUT_H_

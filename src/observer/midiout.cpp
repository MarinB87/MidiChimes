#include <fstream>
#include <unistd.h>
#include "midiout.h"
#include "notes.h"

std::mutex HoldOutput::noteMutex;
std::queue<std::pair<milliseconds, int>> HoldOutput::noteTimeQueue;
PwmDriverWrapper HoldOutput::driver;

void HoldOutput::makeOutputThread()
{
    outputThread = std::thread(&HoldOutput::taskFunction, this);
}

void HoldOutput::taskFunction()
{
   while (1) {
    if (!HoldOutput::noteTimeQueue.empty()) {
      milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
      std::pair<milliseconds, int> notePress = HoldOutput::noteTimeQueue.front();
        if (ms > (notePress.first + milliseconds(100))) {
              int outChannel = notespace::noteMap.at((int)notePress.second).getNoteOutputChannel();
              HoldOutput::driver.enable(outChannel, false);
              noteMutex.lock();
              HoldOutput::noteTimeQueue.pop();
              noteMutex.unlock();
            }
        }
        usleep(500);
    }
}

MidiOutputInterface::MidiOutputInterface(std::string name)
{
  this->name = name;
  noteOutputThreadObject.makeOutputThread();
}

void MidiOutputInterface::update(unsigned char note, unsigned char velocity)
{
    this->note = note;
    this->velocity = velocity;
    int outChannel = notespace::noteMap.at((int)note).getNoteOutputChannel();

    // This is where the output to the chimes should get executed
    // there should be a method call just below to strike the chimes
    // using driver functions for PWMs which control the strikers
    // all of the parameters should be passed directly to this
    // method - update

    HoldOutput::driver.setPeriod(outChannel);
    HoldOutput::driver.setDutyCycle(outChannel, velocity);
    HoldOutput::driver.enable(outChannel, true);

    std::cout << "Note played: " << notespace::noteMap.at((int)note).getNoteName() << 
    " velocity: " << (int)velocity << 
    " output channel: " << notespace::noteMap.at((int)note).getNoteOutputChannel() << std::endl;

    milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    std::pair<milliseconds, int> notePressEvent;
    notePressEvent.first = ms;
    notePressEvent.second = note;
    HoldOutput::noteMutex.lock();
    HoldOutput::noteTimeQueue.push(notePressEvent);
    HoldOutput::noteMutex.unlock();
}

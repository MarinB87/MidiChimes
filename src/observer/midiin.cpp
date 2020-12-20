#include "midiin.h"
#include "midicommands.h"

void MidiInputInterface::midiMsgCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  MidiInputInterface * keys = static_cast<MidiInputInterface *>(userData);
  keys->rtmidiMsgCallback(deltatime, message, NULL);
}

void MidiInputInterface::playNote(unsigned char note, unsigned char velocity)
{
    notify(note, velocity);
}

void MidiInputInterface::rtmidiMsgCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  //TODO: handle all midi commands inside this function

  if ( ((int)message->at(0) == notespace::noteOn) && ((int)message->at(2) > 0) ) {
      playNote(message->at(1), message->at(2));
  }
}

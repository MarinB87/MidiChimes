#ifndef _MIDIIN_H_
#define _MIDIIN_H_

#include "observable.h"
#include "RtMidi.h"

class MidiInputInterface : public AMidiInterface
{
public:
    static void midiMsgCallback( double deltatime, std::vector< unsigned char > *message, void *userData );
    void rtmidiMsgCallback( double deltatime, std::vector< unsigned char > *message, void *userData );
    void playNote(unsigned char note, unsigned char velocity);
};

#endif // _MIDIIN_H_

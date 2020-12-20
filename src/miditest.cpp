#include <iostream>
#include <cstdlib>
#include <string>
#include "RtMidi.h"
#include "notes.h"
#include "midiin.h"
#include "midiout.h"
#include "midicommands.h"

int main()
{
  RtMidiIn *midiin = new RtMidiIn();

  // My part
  notespace::initNoteMap();
  MidiInputInterface *midiKeys = new MidiInputInterface();
  MidiOutputInterface *midiChimes = new MidiOutputInterface("Chimes");
  midiKeys->add(midiChimes);

  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  midiin->openPort( 0 );

  // Set our callback function.  This should be done immediately after
  // opening the port to avoid having incoming messages written to the
  // queue.
  midiin->setCallback( MidiInputInterface::midiMsgCallback, midiKeys );
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );
  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  char input;
  std::cin.get(input);
  // Clean up

 cleanup:
  delete midiin;
  delete midiKeys;
  delete midiChimes;
  return 0;
}

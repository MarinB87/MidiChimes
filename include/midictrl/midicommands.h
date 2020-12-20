#ifndef _MIDICOMMANDS_H_
#define _MIDICOMMANDS_H_

namespace notespace {

    enum midiCommands {
        noteOff = 0x80,
        noteOn = 0x90,
        aftertouch = 0xA0,
        continuousController = 0xB0,
        patchChange = 0xC0,
        channelPressure = 0xD0,
        pitchBend = 0xE0,
        /* non-musical commands */
        startSysExMsg = 0xF0,
        midiTimeCodeQuarterFrame = 0xF1,
        songPosPointer = 0xF2,
        songSelect = 0xF3,
        tuneRequest = 0xF6,
        endSysExMsg = 0xF7,
        timingClock = 0xF8,
        start = 0xFA,
        cont = 0xFB,
        stop = 0xFC,
        activeSensing = 0xFE,
        sysReset = 0xFF
    };

}

#endif //_MIDICOMMANDS_H_

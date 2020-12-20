#ifndef _NOTES_H_
#define _NOTES_H_

#include <map>
#include <string>

namespace notespace {
  extern std::string configFilePath;
  extern std::string configFileName;
  
  void initNoteMap(const std::string filePath = configFilePath, const std::string fileName = configFileName);
  void initNotePwmOutputs(const int numOutputs);

  class MidiNotes
  {
  private:
    std::string noteName;
    int noteOutputChannel;
    int calibMinValue;
    int calibMaxValue;
  public:
    MidiNotes(std::string name, int outChannel, int minVal, int maxVal) : 
      noteName(name), noteOutputChannel(outChannel), calibMinValue(minVal), calibMaxValue(maxVal) {}
    std::string getNoteName();
    int getNoteOutputChannel();
    int getCalibMinValue();
    int getCalibMaxValue();
  };

  extern std::map<int, MidiNotes> noteMap;
}

#endif //_NOTES_H_

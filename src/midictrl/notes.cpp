#include <fstream>
#include <nlohmann/json.hpp>
#include "notes.h"
#include "sysfswrapper.h"

namespace notespace {

std::map<int, MidiNotes> noteMap;
std::string configFilePath = "/var/midichimes/configs/";
std::string configFileName = "midikeysconfig.json";

//TODO: add setters for calibration and interface to calibrate keys
// using MIDI keyboard buttons

std::string MidiNotes::getNoteName() {
  return noteName;
}

int MidiNotes::getNoteOutputChannel() {
  return noteOutputChannel;
}

int MidiNotes::getCalibMinValue() {
  return calibMinValue;
}

int MidiNotes::getCalibMaxValue() {
  return calibMaxValue;
}

void initNotePwmOutputs(const int numOutputs) {
  for (int channel = 0; channel <= numOutputs; ++channel)
  {
    std::ofstream outPwmExport(pwmDriverPath + pwmExportFileName);
    outPwmExport << channel;
    outPwmExport.close();
  }
}

void initNoteMap(const std::string filePath, const std::string fileName){
  // TODO: add exception handling for opening and parsing file
  std::ifstream ifs(filePath + fileName, std::ifstream::in);
    nlohmann::json jf = nlohmann::json::parse(ifs);

    for (const auto& item : jf.items())
    {
      int noteNum = item.value()["noteNumber"].get<int>();

      MidiNotes midiNote(item.value()["noteName"].get<std::string>(), item.value()["outputChannel"].get<int>(),
        item.value()["calibrationData"]["minValue"].get<int>(), item.value()["calibrationData"]["maxValue"].get<int>());


      noteMap.insert(std::pair<int, MidiNotes>(noteNum, midiNote));
    }

    initNotePwmOutputs(noteMap.size());
}

}

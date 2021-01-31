#include <fstream>
#include "sysfswrapper.h"

std::string pwmDriverPath = "/sys/class/pwm/pwmchip0/";
std::string pwmExportFileName = "export";
std::string pwmChannelName = "pwm-0:";
std::string pwmPeriod = "period";
std::string pwmDutyCycle = "duty_cycle";
std::string pwmEnable = "enable";


int PwmDriverWrapper::setPeriod(int channel, int value){
    std::ofstream outNotePeriod(pwmDriverPath + pwmChannelName + 
    std::to_string(channel) + "/" + pwmPeriod);
    outNotePeriod << value;
    outNotePeriod.close();
    return 0;
}

int PwmDriverWrapper::setDutyCycle(int channel, int value){
    std::ofstream outNoteDutyCycle(pwmDriverPath + pwmChannelName + 
    std::to_string(channel) + "/" + pwmDutyCycle);
    outNoteDutyCycle << ((int)value * (10000 / 127));
    outNoteDutyCycle.close();
    return 0;
}

int PwmDriverWrapper::enable(int channel, bool enable){
    std::ofstream outNoteEnable(pwmDriverPath + pwmChannelName + 
    std::to_string(channel) + "/" + pwmEnable);
    if (enable){
      outNoteEnable << 1;
    } else {
      outNoteEnable << 0;
    }
    outNoteEnable.close();
    return 0;
}

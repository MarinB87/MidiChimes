#ifndef _SYSFSWRAPPER_H_
#define _SYSFSWRAPPER_H_

#include <string>
#define FIX_PERIOD 10000

extern std::string pwmDriverPath;
extern std::string pwmExportFileName;
extern std::string pwmChannelName;
extern std::string pwmPeriod;
extern std::string pwmDutyCycle;
extern std::string pwmEnable;

class PwmDriverWrapper
{
public:
    int setPeriod(int channel, int value = FIX_PERIOD);
    int setDutyCycle(int channel, int value);
    int enable(int channel, bool enable);
};

#endif //_SYSFSWRAPPER_H_
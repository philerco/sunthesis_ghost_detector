#ifndef PHIDGETVOLTAGEINPUT_H
#define PHIDGETVOLTAGEINPUT_H

#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

class PhidgetVoltageInput
{
public:
    PhidgetVoltageInput();
    ~PhidgetVoltageInput();

    int init(int pChannelNumber);
    int release();
    int status();
    int channel();
    double currentVoltage();

    virtual void internalCallbackFunction(double pNewVoltage);

private:

    PhidgetReturnCode initChannel(PhidgetHandle ch, int pChannel);

    int mChannel;
    int mStatus;//-1 : not initialised / 0 : not active / 1 : active
    double mLastVoltage;
    PhidgetVoltageInputHandle mHandle;
};

#endif // PHIDGETVOLTAGEINPUT_H

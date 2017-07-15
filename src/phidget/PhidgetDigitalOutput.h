#ifndef PHIDGETDIGITALOUTPUT_H
#define PHIDGETDIGITALOUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

class PhidgetDigitalOutput
{
public:
    PhidgetDigitalOutput();
    ~PhidgetDigitalOutput();

    int init(int pChannelNumber);
    int release();
    void activate();
    void deactivate();
    int status();
    int channel();

private:

    PhidgetReturnCode initChannel(PhidgetHandle ch, int pChannel);

    int mChannel;
    int mStatus;//-1 : not initialised / 0 : not active / 1 : active
    PhidgetDigitalOutputHandle mHandle;

};

#endif // PHIDGETDIGITALOUTPUT_H

#ifndef GHOSTDETECTOR_H
#define GHOSTDETECTOR_H

#include "src/phidget/PhidgetDigitalOutput.h"
#include "src/phidget/PhidgetVoltageInput.h"
#include "src/RPi/GPIOClass.h"

#include <vector>
#include <thread>

using namespace std;

class GhostDetector
{
public:
    GhostDetector(int pNbLeds, int pMoletteInputPin, int pGachetteInputPin, string mSonGPioPin);

private:

    std::vector<PhidgetDigitalOutput>   mLeds;
    PhidgetVoltageInput                 mMolette;
    PhidgetVoltageInput                 mGachette;
    GPIOClass*                          mSound;

    int                                 mIntensity;//intensité du signal entre 0 et 100
    int                                 mSoundCptr;

    std::unique_ptr<std::thread>        mSoundThread;
    std::unique_ptr<std::thread>        mMainThread;

    void soundThread();
    void mainThread();
};

#endif // GHOSTDETECTOR_H

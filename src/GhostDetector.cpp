#include "GhostDetector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GhostDetector::GhostDetector(int pNbLeds, int pMoletteInputPin, int pGachetteInputPin, std::string mSonGPioPin):
    mIntensity(0),
    mSoundCptr(0)
{
    //Init LEDs
    this->mLeds.assign(pNbLeds, PhidgetDigitalOutput());
    for(int i=0; i < pNbLeds; i++){
        this->mLeds[i].init(i);
        this->mLeds[i].activate();
        usleep(20000);
    }
    for(auto& led:this->mLeds){
        led.deactivate();
        usleep(20000);
    }

    //Init Inputs
    this->mMolette.init(pMoletteInputPin);
    this->mGachette.init(pGachetteInputPin);

    //Init sound GPIO pin
    this->mSound = new GPIOClass(mSonGPioPin);
    this->mSound->export_gpio();
    this->mSound->setdir_gpio("out");

    //Init threads
    this->mSoundThread = std::unique_ptr<std::thread>( new std::thread( [=]{ this->soundThread(); } ) );
    this->mMainThread = std::unique_ptr<std::thread>( new std::thread( [=]{ this->mainThread(); } ) );

}

/**
 * @brief GhostDetector::soundThread
 * Gère l'activation et la désactivation du son par un signal GPIO
 *
 */
void GhostDetector::soundThread(){

    int lThreshold = 0;

    while(1){
        if(this->mIntensity == 0){
            usleep(500000);
        }else{
            lThreshold = 90-this->mIntensity;

            if(lThreshold <=0 || (this->mSoundCptr++)%lThreshold == 0){
                this->mSound->setval_gpio("1");
            }else{
                this->mSound->setval_gpio("0");
            }
            usleep(20000);
        }

    }


}

/**
 * @brief GhostDetector::mainThread
 * Gère les inputs, la gestion de l'aléatoire, la modification de l'intensité et l'éclairage des leds.
 */
void GhostDetector::mainThread(){

    //intensité random entre 0 et 30
    //modification du random de +-5 par tour



}

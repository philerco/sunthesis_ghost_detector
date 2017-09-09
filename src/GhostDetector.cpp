#include "GhostDetector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

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
        cout << this->mIntensity << endl;
        if(this->mSoundCptr > 3000000000) this->mSoundCptr=0;
        if(this->mIntensity == 0){
            usleep(500000);
        }else{
            lThreshold = 90-this->mIntensity;

            if(lThreshold <=0 || (this->mSoundCptr++)%lThreshold == 0){
                this->mSound->setval_gpio("1");
                cout << "bip" << endl;
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
    int random = 0;
    int lIntensity = 0;//intensité de base non modifiée par le random. Ne dépend que du slider
    int lRandomPuissance = 0;//force du signal random : entre 0 et 15
    int ledCptr;
    int ledThrshld;

    while(1){
        lRandomPuissance = this->mMolette.currentVoltage() * 3.;
        if(lRandomPuissance == 0){
            this->mIntensity = 0;
        }else{
            random += rand()%lRandomPuissance-(lRandomPuissance/2);
            if(random < 0){
                random = 0;
            }
            if(random > lRandomPuissance*2){
                random = lRandomPuissance*2;
            }

            lIntensity = this->mGachette.currentVoltage() * 20. ;

            this->mIntensity = lIntensity+random;


            //change leds based on intensity
            ledCptr = 0;
            ledThrshld = this->mIntensity*8/90;
            for(ledCptr=0; ledCptr<this->mLeds.size(); ledCptr++){
                if(ledCptr < ledThrshld){
                    this->mLeds[ledCptr].activate();
                }else{
                    this->mLeds[ledCptr].deactivate();
                }
            }
        }

        usleep(50000);

    }


}

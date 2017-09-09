#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <vector>

#include "src/phidget/PhidgetDigitalOutput.h"
#include "src/phidget/PhidgetVoltageInput.h"
#include "src/RPi/GPIOClass.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    //Init sound GPIO pin
    GPIOClass* mSound;
    mSound = new GPIOClass();
    mSound->export_gpio();
    mSound->setdir_gpio("out");

    int cptr=20;
    int sleep = 2000000;
    while(cptr-->0){
        if(cptr%2 == 0){
            mSound->setval_gpio("1");
        }else{
            mSound->setval_gpio("0");
        }
        usleep(sleep);
        sleep /=2;
    }

    return 0;
}

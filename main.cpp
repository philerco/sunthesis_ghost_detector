#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <vector>

#include "src/phidget/PhidgetDigitalOutput.h"
#include "src/phidget/PhidgetVoltageInput.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    vector<PhidgetDigitalOutput> leds(8);

    for(int i=0; i < 8; i++){
        leds[i].init(i);
        leds[i].activate();
        usleep(20000);
    }

    cout << "lights out !" << endl;
    for(auto& led:leds){
        led.deactivate();
        usleep(20000);
    }

    cout << "End of the World..." << endl;

    PhidgetVoltageInput rotationSensor;
    rotationSensor.init(0);
    double voltage = 1;
    //voltage = rotationSensor.currentVoltage();
    sleep(1);
    while(voltage > 0.0001){
        voltage = rotationSensor.currentVoltage();

        //get nbled to light
        int nbled = voltage*8/5;
        for(int i = 0; i < nbled; ++i){
            leds[i].activate();
        }
        for(int i = nbled; i < 8; ++i){
            leds[i].deactivate();
        }
    }

    for(auto& led:leds){
        led.release();
    }

    cout << "end release" << endl;

    return 0;
}

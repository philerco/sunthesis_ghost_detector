#include "PhidgetDigitalOutput.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

#include "PhidgetGenericHandlers.h"

using namespace std;

PhidgetDigitalOutput::PhidgetDigitalOutput():
    mStatus(-1)
{
}

PhidgetDigitalOutput::~PhidgetDigitalOutput()
{
    this->release();
}

PhidgetReturnCode PhidgetDigitalOutput::initChannel(PhidgetHandle ch, int pChannel)
{
    PhidgetReturnCode res;

    res = Phidget_setOnAttachHandler(ch, onAttachHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on attach handler\n");
        return (res);
    }

    res = Phidget_setOnDetachHandler(ch, onDetachHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on detach handler\n");
        return (res);
    }

    res = Phidget_setOnErrorHandler(ch, errorHandler, NULL);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to assign on error handler\n");
        return (res);
    }

    /*
        * Please review the Phidget22 channel matching documentation for details on the device
        * and class architecture of Phidget22, and how channels are matched to device features.
        */

    /*
        * Specifies the serial number of the device to attach to.
        * For VINT devices, this is the hub serial number.
        *
        * The default is any device.
        */
    // Phidget_setDeviceSerialNumber(ch, <YOUR DEVICE SERIAL NUMBER>);

    /*
        * For VINT devices, this specifies the port the VINT device must be plugged into.
        *
        * The default is any port.
        */
    //Phidget_setHubPort(ch, 0);

    /*
        * Specifies that the channel should only match a VINT hub port.
        * The only valid channel id is 0.
        *
        * The default is 0 (false), meaning VINT hub ports will never match
        */
    //Phidget_setIsHubPortDevice(ch, 1);

    /*
        * Specifies which channel to attach to.  It is important that the channel of
        * the device is the same class as the channel that is being opened.
        *
        * The default is any channel.
        */
    Phidget_setChannel(ch, pChannel);

    /*
        * In order to attach to a network Phidget, the program must connect to a Phidget22 Network Server.
        * In a normal environment this can be done automatically by enabling server discovery, which
        * will cause the client to discovery and connect to available servers.
        *
        * To force the channel to only match a network Phidget, set remote to 1.
        */
    // PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICE);
    // Phidget_setIsRemote(ch, 1);

    return (EPHIDGET_OK);
}

int PhidgetDigitalOutput::init(int pChannelNumber)
{
    PhidgetReturnCode res;
    const char* errs;

    res = PhidgetDigitalOutput_create(&this->mHandle);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to create digital output channel\n");
        return 1;
    }

    res = initChannel((PhidgetHandle)this->mHandle, pChannelNumber);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "failed to initialize channel:%s\n", errs);
        return 1;
    }

    /*
            * Open the channel synchronously: waiting a maximum of 5 seconds.
            */
    res = Phidget_openWaitForAttachment((PhidgetHandle)this->mHandle, 5000);
    if (res != EPHIDGET_OK) {
        if (res == EPHIDGET_TIMEOUT) {
            printf("Channel did not attach after 5 seconds: please check that the device is attached\n");
        } else {
            Phidget_getErrorDescription(res, &errs);
            fprintf(stderr, "failed to open channel:%s\n", errs);
        }
        return 2;
    }

    this->mStatus = 0;
    this->mChannel = pChannelNumber;

    return 0;
}

int PhidgetDigitalOutput::release()
{
    if(this->mStatus > -1){
        this->deactivate();
        Phidget_close((PhidgetHandle)this->mHandle);
        PhidgetDigitalOutput_delete(&this->mHandle);
        this->mStatus = -1;
        return 0;
    }else{
        return 1;
    }
}

void PhidgetDigitalOutput::activate()
{
    if(mStatus > -1){
        PhidgetDigitalOutput_setState(this->mHandle, 1);
        this->mStatus = 1;
    }
}

void PhidgetDigitalOutput::deactivate()
{
    if(mStatus > -1){
        PhidgetDigitalOutput_setState(this->mHandle, 0);
        this->mStatus = 0;
    }
}

int PhidgetDigitalOutput::status()
{
    return this->mStatus;
}

int PhidgetDigitalOutput::channel()
{
    return this->mChannel;
}

#ifndef PHIDGETGENERICHANDLERS_H
#define PHIDGETGENERICHANDLERS_H

#include <stdio.h>
#include <stdlib.h>

#include <phidget22.h>

static void CCONV
onAttachHandler(PhidgetHandle phid, void *ctx) {
    PhidgetReturnCode res;
    int hubPort;
    int channel;
    int serial;

    res = Phidget_getDeviceSerialNumber(phid, &serial);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get device serial number\n");
        return;
    }

    res = Phidget_getChannel(phid, &channel);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get channel number\n");
        return;
    }

    res = Phidget_getHubPort(phid, &hubPort);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get hub port\n");
        hubPort = -1;
    }

    if (hubPort == -1)
        printf("channel %d on device %d attached\n", channel, serial);
    else
        printf("channel %d on device %d hub port %d attached\n", channel, serial, hubPort);
}

static void CCONV
onDetachHandler(PhidgetHandle phid, void *ctx) {
    PhidgetReturnCode res;
    int hubPort;
    int channel;
    int serial;

    res = Phidget_getDeviceSerialNumber(phid, &serial);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get device serial number\n");
        return;
    }

    res = Phidget_getChannel(phid, &channel);
    if (res != EPHIDGET_OK) {
        fprintf(stderr, "failed to get channel number\n");
        return;
    }

    res = Phidget_getHubPort(phid, &hubPort);
    if (res != EPHIDGET_OK)
        hubPort = -1;

    if (hubPort != -1)
        printf("channel %d on device %d detached\n", channel, serial);
    else
        printf("channel %d on device %d hub port %d detached\n", channel, hubPort, serial);
}

static void CCONV
errorHandler(PhidgetHandle phid, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {

    fprintf(stderr, "Error: %s (%d)\n", errorString, errorCode);
}

#endif // PHIDGETGENERICHANDLERS_H

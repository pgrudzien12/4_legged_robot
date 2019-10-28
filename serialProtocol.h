#ifndef __SERIALPROTOCOL_H_
#define __SERIALPROTOCOL_H_
#include "USBAPI.h"
#include "hidMessage.h"

HidMessage receive(Serial_ &serial){
    if (serial.available())
    {
        char buffer[10];
        int length = serial.readBytesUntil((char)0, buffer, 10);
        if (length != 1)
            return HidMessage(0);

        HidMessage message((int)buffer[0]);
        return message;
    }
    return HidMessage(0);
}

#endif
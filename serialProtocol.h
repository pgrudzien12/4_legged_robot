#ifndef __SERIALPROTOCOL_H_
#define __SERIALPROTOCOL_H_
#include "USBAPI.h"
#include "behaviour/keyboardMessage.h"

KeyboardMessage receive(Serial_ &serial){
    if (serial.available())
    {
        char buffer[10];
        int length = serial.readBytesUntil((char)0, buffer, 10);
        if (length != 1)
            return KeyboardMessage(0);

        KeyboardMessage message((int)buffer[0]);
        return message;
    }
    return KeyboardMessage(0);
}

#endif
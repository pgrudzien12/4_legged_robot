#ifndef __SERIALPROTOCOL_H_
#define __SERIALPROTOCOL_H_
#include "USBAPI.h"
#include "hidMessage.h"

HidMessage receive(Serial_ &serial)
{
    if (serial.available())
    {
        char buffer[9];
        int length = serial.readBytesUntil((char)0, buffer, 9);
        if (length != 8)
        {
            serial.println("bad message");
            return HidMessage();
        }

        HidMessage message(buffer);
        return message;
    }

    return HidMessage();
}

#endif
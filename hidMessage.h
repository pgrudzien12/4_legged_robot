#ifndef __HIDMESSAGE_H__
#define __HIDMESSAGE_H__

class HidMessage
{
private:
    byte byte0;
    byte byte1;
    byte byte2;
    byte byte3;
    byte byte4;
    byte byte5;
    byte byte6;
    byte byte7;
public:
    HidMessage();
    HidMessage(char buffer[6]);
    ~HidMessage();

    bool isUpPressed(){
        return (byte1 & (byte)8) > 0;
    }
    
    bool isDownPressed(){
        return (byte1 & (byte)4) > 0;
    }
    
    bool isLeftPressed(){
        return (byte1 & (byte)2) > 0;
    }
        
    bool isRightPressed(){
        return (byte1 & (byte)1) > 0;
    }

    bool isCtrlPressed(){
        return (byte0 & (byte)1) > 0;
    }
    bool isShiftPressed(){
        return (byte0 & (byte)2) > 0;
    }
    bool isAltPressed(){
        return (byte0 & (byte)4) > 0;
    }

    bool noArrowPressed(){
        return (byte1 & (byte)15) == 0;
    }

    bool isCorrectMessage(){
        return (byte0 & (byte)128) > 0;
    }
};

HidMessage::HidMessage(char buffer[6])
{
    this->byte0 = (byte)buffer[0];
    this->byte1 = (byte)buffer[1];
    this->byte2 = (byte)buffer[2];
    this->byte3 = (byte)buffer[3];
    this->byte4 = (byte)buffer[4];
    this->byte5 = (byte)buffer[5];
    this->byte6 = (byte)buffer[6];
    this->byte7 = (byte)buffer[7];
}

HidMessage::HidMessage()
{
    this->byte0 = (byte)0;
    this->byte1 = (byte)0;
    this->byte2 = (byte)0;
    this->byte3 = (byte)0;
    this->byte4 = (byte)0;
    this->byte5 = (byte)0;
    this->byte6 = (byte)0;
    this->byte7 = (byte)0;
}

HidMessage::~HidMessage()
{
}

#endif

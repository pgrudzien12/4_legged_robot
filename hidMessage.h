#ifndef __HIDMESSAGE_H__
#define __HIDMESSAGE_H__

class HidMessage
{
private:
    int data;
public:
    HidMessage(int data);
    ~HidMessage();

    bool isUpPressed(){
        return (data & (byte)64) > 0;
    }
    
    bool isDownPressed(){
        return (data & (byte)32) > 0;
    }
    
    bool isLeftPressed(){
        return (data & (byte)16) > 0;
    }
        
    bool isRightPressed(){
        return (data & (byte)8) > 0;
    }

    bool isCtrlPressed(){
        return (data & (byte)4) > 0;
    }

    bool noArrowPressed(){
        return (data & (byte)120) == 0;
    }

    bool isCorrectMessage(){
        return (data & (byte)1) == 1;
    }
};

HidMessage::HidMessage(int data)
{
    this->data = data;
}

HidMessage::~HidMessage()
{
}

#endif

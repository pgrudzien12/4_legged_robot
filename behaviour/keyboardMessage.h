#ifndef __KEYBOARDMESSAGE_H__
#define __KEYBOARDMESSAGE_H__

class KeyboardMessage
{
private:
    int data;
public:
    KeyboardMessage(int data);
    ~KeyboardMessage();

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

KeyboardMessage::KeyboardMessage(int data)
{
    this->data = data;
}

KeyboardMessage::~KeyboardMessage()
{
}

#endif

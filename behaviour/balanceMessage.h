#ifndef __BALANCEMESSAGE_H__
#define __BALANCEMESSAGE_H__

class BalanceMessage
{
private:
    int data;
public:
    BalanceMessage(int data);
    ~BalanceMessage();

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

BalanceMessage::BalanceMessage(int data)
{
    this->data = data;
}

BalanceMessage::~BalanceMessage()
{
}

#endif

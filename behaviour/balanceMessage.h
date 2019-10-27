#ifndef __BALANCEMESSAGE_H__
#define __BALANCEMESSAGE_H__

class BalanceMessage
{
private:
    int data;
public:
    BalanceMessage(int data);
    ~BalanceMessage();
};

BalanceMessage::BalanceMessage(int data)
{
    this->data = data;
}

BalanceMessage::~BalanceMessage()
{
}

#endif

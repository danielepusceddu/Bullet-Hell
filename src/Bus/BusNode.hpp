#pragma once
#include "Message.hpp"

class BusNode{
    public:
    virtual void notify(Message msg) = 0;
    BusNode();
    ~BusNode();
};
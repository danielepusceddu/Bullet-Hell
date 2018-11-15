#pragma once
#include "Message.hpp"
#include <functional>

class Bus;
class BusNode{
    public:
    BusNode(Bus& bus);
    virtual void notify(Message msg) = 0;
    virtual ~BusNode();

    private:
    std::reference_wrapper<Bus> busRef;
};
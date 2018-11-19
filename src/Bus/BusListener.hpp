#pragma once
#include "Message.hpp"
#include <functional>

class Bus;
class BusListener{
    public:
    BusListener(Bus& bus);
    virtual void notify(Message msg) = 0;
    virtual ~BusListener();

    protected:
    Bus& getBus();

    private:
    std::reference_wrapper<Bus> busRef;
};
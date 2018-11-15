#pragma once
#include "Bus.hpp"
#include "Message.hpp"
#include <functional>

class BusWriter{
    public:
    BusWriter(Bus& bus);
    virtual ~BusWriter();

    protected:
    void sendMessage(Message msg);

    private:
    std::reference_wrapper<Bus> busRef;
};
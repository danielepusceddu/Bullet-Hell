#include "BusListener.hpp"
#include "Bus.hpp"

BusListener::BusListener(Bus& bus):
busRef{std::ref(bus)}
{
    bus.addListener(*this);
}

Bus& BusListener::getBus(){
    return busRef.get();
}

BusListener::~BusListener(){
    busRef.get().removeListener(*this);
}
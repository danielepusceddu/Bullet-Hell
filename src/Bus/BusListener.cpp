#include "BusListener.hpp"
#include "Bus.hpp"

BusListener::BusListener(Bus& bus):
busRef{std::ref(bus)}
{
    bus.addListener(*this);
}

BusListener::~BusListener(){
    busRef.get().removeListener(*this);
}
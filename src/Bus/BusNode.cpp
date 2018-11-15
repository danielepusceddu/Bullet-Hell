#include "BusNode.hpp"
#include "Bus.hpp"

BusNode::BusNode(Bus& bus):
busRef{std::ref(bus)}
{
    bus.addListener(*this);
}

BusNode::~BusNode(){
    busRef.get().removeListener(*this);
}
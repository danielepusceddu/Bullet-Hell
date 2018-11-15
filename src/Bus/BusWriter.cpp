#include "BusWriter.hpp"

BusWriter::BusWriter(Bus& bus):
busRef{std::ref(bus)}
{

}

void BusWriter::sendMessage(Message msg){
    busRef.get().sendMessage(msg);
}

BusWriter::~BusWriter(){
    
}
#include "Message.hpp"

//Constructor
Message::Message(Type messageType, BusWriter& messageCreator)
    : type{messageType}, creator{messageCreator}
    {
}

//Copy Constructor
Message::Message(const Message& msg)
    : type{msg.getType()}, creator{msg.getCreator()}
    {

    }

//Getters
Message::Type Message::getType() const {
    return type;
}

BusWriter& Message::getCreator() const {
    return creator;
}
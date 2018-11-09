#include "Message.hpp"

//Constructor
Message::Message(Type messageType, BusSender& messageCreator)
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

BusSender& Message::getCreator() const {
    return creator;
}
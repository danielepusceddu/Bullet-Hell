#pragma once

class BusWriter;
class Message{
    public:
    enum class Type{SHIP_SHOT, BLUE_SHIP_SHOT, RED_SHIP_SHOT, SHIP_DEATH};
    Message(Type messageType, BusWriter& messageCreator);
    Message(const Message& msg);
    Type getType() const;
    BusWriter& getCreator() const;

    private:
    Type type;
    BusWriter& creator;
};
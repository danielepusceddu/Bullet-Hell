#pragma once

class BusSender;
class Message{
    public:
    enum class Type{SHIP_SHOT, SHIP_DEATH};
    Message(Type messageType, BusSender& messageCreator);
    Message(const Message& msg);
    Type getType() const;
    BusSender& getCreator() const;

    private:
    Type type;
    BusSender& creator;
};
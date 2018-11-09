#pragma once
#include "BusNode.hpp"
#include "Message.hpp"
#include <functional>
#include <vector>
#include <queue>

class Bus{
    public:

    //If listener is not already in the listener list, add it and return true
    //Else return false
    bool addListener(BusNode &listener);

    //If listener is in the listener list, remove it and return true
    //Else return false
    bool removeListener(const BusNode &listener);

    //Add a Message to the bus
    void sendMessage(Message msg);
    
    //Notify listeners of each message and then clear the message queue
    void notifyListeners();

    private:
    std::queue<Message> messages;
    std::vector<std::reference_wrapper<BusNode>> listeners;
    bool isInListeners(const BusNode& node);
    std::vector<std::reference_wrapper<BusNode>>::const_iterator findListener(const BusNode& node);
};
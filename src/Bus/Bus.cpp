#include "Bus.hpp"
#include <algorithm>

bool Bus::addListener(BusListener &listener){
    bool isNewListener = !isInListeners(listener);

    if(isNewListener)
        listeners.push_back(std::ref(listener));

    return isNewListener;
}


bool Bus::removeListener(const BusListener &listener){
    bool found;
    auto position = findListener(listener);

    if(position != listeners.cend()){
        found = true;
        listeners.erase(position);
    }

    else found = false;

    return found;
}


void Bus::sendMessage(Message msg){
    messages.push(msg);
}


void Bus::notifyListeners(){
    //While the message queue is not empty
    while(!messages.empty()){

        //Notify every listener with the message at the front
        for(auto &listener : listeners)
            listener.get().notify(messages.front());
        
        //Then remove the message
        messages.pop();
    }
}


/////////////////
//PRIVATE METHODS
/////////////////

bool Bus::isInListeners(const BusListener &node){
    auto position = findListener(node);
    return position != listeners.cend();
}

std::vector<std::reference_wrapper<BusListener>>::const_iterator Bus::findListener(const BusListener& node){
    auto iterator = std::find_if(listeners.cbegin(), listeners.cend(), 
                    [&](std::reference_wrapper<BusListener> node2){return &node == &(node2.get());});
    return iterator;
}
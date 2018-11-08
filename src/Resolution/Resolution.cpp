#include "Resolution.hpp"

void Resolution::setIntFromResolution(Resolution::Setting res, unsigned int &height, unsigned int &width){
    switch(res){
        case Resolution::Setting::h600w800:
        height = 600;
        width = 800;
        break;

        case Resolution::Setting::h768w1024:
        height = 768;
        width = 1024;
        break;

        case Resolution::Setting::h864w1152:
        height = 864;
        width = 1152;
        break;

        case Resolution::Setting::h960w1280:
        height = 960;
        width = 1280;
        break;
    }
}


bool Resolution::setResolutionFromStr(std::string str, Resolution::Setting &res){
    bool resModified = true;

    if(str.compare("600x800") == 0)
        res =  Resolution::Setting::h600w800;

    else if(str.compare("768x1024") == 0)
        res = Resolution::Setting::h768w1024;

    else if(str.compare("864x1152") == 0)
        res = Resolution::Setting::h864w1152;

    else if(str.compare("960x1280") == 0)
        res = Resolution::Setting::h960w1280;

    else resModified = false;

    return resModified;
}


std::string Resolution::resolutionToStr(Resolution::Setting resolution){
    std::string str;

    switch(resolution){
        case Resolution::Setting::h600w800:
        str = "600x800";
        break;

        case Resolution::Setting::h768w1024:
        str = "768x1024";
        break;

        case Resolution::Setting::h864w1152:
        str = "864x1152";
        break;

        case Resolution::Setting::h960w1280:
        str = "960x1280";
        break;
    }

    return str;
}
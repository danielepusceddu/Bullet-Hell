#pragma once
#include <string>

namespace Resolution{
    enum Setting{h600w800, h768w1024, h864w1152, h960w1280};

    bool setResolutionFromStr(std::string str, Setting &res);
    void setIntFromResolution(Resolution::Setting res, unsigned int &height, unsigned int &width);
    std::string resolutionToStr(Setting resolution);
}
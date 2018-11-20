#pragma once
#include <string>

namespace Difficulty{
    enum Level{easy, normal, hard};

    std::string difficultyToStr(Level difficulty);
    bool setDifficultyFromStr(std::string str, Level &difficulty);
}
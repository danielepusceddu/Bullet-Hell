#include "Difficulty.hpp"

bool Difficulty::setDifficultyFromStr(std::string str, Difficulty::Level &difficulty){
    bool modified = true;

    if(str.compare("easy") == 0)
        difficulty = Difficulty::Level::easy;

    else if(str.compare("normal") == 0)
        difficulty = Difficulty::Level::normal;

    else if(str.compare("hard") == 0)
        difficulty = Difficulty::Level::hard;

    else modified = false;

    return modified;
}


std::string Difficulty::difficultyToStr(Difficulty::Level difficulty){
    std::string str;

    switch(difficulty){
        case Difficulty::Level::easy:
        str = "easy";
        break;

        case Difficulty::Level::normal:
        str = "normal";
        break;

        case Difficulty::Level::hard:
        str = "hard";
        break;
    }

    return str;
}
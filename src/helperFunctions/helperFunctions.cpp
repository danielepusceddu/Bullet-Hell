#include "helperFunctions.hpp"


std::string Helpers::allUpperCase(std::string str){
    for(char &c : str)
        if(c >= 'a' && c <= 'z')
            c += 'A' - 'a';

    return str;
}


std::string Helpers::minutesAndSeconds(sf::Time time){
    std::ostringstream str;
    int minutes = 0;
    int seconds = (int) time.asSeconds();

    while(seconds >= 60){
        minutes++;
        seconds -= 60;
    }

    if(seconds < 10)
        str << minutes << ":0" << seconds;

    else str << minutes << ":" << seconds;
    return str.str();
}


sf::FloatRect Helpers::scaleRect(sf::FloatRect rect, float scaleX, float scaleY){
    rect.width *= scaleX;
    rect.height *= scaleY;
    rect.left *= scaleX;
    rect.top *= scaleY;

    return rect;
}


sf::Vector2f Helpers::flipPointVertically(sf::Vector2f point, sf::Vector2f center){
    sf::Vector2f newPoint = point;
    newPoint.y = center.y + (center.y - newPoint.y);

    return newPoint;
}


sf::FloatRect Helpers::flipRectVertically(sf::FloatRect rect, sf::Vector2f center){
    sf::Vector2f rectPos{rect.left, rect.top};
    rectPos = Helpers::flipPointVertically(rectPos, center);

    rect.left = rectPos.x;
    rect.top = rectPos.y - rect.height;

    return rect;
}
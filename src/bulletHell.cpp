//-std=c++11 -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

#include "Resolution/Resolution.hpp"
#include "Difficulty/Difficulty.hpp"
#include "Game/Game.hpp"
#include <fstream>
#include <string>

void parseConfigFile(Resolution::Setting &res, Difficulty::Level &dif);
void writeDefaultConfigFile();
void parseArgs(int argc, char **argv, Resolution::Setting &res, bool &vsync, Difficulty::Level &dif);

int main(int argc, char **argv){
    Resolution::Setting gameRes = Resolution::Setting::h864w1152; //default res
    Difficulty::Level difficulty = Difficulty::Level::normal; //default difficulty
    bool vsync = true;  //vsync enabled by default

    //Parse config file
    parseConfigFile(gameRes, difficulty);

    //Command line options override the config file
    parseArgs(argc, argv, gameRes, vsync, difficulty);

   
    //Game init
    Game game{gameRes, difficulty, vsync};
    //Game loop
    while(game.isRunning()){
        game.handleInput();
        game.doMovement();
        game.doActions();
        game.destroyObjects();
        game.render();
    }

    return 0;
}



void parseConfigFile(Resolution::Setting &res, Difficulty::Level &dif){
    std::string line;
    std::ifstream file{"bulletHell-config.txt", std::ifstream::in};

    //If file couldn't be opened, 
    //attempt writing the default config file and quit the function
    if(file.is_open() == false){
        std::cout << "Config file could not be opened.\n";
        writeDefaultConfigFile();
        return;
    }

    //While we haven't read all of the file
    while(file.eof() == false){
        //Load a stringstream with the current line
        std::stringstream stream;
        std::getline(file, line);
        stream.str(line);  

        //While we haven't finished parsing the line
        while(stream.eof() == false){
            std::string arg;
            stream >> arg;
            
            //Break if line is whitespace or if this is the start of a comment
            if(arg.size() == 0 || arg[0] == '#')
                break;

            //Resolution arg
            if(arg.compare("resolution") == 0){
                std::string resArg;
                stream >> resArg;
                if(Resolution::setResolutionFromStr(resArg, res) == false)
                    std::cout << "Bad Resolution option in bulletHell-config.txt" << std::endl;
            }

            else if(arg.compare("difficulty") == 0){
                std::string difArg;
                stream >> difArg;
                if(Difficulty::setDifficultyFromStr(difArg, dif) == false)
                    std::cout << "Bad Difficulty option in bulletHell-config.txt" << std::endl;
            }

        }   //end of line parsing

    }   //end of file parsing
}


void parseArgs(int argc, char **argv, Resolution::Setting &res, bool &vsync, Difficulty::Level &dif){
    //Loop through every argument
    for(int i = 1; i < argc; i++){
        //Get a std::string out of the char* argument
        std::string arg{argv[i]};

        //Check for no vsync argument
        if(arg.compare("-novsync") == 0)
            vsync = false;

        //Check for resolution argument
        else if(arg.compare("-r") == 0 && i < argc - 1){
            std::string resArg{argv[++i]};

            //Set resolution based on the argument
            if(Resolution::setResolutionFromStr(resArg, res) == false)
                std::cout << "Bad Resolution Argument." << std::endl;

        }

        //Difficulty arguments
        else if(arg.compare("-d") == 0 && i < argc - 1){
            std::string difArg{argv[++i]};

            if(Difficulty::setDifficultyFromStr(difArg, dif) == false)
                std::cout << "Bad Difficulty Argument." << std::endl;
        }
    }
}

void writeDefaultConfigFile(){
    std::cout << "Creating default config file." << std::endl;
    std::ofstream configFile{"bulletHell-config.txt", std::ofstream::out | std::ofstream::trunc};

    if(!configFile){
        std::cout << "Couldn't create the file." << std::endl;
        return;
    }

    std::string configStr = "#Resolution\n"
                             "#Options: 600x800, 768x1024, 864x1152, 960x1280\n"
                             "resolution 864x1152\n\n"
                             
                             "#vsync\n"
                             "#Options: on, off\n"
                             "vsync on\n\n"
                             
                             "#Difficulty\n"
                             "#Options: easy, normal, hard\n"
                             "difficulty normal";

    configFile << configStr;
    if(configFile.good() == false)
        std::cout << "Error while writing to config file." << std::endl;
}
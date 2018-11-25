#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> //Console output
#include <fstream>  //File streams, to keep track of highest score
#include <sstream>  //String streams (purpose is similar to sprintf), used for score text
#include <vector>   //Vectors to hold enemies and bullets
#include <memory>   //Smart pointers for player and background object
#include <array>    //Safer, easier to use fixed size arrays to hold textures
#include <ctime>    //time(NULL) for Rand Seed
#include <cstdlib>  //Rand
#include "../Bus/Bus.hpp"
#include "../AudioManager/AudioManager.hpp"
#include "../Spawner/Spawner.hpp"
#include "../Background/Background.hpp"   //Moving, looping background
#include "../Animation/Animation.hpp"    //Game object with looping animation
#include "../Effect/Effect.hpp"   //Animation that plays once
#include "../PlayerShip/PlayerShip.hpp"  //Ship object with shoot methods etc.
#include "../helperFunctions/helperFunctions.hpp"   //General helper functions
#include "../Resolution/Resolution.hpp" //Namespace for resolution enum and related helper functions
#include "../Difficulty/Difficulty.hpp" //Namespace for difficulty enum and related helper functions

class Game{
        public:
        Game(Resolution::Setting res, Difficulty::Level difficulty, bool vsync);
        void run();

    private:
        //Bus and Bus Nodes
        Bus bus;
        AudioManager audioManager;

        //Spawner
        Spawner spawner;

        //Window
        sf::RenderWindow window;
        unsigned int screen_w;
        unsigned int screen_h;

        //System
        sf::Clock playTimeClock;
        sf::Time timePerFrame = sf::seconds(1.0 / 60.0);
        float delta = timePerFrame.asSeconds();

        //Game
        std::array<int, 3> highScores;  //high scores for each difficulty
        Difficulty::Level difficulty;  //difficulty the game is being played at

        //Font
        sf::Font font;

        //Textures
        sf::Texture bgTexture;
        sf::Texture blueBulletTexture;
        sf::Texture redBulletTexture;
        sf::Texture playerLife;

        std::array<sf::Texture, 2> blueMosquitoTextures;
        std::array<sf::Texture, 3> blueEagleTextures;
        std::array<sf::Texture, 4> blueDragonTextures;

        //Text
        sf::Text scoreText;
        sf::Text highScoreText;
        sf::Text restartText;
        sf::Text authorName;
        sf::Text authorSurname;
        sf::Text composerName;
        sf::Text timeText;
        sf::Text difficultyText;

        //Game objects
        std::unique_ptr<Background> bg;
        std::unique_ptr<Player_Ship> player;
        std::vector<AI_Ship> enemies;
        std::vector<sf::Sprite> playerBullets;
        std::vector<sf::Sprite> enemyBullets;
        std::vector<Effect> explosions;
        std::vector<sf::Sprite> lives;

        //variables
        bool running = true;
        float lifeScale = 0.03;
        float textScale = 2.0;
        int enemyCount = 0;
        int score = 0;

        //Control booleans
        bool shootToogle = false;
        bool shoot = false;
        bool moveLeft = false;
        bool moveRight = false;
        bool moveUp = false;
        bool moveDown = false;

        //constants
        int maxPlayerHealth = 5;
        float playerSpeed = 420;
        float playerBulletSpeed = 600;
        float enemyBulletSpeed = 240;
        float bgSpeed = 1200;
        float enemyChanceNotToShoot = 100 * 0.065;

        //Private methods
        bool loadHighScores();
        void saveNewHighscore();
        void updateScoreText();
        void restart();
        void initLifeIndicators();
        void playerMovement();
        void initText();
        void initPlayer();
        void initSound();
        void setRes(Resolution::Setting res);
        void spawnEnemies();
        void setDifficulty(Difficulty::Level diff);
        bool outOfScreen(sf::FloatRect rect, int w, int h);

        //Loop Methods
        void handleInput();
        void doMovement();
        void doActions();
        void destroyObjects();
        void render();
};
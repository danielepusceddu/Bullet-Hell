#include "Game.hpp"

//****************
//*PUBLIC METHODS*
//****************

//Constructor
Game::Game(Resolution::Setting res, Difficulty::Level dfculty, bool vsync){
    //Rand seed init
    srand(std::time(NULL));

    //Setting resolution
    this->setRes(res);

    //Loading High Scores
    if(this->loadHighScores() == false)
        this->highScores.fill(0);

    //Setting difficulty
    this->setDifficulty(dfculty);

    //Text init
    this->initText();

    //Textures init
    std::cout << "Loading textures..." << std::endl;

    //background texture
    this->bgTexture.loadFromFile("../assets/textures/background.jpg");

    //bullet textures
    this->blueBulletTexture.loadFromFile("../assets/textures/blue/bullet.bmp");
    this->redBulletTexture.loadFromFile("../assets/textures/red/bullet.bmp");

    //blue eagle textures
    Helpers::loadTextures(this->blueEagleTextures, "../assets/textures/blue/eagle_$d.png");

    //blue mosquito textures
    Helpers::loadTextures(this->blueMosquitoTextures, "../assets/textures/blue/mosquito_$d.png");

    //blue dragon textures
    Helpers::loadTextures(this->blueDragonTextures, "../assets/textures/blue/dragon_$d.png");

    //player life texture
    this->playerLife.loadFromFile("../assets/textures/blue/mothership.png");

    //red mosquito textures
    Helpers::loadTextures(this->redMosquitoTextures, "../assets/textures/red/mosquito_$d.png");

    //red eagle textures
    Helpers::loadTextures(this->redEagleTextures, "../assets/textures/red/eagle_$d.png");

    //red eagle textures
    Helpers::loadTextures(this->redDragonTextures, "../assets/textures/red/dragon_$d.png");

    //Red explosion textures
    Helpers::loadTextures(this->redExplosionTextures, "../assets/textures/red/explosion_$d.png");

    //Blue explosion
    Helpers::loadTextures(this->blueExplosionTextures, "../assets/textures/blue/explosion_$d.png");


    //Game Objects init
    std::cout << "Creating game objects..." << std::endl;

    //Background init
    this->bg = std::unique_ptr<Background>(new Background{this->bgTexture, this->screen_w, this->screen_h});

    //Player init
    this->initPlayer();

    //Life counter sprites init
    this->initLifeIndicators();

    //Sound init
    std::cout << "Loading sounds..." << std::endl;
    this->initSound();


    //Window init
    std::cout << "Opening window..." << std::endl;

    //Calculating coordinates for a centered window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPos;
    windowPos.x = (desktop.width / 2) - (this->screen_w / 2);
    windowPos.y = (desktop.height / 2) - (this->screen_h / 2);

    //Creating it
    sf::VideoMode videomode{this->screen_w, this->screen_h};
    this->window.create(videomode, "Bullet Hell", sf::Style::Titlebar | sf::Style::Close);

    //Centering it
    this->window.setPosition(windowPos);

    //fps limit
    if(vsync){
        this->window.setVerticalSyncEnabled(true);
        std::cout << "Vsync enabled." << std::endl;
    }
    else{
        this->window.setFramerateLimit(144);
        std::cout << "Framerate Limit: 144." << std::endl;
    }

    //Disabling repeated key events
    this->window.setKeyRepeatEnabled(false);

    //Starting music
    this->music.play();

    std::cout << "Game ready." << std::endl;

    //Starting clocks
    this->movementClock.restart();
    this->playTimeClock.restart();

}



//Handling events
void Game::handleInput(){
    sf::Event event;

    //Get all pending events
    while(this->window.pollEvent(event)){
        
        //check the type of the event
        switch(event.type){
            //window closed
            case sf::Event::Closed:
            window.close();
            this->running = false;
            break;

            //key pressed
            case sf::Event::KeyPressed:
            switch(event.key.code){

                //escape key || q key - Close game
                case sf::Keyboard::Escape:
                case sf::Keyboard::Q:
                window.close();
                this->running = false;
                break;

                //R key - Restart if dead
                case sf::Keyboard::R:
                if(this->player->dead)
                    this->restart();
                break;


                //When Shift is pressed, slow player down by 50%
                case sf::Keyboard::LShift:
                case sf::Keyboard::RShift:
                this->playerSpeed /= 1.5;
                break;

                //Ship change 1
                case sf::Keyboard::Num1:
                case sf::Keyboard::Num8:
                this->player->switchShipType(ShipTypes::eagle, this->blueEagleTextures);
                break;

                //Ship change 2
                case sf::Keyboard::Num2:
                case sf::Keyboard::Num9:
                this->player->switchShipType(ShipTypes::mosquito, this->blueMosquitoTextures);
                break;

                //Ship change 3
                case sf::Keyboard::Num3:
                case sf::Keyboard::Num0:
                this->player->switchShipType(ShipTypes::dragon, this->blueDragonTextures);
                break;

                //Fire
                case sf::Keyboard::Space:
                this->shoot = true;
                break;

                //Fire toggle
                case sf::Keyboard::G:
                this->shootToogle = !this->shootToogle;
                break;

                //Start Movement
                //Move Up
                case sf::Keyboard::W:
                case sf::Keyboard::I:
                case sf::Keyboard::Up:
                this->moveUp = true;
                break;

                //Move Down
                case sf::Keyboard::S:
                case sf::Keyboard::K:
                case sf::Keyboard::Down:
                this->moveDown = true;
                break;

                //Move Left
                case sf::Keyboard::A:
                case sf::Keyboard::J:
                case sf::Keyboard::Left:
                this->moveLeft = true;
                break;

                //Move Right
                case sf::Keyboard::D:
                case sf::Keyboard::L:
                case sf::Keyboard::Right:
                this->moveRight = true;
                break;

                default:
                break;
            }   //end key code switch
            break;  //end key pressed case

            //Key released
            case sf::Event::KeyReleased:
            switch(event.key.code){
                //Restore player speed
                case sf::Keyboard::LShift:
                case sf::Keyboard::RShift:
                    this->playerSpeed *= 1.5;
                break;

                //Stop fire
                case sf::Keyboard::Space:
                this->shoot = false;
                break;


                //Stop Movement
                //Move Up
                case sf::Keyboard::W:
                case sf::Keyboard::I:
                case sf::Keyboard::Up:
                this->moveUp = false;
                break;

                //Move Down
                case sf::Keyboard::S:
                case sf::Keyboard::K:
                case sf::Keyboard::Down:
                this->moveDown = false;
                break;

                //Move Left
                case sf::Keyboard::A:
                case sf::Keyboard::J:
                case sf::Keyboard::Left:
                this->moveLeft = false;
                break;

                //Move Right
                case sf::Keyboard::D:
                case sf::Keyboard::L:
                case sf::Keyboard::Right:
                this->moveRight = false;
                break;

                default:
                break;
            }   //end key released switch
            break;

            default:
            break;
        }   //end event type switch

    }  //end while pending events
}   //end handleInput



//Moving game objects
void Game::doMovement(){
    //We will multiply the speed by the time elapsed since our last movement.
    //This way, the speed of the game will be constant no matter the refresh rate.
    //Ex: if game runs at 120fps, a loop will take half as much time as it would with 60fps
    //    So we halve the speed of the objects
    this->time = this->movementClock.restart().asMilliseconds();

    //Background movement
    this->bg->moveDown(this->bgSpeed * this->time);

    //Player movement based on input
    this->playerMovement();

    //Enemy AI movement
    for(Player_Ship &enemy : this->enemies){
        float speed;
        ShipTypes enemyType = enemy.getShipType();

        switch(enemyType){
            case ShipTypes::mosquito:
            default:
            speed = this->enemyMosquitoSpeed;
            break;

            case ShipTypes::eagle:
            speed = this->enemyEagleSpeed;
            break;

            case ShipTypes::dragon:
            speed = this->enemyDragonSpeed;
            break;
        }
        enemy.AI_MoveWithinBounds(this->screen_w, speed * this->time);
    }

    //Moving player bullets up
    for(sf::Sprite &bullet : this->playerBullets)
        bullet.move(0, 0 - this->playerBulletSpeed * this->time);

    //Moving enemy bullets down
    for(sf::Sprite &bullet : this->enemyBullets)
        bullet.move(0, this->enemyBulletSpeed * this->time);
}


//Shooting and damage
void Game::doActions(){

    //If player is alive, enable player and enemy shooting
    if(player->dead == false){
        //Player shooting
        if(this->shoot || this->shootToogle){
            std::vector<sf::Sprite> shots = this->player->shoot();

            if(shots.size()){   //if bullets are shot
                for(sf::Sprite &bullet : shots)
                    this->playerBullets.push_back(bullet);

                this->playerShotSound.play();
            }
        }

        //Enemy shooting
        int div = 100;
        if(this->enemyChanceNotToShoot * this->time > 0)
            div = this->enemyChanceNotToShoot * this->time;
        
        for(Player_Ship &enemy : this->enemies){
            //1% chance of shooting each frame if game is 60hz. 0.5% if 120hz etc.
            if(rand() % div == 0){
                //At least 500ms will pass before next bullet is shot
                std::vector<sf::Sprite> shots = enemy.shoot();

                if(shots.size()){   //If bullets are shot
                    for(sf::Sprite bullet : shots)
                        this->enemyBullets.push_back(bullet);

                    //Play enemy shooting sound
                    this->enemyShotSound.play();
                }
            }
        }
    }


    //Bullet contact
    //Player bullets - enemy ships
    //For each bullet
    for(auto i = this->playerBullets.begin(); i != this->playerBullets.end(); i++){
        //For each enemy
        for(Player_Ship &enemy : this->enemies){
            //If enemy is hit by bullet, decrease health and remove bullet
            if(enemy.isHitBy(*i)){
                enemy.health -= this->player->damage;
                enemy.flash(sf::Color{255, 255, 255, 127}, 20);   //turn the ship half transparent for 20ms

                //get a valid iterator to the next element
                //if we don't it might still work but it's undefined behavior
                i = this->playerBullets.erase(i);
                i--;    //This is so we don't skip a bullet
                break;
            }
        }
    }

    //Enemy bullets - player ship
    if(this->player->dead == false){
        for(auto i = this->enemyBullets.begin(); i != this->enemyBullets.end(); i++){

            //First check if the rectangles intersect, then check if bullet hits one of the hitboxes
            if(player->isHitBy(*i)){
                this->player->health--;
                this->player->flash(sf::Color::Red, 35);    //flash player red for 30ms
                i = this->enemyBullets.erase(i);
                this->lives.pop_back();
                i--;
            }
        }
    }


    //If current wave has been destroyed, increase enemy count and spawn a new wave
    if(this->enemies.size() == 0){
        this->enemyCount++;
        this->spawnEnemies();
    }
}



//Method to remove out of screen bullets and destroying dead ships, 
//placing an explosion effects in their place.
void Game::destroyObjects(){
    //Removing out of screen player bullets
    for(auto i = this->playerBullets.begin(); i != this->playerBullets.end(); i++){
        if(this->outOfScreen(i->getGlobalBounds(), this->screen_w, this->screen_h)){
            i = this->playerBullets.erase(i);
            i--;
        }
    }

    //Removing out of screen enemy bullets
    for(auto i = this->enemyBullets.begin(); i != this->enemyBullets.end(); i++){
        if(this->outOfScreen(i->getGlobalBounds(), this->screen_w, this->screen_h)){
            i = this->enemyBullets.erase(i);
            i--;
        }
    }


    //Destroying dead enemy ships
    for(auto i = this->enemies.begin(); i != this->enemies.end(); i++){
        if(i->health <= 0){
            //setting explosion effect
            sf::Vector2f enemyPos = i->getPos();

            enemyPos.x -= 20 * (this->screen_w / 1024);
            this->explosions.push_back(Effect{this->redExplosionTextures});
            this->explosions.back().setPos(enemyPos.x, enemyPos.y);
            this->explosions.back().setMsBetweenFrames(20);
            this->explosions.back().play();

            //removing ship object from vector
            i = this->enemies.erase(i);

            //playing explosion audio
            this->shipExplosionSound.play();
            i--;

            //incrementing player score
            this->score++;
        }
    }


    //Exploding player ship if health <= 0
    //This will disable player input and enemy shooting, and update score text + draw it
    if(this->player->health <= 0 && this->player->dead == false){
        sf::Vector2f playerPos = this->player->getPos();
        this->player->dead = true;

        //placing explosion effect
        playerPos.x -= 20 * (this->screen_w / 1024);
        this->explosions.push_back(Effect{this->blueExplosionTextures});
        this->explosions.back().setPos(playerPos.x, playerPos.y);
        this->explosions.back().setMsBetweenFrames(1000 / 60);
        this->explosions.back().play();

        //playing explosion audio
        this->shipExplosionSound.play();

        //Update score text and highscore
        this->updateScoreText();
    }
}



void Game::render(){
    //Clear the window
    this->window.clear();

    //Draw background
    this->bg->draw(this->window);

    //Draw player bullets
    for(sf::Sprite bullet : this->playerBullets)
        this->window.draw(bullet);

    //Draw enemy bullets
    for(sf::Sprite bullet : this->enemyBullets)
        this->window.draw(bullet);

    //Draw player if alive
    if(this->player->dead == false)
        this->player->drawAnimation(this->window);

    //Draw enemies
    for(Player_Ship &enemy : this->enemies)
        enemy.drawAnimation(this->window);

    //Draw explosion effects
    for(Effect &explosion : this->explosions)
        explosion.drawNext(this->window);

    //Draw lives left
    for(sf::Sprite life : this->lives)
        this->window.draw(life);

    //If player is dead, draw text on top of everything else
    if(this->player->dead){
        window.draw(composerName);
        this->window.draw(this->restartText);
        this->window.draw(this->scoreText);
        this->window.draw(this->timeText);
        this->window.draw(this->highScoreText);
        this->window.draw(this->authorName);
        this->window.draw(this->authorSurname);
        this->window.draw(this->difficultyText);
    }

    //Display everything we've drawn
    this->window.display();
}



//*****************
//*PRIVATE METHODS*
//*****************


bool Game::loadHighScores(){
    int buf;
    std::ifstream scoresFile{"highscore.bin", std::ofstream::in | std::ofstream::binary};

    //Return if file couldn't be opened
    if(!scoresFile){
        std::cout << "Couldn't open high score file." << std::endl;
        return false;
    }

    //Try loading each score from the file
    for(auto i = this->highScores.begin(); i != this->highScores.end(); i++){
        scoresFile.read(reinterpret_cast<char*>(&buf), sizeof(buf));

        if(scoresFile.good())
            *i = buf;

        //Return if error
        else{
            std::cout << "Failed to read high scores from file." << std::endl;
            return false;
        }
    }

    return true;
}


void Game::setDifficulty(Difficulty::Level diff){
    this->difficulty = diff;
    std::cout << "Difficulty set to ";

    switch(difficulty){
        case Difficulty::Level::easy:
        this->enemyChanceNotToShoot *= 2;
        std::cout << "Easy.";
        break;

        case Difficulty::Level::normal:
        std::cout << "Normal.";
        break;

        case Difficulty::Level::hard:
        this->enemyChanceNotToShoot /= 2;
        std::cout << "Hard.";
        break;
    }

    std::cout << std::endl;
}

void Game::setRes(Resolution::Setting res){
    //Setting resolution
    Resolution::setIntFromResolution(res, this->screen_h, this->screen_w);

    //Scaling objects and their speed based on screen resolution
    float factor = this->screen_w / 800.0;

    this->playerSpeed *= factor;
    this->enemyMosquitoSpeed *= factor;
    this->enemyEagleSpeed *= factor;
    this->enemyDragonSpeed *= factor;
    this->playerBulletSpeed *= factor;
    this->enemyBulletSpeed *= factor;
    this->lifeScale *= factor;
    this->textScale *= factor;
}


void Game::initSound(){
    //Music
    this->music.openFromFile("../assets/audio/8-Bit-Mayhem.ogg");
    this->music.setVolume(50);
    this->music.setLoop(true);

    //Player laser shot sound
    this->playerShotSoundBuf.loadFromFile("../assets/audio/laser_shot1.wav");
    this->playerShotSound.setBuffer(this->playerShotSoundBuf);
    this->playerShotSound.setVolume(10);

    //Enemy laser shot sound
    this->enemyShotSoundBuf.loadFromFile("../assets/audio/laser_shot2.wav");
    this->enemyShotSound.setBuffer(this->enemyShotSoundBuf);
    this->enemyShotSound.setVolume(15);

    //Ship explosion sound
    this->shipExplosionSoundBuf.loadFromFile("../assets/audio/explosion1.wav");
    this->shipExplosionSound.setBuffer(this->shipExplosionSoundBuf);
    this->shipExplosionSound.setVolume(20);
}


void Game::initPlayer(){
    //Constructor with ship and bullet textures
    this->player = std::unique_ptr<Player_Ship>
    (new Player_Ship(ShipTypes::eagle, (float)this->screen_w / 800,this->blueEagleTextures, this->blueBulletTexture));

    //Setting position
    sf::FloatRect playerRect = this->player->getRect();
    this->player->setPos((this->screen_w / 2) - (playerRect.width / 2), this->screen_h - playerRect.height);

    //Setting health
    this->player->health = this->maxPlayerHealth;
}


void Game::saveNewHighscore(){
    //Set the high score for current difficulty to current score
    this->highScores[static_cast<int>(this->difficulty)] = this->score;

    //Update the high scores file
    std::ofstream scoreOutput{"highscore.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc};
    for(int score : this->highScores){
        scoreOutput.write(reinterpret_cast<const char*>(&score), sizeof(score));
    }
}



void Game::updateScoreText(){
    int highScore = this->highScores[static_cast<int>(this->difficulty)];

    //Set playtime text
    sf::Time playTime = this->playTimeClock.getElapsedTime();
    std::string timeStr = "TIME: " + Helpers::minutesAndSeconds(playTime);
    this->timeText.setString(timeStr);

    //Setting score text
    std::ostringstream text;
    text << "SCORE: " << this->score;
    this->scoreText.setString(text.str());

    //Setting high score text
    std::ostringstream highText;
    if(highScore < this->score){
        highText << "NEW HIGH SCORE!";
        this->saveNewHighscore();
    }
    else highText << "HIGH SCORE: " << highScore;
    this->highScoreText.setString(highText.str());


    //Centering score text
    sf::FloatRect textRect = this->scoreText.getGlobalBounds();
    int x = (this->screen_w / 2) - (textRect.width / 2);
    int y = (this->screen_h / 2) - (textRect.height / 2);
    this->scoreText.setPosition(x, y);

    //Centering playtime text just below score text
    sf::FloatRect timeRect = this->timeText.getGlobalBounds();
    x = (this->screen_w / 2) - (timeRect.width / 2);
    y += textRect.height * 1.3; //* 1.3 is so the time text isn't too close to the text above
    this->timeText.setPosition(x, y);

    //Placing high score text x = centered, y = (maxY - maxY / 4)
    sf::FloatRect highScoreRect = this->highScoreText.getGlobalBounds();
    x = (this->screen_w / 2) - (highScoreRect.width / 2);
    y = this->screen_h - this->screen_h / 3;
    this->highScoreText.setPosition(x, y);

    //Placing difficulty text just below high score text
    sf::FloatRect difficultyRect = this->difficultyText.getGlobalBounds();
    x = (this->screen_w / 2) - (difficultyRect.width / 2);
    y += highScoreRect.height * 1.3;
    this->difficultyText.setPosition(x, y);
}


void Game::initLifeIndicators(){
    //Add as many life indicators as the player's starting health
    for(int i = 0; i < this->maxPlayerHealth; i++){
        this->lives.push_back(sf::Sprite{});
        this->lives.back().setTexture(this->playerLife);
        this->lives.back().setScale(this->lifeScale, this->lifeScale);

        int x = this->lives.back().getGlobalBounds().width * i;
        int y = this->screen_h - this->lives.back().getGlobalBounds().height;
        this->lives.back().setPosition(x, y);
    }
}


void Game::restart(){
    //Resetting Player
    sf::FloatRect playerRect = this->player->getRect();
    this->player->dead = false;
    this->player->health = this->maxPlayerHealth;
    this->player->setPos((this->screen_w / 2) - (playerRect.width / 2), this->screen_h - playerRect.height);

    //Resetting Life sprites
    this->initLifeIndicators();

    //Clearing all game object vectors
    this->enemies.clear();
    this->playerBullets.clear();
    this->enemyBullets.clear();

    //Resetting enemy count, which will spawn first wave
    this->enemyCount = 0;

    //Resetting score
    this->score = 0;

    //Resetting playtime clock
    this->playTimeClock.restart();
}


void Game::initText(){
    //Loading Font
    this->font.loadFromFile("../assets/font/SourceSansPro-Regular.ttf");

    //Init Score Text
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize((int)(32 * this->textScale));
    this->scoreText.setFillColor(sf::Color::Red);
    this->scoreText.setStyle(sf::Text::Bold);

    //Init Highscore Text
    this->highScoreText.setFont(this->font);
    this->highScoreText.setCharacterSize((int)(12 * this->textScale));
    this->highScoreText.setFillColor(sf::Color::Red);
    this->highScoreText.setStyle(sf::Text::Bold);

    //Init Time Text
    this->timeText.setFont(this->font);
    this->timeText.setCharacterSize((int)(12 * this->textScale));
    this->timeText.setFillColor(sf::Color::Red);
    this->timeText.setStyle(sf::Text::Bold);

    //Init Restart Text
    this->restartText.setString("PRESS R TO RESTART!");
    this->restartText.setFont(this->font);
    this->restartText.setCharacterSize((int)(16 * this->textScale));
    this->restartText.setFillColor(sf::Color::Red);
    this->restartText.setStyle(sf::Text::Bold);

    //Init Difficulty Text
    this->difficultyText.setString("DIFFICULTY: " + Helpers::allUpperCase(Difficulty::difficultyToStr(this->difficulty)));
    this->difficultyText.setFont(this->font);
    this->difficultyText.setCharacterSize((int)(12 * this->textScale));
    this->difficultyText.setFillColor(sf::Color::Red);
    this->difficultyText.setStyle(sf::Text::Bold);

    //Init Name and Surname Text
    this->authorName.setString("DANIELE");
    this->authorSurname.setString("PUSCEDDU");
    this->authorName.setFont(this->font);
    this->authorSurname.setFont(this->font);
    this->authorName.setCharacterSize((int)(10 * this->textScale));
    this->authorSurname.setCharacterSize((int)(10 * this->textScale));
    this->authorName.setFillColor(sf::Color::Red);
    this->authorSurname.setFillColor(sf::Color::Red);
    this->authorName.setStyle(sf::Text::Bold);
    this->authorSurname.setStyle(sf::Text::Bold);

    //Init Composer Text
    composerName.setString("MUSIC BY ERIC MATYAS - www.soundimage.org");
    composerName.setFont(font);
    composerName.setCharacterSize((int)(8 * textScale));
    composerName.setFillColor(sf::Color::Red);
    composerName.setPosition(0, 0);

    //Centering X of Restart Text and placing it under composer credits
    sf::FloatRect textRect = this->restartText.getGlobalBounds();
    int x = (this->screen_w / 2) - (textRect.width / 2);
    this->restartText.setPosition(x, composerName.getGlobalBounds().height * 1.2f);

    //Setting position of name text
    textRect = this->authorName.getGlobalBounds();
    this->authorName.setPosition(10, this->screen_h - textRect.height - 10);

    //Setting position of surname text
    textRect = this->authorSurname.getGlobalBounds();
    this->authorSurname.setPosition(this->screen_w - textRect.width - 10, this->screen_h - textRect.height - 10);
}


void Game::spawnEnemies(){
    // Spawn as many enemies as enemyCount
    for(int i = 0; i < this->enemyCount; i++){
        int randNum = rand() % 100;

        //70% chance for the enemy to be a mosquito
        if(randNum < 70){
            this->enemies.push_back(
                Player_Ship{ShipTypes::mosquito, (float)this->screen_w / 800, this->redMosquitoTextures, this->redBulletTexture}
            );
            this->enemies.back().health = 15;
        }

        //20% chance for the enemy to be an eagle
        else if(randNum < 90){
            this->enemies.push_back(
                Player_Ship{ShipTypes::eagle, (float)this->screen_w / 800, this->redEagleTextures, this->redBulletTexture}
            );
            this->enemies.back().health = 20;
        }

        //10% chance for the enemy to be a dragon
        else{
            this->enemies.push_back(
                Player_Ship{ShipTypes::dragon, (float)this->screen_w / 800, this->redDragonTextures, this->redBulletTexture}
            );
            this->enemies.back().health = 30;
        }

        //Set position
        int y = (rand() % 2) * this->enemies.back().getRect().height;
        int x = rand() % (int)(this->screen_w - this->enemies.back().getRect().width);
        this->enemies.back().setPos(x, y);

        //Flip Vertically so enemy faces the player
        this->enemies.back().flipVertically();

        //Setting shooting cooldown, overriding the ship type's cooldown
        this->enemies.back().setMsBetweenShots(500);
    }
}


//Function to check if a game object rectangle is outside the game window
bool Game::outOfScreen(sf::FloatRect rect, int w, int h){
    bool out = false;

    if(rect.left + rect.width < 0 || rect.left > w)
        out = true;

    else if(rect.top + rect.height < 0 || rect.top > h)
        out = true;

    return out;
}


void Game::playerMovement(){
    //Move left if key is pressed
    if(this->moveLeft)
        this->player->moveLeft(playerSpeed * this->time, 0);

    //Move right if key is pressed
    if(this->moveRight)
        this->player->moveRight(playerSpeed * this->time, this->screen_w);

    //Move up if key is pressed
    if(this->moveUp)
        this->player->moveUp(playerSpeed * this->time, 0);

    //Move down if key is pressed
    if(this->moveDown)
        this->player->moveDown(playerSpeed * this->time, this->screen_h);
}
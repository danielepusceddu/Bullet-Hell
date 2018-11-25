#include "Game.hpp"

//*******************
//*GAME LOOP METHODS*
//*******************

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    playTimeClock.restart();
    while(running){
        handleInput();

        timeSinceLastUpdate += clock.getElapsedTime();
        clock.restart();

        while(timeSinceLastUpdate >= timePerFrame){
            doMovement();
            doActions();
            destroyObjects();

            timeSinceLastUpdate -= timePerFrame;
        }

        render();
    }
}


//Moving game objects
void Game::doMovement(){
    //We will multiply the speed by the time elapsed since our last movement.
    //This way, the speed of the game will be constant no matter the refresh rate.
    //Ex: if game runs at 120fps, a loop will take half as much time as it would with 60fps
    //    So we halve the speed of the objects

    //Background movement
    bg->moveDown(bgSpeed * delta);

    //Player movement based on input
    playerMovement();

    //Enemy AI movement
    for(AI_Ship& enemy : enemies)
        enemy.update(timePerFrame.asSeconds());

    //Moving player bullets up
    for(sf::Sprite &bullet : playerBullets)
        bullet.move(0, 0 - playerBulletSpeed * delta);
    

    //Moving enemy bullets down
    for(sf::Sprite &bullet : enemyBullets)
        bullet.move(0, enemyBulletSpeed * delta);

    //Updating explosions
    for(Effect& explosion : explosions)
        explosion.update(timePerFrame.asSeconds());
}



//Shooting and damage
void Game::doActions(){

    //If player is alive, enable player and enemy shooting
    if(player->isDead() == false){
        //Player shooting
        if(shoot || shootToogle){
            std::vector<sf::Sprite> shots = player->shoot();

            if(shots.size())  //if bullets are shot
                for(sf::Sprite &bullet : shots)
                    playerBullets.push_back(bullet);
            
        }
    }

    //Enemy bullets - player ship
    if(player->isDead() == false){
        for(auto i = enemyBullets.begin(); i != enemyBullets.end(); i++){

            //First check if the rectangles intersect, then check if bullet hits one of the hitboxes
            if(player->isHitBy(*i)){
                player->damage(1);
                player->flash(sf::Color::Red, 35);    //flash player red for 30ms
                i = enemyBullets.erase(i);
                lives.pop_back();
                i--;
            }
        }
    }

    //Player Bullets - Enemy Ships
    for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++){
        for(auto i = playerBullets.begin(); i != playerBullets.end(); i++){
            if(enemy->isHitBy(*i)){
                enemy->damage(1);
                i = playerBullets.erase(i);
                i--;
            }
        }
    }


    bus.notifyListeners();


    for(auto enemy = enemies.begin(); enemy != enemies.end(); enemy++){
        if(enemy->isDead()){
            enemy = enemies.erase(enemy);
            enemy--;
        }
    }


    //If current wave has been destroyed, increase enemy count and spawn a new wave
    if(enemies.size() == 0){
        enemyCount++;
        spawnEnemies();
    }
}



//Method to remove out of screen bullets and destroying dead ships, 
//placing an explosion effects in their place.
void Game::destroyObjects(){
    //Removing out of screen player bullets
    for(auto i = playerBullets.begin(); i != playerBullets.end(); i++){
        if(outOfScreen(i->getGlobalBounds(), screen_w, screen_h)){
            i = playerBullets.erase(i);
            i--;
        }
    }

    //Removing out of screen enemy bullets
    for(auto i = enemyBullets.begin(); i != enemyBullets.end(); i++){
        if(outOfScreen(i->getGlobalBounds(), screen_w, screen_h)){
            i = enemyBullets.erase(i);
            i--;
        }
    }

    //Removing finished explosions
    for(auto i = explosions.begin(); i != explosions.end(); i++)
        if(i->isFinished()){
            i = explosions.erase(i);
            i--;
        }


    //Exploding player ship if health <= 0
    //This will disable player input and enemy shooting, and update score text + draw it
    if(player->isDead() && player->isInvisible() == false){
        player->toggleInvisibility();

        //Update score text and highscore
        updateScoreText();
    }
}



void Game::render(){
    //Clear the window
    window.clear();

    //Draw background
    bg->draw(window);

    //Draw player bullets
    for(sf::Sprite bullet : playerBullets)
        window.draw(bullet);

    //Draw enemy bullets
    for(sf::Sprite bullet : enemyBullets)
        window.draw(bullet);

    //Draw player if alive
    if(player->isDead() == false)
        player->drawAnimation(window);

    //Draw enemies
    for(AI_Ship &enemy : enemies)
        enemy.draw(window);

    //Draw explosion effects
    for(Effect &explosion : explosions)
        explosion.draw(window);

    //Draw lives left
    for(sf::Sprite life : lives)
        window.draw(life);

    //If player is dead, draw text on top of everything else
    if(player->isDead()){
        window.draw(composerName);
        window.draw(restartText);
        window.draw(scoreText);
        window.draw(timeText);
        window.draw(highScoreText);
        window.draw(authorName);
        window.draw(authorSurname);
        window.draw(difficultyText);
    }

    //Display everything we've drawn
    window.display();
}



//Handling events
void Game::handleInput(){
    sf::Event event;

    //Get all pending events
    while(window.pollEvent(event)){
        
        //check the type of the event
        switch(event.type){
            //window closed
            case sf::Event::Closed:
            window.close();
            running = false;
            break;

            //key pressed
            case sf::Event::KeyPressed:
            switch(event.key.code){

                //escape key || q key - Close game
                case sf::Keyboard::Escape:
                case sf::Keyboard::Q:
                window.close();
                running = false;
                break;

                //R key - Restart if dead
                case sf::Keyboard::R:
                if(player->isDead())
                    restart();
                break;


                //When Shift is pressed, slow player down by 50%
                case sf::Keyboard::LShift:
                case sf::Keyboard::RShift:
                playerSpeed /= 1.5;
                break;

                //Ship change 1
                case sf::Keyboard::Num1:
                case sf::Keyboard::Num8:
                player->switchShipType(ShipTypes::eagle, blueEagleTextures);
                break;

                //Ship change 2
                case sf::Keyboard::Num2:
                case sf::Keyboard::Num9:
                player->switchShipType(ShipTypes::mosquito, blueMosquitoTextures);
                break;

                //Ship change 3
                case sf::Keyboard::Num3:
                case sf::Keyboard::Num0:
                player->switchShipType(ShipTypes::dragon, blueDragonTextures);
                break;

                //Fire
                case sf::Keyboard::Space:
                shoot = true;
                break;

                //Fire toggle
                case sf::Keyboard::G:
                shootToogle = !shootToogle;
                break;

                //Start Movement
                //Move Up
                case sf::Keyboard::W:
                case sf::Keyboard::I:
                case sf::Keyboard::Up:
                moveUp = true;
                break;

                //Move Down
                case sf::Keyboard::S:
                case sf::Keyboard::K:
                case sf::Keyboard::Down:
                moveDown = true;
                break;

                //Move Left
                case sf::Keyboard::A:
                case sf::Keyboard::J:
                case sf::Keyboard::Left:
                moveLeft = true;
                break;

                //Move Right
                case sf::Keyboard::D:
                case sf::Keyboard::L:
                case sf::Keyboard::Right:
                moveRight = true;
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
                    playerSpeed *= 1.5;
                break;

                //Stop fire
                case sf::Keyboard::Space:
                shoot = false;
                break;


                //Stop Movement
                //Move Up
                case sf::Keyboard::W:
                case sf::Keyboard::I:
                case sf::Keyboard::Up:
                moveUp = false;
                break;

                //Move Down
                case sf::Keyboard::S:
                case sf::Keyboard::K:
                case sf::Keyboard::Down:
                moveDown = false;
                break;

                //Move Left
                case sf::Keyboard::A:
                case sf::Keyboard::J:
                case sf::Keyboard::Left:
                moveLeft = false;
                break;

                //Move Right
                case sf::Keyboard::D:
                case sf::Keyboard::L:
                case sf::Keyboard::Right:
                moveRight = false;
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


/////////////
//CONSTRUCTOR
/////////////
Game::Game(Resolution::Setting res, Difficulty::Level dfculty, bool vsync):
audioManager{bus}, spawner{bus, enemyBullets, explosions}
{

    //Rand seed init
    srand(std::time(NULL));

    //Setting resolution
    setRes(res);

    //Loading High Scores
    if(loadHighScores() == false)
        highScores.fill(0);

    //Setting difficulty
    setDifficulty(dfculty);

    //Text init
    initText();

    //Textures init
    std::cout << "Loading textures..." << std::endl;

    //background texture
    bgTexture.loadFromFile("../assets/textures/background.jpg");

    //bullet textures
    blueBulletTexture.loadFromFile("../assets/textures/blue/bullet.bmp");
    redBulletTexture.loadFromFile("../assets/textures/red/bullet.bmp");

    //blue eagle textures
    Helpers::loadTextures(blueEagleTextures, "../assets/textures/blue/eagle_$d.png");

    //blue mosquito textures
    Helpers::loadTextures(blueMosquitoTextures, "../assets/textures/blue/mosquito_$d.png");

    //blue dragon textures
    Helpers::loadTextures(blueDragonTextures, "../assets/textures/blue/dragon_$d.png");

    //player life texture
    playerLife.loadFromFile("../assets/textures/blue/mothership.png");

    //Game Objects init
    std::cout << "Creating game objects..." << std::endl;

    //Background init
    bg = std::unique_ptr<Background>(new Background{bgTexture, screen_w, screen_h});

    //Player init
    initPlayer();

    //Life counter sprites init
    initLifeIndicators();

    //Window init
    std::cout << "Opening window..." << std::endl;

    //Calculating coordinates for a centered window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPos;
    windowPos.x = (desktop.width / 2) - (screen_w / 2);
    windowPos.y = (desktop.height / 2) - (screen_h / 2);

    //Creating it
    sf::VideoMode videomode{screen_w, screen_h};
    window.create(videomode, "Bullet Hell", sf::Style::Titlebar | sf::Style::Close);

    //Centering it
    window.setPosition(windowPos);

    //fps limit
    if(vsync){
        window.setVerticalSyncEnabled(true);
        std::cout << "Vsync enabled." << std::endl;
    }
    else{
        window.setFramerateLimit(144);
        std::cout << "Framerate Limit: 144." << std::endl;
    }

    //Disabling repeated key events
    window.setKeyRepeatEnabled(false);

    //Starting music
    audioManager.startMusic();

    std::cout << "Game ready." << std::endl;
}



//***********************
//*OTHER PRIVATE METHODS*
//***********************


bool Game::loadHighScores(){
    int buf;
    std::ifstream scoresFile{"highscore.bin", std::ofstream::in | std::ofstream::binary};

    //Return if file couldn't be opened
    if(!scoresFile){
        std::cout << "Couldn't open high score file." << std::endl;
        return false;
    }

    //Try loading each score from the file
    for(auto i = highScores.begin(); i != highScores.end(); i++){
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
    difficulty = diff;
    std::cout << "Difficulty set to ";

    switch(difficulty){
        case Difficulty::Level::easy:
        enemyChanceNotToShoot *= 2;
        std::cout << "Easy.";
        break;

        case Difficulty::Level::normal:
        std::cout << "Normal.";
        break;

        case Difficulty::Level::hard:
        enemyChanceNotToShoot /= 2;
        std::cout << "Hard.";
        break;
    }

    std::cout << std::endl;
}

void Game::setRes(Resolution::Setting res){
    //Setting resolution
    Resolution::setIntFromResolution(res, screen_h, screen_w);

    //Scaling objects and their speed based on screen resolution
    float factor = screen_w / 800.0;

    playerSpeed *= factor;
    playerBulletSpeed *= factor;
    enemyBulletSpeed *= factor;
    lifeScale *= factor;
    textScale *= factor;
}


void Game::initPlayer(){
    //Constructor with ship and bullet textures
    player = std::unique_ptr<Player_Ship>
    (new Player_Ship(bus, ShipTypes::eagle, Player_Ship::Team::blue, (float)screen_w / 800,blueEagleTextures, blueBulletTexture));

    //Setting position
    sf::FloatRect playerRect = player->getRect();
    player->setPos((screen_w / 2) - (playerRect.width / 2), screen_h - playerRect.height);

    //Setting health
    player->setHealth(maxPlayerHealth);
}


void Game::saveNewHighscore(){
    //Set the high score for current difficulty to current score
    highScores[static_cast<int>(difficulty)] = score;

    //Update the high scores file
    std::ofstream scoreOutput{"highscore.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc};
    for(int score : highScores){
        scoreOutput.write(reinterpret_cast<const char*>(&score), sizeof(score));
    }
}



void Game::updateScoreText(){
    int highScore = highScores[static_cast<int>(difficulty)];

    //Set playtime text
    sf::Time playTime = playTimeClock.getElapsedTime();
    std::string timeStr = "TIME: " + Helpers::minutesAndSeconds(playTime);
    timeText.setString(timeStr);

    //Setting score text
    std::ostringstream text;
    text << "SCORE: " << score;
    scoreText.setString(text.str());

    //Setting high score text
    std::ostringstream highText;
    if(highScore < score){
        highText << "NEW HIGH SCORE!";
        saveNewHighscore();
    }
    else highText << "HIGH SCORE: " << highScore;
    highScoreText.setString(highText.str());


    //Centering score text
    sf::FloatRect textRect = scoreText.getGlobalBounds();
    int x = (screen_w / 2) - (textRect.width / 2);
    int y = (screen_h / 2) - (textRect.height / 2);
    scoreText.setPosition(x, y);

    //Centering playtime text just below score text
    sf::FloatRect timeRect = timeText.getGlobalBounds();
    x = (screen_w / 2) - (timeRect.width / 2);
    y += textRect.height * 1.3; //* 1.3 is so the time text isn't too close to the text above
    timeText.setPosition(x, y);

    //Placing high score text x = centered, y = (maxY - maxY / 4)
    sf::FloatRect highScoreRect = highScoreText.getGlobalBounds();
    x = (screen_w / 2) - (highScoreRect.width / 2);
    y = screen_h - screen_h / 3;
    highScoreText.setPosition(x, y);

    //Placing difficulty text just below high score text
    sf::FloatRect difficultyRect = difficultyText.getGlobalBounds();
    x = (screen_w / 2) - (difficultyRect.width / 2);
    y += highScoreRect.height * 1.3;
    difficultyText.setPosition(x, y);
}


void Game::initLifeIndicators(){
    //Add as many life indicators as the player's starting health
    for(int i = 0; i < maxPlayerHealth; i++){
        lives.push_back(sf::Sprite{});
        lives.back().setTexture(playerLife);
        lives.back().setScale(lifeScale, lifeScale);

        int x = lives.back().getGlobalBounds().width * i;
        int y = screen_h - lives.back().getGlobalBounds().height;
        lives.back().setPosition(x, y);
    }
}


void Game::restart(){
    //Resetting Player
    sf::FloatRect playerRect = player->getRect();

    if(player->isInvisible())
        player->toggleInvisibility();

    player->setHealth(maxPlayerHealth);
    player->setPos((screen_w / 2) - (playerRect.width / 2), screen_h - playerRect.height);

    //Resetting Life sprites
    initLifeIndicators();

    //Clearing all game object vectors
    enemies.clear();
    playerBullets.clear();
    enemyBullets.clear();

    //Resetting enemy count, which will spawn first wave
    enemyCount = 0;

    //Resetting score
    score = 0;

    //Resetting playtime clock
    playTimeClock.restart();
}


void Game::initText(){
    //Loading Font
    font.loadFromFile("../assets/font/SourceSansPro-Regular.ttf");

    //Init Score Text
    scoreText.setFont(font);
    scoreText.setCharacterSize((int)(32 * textScale));
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setStyle(sf::Text::Bold);

    //Init Highscore Text
    highScoreText.setFont(font);
    highScoreText.setCharacterSize((int)(12 * textScale));
    highScoreText.setFillColor(sf::Color::Red);
    highScoreText.setStyle(sf::Text::Bold);

    //Init Time Text
    timeText.setFont(font);
    timeText.setCharacterSize((int)(12 * textScale));
    timeText.setFillColor(sf::Color::Red);
    timeText.setStyle(sf::Text::Bold);

    //Init Restart Text
    restartText.setString("PRESS R TO RESTART!");
    restartText.setFont(font);
    restartText.setCharacterSize((int)(16 * textScale));
    restartText.setFillColor(sf::Color::Red);
    restartText.setStyle(sf::Text::Bold);

    //Init Difficulty Text
    difficultyText.setString("DIFFICULTY: " + Helpers::allUpperCase(Difficulty::difficultyToStr(difficulty)));
    difficultyText.setFont(font);
    difficultyText.setCharacterSize((int)(12 * textScale));
    difficultyText.setFillColor(sf::Color::Red);
    difficultyText.setStyle(sf::Text::Bold);

    //Init Name and Surname Text
    authorName.setString("DANIELE");
    authorSurname.setString("PUSCEDDU");
    authorName.setFont(font);
    authorSurname.setFont(font);
    authorName.setCharacterSize((int)(10 * textScale));
    authorSurname.setCharacterSize((int)(10 * textScale));
    authorName.setFillColor(sf::Color::Red);
    authorSurname.setFillColor(sf::Color::Red);
    authorName.setStyle(sf::Text::Bold);
    authorSurname.setStyle(sf::Text::Bold);

    //Init Composer Text
    composerName.setString("MUSIC BY ERIC MATYAS - www.soundimage.org");
    composerName.setFont(font);
    composerName.setCharacterSize((int)(8 * textScale));
    composerName.setFillColor(sf::Color::Red);
    composerName.setPosition(0, 0);

    //Centering X of Restart Text and placing it under composer credits
    sf::FloatRect textRect = restartText.getGlobalBounds();
    int x = (screen_w / 2) - (textRect.width / 2);
    restartText.setPosition(x, composerName.getGlobalBounds().height * 1.2f);

    //Setting position of name text
    textRect = authorName.getGlobalBounds();
    authorName.setPosition(10, screen_h - textRect.height - 10);

    //Setting position of surname text
    textRect = authorSurname.getGlobalBounds();
    authorSurname.setPosition(screen_w - textRect.width - 10, screen_h - textRect.height - 10);
}


void Game::spawnEnemies(){
    sf::IntRect windowRect{0, 0, static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y)};

    // Spawn as many enemies as enemyCount
    for(int i = 0; i < enemyCount; i++)
        spawner.spawnAI(enemies, windowRect);
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
    if(moveLeft)
        player->moveLeft(playerSpeed * delta, 0);

    //Move right if key is pressed
    if(moveRight)
        player->moveRight(playerSpeed * delta, screen_w);

    //Move up if key is pressed
    if(moveUp)
        player->moveUp(playerSpeed * delta, 0);

    //Move down if key is pressed
    if(moveDown)
        player->moveDown(playerSpeed * delta, screen_h);
}
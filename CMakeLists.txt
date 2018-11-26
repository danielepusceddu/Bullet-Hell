cmake_minimum_required(VERSION 2.8.9)
project(BulletHell)

#C++11 Standard
set(CMAKE_CXX_STANDARD 11)

#Extended Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

#Sanitizer
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined,address -fno-omit-frame-pointer")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fsanitize=undefined,address -fno-omit-frame-pointer")


set(SOURCE_FILES src/bulletHell.cpp 
                 src/helperFunctions/helperFunctions.cpp
                 src/Background/Background.cpp 
                 src/Effect/Effect.cpp
                 src/Effect/Effect.cpp
                 src/Game/Game.cpp
                 src/Resolution/Resolution.cpp
                 src/Difficulty/Difficulty.cpp
                 src/Bus/Bus.cpp
                 src/Bus/BusListener.cpp
                 src/Bus/BusWriter.cpp
                 src/Bus/Message.cpp
                 src/AudioManager/AudioManager.cpp
                 src/Spawner/Spawner.cpp
                 src/Ship/Ship.cpp
                 src/Ship/AI_Ship.cpp
                 src/Ship/Player_Ship.cpp
                 src/InputComponent/InputComponent.cpp
                 src/Animation/Animation.cpp
                 src/Animation/SpriteSheet.cpp
                 src/GameObject/GameObject.cpp
                 src/AIComponent/AIComponent.cpp
                 extlibs/Collision/Collision.cpp)

add_executable(bulletHell ${SOURCE_FILES})
target_link_libraries(bulletHell -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio)
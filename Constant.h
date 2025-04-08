#pragma once
#include<iostream>
#include<SDL.h>
#include<string>

using namespace std;


#define WINDOW_WIDTH 420
#define WINDOW_HEIGHT 500



#define PLAYER_WIDTH 27
#define PLAYER_HEIGHT 30

#define PLATFORM_WIDTH 82
#define PLATFORM_HEIGHT 30

#define DISTANCE_BETWEEN_TWO_PLATFORM 80

#define NORMAL_PATH "res/gfx/svg/normal.png"
#define BREAKABLE_PATH "res/gfx/svg/breakable.png"
#define BOOSTED_PATH "res/gfx/svg/bouncey.png"
#define SPIKE_PATH "res/gfx/svg/spike.png"
#define PLAYER_PATH "res/gfx/svg/sprite1_right.png"

#define PADDLING 50

const float PLAYER_MOVE_SPEED = 350;
const float PLAYER_JUMP_FORCE = -750; 
const float GRAVITY = 1400; 
//const float GRAVITY = 0;


enum class GameState {
	mainMenu, mainGame, gameOver, quit
};	
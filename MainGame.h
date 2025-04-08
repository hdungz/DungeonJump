#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include <chrono>
#include <random>
#include <vector>
#include "Constant.h"
#include "Sprite.h"
#include "Platform.h"
#include "BreakablePlatform.h"
#include "BoostedPlatform.h"
#include<SDL_ttf.h>
#include <sstream>
#include <string>


const double SCROLL_THRESHOLD = 250;
const int NUM_COLUMN = 3;
const double GENERATION_BUFFER = WINDOW_HEIGHT * 2;
const double GENERATION_RANGE = WINDOW_HEIGHT * 1.0;
const int PLATFORMS_PER_RANGE = 15;
const int COLUMN_MARGIN = 15;
const double CLEANUP_BUFFER = 200; 


class MainGame {
public:
	SDL_Color textColor = { 76,85,108,255 };
	MainGame(SDL_Window* p_window, SDL_Renderer* p_renderer, TTF_Font* p_font);
	~MainGame();
	void update();
	void render();
	void run();
	void createPlatformsAndPlayer();
	void handleInput();
	void printScore(string& score);
	bool running = 0;
	GameState gameState;
private:
	void cameraLocking(Player* t_player);
	void FpsLimiter(int LastFrameTicks);
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	std::vector<Platform*> platforms;
	Platform* initialPlatform;
	Player* m_player;
	Sprite* backGround;
	const Uint8* m_keyboardState = nullptr;
	Uint32 m_lastTick = 0;
	double m_deltaTime = 0;
	double cameraY = 0;

};
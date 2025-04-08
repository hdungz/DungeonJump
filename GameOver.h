#pragma once 
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "Constant.h"

const Uint32 ANIMATION_DURATION = 500;

class GameOver {
public:
	GameOver(SDL_Window* t_window, SDL_Renderer* t_renderer, TTF_Font* t_font);
	~GameOver();
	void run();
	void render();
	void handleInput();
	void loadTex();
	GameState gameState = GameState::gameOver;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* backBoard;
	SDL_Texture* text;
	SDL_Texture* homeButton;
	SDL_Texture* restartButton;
	SDL_Texture* backGround;
	bool isRunning = 1;
	
};
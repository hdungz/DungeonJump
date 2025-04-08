#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Constant.h"

class MainMenu {
public:
	MainMenu(SDL_Window* t_window, SDL_Renderer* t_renderer);
	~MainMenu();
	void run();
	void render();
	void handleInput();
	void loadTex();
	GameState gameState = GameState::mainGame;
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Texture* titleTexture;
	SDL_Texture* buttonTexture;
	SDL_Texture* backGround;
};
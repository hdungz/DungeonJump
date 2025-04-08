#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<iostream>
using namespace std;

#include "Constant.h"
#include "MainGame.h"
#include "GameOver.h"
#include "MainMenu.h"

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
GameState gameState;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) cout << "init video failed: " << SDL_GetError() << endl;
	if (!IMG_Init(IMG_INIT_PNG)) cout << "init img failed: " << SDL_GetError() << endl;
	if (TTF_Init() < 0) cout << "init ttf failed: " << SDL_GetError() << endl;
	window = SDL_CreateWindow("Dungeon Jump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << "init window failed: " << SDL_GetError();
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cout << "init renderer failed: " << SDL_GetError() << endl;
	}
	font = TTF_OpenFont("res/PressStart2P.ttf", 50);

	gameState = GameState::mainMenu;
	bool running = 1;
	SDL_Event event;
	while(running) {
		
		switch (gameState) {
		case GameState::mainGame:
		{
			MainGame game(window, renderer, font);
			game.run();
			gameState = game.gameState;
		}
		break;
		case GameState::quit:
			running = 0;
			break;

		case GameState::gameOver:
		{
			GameOver gameOver(window, renderer, font);
			gameOver.run();
			gameState = gameOver.gameState;
		}
		break;
		case GameState::mainMenu:
		{
			MainMenu mainMenu(window, renderer);
			mainMenu.run();
			gameState = mainMenu.gameState;
		}
		break;
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	

	return 0;
}
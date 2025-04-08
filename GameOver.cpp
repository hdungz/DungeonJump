#include "GameOver.h"

GameOver::GameOver(SDL_Window* t_window, SDL_Renderer* t_renderer, TTF_Font* t_font) :
	window(t_window),
	renderer(t_renderer),
	font(t_font)
{
}

GameOver::~GameOver(){

}

void GameOver::run() {
	loadTex();
	render();
}

void GameOver::loadTex() {
	backGround = IMG_LoadTexture(renderer, "res/gfx/background.png");
	backBoard = IMG_LoadTexture(renderer, "res/gfx/svg/background.png");
	text = IMG_LoadTexture(renderer, "res/gfx/svg/text.png");
	homeButton = IMG_LoadTexture(renderer, "res/gfx/svg/titleScreenButton.png");
	restartButton = IMG_LoadTexture(renderer, "res/gfx/svg/restartButton.png");
	if (backGround == nullptr) cout << "init texture failed: " << SDL_GetError() << endl;
}

void GameOver::render() {
	

	double startW = 20;
	double startH = 1;
	double endW = WINDOW_WIDTH - 20;
	double endH = 250;

	double startW2 = 1;
	double startH2 = 1;
	double endW2 = WINDOW_WIDTH - 20;
	double endH2 = 100;

	int SPACE = 40;

	const int bottomMargin = 50;
	const int buttonSpacing = 60;

	int tex3W, tex3H, tex4W, tex4H;
	SDL_QueryTexture(homeButton, NULL, NULL, &tex3W, &tex3H);
	SDL_QueryTexture(restartButton, NULL, NULL, &tex4W, &tex4H);
	int maxButtonH = (tex3H > tex4H) ? tex3H : tex4H;
	int commonButtonY = WINDOW_HEIGHT - 100 - maxButtonH - bottomMargin; 
	int totalButtonWidth = tex3W + buttonSpacing + tex4W;
	int startButtonX = (WINDOW_WIDTH - totalButtonWidth) / 2; 
	int finalX3 = startButtonX;                              
	int finalW3 = tex3W;                                     
	int finalH3 = tex3H;                                    
	int finalX4 = startButtonX + tex3W + buttonSpacing;      
	int finalW4 = tex4W;                                    
	int finalH4 = tex4H;

	Uint32 startTime = SDL_GetTicks();
	SDL_Event event;
	while (isRunning) {
		SDL_RenderClear(renderer);

		SDL_Rect desRect = { 0, 0 , WINDOW_WIDTH, WINDOW_HEIGHT };
		SDL_RenderCopy(renderer, backGround, NULL, &desRect);

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				gameState = GameState::quit;
				isRunning = 0;
			}
		}
		Uint32 currTime = SDL_GetTicks();
		Uint32 eTime = currTime - startTime;
		double progress = eTime * 1.0 / ANIMATION_DURATION;
		if (progress > 1) {
			progress = 1;
		}

		double currW = startW + (endW - startW) * progress;
		double currH = startH + (endH - startH) * progress;
		double currX = (WINDOW_WIDTH - currW) / 2.0;
		double currY = (WINDOW_HEIGHT - currH) / 2.0;

		desRect = { int(currX), int(currY), (int)currW, (int)currH };

		double currX2 = (float)currX + SPACE * ((float)currW / WINDOW_WIDTH);
		double currY2 = (float)currY + SPACE * ((float)currH / WINDOW_HEIGHT);
		double currW2 = (float)currW * (WINDOW_WIDTH - 2.0f * SPACE) / WINDOW_WIDTH;
		double currH2 = (float)currH * (100.0 / WINDOW_HEIGHT);
		SDL_Rect desRect2 = {currX2, currY2, currW2, currH2};

		SDL_Rect desRect3;
		float startX_center = WINDOW_WIDTH / 2.0f;
		float startY_center = WINDOW_HEIGHT / 2.0f;
		float startW_small = 1.0f, startH_small = 1.0f;
		desRect3.x = (int)(startX_center + ((float)finalX3 - startX_center) * progress);
		desRect3.y = (int)(startY_center + ((float)commonButtonY - startY_center) * progress);
		desRect3.w = (int)(startW_small + ((float)finalW3 - startW_small) * progress);
		desRect3.h = (int)(startH_small + ((float)finalH3 - startH_small) * progress);

		SDL_Rect desRect4;
		desRect4.x = (int)(startX_center + ((float)finalX4 - startX_center) * progress);
		desRect4.y = (int)(startY_center + ((float)commonButtonY - startY_center) * progress); 
		desRect4.w = (int)(startW_small + ((float)finalW4 - startW_small) * progress);
		desRect4.h = (int)(startH_small + ((float)finalH4 - startH_small) * progress);

		SDL_RenderCopy(renderer, backBoard , NULL, &desRect);
		SDL_RenderCopy(renderer, text, NULL, &desRect2);
		SDL_RenderCopy(renderer, homeButton, NULL, &desRect3);
		SDL_RenderCopy(renderer, restartButton, NULL, &desRect4);

		cout << progress << endl;
		int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
		if (progress == 1 ) {
			SDL_Point mousePos = { mouseX, mouseY };
			cout << 1;
			if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if (SDL_PointInRect(&mousePos, &desRect3)) {
					gameState = GameState::mainMenu;
					isRunning = 0;
				}
				if (SDL_PointInRect(&mousePos, &desRect4)) {
					gameState = GameState::mainGame;
					isRunning = 0;
				}
			}
		}

		SDL_RenderPresent(renderer);
	
	}
}
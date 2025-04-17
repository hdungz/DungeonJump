#include "MainMenu.h"

MainMenu::MainMenu(SDL_Window* t_window, SDL_Renderer* t_renderer) :
	window(t_window),
	renderer(t_renderer)
{
	
}

MainMenu::~MainMenu() {
	
}

void MainMenu::run() {
	loadTex();
    render();
}

void MainMenu::render() {
    SDL_RenderClear(renderer);
   
    const int TOP_MARGIN = 50;      
    const int TITLE_BUTTON_GAP = 40;
    const float BOB_AMOUNT = 10.0f;  
    const float BOB_SPEED = 0.005f;  

    int titleW, titleH;
    int buttonW, buttonH;
    SDL_QueryTexture(titleTexture, NULL, NULL, &titleW, &titleH);
    SDL_QueryTexture(buttonTexture, NULL, NULL, &buttonW, &buttonH);
    
    titleW /= 1.5f;
    titleH /= 1.5f;

    int baseTitleX = (WINDOW_WIDTH - titleW) / 2;
    int baseTitleY = TOP_MARGIN; 

    int remainingSpaceTop = baseTitleY + titleH + TITLE_BUTTON_GAP;
    int remainingSpaceHeight = WINDOW_HEIGHT - remainingSpaceTop;
    int buttonY = remainingSpaceTop + (remainingSpaceHeight / 2) - (buttonH / 2);
    int buttonX = (WINDOW_WIDTH - buttonW) / 2;

    SDL_Rect buttonRect = { buttonX, buttonY, buttonW, buttonH };
    bool wasLeftMouseDownLastFrame = false;

    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        SDL_Rect titleRect;
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                gameState = GameState::quit;
                isRunning = false;
            }

        }

        Uint32 currentTime = SDL_GetTicks();
        float displacement = BOB_AMOUNT * sinf((float)currentTime * BOB_SPEED);
        titleRect.y = baseTitleY + (int)displacement;

        titleRect.x = baseTitleX;
        titleRect.w = titleW;
        titleRect.h = titleH;

        int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        SDL_Point mousePos = { mouseX, mouseY };

        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (SDL_PointInRect(&mousePos, &buttonRect)) {
                gameState = GameState::mainGame;
                isRunning = 0;
            }

        }
        SDL_RenderCopy(renderer, backGround, NULL, NULL);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        SDL_RenderPresent(renderer);

    }
}

void MainMenu::handleInput() {

}

void MainMenu::loadTex() {
    backGround = IMG_LoadTexture(renderer, "res/gfx/background.png");
    titleTexture = IMG_LoadTexture(renderer, "res/gfx/svg/titleLogo.png");
    buttonTexture = IMG_LoadTexture(renderer, "res/gfx/svg/play.png");
}

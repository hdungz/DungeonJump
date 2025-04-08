#include "MainGame.h"
#include "Player.h"
#include <iostream>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

MainGame::MainGame(SDL_Window* p_window, SDL_Renderer* p_renderer, TTF_Font* p_font) :
	window(p_window),
	renderer(p_renderer),
	font(p_font),
	running(1)
{
}
int getRandom(int l, int r) {
	return l + rng() % ((r - l) != 0 ? r - l : 1);
}

MainGame::~MainGame() 
{

}
void MainGame::createPlatformsAndPlayer() {
	//platforms.push_back()
	m_player = new Player(renderer, (WINDOW_WIDTH - PLAYER_WIDTH) / 2, WINDOW_HEIGHT - PADDLING - PLAYER_HEIGHT - 10, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_PATH);
	initialPlatform = new Platform(renderer, (WINDOW_WIDTH - PLAYER_WIDTH) / 2, WINDOW_HEIGHT - PADDLING , PLATFORM_WIDTH, PLATFORM_HEIGHT, NORMAL_PATH);
	double columnWidth = double(WINDOW_WIDTH / NUM_COLUMN);
	initialPlatform->loadTex();
	platforms.push_back(initialPlatform);
	m_player->loadTex();
	
}


void MainGame::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameState = GameState::quit;
			running = 0;
		}
	}
	m_keyboardState = SDL_GetKeyboardState(NULL);
	m_player->handleInput(m_keyboardState);
	
}

void MainGame::FpsLimiter(int LastFrameTicks) {
	int RNTicks = SDL_GetTicks();
	if (RNTicks - LastFrameTicks < (1000 / 60)) {
		SDL_Delay((1000 / 60) - (RNTicks - LastFrameTicks));
	}

}

bool cmp(Platform* p) {
	if (p and p->getY() > WINDOW_HEIGHT) {
		delete p;
		p = nullptr;
		return 1;
	}
	return 0;
}

string numToChar(int score) {
	ostringstream scoreStream;
	scoreStream << score;
	string scoreText = scoreStream.str();
	return scoreText;
}

void MainGame::printScore(string& score) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, score.c_str(), textColor);
	if (textSurface == nullptr) {
		std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == nullptr) {
		std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		
		SDL_Rect renderQuad = { (WINDOW_WIDTH - textSurface->w) / 2 , (WINDOW_HEIGHT - textSurface->h) / 2, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr; 
	}
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}

void MainGame::update() {
	FpsLimiter(m_lastTick);
	Uint32 currentTick = SDL_GetTicks();
	m_deltaTime = (currentTick - m_lastTick) * 1.0 / 1000;
	m_lastTick = currentTick;
	const double MAX_DELTATIME = 0.05; 
	if (m_deltaTime > MAX_DELTATIME) {
		m_deltaTime = MAX_DELTATIME;
	}

	//cout << m_player->getY() << " " << cameraY << endl;
	cameraLocking(m_player);
	
	//cout << platforms.size() << " " << endl;
	
	
	double cMaxY = platforms[platforms.size() - 1]->getY();
	while (cMaxY >= -WINDOW_HEIGHT + cameraY) {
		cout << cMaxY << endl;
		int prevX = platforms[platforms.size() - 1]->getX();
		int seed = getRandom(0, 1);
		double startX;
		if (seed == 1 and prevX >= PLATFORM_WIDTH + COLUMN_MARGIN) {
			double minX = 0;
			double maxX = prevX - COLUMN_MARGIN - PLATFORM_WIDTH;
			startX = getRandom(minX, maxX);
		}
		else {
			if (prevX + PLATFORM_WIDTH * 2 + COLUMN_MARGIN > WINDOW_WIDTH) {
				double minX = 0;
				double maxX = WINDOW_WIDTH - PLATFORM_WIDTH - COLUMN_MARGIN;
				startX = getRandom(minX, maxX);
			}
			else {
				double minX = prevX + PLATFORM_WIDTH + COLUMN_MARGIN;
				double maxX = WINDOW_WIDTH - PLATFORM_WIDTH;
				startX = getRandom(minX, maxX);
			}
		}
		Platform* nP = nullptr;
		int seed2 = getRandom(1, 100);
		if (seed2 <= 40) {
			nP = new Platform(renderer, startX, cMaxY - DISTANCE_BETWEEN_TWO_PLATFORM, PLATFORM_WIDTH, PLATFORM_HEIGHT, NORMAL_PATH);
		}
		else if (seed2 <= 65) {
			nP = new BoostedPlatform(renderer, startX, cMaxY - DISTANCE_BETWEEN_TWO_PLATFORM, PLATFORM_WIDTH, PLATFORM_HEIGHT, BOOSTED_PATH, 1600);
		}
		else if (seed2 <= 85){
			nP = new BreakablePlatform(renderer, startX, cMaxY - DISTANCE_BETWEEN_TWO_PLATFORM, PLATFORM_WIDTH, PLATFORM_HEIGHT, BREAKABLE_PATH);
		}
		else {
			nP = new SpikePlatform(renderer, startX, cMaxY - DISTANCE_BETWEEN_TWO_PLATFORM, PLATFORM_WIDTH, PLATFORM_HEIGHT, SPIKE_PATH);
		}
		cMaxY -= DISTANCE_BETWEEN_TWO_PLATFORM;
		nP->loadTex();
		platforms.push_back(nP);
	}

	while (platforms.size() > 0 and platforms[0]->getY() > m_player->getY() + SCROLL_THRESHOLD) {
		 //delete platforms[0];
		platforms.erase(platforms.begin(), platforms.begin() + 1);
	}

	if (cameraY < -1000) {
		cameraY += 1000;
		for (auto p : platforms) {
			p->setPosition(p->getX(), p->getY() + 1000);
		}
		m_player->setPosition(m_player->getX(), m_player->getY() + 1000);
	}

	m_player->update(m_deltaTime, platforms);
	if (m_player->isDied()) {
		gameState = GameState::gameOver;
		running = 0;
	}

	
	//std::cout << endl << "SCORE: " << score << std::endl;
	
}

void MainGame::cameraLocking(Player* t_player) {
	if (t_player->getY() < cameraY + SCROLL_THRESHOLD) {
		cameraY = t_player->getY() - SCROLL_THRESHOLD;
		
		//sumCameraScrolling += cameraY;
	}
	//cout << cameraY << endl;
}

void MainGame::render() {
	SDL_RenderClear(renderer);
	backGround->render(0);
	string score = numToChar(m_player->score);
	printScore(score);
	for (auto p : platforms) {
		p->render(cameraY);
		if (p->getPlatformType() == PlatformType::Breakable) {
			BreakablePlatform* breakable = dynamic_cast<BreakablePlatform*>(p);
			breakable->setDeltaTime(m_deltaTime);
		}
	}
	m_player->render(cameraY);
	SDL_RenderPresent(renderer);
	
}	

void MainGame::run() {

	//highestPlatform = WINDOW_HEIGHT - PADDLING;
	createPlatformsAndPlayer();
	backGround = new Sprite(renderer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, "res/gfx/background.png");
	backGround->loadTex();
	while (running) {
		handleInput();
		update();
		render();
	}

	
}


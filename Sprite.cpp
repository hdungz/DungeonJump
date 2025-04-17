#include "Sprite.h"
#include <iostream>
using namespace std;

Sprite::Sprite(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath) :
	renderer(p_renderer),
	m_x(x), m_y(y), m_w(w), m_h(h),
	m_filePath(filePath)
{
	
}
Sprite::~Sprite() {
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyTexture(texture);
}

void Sprite::loadTex() {
	//cout << 1;
	texture = IMG_LoadTexture(renderer, m_filePath);
	if (texture == nullptr) cout << "init texture failed: " << SDL_GetError() << endl;
	SDL_QueryTexture(texture, NULL, NULL, &originalW, &originalH);
	srcRect = { 0, 0, originalW, originalH };
	
	
	/*SDL_RenderCopy(renderer, texture, &srcRect, &desRect);*/
}

void Sprite::render(double cameraY) {
	if (texture == nullptr || renderer == nullptr) {
		return;
	}
	desRect = { int(m_x), int(m_y), m_w, m_h };
	desRectClone = desRect;
	desRectClone.y = int(m_y) - cameraY;
	SDL_RenderCopy(renderer, texture, &srcRect, &desRectClone);
}

void Sprite::setPosition(double x , double y ){
	m_x = x;
	m_y = y;
}

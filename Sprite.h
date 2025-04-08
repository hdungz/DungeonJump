#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Constant.h"

class Sprite {
public:
	Sprite(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath );
	virtual ~Sprite();
	virtual	void loadTex();
	virtual void render(double cameraY);
	SDL_Texture* getTexture() const { return texture; }
	SDL_Renderer* getRenderer() const { return renderer; }
	void setPosition(double x , double y );
	double getX() const { return m_x; }
	double getY() const { return m_y; }
	SDL_Rect getDesRect() const { return desRect; }
	SDL_Rect desRectClone;
protected:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect;
	SDL_Rect desRect;
	const char* m_filePath;
	double m_x, m_y;
	int m_w, m_h;
	int originalW, originalH;
};
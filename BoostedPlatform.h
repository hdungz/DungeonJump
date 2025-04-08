#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Platform.h"

class BoostedPlatform : public Platform {
public:
	BoostedPlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath, double boostSpeed);
	void playerLand(Player* player);
	double getBoostedSpeed() const { return m_boostedSpeed; }
private:
	double m_boostedSpeed;
};
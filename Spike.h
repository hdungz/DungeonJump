#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Platform.h"

class SpikePlatform : public Platform {
public:
	SpikePlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath);
	~SpikePlatform() = default;
	
private:

	

};

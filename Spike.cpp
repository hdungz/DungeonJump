#include "Spike.h"

SpikePlatform::SpikePlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath) :
	Platform(p_renderer, x, y, w, h, filePath, PlatformType::Spike)
{
	
}


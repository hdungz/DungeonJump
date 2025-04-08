#pragma once
#include "Platform.h"
Platform::Platform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath, PlatformType platformType) :
	Sprite(p_renderer, x, y, w, h, filePath),
	m_platFormType(platformType)
{
	
}

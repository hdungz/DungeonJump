#pragma once
#include "BreakablePlatform.h"
#include "MainGame.h"

BreakablePlatform::BreakablePlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath) :
	Platform(p_renderer, x, y, w, h, filePath, PlatformType::Breakable),
	m_isBroken(0)
{
	
}

void BreakablePlatform::loadTex()
{
	texture1 = IMG_LoadTexture(renderer, BREAKABLE_PATH);
	texture2 = IMG_LoadTexture(renderer, "res/gfx/svg/breakable2.png");
	texture3 = IMG_LoadTexture(renderer, "res/gfx/svg/breakable3.png");
	if (texture1 == nullptr) cout << "init texture failed: " << SDL_GetError() << endl;
	SDL_QueryTexture(texture1, NULL, NULL, &originalW, &originalH);
	srcRect = { 0, 0, originalW, originalH };
	
}

void BreakablePlatform::render(double cameraY) {
	cout << 1;
	desRect = { int(m_x), int(m_y), m_w, m_h };
	desRect2 = { int(m_x), int(m_y-cameraY), m_w / 2, m_h };
	desRect3 = { int(m_x) + m_w/2, int(m_y-cameraY), m_w/2, m_h };
	desRectClone = desRect;
	desRectClone.y = int(m_y) - cameraY;
	if (!m_isBroken) {
		SDL_RenderCopy(renderer, texture1, &srcRect, &desRectClone);
	}
	else {
		SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(texture3, SDL_BLENDMODE_BLEND);
		if (rotating) {
			currentAngle1 += rotationSpeed * m_deltaTime;
			currentAngle2 += -rotationSpeed * m_deltaTime;
			if (currentAngle1 > 30.0) {
				rotationSpeed = 0;
			}
		}
		if (fadingOut) {
			float newAlphaFloat = (float)currentAlpha - (fadeSpeed * m_deltaTime);
			if (newAlphaFloat <= 0.0f) {
				currentAlpha = 0;
				fadingOut = false;
			}
			else {
				currentAlpha = (Uint8)newAlphaFloat;
			}

		}
		SDL_SetTextureAlphaMod(texture1, currentAlpha);
		SDL_SetTextureAlphaMod(texture2, currentAlpha);
		SDL_RenderCopyEx(renderer, texture1, NULL, &desRect2, currentAngle1, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, texture2, NULL, &desRect3, currentAngle2, NULL, SDL_FLIP_NONE);
	}
	
}

void BreakablePlatform::setDeltaTime(double t_deltaTime) {
	m_deltaTime = t_deltaTime;
}






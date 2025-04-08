#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Platform.h"
class MainGame;
class BreakablePlatform : public Platform {
public:
	BreakablePlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath);
	~BreakablePlatform() = default;

	void loadTex() override;
	void render(double cameraY) override;
	bool getBroken() const { return m_isBroken; }
	void setToBroken() { m_isBroken = 1; }
	bool isVisible() const override { return !m_isBroken; }
	void setDeltaTime(double t_deltaTime);

private:
	SDL_Texture* texture1;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	double currentAngle1 = 0.0;
	double currentAngle2 = 0.0;
	float rotationSpeed = 90.0f; 
	Uint8 currentAlpha = 255;    
	float fadeSpeed = 100.0f;    
	bool rotating = true;
	bool fadingOut = true; 
	bool m_isBroken;
	double m_deltaTime = 0;
	SDL_Rect desRect2, desRect3;
};

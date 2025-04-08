#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Sprite.h"

class Player;
enum class PlatformType {
	Normal, Boosted, Breakable, Spike
};
class Platform : public Sprite {
public:
	Platform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath, PlatformType platformType = PlatformType::Normal);
	virtual ~Platform() = default;
	virtual void playerLand(Player* player) {}
	virtual void playerStay(Player* player) {}
	virtual void playerJumpOff(Player* player) {}
	virtual bool isVisible() const { return true; }
	virtual bool shouldBeRemoved() const { return true; }

	PlatformType getPlatformType() const { return m_platFormType; }
protected:
	PlatformType m_platFormType;
};

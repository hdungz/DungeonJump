#include "BoostedPlatform.h"
#include "Player.h"


BoostedPlatform::BoostedPlatform(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath, double boostSpeed) :
	Platform(p_renderer, x, y, w, h, filePath, PlatformType::Boosted),
	m_boostedSpeed(boostSpeed)
{
}

void BoostedPlatform::playerLand(Player* player)
{
	if (player != nullptr) {
		player->boosted = 1;
	}
}


#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <vector>
#include "Constant.h"
#include "Sprite.h"
#include "Platform.h"
#include "BreakablePlatform.h"
#include "Spike.h"
class Platform;
class Player;

class Player : public Sprite {
public:
	Player(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath);
	~Player() = default;
    void handleInput(const Uint8* keyboardState);
    void update(float deltaTime, const std::vector<Platform*>& platforms);
    bool boosted = 0;
    int score = 0;
    double getVelX() const { return m_velocityX; }
    void setVelX(double vx) { m_velocityX = vx; }
    double getVelY() const { return m_velocityY; }
    void setVelY(double vy) { m_velocityY = vy; }
    bool isOnGround() const { return m_isOnGround; }
    bool isDied() const { return died; }

private:
    double m_velocityX = 0;
    double m_velocityY = 0;
    bool m_isOnGround = false;
    bool m_wantsToJump = false; 
    bool died = 0;
    Platform* prevP = nullptr;
    bool readyToJump ;
    Platform* checkingReadyToJump(const std::vector<Platform*>& platforms, double& nextX, double& nextY);
    void moveLeft();
    void moveRight();
    void stopMovingX();
    void jump();
    void applyGravity(double deltaTime);
    bool checkAABBCollision(const SDL_Rect& a, const SDL_Rect& b);
};

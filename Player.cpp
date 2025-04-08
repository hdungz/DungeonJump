#include "Player.h"
#include<iostream>
using namespace std;
Player::Player(SDL_Renderer* p_renderer, double x, double y, int w, int h, const char* filePath) :
	Sprite(p_renderer, x, y, w, h, filePath)
{
    cout << "init player" << endl;
}

void Player::handleInput(const Uint8* keyboardState) {
    if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
        cout << "left" << endl;
        moveLeft();
        
    }
    else if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
        cout << "right" << endl;
        moveRight();
    }
    else {
        stopMovingX();
    }

}

void Player::update(float deltaTime, const std::vector<Platform*>& platforms) {
    if (m_y > WINDOW_HEIGHT) died = 1;
    if (died) return;
    if (readyToJump) {
        jump();
        boosted = 0;
    }
    applyGravity(deltaTime);
    double nextX = m_x + m_velocityX * deltaTime;
    double nextY = m_y + m_velocityY * deltaTime;
    Platform* currP = checkingReadyToJump(platforms, nextX, nextY);
    if (prevP != currP and m_velocityY < 0) score++;
    cout << prevP << " " << currP << " " << readyToJump << " " << score << endl;
    prevP = currP;
   
    setPosition(nextX, nextY);
  
}


Platform* Player::checkingReadyToJump(const std::vector<Platform*>& platforms, double& nextX, double& nextY)
{
    
    readyToJump = 0;
    int i = 0;
    SDL_Rect playerRect = { nextX, nextY, m_w, m_h };
    for (Platform* p : platforms) {
       SDL_Rect platformRect = p->getDesRect();
     /*  cout << ++i << " ";
       cout << m_x << " " << m_y << " " << nextX << " " << nextY << " " <<
           platformRect.x << " " << platformRect.y << endl;*/
       if (p->isVisible() and checkAABBCollision(playerRect, platformRect)) {
           bool currentAbove = (m_y + m_h <= platformRect.y);
           bool willBeCollised = (playerRect.y + m_h >= platformRect.y);
           if (currentAbove and willBeCollised) {
               if (p->getPlatformType() == PlatformType::Spike) {
                   died = 1;
                   break;
               }
               if (p->getPlatformType() == PlatformType::Boosted) {
                   p->playerLand(this);
               }
               if (p->getPlatformType() == PlatformType::Breakable) {
                   BreakablePlatform* breakable = dynamic_cast<BreakablePlatform*>(p);
                   if (!breakable->getBroken()) {
                       breakable->setToBroken();
                   }
                   else continue;
               }
               nextY = platformRect.y - m_h;
               readyToJump = 1;
               return p;
           }
       }
    }
}

void Player::moveLeft() {
    m_velocityX = -PLAYER_MOVE_SPEED;
}

void Player::moveRight() {
    m_velocityX = PLAYER_MOVE_SPEED;
}

void Player::stopMovingX() {
    m_velocityX = 0;
}

void Player::jump() {
    
    m_velocityY = PLAYER_JUMP_FORCE + PLAYER_JUMP_FORCE * boosted;
    m_isOnGround = false;
}

void Player::applyGravity(double deltaTime) {
    m_velocityY += GRAVITY * deltaTime;
   
}

bool Player::checkAABBCollision(const SDL_Rect& a, const SDL_Rect& b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA < topB) return false;
    if (topA > bottomB) return false;
    if (rightA < leftB) return false;
    if (leftA > rightB) return false;

    return true;
}

#include "player.h"
#include "graphics.h"

namespace player_constants {
    const float WALK_SPEED = 0.2f;
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) : AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100) {
    graphics.loadImage("content/sprites/MyChar.png");

    setupAnimations();
    playAnimation("RunRight");
}

void Player::setupAnimations() {
    addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
    addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation) {
}

void Player::moveLeft() {
    dx = -player_constants::WALK_SPEED;
    playAnimation("RunLeft");
    facing = LEFT;
}

void Player::moveRight() {
    dx = player_constants::WALK_SPEED;
    playAnimation("RunRight");
    facing = RIGHT;
}

void Player::stopMoving() {
    dx = 0.0f;
    playAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float elapsedTime) {

    // Move by dx
    x += dx * elapsedTime;

    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics, x, y);
}

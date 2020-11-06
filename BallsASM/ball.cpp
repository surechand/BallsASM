#include "pch.h"
#include "ball.h"

Ball::Ball(float posX, float posY, float radius, float speedX, float speedY) : posX(posX), posY(posY), radius(radius), speedX(speedX), speedY(speedY) {
    this->ball.setPosition(posX, posY);
    this->ball.setOrigin(radius, radius);
    this->ball.setRadius(radius);
    this->ball.setFillColor(sf::Color::Red);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setOutlineThickness(1);
    this->radius++;
    this->canMove = false;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(this->ball, state);
}

sf::CircleShape& Ball::getBall() {
    return ball;
}

float Ball::getPosX()  const {
    return posX;
}

void Ball::setPosX(float posX) {
    Ball::posX = posX;
}

float Ball::getPosY() const {
    return posY;
}

void Ball::setPosY(float posY) {
    Ball::posY = posY;
}

float Ball::getSpeedX() const {
    return speedX;
}

void Ball::setSpeedX(float speedX) {
    Ball::speedX = speedX;
}

float Ball::getSpeedY() const {
    return speedY;
}

void Ball::setSpeedY(float speedY) {
    Ball::speedY = speedY;
}

float Ball::getRadius() const {
    return radius;
}

int Ball::getId() const {
    return id;
}

void Ball::setId(int id) {
    Ball::id = id;
}

bool Ball::getCanMove() const {
    return canMove;
}

void Ball::setCanMove(bool canMove) {
    Ball::canMove = canMove;
}
#include "pch.h"
#include "ball.h"

Ball::Ball(float posX, float posY, float radius) : posX(posX), posY(posY), radius(radius) {
    this->ball.setPosition(posX, posY);
    this->ball.setOrigin(radius, radius);
    this->ball.setRadius(radius);
    this->ball.setFillColor(sf::Color::Red);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setOutlineThickness(1);
    this->radius++;
    this->speedX = 0;
    this->speedY = 0;
    this->accX = 0;
    this->accY = 0;
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

float Ball::getSpeedY() const {
    return speedY;
}

float Ball::getAccX() const {
    return accX;
}

float Ball::getAccY() const {
    return accY;
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
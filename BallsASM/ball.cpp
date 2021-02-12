/*;-------------------------------------------------------------------------
; SYMULATOR ZDERZEÑ
; KRZYSZTOF DEC GR.1
; INFORMATYKA SSI SEMESTR 5 2020/2021
; v.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.1.1 - stworzony interfejs graficzny do obs³ugi programu (14.10.2020)
; v.0.2 - dodanie bibliotek CppDLL oraz AsmDLL do projektu (27.10.2020)
; v.0.3 - implementacja interfejsu graficznego symulacji oraz dodanie podstaw ruchu kul (12.11.2020)
; v.0.3.1 - dodanie obs³ugi wykrywania zderzeñ oraz tworzenia losowych symulacji (14.11.2020)
; v.0.4 - implementacja mechanizmu odbiæ kul od krawêdzi okna symulacji oraz rozdzielania kul nachodz¹cych na siebie (2.12.2020)
; v.0.5 - implementacja algorytmu zderzeñ miêdzy kulami w C++ (9.01.2021)
; v.0.5.1 - dodanie si³ tarcia do symulacji ruchu kul (10.01.2021)
; v.0.5.2 - dodanie obs³ugi w¹tków w symulacji zderzeñ oraz ruchu kul (16.01.2021)
; v.0.6 - implementacja algorytmów zderzeñ oraz ruchu kul w asemblerze (5.02.2021)
; v.0.6.1 - dodanie pomiarów czasu wykonania algorytmów (7.02.2021)
; v.0.7 - poprawiona implementacja algorytmów w asemblerze, usprawnienie dzia³ania w trybie Release w VS2019 (11.02.2021)
; v.1.0 - finalna wersja programu zgodna z za³o¿eniami projektu (12.02.2021)
;-------------------------------------------------------------------------*/

#include "pch.h"
#include "ball.h"

Ball::Ball(float posX, float posY, float radius, float speedX, float speedY) : radius(radius), speedX(speedX), speedY(speedY) {
    this->ball.setPosition(posX, posY);
    this->ball.setOrigin(radius, radius);
    this->ball.setRadius(radius);
    this->ball.setFillColor(sf::Color::Red);
    this->ball.setOutlineColor(sf::Color::Black);
    this->ball.setOutlineThickness(1);
    this->radius++;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const {
    target.draw(this->ball, state);
}

sf::CircleShape& Ball::getBall() {
    return ball;
}

float Ball::getPosX()  const {
    return ball.getPosition().x;
}

float Ball::getPosY() const {
    return ball.getPosition().y;
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
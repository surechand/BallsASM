/*;-------------------------------------------------------------------------
; SYMULATOR ZDERZE�
; KRZYSZTOF DEC GR.1
; INFORMATYKA SSI SEMESTR 5 2020/2021
; v.0.1 - stworzona solucja w visual studio 2019 (13.10.2020)
; v.0.1.1 - stworzony interfejs graficzny do obs�ugi programu (14.10.2020)
; v.0.2 - dodanie bibliotek CppDLL oraz AsmDLL do projektu (27.10.2020)
; v.0.3 - implementacja interfejsu graficznego symulacji oraz dodanie podstaw ruchu kul (12.11.2020)
; v.0.3.1 - dodanie obs�ugi wykrywania zderze� oraz tworzenia losowych symulacji (14.11.2020)
; v.0.4 - implementacja mechanizmu odbi� kul od kraw�dzi okna symulacji oraz rozdzielania kul nachodz�cych na siebie (2.12.2020)
; v.0.5 - implementacja algorytmu zderze� mi�dzy kulami w C++ (9.01.2021)
; v.0.5.1 - dodanie si� tarcia do symulacji ruchu kul (10.01.2021)
; v.0.5.2 - dodanie obs�ugi w�tk�w w symulacji zderze� oraz ruchu kul (16.01.2021)
; v.0.6 - implementacja algorytm�w zderze� oraz ruchu kul w asemblerze (5.02.2021)
; v.0.6.1 - dodanie pomiar�w czasu wykonania algorytm�w (7.02.2021)
; v.0.7 - poprawiona implementacja algorytm�w w asemblerze, usprawnienie dzia�ania w trybie Release w VS2019 (11.02.2021)
; v.1.0 - finalna wersja programu zgodna z za�o�eniami projektu (12.02.2021)
;-------------------------------------------------------------------------*/

#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable {
	sf::CircleShape ball;
	float speedX, speedY;
	float radius;
	int id;

public:
	Ball() = default;

	Ball(float posX, float posY, float radius, float speedX, float speedY);

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

	sf::CircleShape& getBall();

	float getPosX() const;

	void setPosX(float posX);

	float getPosY() const;

	void setPosY(float posY);

	float getSpeedX() const;

	void setSpeedX(float speedX);

	float getSpeedY() const;

	void setSpeedY(float speedY);

	float getRadius() const;

	int getId() const;

	void setId(int id);
};

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
#include <SFML/Graphics.hpp>
#include "ball.h"
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include "windows.h"

typedef void(_stdcall* CalculateSpeeds)(float*, float*);
typedef float(_stdcall* UpdateSpeed)(float, float, float);

class Simulation {
	int threadsNum;
	int ballsNum;
	int dllMethod;
	float WindowLenght, WindowHeight;
	int finishCounter;
	sf::ContextSettings settings;
	sf::RenderWindow window;
	int mouseX = 0, mouseY = 0;
	std::vector<Ball> vecBalls;
	std::vector<std::pair<Ball*, Ball*>> vecCollisions;
	std::vector<std::thread> vecThreads;
	std::vector<long long> vecMoveTime;
	std::vector<long long> vecCollisionTime;
	HINSTANCE library;
public:
	Simulation(int threads, int balls, int dll);
	long long* init();
	void setDllMethod(int dllMethod);
	void addBall(float posX, float posY, float radius);
	bool doBallsOverlap(Ball ball1, Ball ball2);
	static float distanceBetweenBalls(Ball ball1, Ball ball2);
	static void handleCollision(CalculateSpeeds calculateSpeeds, std::pair <Ball*, Ball*> collision);
	static void moveBall(UpdateSpeed updateSpeed, Ball* ball);
	float randomGenerator(float min, float max);
	static float getFriction();
	bool checkIfNotRepeated(Ball* ball1, Ball* ball2);
};
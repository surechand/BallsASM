#pragma once
#include <SFML/Graphics.hpp>
#include "ball.h"
#include <random>
#include <vector>
#include <chrono>
#include "windows.h"

class Simulation {
	int threadsNum;
	int ballsNum;
	int dllMethod;
	int WindowLenght, WindowHeight;
	sf::ContextSettings settings;
	sf::RenderWindow window;
	int mouseX = 0, mouseY = 0;
	float friction;
public:
	std::vector<Ball> vecBalls;
	Simulation(int threads, int balls);
	void init();
	void close();
	void setDllMethod(int dllMethod);
	void addBall(float posX, float posY, float radius);
	bool doBallsOverlap(Ball ball1, Ball ball2);
	float distanceBetweenBalls(Ball ball1, Ball ball2);
	void pickBall(sf::Event& action, Ball& ball);
	float randomGenerator(float min, float max);
};
#include "pch.h"
#include "simulation.h"

Simulation::Simulation(int threads, int balls) : threadsNum(threads), ballsNum(balls) {
    this->WindowLenght = 1900;
    this->WindowHeight = 1080;
};

void Simulation::init() {
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WindowLenght, WindowHeight), "Collision Simulator", sf::Style::Default, settings);
    window.setFramerateLimit(1000);
    sf::Event event;
    //float speedX, speedY, accX, accY;
    for (int i = 0; i < ballsNum; i++) {
        addBall((float)(rand() % WindowLenght), (float)(rand() % WindowHeight), (float)(15 + rand() % 50));
    }
    vecBalls.shrink_to_fit();
    while (window.isOpen())
    {
        window.clear(sf::Color(220, 220, 220));
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //update coordinates
        for (auto& ball : vecBalls) {
            ball.setPosX(ball.getBall().getPosition().x);
            ball.setPosY(ball.getBall().getPosition().y);
        }

        //pick manually
        for (auto& ball : vecBalls) {
            pickBall(event, ball);
        }

        //dynamic collision
        for (auto& ball : vecBalls) {
            //speedX = ball.getSpeedX();
            //speedY = ball.getSpeedY();
            //accX = ball.getAccX();
            //accY = ball.getAccY();
            ball.getBall().move(0.2f, 0.2f);
        }

        //static collision
        for (auto& ball : vecBalls) {
            for (auto& target : vecBalls) {
                if (ball.getId() != target.getId()) {
                    if (doBallsOverlap(ball, target)) {
                        float distance = distanceBetweenBalls(ball, target);
                        float overlap = 0.5f * (distance - ball.getRadius() - target.getRadius());
                        ball.getBall().move(-overlap * (ball.getPosX() - target.getPosX()) / distance, -overlap * (ball.getPosY() - target.getPosY()) / distance);
                        target.getBall().move(overlap * (ball.getPosX() - target.getPosX()) / distance, overlap * (ball.getPosY() - target.getPosY()) / distance);

                    }
                }
            }
            if (ball.getPosX() - ball.getRadius() < 0) {
                ball.getBall().move(ball.getRadius() - ball.getPosX(), 0);
            }
            if (ball.getPosX() + ball.getRadius() > WindowLenght) {
                ball.getBall().move(WindowLenght - ball.getPosX() - ball.getRadius(), 0);
            }
            if (ball.getPosY() - ball.getRadius() < 0) {
                ball.getBall().move(0, ball.getRadius() - ball.getPosY());
            }
            if (ball.getPosY() + ball.getRadius() > WindowHeight) {
                ball.getBall().move(0, WindowHeight - ball.getPosY() - ball.getRadius());
            }
        }
        //draw balls on screen
        for (auto ball : vecBalls) {
            window.draw(ball);
        }

        window.display();
    }
}

void Simulation::setDllMethod(int dllMethod) {
    Simulation::dllMethod = dllMethod;
}

void Simulation::close() {
    window.close();
}

void Simulation::addBall(float posX, float posY, float radius) {
    Ball newBall(posX, posY, radius);
    newBall.setId(vecBalls.size());
    vecBalls.emplace_back(newBall);
}

bool Simulation::doBallsOverlap(Ball ball1, Ball ball2) {
    return ((ball1.getPosX() - ball2.getPosX()) * (ball1.getPosX() - ball2.getPosX()) + (ball1.getPosY() - ball2.getPosY()) * (ball1.getPosY() - ball2.getPosY())) <= (ball1.getRadius() + ball2.getRadius()) * (ball1.getRadius() + ball2.getRadius());
}

float Simulation::distanceBetweenBalls(Ball ball1, Ball ball2) {
    return sqrtf((ball1.getPosX() - ball2.getPosX()) * (ball1.getPosX() - ball2.getPosX()) + (ball1.getPosY() - ball2.getPosY()) * (ball1.getPosY() - ball2.getPosY()));
}

void Simulation::pickBall(sf::Event& action, Ball& ball) {
    if (ball.getBall().getGlobalBounds().contains(action.mouseButton.x, action.mouseButton.y)) {
        if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left) {
            ball.setCanMove(true);
        }
    }
    if (ball.getCanMove()) {
        if (action.type == sf::Event::MouseButtonReleased && action.mouseButton.button == sf::Mouse::Left) {
            ball.getBall().setPosition(sf::Vector2f(mouseX, mouseY));
            ball.setCanMove(false);
        }
    }
    if (action.type == sf::Event::MouseMoved) {
        mouseX = action.mouseMove.x;
        mouseY = action.mouseMove.y;
    }
    if (ball.getCanMove()) {
        ball.getBall().setPosition(static_cast<float>(mouseX), static_cast<float>(mouseY));
    }
}
#include "pch.h"
#include "simulation.h"

Simulation::Simulation(int threads, int balls) : threadsNum(threads), ballsNum(balls) {
    this->WindowLenght = 1900;
    this->WindowHeight = 1080;
    this->friction = 0.015f;
};

void Simulation::init() {
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WindowLenght, WindowHeight), "Collision Simulator", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Event event;
    float speedX, speedY, accX, accY;
    for (int i = 0; i < ballsNum; i++) {
        addBall(randomGenerator(0,WindowLenght), randomGenerator(0, WindowHeight), randomGenerator(15.0f, 50.0f));
    }
    vecBalls.shrink_to_fit();
    //auto start = std::chrono::high_resolution_clock::now();
    //auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed;
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

        //static collision
        for (auto& ball : vecBalls) {
            for (auto& target : vecBalls) {
                if (ball.getId() != target.getId()) {
                    if (doBallsOverlap(ball, target)) {
                        vecCollisions.push_back(std::make_pair(&ball, &target));
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
        //moving balls and changing speed
        for (auto& ball : vecBalls) {
            accX = -ball.getSpeedX() * friction;
            accY = -ball.getSpeedY() * friction;
            speedX = ball.getSpeedX();
            speedY = ball.getSpeedY();
            speedX += accX;
            speedY += accY;
            ball.setSpeedX(speedX);
            ball.setSpeedY(speedY);
            if ((ball.getSpeedX() * ball.getSpeedX() + ball.getSpeedY() * ball.getSpeedY()) < 0.1f) {
                ball.setSpeedX(0);
                ball.setSpeedY(0);
            }
            if (ball.getPosX() - ball.getRadius() < 0 || ball.getPosX() + ball.getRadius() > WindowLenght) {
                ball.setSpeedX(-ball.getSpeedX());
            }
            if (ball.getPosY() - ball.getRadius() < 0 || ball.getPosY() + ball.getRadius() > WindowHeight) {
                ball.setSpeedY(-ball.getSpeedY());
            }
            ball.getBall().move(ball.getSpeedX(), ball.getSpeedY());
        }

        //dynamic collision
        for (auto collision : vecCollisions) {
            Ball *ball1 = collision.first;
            Ball *ball2 = collision.second;

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
    Ball newBall(posX, posY, radius, randomGenerator(-75.0f, 75.0f), randomGenerator(-75.0f, 75.0f));
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

float Simulation::randomGenerator(float min, float max) {
    Sleep(1);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<float>(min, max)(rng);
}
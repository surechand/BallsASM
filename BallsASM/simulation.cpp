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
#include "simulation.h"

Simulation::Simulation(int threads, int balls, int dll) : threadsNum(threads), ballsNum(balls), dllMethod(dll) {
    this->WindowLenght = 1900;
    this->WindowHeight = 1080;
    this->finishCounter = 0;
    if (this->dllMethod == 1) {
        library = LoadLibrary(TEXT("CppDLL.dll"));
    }
    else if (this->dllMethod == 2) {
        library = LoadLibrary(TEXT("AsmDLL.dll"));
    }
};

long long* Simulation::init() {
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WindowLenght, WindowHeight), "Collision Simulator", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Event event;

    for (int i = 0; i < ballsNum; i++) {
        addBall(randomGenerator(0, WindowLenght), randomGenerator(0, WindowHeight), randomGenerator(15.0f, 50.0f));
    }
    vecBalls.shrink_to_fit();

    CalculateSpeeds calculateSpeeds = (CalculateSpeeds)GetProcAddress(library, "calculateSpeeds");
    UpdateSpeed updateSpeed = (UpdateSpeed)GetProcAddress(library, "updateSpeed");

    while (window.isOpen())
    {
        window.clear(sf::Color(220, 220, 220));
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //static collision
        for (auto& ball : vecBalls) {
            for (auto& target : vecBalls) {
                if (ball.getId() != target.getId()) {
                    if (doBallsOverlap(ball, target)) {
                        if (checkIfNotRepeated(&ball, &target)) {
                            vecCollisions.push_back(std::make_pair(&ball, &target));
                            float distance = distanceBetweenBalls(ball, target);
                            float overlap = 0.5f * (distance - ball.getRadius() - target.getRadius());
                            ball.getBall().move(-overlap * (ball.getPosX() - target.getPosX()) / distance, -overlap * (ball.getPosY() - target.getPosY()) / distance);
                            target.getBall().move(overlap * (ball.getPosX() - target.getPosX()) / distance, overlap * (ball.getPosY() - target.getPosY()) / distance);
                        }
                    }
                }
            }
            if (ball.getPosX() - ball.getRadius() < 0) {
                ball.setSpeedX(-ball.getSpeedX());
                ball.getBall().move(ball.getRadius() - ball.getPosX(), 0);
            }
            if (ball.getPosX() + ball.getRadius() > WindowLenght) {
                ball.setSpeedX(-ball.getSpeedX());
                ball.getBall().move(WindowLenght - ball.getPosX() - ball.getRadius(), 0);
            }
            if (ball.getPosY() - ball.getRadius() < 0) {
                ball.setSpeedY(-ball.getSpeedY());
                ball.getBall().move(0, ball.getRadius() - ball.getPosY());
            }
            if (ball.getPosY() + ball.getRadius() > WindowHeight) {
                ball.setSpeedY(-ball.getSpeedY());
                ball.getBall().move(0, WindowHeight - ball.getPosY() - ball.getRadius());
            }
        }

        //dynamic collision        
        if (vecCollisions.size() > 0) {
            auto start = std::chrono::high_resolution_clock::now();
            if (vecCollisions.size() < threadsNum) {
                for (auto& collision : vecCollisions) {
                    vecThreads.push_back(std::thread(&Simulation::handleCollision, calculateSpeeds, collision));
                }
                for (auto& thread : vecThreads) {
                    thread.join();
                }
            } else {
                int counter = 0;
                for (auto& collision : vecCollisions) {
                    vecThreads.push_back(std::thread(&Simulation::handleCollision, calculateSpeeds, collision));
                    ++counter;
                    if (counter == threadsNum) {
                        for (auto& thread : vecThreads) {
                            thread.join();
                        }
                        vecThreads.clear();
                        counter = 0;
                    }
                }
                if (vecThreads.size() > 0) {
                    for (auto& thread : vecThreads) {
                        thread.join();
                    }
                }
            }
            auto finish = std::chrono::high_resolution_clock::now();
            vecCollisionTime.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
            vecThreads.clear();
        }
        vecCollisions.clear();

        auto start = std::chrono::high_resolution_clock::now();
        //moving balls and changing speed
        for (auto& ball : vecBalls) {
            vecThreads.push_back(std::thread(&Simulation::moveBall, updateSpeed, &ball));
        }
        for (auto& thread : vecThreads) {
            thread.join();
        }
        vecThreads.clear();
        auto finish = std::chrono::high_resolution_clock::now();
        vecMoveTime.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());

        //draw balls on screen
        for (auto& ball : vecBalls) {
            window.draw(ball);
        }

        window.display();

        //draw balls on screen
        for (auto& ball : vecBalls) {
            if ((ball.getSpeedX() * ball.getSpeedX() + ball.getSpeedY() * ball.getSpeedY()) < 0.05f) {
                finishCounter++;
            }
        }

        if (finishCounter == ballsNum) {
            Sleep(2000);
            long long averageMoveTime = 0, averageCollisionTime = 0;
            for (auto& time : vecMoveTime) {
                averageMoveTime += time;
            }
            averageMoveTime /= vecMoveTime.size();
            if (vecCollisionTime.size() > 0) {
                for (auto& time : vecCollisionTime) {
                    averageCollisionTime += time;
                }
                averageCollisionTime /= vecCollisionTime.size();
            } else {
                averageCollisionTime = 0;
            }
            auto* averageTimes = new long long[2];
            averageTimes[0] = averageMoveTime;
            averageTimes[1] = averageCollisionTime;
            window.close();
            return averageTimes;
        }

        finishCounter = 0;
    }
}

void Simulation::setDllMethod(int dllMethod) {
    Simulation::dllMethod = dllMethod;
}

void Simulation::addBall(float posX, float posY, float radius) {
    Ball newBall(posX, posY, radius, randomGenerator(-35.0f, 35.0f), randomGenerator(-35.0f, 35.0f));
    newBall.setId(vecBalls.size());
    vecBalls.emplace_back(newBall);
}

bool Simulation::checkIfNotRepeated(Ball* ball1, Ball* ball2) {
    for (auto& collision : vecCollisions) {
        if (ball1->getId() == collision.second->getId() || ball2->getId() == collision.first->getId()) {
            return false;
        }
    }
    return true;
}

bool Simulation::doBallsOverlap(Ball ball1, Ball ball2) {
    return ((ball1.getPosX() - ball2.getPosX()) * (ball1.getPosX() - ball2.getPosX()) + (ball1.getPosY() - ball2.getPosY()) * (ball1.getPosY() - ball2.getPosY())) <= (ball1.getRadius() + ball2.getRadius()) * (ball1.getRadius() + ball2.getRadius());
}

float Simulation::distanceBetweenBalls(Ball ball1, Ball ball2) {
    return sqrtf((ball1.getPosX() - ball2.getPosX()) * (ball1.getPosX() - ball2.getPosX()) + (ball1.getPosY() - ball2.getPosY()) * (ball1.getPosY() - ball2.getPosY()));
}

void Simulation::handleCollision(CalculateSpeeds calculateSpeeds, std::pair <Ball*, Ball*> collision) {

    auto ball1 = collision.first;
    auto ball2 = collision.second;

    float distance = distanceBetweenBalls(*ball1, *ball2);

    auto* speedValues = new float[4];

    auto* parameters = new float[11];
    parameters[0] = distance;
    parameters[1] = ball1->getPosX();
    parameters[2] = ball1->getPosY();
    parameters[3] = ball1->getSpeedX();
    parameters[4] = ball1->getSpeedY();
    parameters[5] = ball1->getRadius();
    parameters[6] = ball2->getPosX();
    parameters[7] = ball2->getPosY();
    parameters[8] = ball2->getSpeedX();
    parameters[9] = ball2->getSpeedY();
    parameters[10] = ball2->getRadius();

    calculateSpeeds(speedValues, parameters);

    ball1->setSpeedX(speedValues[0]);
    ball1->setSpeedY(speedValues[1]);
    ball2->setSpeedX(speedValues[2]);
    ball2->setSpeedY(speedValues[3]);

    delete []speedValues;
    delete []parameters;
}


void Simulation::moveBall(UpdateSpeed updateSpeed, Ball* ball) {

    float speedX = ball->getSpeedX();
    float speedY = ball->getSpeedY();

    speedX += updateSpeed(ball->getSpeedX(), getFriction(), ball->getRadius());
    speedY += updateSpeed(ball->getSpeedY(), getFriction(), ball->getRadius());

    if ((speedX * speedX + speedY * speedY) < 0.05f) {
        ball->setSpeedX(0);
        ball->setSpeedY(0);
    }
    else {
        ball->setSpeedX(speedX);
        ball->setSpeedY(speedY);
    }
    ball->getBall().move(ball->getSpeedX(), ball->getSpeedY());
}



float Simulation::randomGenerator(float min, float max) {
    Sleep(1);
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<float>(min, max)(rng);
}

float Simulation::getFriction() {
    return 0.0008f;
}
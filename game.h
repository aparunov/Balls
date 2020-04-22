#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>
#include <ctime>

#include "ball.h"


class Game{
public:
    Game(size_t nBalls);
    void run();
private:
    sf::RenderWindow mWindow;
    // Vanjski okvir
    sf::RectangleShape mRectangle;
    // Kugle.
    std::vector<std::unique_ptr<Ball> > mBall;
    Ball mB;
    Ball mB_2;

    size_t mNball = 6;

    float mDx;
    float mDy;
    // Za generiranje slučajnih brojeva
    std::default_random_engine mRand;

    void processEvents();
    void update(sf::Time const & dt);
    void render();

    // Postavi kugle u inicijalne pozicije
    void initPositions(float radius);
    // Daj kuglama inicijalne brzine. maxVel je maksimalna moguća brzina. 
    void initVelocity(float maxVel);

    bool theyIntersect();

    // Provjeri koliziju sa zidom i promjeni brzinu kuglice na adekvatan način
    void checkForCollisionsWithWalls(Ball * pball) const;
    // Provjeri koliziju kuglice pball s ostali kuglicama i promjeni brzine 
    // na odgovarajući način.
    void checkForCollisionsWithBalls(Ball * pball_1, Ball *pball_2) const;

};





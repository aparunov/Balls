#include "game.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Ovdje dolazi vaš kod

float scalarProduct (sf::Vector2f &&v1, sf::Vector2f &&v2){
    return v1.x*v2.x + v1.y*v2.y;
}

float distance(sf::Vector2f &&v1, sf::Vector2f &&v2){
    return pow(v1.x-v2.x,2) + pow(v1.y-v2.y,2);
}

bool Game::theyIntersect(){
    for (auto it = mBall.begin(); it != mBall.end(); ++it){
        for (auto jt = it+1; jt != mBall.end(); jt++){
            if (sqrt(distance((*it)->getPosition(), (*jt)->getPosition() ))<=2*(*it)->getRadius()){
                return true;
            }
        }
    }
    return  false;
}


Game::Game(size_t nBalls) : mWindow(sf::VideoMode(820,420), "SFML window"), mNball(mNball=nBalls)
{

    for (unsigned int i = 0; i < mNball; ++i){
        std::unique_ptr<Ball> b (new Ball());
        (*b.get()).setRadius(13.f);
        (*b.get()).setColor(sf::Color::Yellow);
        (*b.get()).setChar(char(65+i));
        (*b.get()).setOriginToCenter();
        mBall.push_back(std::move(b));
    }

    mRectangle.setSize(sf::Vector2f(800,400));
    mRectangle.setOutlineThickness(10);
    mRectangle.setPosition(10,10);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setFillColor(sf::Color::Black);

    initPositions(13.f);
    initVelocity(4.1f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time protekloVrijeme = sf::Time::Zero;
    sf::Time dt = sf::seconds(1.06f/60.f);

    while (mWindow.isOpen())
    {
        processEvents();
        protekloVrijeme += clock.restart();
        while (protekloVrijeme >= dt){
            protekloVrijeme -= dt;
            update(dt);
        }
        update(dt);
        render();

    }
}


void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        // Close window : exit
        switch(event.type){
        default:
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time const & dt)
{
    float brzina = 3.0f; //pps
    float dx = brzina*dt.asSeconds();
    dx*=2;

    for (unsigned int i = 0; i < mNball; ++i){
        for (unsigned j = i+1; j < mNball; ++j){
               checkForCollisionsWithBalls( mBall[i].get(), mBall[j].get());
        }
        checkForCollisionsWithWalls(mBall[i].get());
    }
    for (unsigned int i = 0; i < mNball; ++i){

        mBall[i]->move(dt);
    }
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    //Draw everything
    mWindow.draw(mRectangle);
    for (unsigned int i = 0; i < mNball; ++i){
        mWindow.draw(*mBall[i]);
    }
    // Update the window
    mWindow.display();
}

void Game::initPositions(float radius)
{
    bool intersect = true;
    while (intersect){
        //std::cout << "test" << std::endl;
        for (auto it = mBall.begin(); it != mBall.end(); ++it){
            std::uniform_real_distribution<float> disx(0.0, 1.0);
            std::uniform_real_distribution<float> disy(0.0, 1.0);
            float dx = radius + 11 + (810-2*radius-11)*disx(mRand);
            float dy = radius + 11 + (410-2*radius-11)*disy(mRand);
            //std::cout << dx << "," << dy << "|" ;
            ((*it).get())->setPosition(dx, dy);

        }
        //std::cout << std::endl;
        intersect = theyIntersect();
    }
}

void Game::initVelocity(float maxVel)
{
    for (auto it = mBall.begin(); it != mBall.end(); ++it){
        std::normal_distribution<float> disVx(0.0,1.0);
        std::normal_distribution<float> disVy(0.0,1.0);
        (*it).get()->mVelocity.x=maxVel * disVx(mRand);
        (*it).get()->mVelocity.y=maxVel * disVy(mRand);
    }
}

void Game::checkForCollisionsWithWalls(Ball *pball) const
{
    if ((*pball).getPosition().x >= 810 - (*pball).getRadius() or (*pball).getPosition().x <= 10 + (*pball).getRadius())
    {
        pball->mVelocity.x *= -1;
    }

    else if ((*pball).getPosition().y >= 410 - (*pball).getRadius() or (*pball).getPosition().y <= 10 + (*pball).getRadius()){
        pball->mVelocity.y *= -1;
    }

}

void Game::checkForCollisionsWithBalls(Ball *pball_1, Ball *pball_2) const
{


    if (sqrt(distance(pball_1->getPosition(),pball_2->getPosition())) <= pball_1->getRadius() + pball_2->getRadius()){

        sf::Vector2f v_tmp = pball_1->mVelocity - scalarProduct((pball_1->mVelocity-pball_2->mVelocity),
                                                                (pball_1->getPosition()-pball_2->getPosition()))
                                                                /distance(pball_1->getPosition(),pball_2->getPosition())
                                                                 *(pball_1->getPosition()
                                                                 -pball_2->getPosition());
        pball_2->mVelocity -= (scalarProduct((pball_2->mVelocity-pball_1->mVelocity),
                            (pball_2->getPosition()-pball_1->getPosition()))
                            /distance(pball_1->getPosition(),pball_2->getPosition())
                             *(pball_2->getPosition()
                             -pball_1->getPosition()));
        pball_1->mVelocity = v_tmp;

     }
}

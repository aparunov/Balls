#include "game.h"

// Ovdje dolazi vaš kod.



Ball::Ball()
{
    /*if(!mFont.loadFromFile("/home/theboss/HOME/cpp/sfml2-aparunov/ObelixProB-cyr.ttf"))
        throw std::runtime_error("Nema Fonta");*/
    if(!mFont.loadFromFile("Comfortaa-Bold.ttf"))
        throw std::runtime_error("Nema Fonta");
    mCircle.setRadius(mRadius);
    mCircle.setOrigin(mCircle.getLocalBounds().width/2,
                      mCircle.getLocalBounds().height/2);
    mText.setFont(mFont);
    mText.setCharacterSize(16);
    mText.setColor(sf::Color::Black);
    //setOriginToCenter();
    mText.setString(mChar);
}

void Ball::setRadius(float r) { mRadius = r; mCircle.setRadius(r); }

void Ball::setChar(char c) { mChar = c; mText.setString(mChar);}

void Ball::setColor(sf::Color T) {mCircle.setFillColor(T);}

void Ball::setPosition(float x, float y) {mCircle.setPosition(x,y);
                                         mText.setPosition(x/*+mCircle.getLocalBounds().width/4*/,
                                                           y/*+mCircle.getLocalBounds().height/4*/);}

void Ball::setOriginToCenter()
{
    mCircle.setOrigin(mCircle.getLocalBounds().height/2,mCircle.getLocalBounds().width/2);
    mText.setOrigin(mCircle.getLocalBounds().height/4,mCircle.getLocalBounds().width/4);
}

void Ball::setText(const char &text)
{
    mText.setString(text);
}

void Ball::move(sf::Time dt)
{
    mCircle.move(mVelocity.x*dt.asSeconds(),mVelocity.y*dt.asSeconds());
    mText.move(mVelocity.x*dt.asSeconds(),mVelocity.y*dt.asSeconds());
    mText.rotate(2*dt.asSeconds());
}

sf::Vector2f Ball::getPosition()
{
    return mCircle.getPosition();
}

float Ball::getRadius() const { return mRadius; }

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mCircle, states);
    target.draw(mText, states);
}

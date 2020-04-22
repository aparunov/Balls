#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable {
public:
    Ball();
    sf::Vector2f mVelocity;
    void setRadius(float r);
    void setChar(char c);
    void setColor(sf::Color T);
    void setPosition (float x, float y);
    void setOriginToCenter();
    void setText(const char & text);
    void move(sf::Time dt);
    sf::Vector2f getPosition();
    float getRadius() const;
private:
    sf::CircleShape mCircle;
    sf::Font mFont;
    sf::Text mText;
    float mRadius;
    char mChar;


    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};











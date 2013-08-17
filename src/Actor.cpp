#include "../include/Actor.h"
#include <string>
#include <cmath>


Actor::Actor()
{
    this->vecPos.x = 0.f;
    this->vecPos.y = 0.f;
}
Actor::Actor( sf::Vector2f vec, std::string url )
{
    this->vecPos = vec;
    setSprite( url );
}

Actor::Actor( sf::Vector2f vec, std::string url, sf::Vector2f dim )
{
    this->setDimensions( dim );
    this->vecPos = vec;
    setSprite( url );
}

Actor::~Actor()
{
    //dtor
}

void Actor::setPosition( sf::Vector2f vec )
{
    this->vecPos = vec;
}

void Actor::setSprite( std::string url )
{
    if( texture.loadFromFile( url ) )
    {
        sprite.setTexture( texture );
        sprite.setOrigin( getDimensions().x/2, getDimensions().y/2 );
        sprite.setPosition( vecPos );
    } // if
}

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw( sprite, states );
}

sf::Vector2f Actor::getMiddle()
{
    float vx = this->vecPos.x + getDimensions().x/2;
    float vy = this->vecPos.y + getDimensions().y/2;

    return sf::Vector2f( vx, vy );
}

void Actor::setDimensions( sf::Vector2f vec )
{
    this->vecDimm = vec;
}

sf::Vector2f Actor::getDimensions()
{
    return this->vecDimm;
}

void Actor::setV( float v )
{
    this->v = v;
}

float Actor::getV()
{
    return this->v;
}

sf::Vector2f Actor::getOrigin()
{
    return this->sprite.getOrigin();
}


sf::Vector2f Actor::getPosition()
{
    return vecPos;
}

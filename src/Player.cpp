#include "../include/Player.h"

Player::Player() : Actor()
{

}

Player::Player( sf::Vector2f vec, std::string url, sf::Vector2f dim ) : Actor( vec, url, dim )
{

}

Player::~Player()
{
    this->HPpoints = 100.f;
    //dtor
}

int Player::getHPpoints()
{
    return this->HPpoints;
}

void Player::reduceHPpoints()
{
    this->HPpoints -= 5.f;
}

float Player::HPpoints = 100;

void Player::moveDown()
{
    if( vecPos.y > 0 && vecPos.y <= 599 - getDimensions().y/2 )
    {
        sprite.setPosition( this->vecPos.x, this->vecPos.y += this->v );
        sprite.setRotation( 180 );
    }
}

void Player::moveLeft()
{
    if( vecPos.x >= getDimensions().y/2 && vecPos.x < 800 - getDimensions().x/2 )
    {
        sprite.setPosition( this->vecPos.x -= this->v, this->vecPos.y );
        sprite.setRotation( -90 );
    }
}

void Player::moveRight()
{
    if( vecPos.x >= getDimensions().x/2 && vecPos.x < 800 - getDimensions().y/2 )
    {
        sprite.setPosition( this->vecPos.x += this->v, this->vecPos.y );
        sprite.setRotation( 90 );
    }
}

void Player::moveUp()
{
    if( vecPos.y > getDimensions().y/2 && vecPos.y <= 600 - getDimensions().y/2 )
    {
        sprite.setPosition( this->vecPos.x, this->vecPos.y -= this->v );
        sprite.setRotation( 0 );
    }
}

float Player::rotateAncle = 0;

float Player::getRotation()
{
    return sprite.getRotation();
}

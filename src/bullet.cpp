#include "../include/bullet.h"

Bullet::Bullet() : Actor()
{
    //ctor
}

Bullet::Bullet( sf::Vector2f vec, std::string url ) : Actor( vec, url )
{
    //ctor
}

Bullet::Bullet( sf::Vector2f vec, std::string url, sf::Vector2f dim, int rot ) : Actor( vec, url, dim )
{
    //ctor
    this->rotation = rot;
    sprite.setRotation( rot );
}


Bullet::~Bullet()
{
    //dtor
}

void Bullet::move()
{
    switch( this->rotation )
    {
    case 0:
        sprite.setPosition( this->getPosition().x, this->vecPos.y -= this->v );
        break;
    case 45:
        sprite.setPosition( this->vecPos.x += v, this->vecPos.y -= this->v );
        break;
    case 90:
        sprite.setPosition( this->vecPos.x += this->v, this->getPosition().y );
        break;
    case 135:
        sprite.setPosition( this->vecPos.x += v, this->vecPos.y += this->v );
        break;
    case 180:
        sprite.setPosition( this->getPosition().x, this->vecPos.y += this->v );
        break;
    case 225:
        sprite.setPosition( this->vecPos.x -= v, this->vecPos.y += this->v );
        break;
    case 270:
        sprite.setPosition( this->vecPos.x -= this->v, this->getPosition().y );
        break;
    case 315:
        sprite.setPosition( this->vecPos.x -= v, this->vecPos.y -= this->v );
        break;
    default:

        break;
    }
}

void Bullet::setRotation( int rot )
{
    this->rotation = rot;
    sprite.setRotation( rot );
}

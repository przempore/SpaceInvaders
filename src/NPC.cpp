#include "../include/NPC.h"

NPC::NPC() : Actor()
{
    this->vecPos.x = 0;
    this->vecPos.y = 0;
}

NPC::NPC( sf::Vector2f vec, std::string url, sf::Vector2f dim, float v ) : Actor( vec, url, dim )
{
    this->v = v;
}

NPC::~NPC()
{
    //dtor
}

void NPC::move()
{
    sprite.setPosition( this->vecPos.x += v, this->vecPos.y );//vecPos.y );
    if( this->vecPos.x <= 0 || this->vecPos.x >= ( 800 - getDimensions().x ) || this->vecPos.y <= 0 || this->vecPos.y >= ( 600 - getDimensions().y ) )
    {
        this->v = -this->v;
    }
}


void NPC::setSprite( std::string url )
{
    if( texture.loadFromFile( url ) )
    {
        sprite.setTexture( texture );
//        sprite.setPosition( this->x - getDimensions().x/2, this->y - getDimensions().y/2 );
//        sprite.setOrigin( this->getDimensions().x/2, this->getDimensions().y/2 );
    } // if
}

#ifndef NPC_H
#define NPC_H

#include "../include/Actor.h"
#include <SFML/Audio.hpp>

class NPC : public Actor, public sf::Transform
{
    public:
        NPC();
        NPC( sf::Vector2f vec, std::string url, sf::Vector2f dim, float v = 0.5f );
        virtual ~NPC();
        void setSprite( std::string url );
        void move();
    protected:
    private:
};

#endif // NPC_H

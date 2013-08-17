#ifndef BULLET_H
#define BULLET_H

#include "../include/Actor.h"


class Bullet : public Actor
{
    public:
        Bullet();
        Bullet( sf::Vector2f vec, std::string url );
        Bullet( sf::Vector2f vec, std::string url, sf::Vector2f dim, int rot );
        virtual ~Bullet();
        void move();
        void setRotation( int rot );
    protected:
        int rotation;
    private:
};

#endif // BULLET_H

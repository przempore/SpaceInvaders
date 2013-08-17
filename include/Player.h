#ifndef PLAYER_H
#define PLAYER_H

#include "../include/Actor.h"


class Player : public Actor
{
    public:
        Player();
        Player( sf::Vector2f vec, std::string url, sf::Vector2f dim );
        virtual ~Player();
//        void moveUp();
//        void moveDown();
        int getHPpoints();
        void reduceHPpoints();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void fire();
        float getRotation();

    protected:
        static float HPpoints;
        static float rotateAncle;
    private:
};

#endif // PLAYER_H

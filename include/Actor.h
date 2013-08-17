#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>

class Actor : public sf::Drawable
{
    public:
        Actor();
        Actor( sf::Vector2f vec, std::string url );
        Actor( sf::Vector2f vec, std::string url, sf::Vector2f dim );
        virtual ~Actor();
        void setPosition( sf::Vector2f vec );
        sf::Vector2f getPosition();
        void setSprite( std::string url );
        sf::Vector2f getMiddle();
        void setDimensions( sf::Vector2f vec );
        sf::Vector2f getDimensions();
        float getV();
        void setV( float v );
        sf::Vector2f getOrigin();

    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f vecPos;
        sf::Vector2f vecDimm;
        float v;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};

#endif // ACTOR_H

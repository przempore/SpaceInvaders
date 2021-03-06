#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include "Actor.h"
#include <SFML/Audio.hpp>

class Playground : public Actor
{
    public:
        Playground();
        Playground( sf::Vector2f vec, std::string url );
        Playground( sf::Vector2f vec, std::string url, sf::Vector2f dim );
        virtual ~Playground();
        void playMusic();
        void pauseMusic();
        void risePoints();
        int getPoints();
        void resetPoints();
        sf::Text text;
        void setFont();
        void setScore();
        void getScore();
        std::string getScore( int* const i );
        std::string int2str( int i );
        void sortVec( std::vector<std::string>& stringVec );
        int str2int( std::string str );
        int getNumber( std::string line );

    protected:
    private:
        static float points;
        sf::Music music;
        sf::Font font;
        std::vector <std::string> stringVec;
};

#endif // PLAYGROUND_H

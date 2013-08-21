#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Playground.h"
#include "include/NPC.h"
#include "include/Player.h"
#include "include/bullet.h"

bool collision( Actor* X, Actor* Y );

int main()
{
    // Tworzenie okna gry
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "space Invaders" );

    // wczytywanie tla gry
    Playground background( sf::Vector2f( 0.f, 0.f ), "img/background.png"  );


    // definiowanie NPC
    const int numOfNpc = 3;
//    NPC npcTab[ numOfNpc ];
    std::vector<NPC*> npcTab;
    srand( time( NULL ) );
    for( int i = 0; i < numOfNpc; i++ )
    {
        int x = rand() % 755;
        int y = rand() % 553;
        NPC* npc = new NPC( sf::Vector2f( x, y ), "img/monster.png", sf::Vector2f( 45.f, 47.f ) );
//        int v = 4 + rand() % 3;
        npc->setV( 4.f );
        npcTab.push_back( npc );
    }

    // ustawianie Playera
    Player player( sf::Vector2f( 376.f, 565.f ), "img/player.png", sf::Vector2f( 48, 70 ) );
    player.setV( 7.f );



    // clock do blokowania wykonywania sie zbyt szybko gry
    sf::Clock clock;

    // bullets
    std::vector<Bullet*> bullets;

    while( window.isOpen() )
    {
        clock.restart();

        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                 window.close();
        } //while

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
        {
            window.close();
        }

        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
        {
            player.moveUp();
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
        {
            player.moveDown();
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
        {
            player.moveLeft();
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
        {
            player.moveRight();
        }

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
        {
            int rot = player.getRotation();
            sf::Vector2f pos;
            switch( rot )
            {
            case 0:
                pos = sf::Vector2f( player.getPosition().x, player.getPosition().y - 20 );
                break;
            case 90:
                pos = sf::Vector2f( player.getPosition().x + 20 , player.getPosition().y );
                break;
            case 180:
                pos =  sf::Vector2f( player.getPosition().x, player.getPosition().y + 20 );
                break;
            case 270:
                pos = sf::Vector2f( player.getPosition().x - 20, player.getPosition().y );
                break;
            }
            Bullet* bull = new Bullet( pos, "img/bullet.png", sf::Vector2f( 4, 18 ), rot );
            bull->setV( 17.f );
            bullets.push_back( bull );
        } // if


        for( int i = 0; i < npcTab.size(); i++ )
        {
            window.draw( *npcTab[ i ] );
        }

        // colizja
        for( int i = 0; i < npcTab.size(); i++ )
        {
            for( int j = 0; j < bullets.size(); j++ )
            {
                if( collision( npcTab[ i ], bullets[ j ] ) )
                {
                    delete npcTab[ i ];
                    npcTab.erase( npcTab.begin()+i );
                    delete bullets[ j ];
                    bullets.erase( bullets.begin()+j );
                    for( int k = 0; k < 2; k++ )
                    {
                        int x = rand() % 755;
                        int y = rand() % 553;
                        NPC* npc = new NPC( sf::Vector2f( x, y ), "img/monster.png", sf::Vector2f( 45.f, 47.f ) );
                        npc->setV( 4.f );
                        npcTab.push_back( npc );
                    } // for
                } // if
            } // for
        } // for

        for( int i = 0; i < npcTab.size(); i++ )
        {
            if( collision( &player, npcTab[ i ] ) )
            {
                player.reduceHPpoints();
            }
        }


        for( int i = 0; i < bullets.size(); i++ )
        {
                bullets[ i ]->move();
        }

        for( int i = 0; i < npcTab.size(); i++ )
        {
            npcTab[ i ]->move();
        }
        window.clear();
        window.draw( background );
        window.draw( player );

        for( int i = 0; i < npcTab.size(); i++ )
        {
            window.draw( *npcTab[ i ] );
        }

        for( int i = 0; i < bullets.size(); i++ )
        {
            window.draw( *bullets[ i ] );
        }

        for( int i = 0; i < bullets.size(); i++ )
        {
            if( bullets[ i ]->getPosition().x < 0 || bullets[ i ]->getPosition().x > 800 || bullets[ i ]->getPosition().y < 0 || bullets[ i ]->getPosition().y > 600 )
            {
                delete bullets[ i ];
                bullets.erase( bullets.begin()+i );
            }
        }

        if( !player.getHPpoints() )
        {
            window.close();
        }

        window.display();
        while( clock.getElapsedTime().asMilliseconds() < 20 );
    } //while

    for( int i = 0; i < npcTab.size(); i++ )
    {
        delete npcTab[ i ];
        npcTab.erase( npcTab.begin()+i );
    } // for
    return 0;
}

bool collision( Actor* X, Actor* Y )
{
    float lx = abs( X->getMiddle().x - Y->getMiddle().x );
    float ly = abs( X->getMiddle().y - Y->getMiddle().y );

    if( X->getDimensions().x/2 + Y->getDimensions().x/2 > lx  &&  X->getDimensions().y/2 +  Y->getDimensions().y/2 > ly )
    {
        return true;
    }

    return false;

}

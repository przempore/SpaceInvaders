#include <SFML/Graphics.hpp>
#include "include/Playground.h"
#include "include/NPC.h"
#include "include/Player.h"
#include "include/bullet.h"

bool game( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore );
bool menu( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore );
bool endMenu( sf::RenderWindow& window, Playground& textPoints );
bool collision( Actor* X, Actor* Y );
bool score( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore );
bool enterScore( sf::RenderWindow& scoreWindow, Playground& textPoints );

int main()
{
    // Tworzenie okna gry

    bool isTrue = false;
    bool repeatScore = false;
    do
    {
        sf::RenderWindow window( sf::VideoMode( 800, 600 ), "space Invaders" );
        Playground textPoints;
        textPoints.getScore();
        bool isPlay = true;
        while( isPlay )
        {
            isPlay = menu( window, textPoints, repeatScore );
        }
        isTrue = game( window, textPoints, repeatScore );
        textPoints.resetPoints();
    }while( isTrue );
}

bool game( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore )
{
    // wczytywanie tla gry
    Playground background( sf::Vector2f( 0.f, 0.f ), "img/background.png"  );

    // definiowanie NPC
    const int numOfNpc = 3;
    std::vector<NPC*> npcTab;
    srand( time( NULL ) );
    for( int i = 0; i < numOfNpc; i++ )
    {
        int x = rand() % 755;
        int y = rand() % 553;
        NPC* npc = new NPC( sf::Vector2f( x, y ), "img/monster.png", sf::Vector2f( 45.f, 47.f ) );
        npc->setV( 4.f );
        npcTab.push_back( npc );
    } // for

    // ustawianie Playera
    Player player( sf::Vector2f( 376.f, 565.f ), "img/player.png", sf::Vector2f( 48, 70 ) );
    player.setV( 7.f );

    textPoints.setFont();

    Playground textHP;
    textHP.setFont();
    textHP.text.setPosition( sf::Vector2f( 380.f, 8.f ) );

    // clock do blokowania wykonywania sie zbyt szybko gry
    sf::Clock clock;

//    pasek �ycia
    float hpLineX = 300.f;
    float hpLineY  = 20.f;
    sf::RectangleShape hpLine( sf::Vector2f( hpLineX, hpLineY ) );
    hpLine.setPosition( 500.f, 15.f );
    hpLine.setFillColor( sf::Color::Red );

    // bullets
    std::vector<Bullet*> bullets;

    // bombs
    std::vector<Bullet*> bombs;
    bool isBClicked = false;
    int bombsCount = 0;
    const int maxCountBombs = 5;
    Playground textBombs;
    textBombs.setFont();
    textBombs.text.setPosition( sf::Vector2f( 280.f, 8.f ) );
    Bullet viewBullet( sf::Vector2f( 250.f, 8.f ), "img/bombs/uu.png" );

    Bullet* bonusBomb = NULL;
    bool isBombVisible = false;

    while( window.isOpen() ) // glowna petla programu
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
            } // switch
            Bullet* bull = new Bullet( pos, "img/bullet.png", sf::Vector2f( 4, 18 ), rot );
            bull->setV( 17.f );
            bullets.push_back( bull );
        } // if

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::B ) && !isBClicked )
        {
            Bullet* uu = new Bullet( sf::Vector2f( player.getPosition().x - 15.f, player.getPosition().y - 21.f ), "img/bombs/uu.png", sf::Vector2f( 29.f, 41.f ), 0 );
            uu->setV( 15.f );
            bombs.push_back( uu );
            Bullet* ur = new Bullet( sf::Vector2f( player.getPosition().x - 16.f, player.getPosition().y - 16.f ), "img/bombs/ur.png", sf::Vector2f( 32.f, 32.f ), 45 );
            ur->setV( 15.f );
            bombs.push_back( ur );
            Bullet* rr = new Bullet( sf::Vector2f( player.getPosition().x - 20.f, player.getPosition().y - 15.f ), "img/bombs/uu.png", sf::Vector2f( 40.f, 30.f ), 90 );
            rr->setV( 15.f );
            bombs.push_back( rr );
            Bullet* dr = new Bullet( sf::Vector2f( player.getPosition().x - 16.f, player.getPosition().y - 16.f ), "img/bombs/uu.png", sf::Vector2f( 32.f, 32.f ), 135 );
            dr->setV( 15.f );
            bombs.push_back( dr );
            Bullet* dd = new Bullet( sf::Vector2f( player.getPosition().x - 14.f, player.getPosition().y - 20.f ), "img/bombs/uu.png", sf::Vector2f( 28.f, 39.f ), 180 );
            dd->setV( 15.f );
            bombs.push_back( dd );
            Bullet* dl = new Bullet( sf::Vector2f( player.getPosition().x - 16.f, player.getPosition().y - 16.f ), "img/bombs/uu.png", sf::Vector2f( 33.f, 32.f ), 225 );
            dl->setV( 15.f );
            bombs.push_back( dl );
            Bullet* ll = new Bullet( sf::Vector2f( player.getPosition().x - 20.f, player.getPosition().y - 15.f ), "img/bombs/uu.png", sf::Vector2f( 40.f, 30.f ), 270 );
            ll->setV( 15.f );
            bombs.push_back( ll );
            Bullet* ul = new Bullet( sf::Vector2f( player.getPosition().x - 16.f, player.getPosition().y - 16.f ), "img/bombs/uu.png", sf::Vector2f( 32.f, 32.f ), 315 );
            ul->setV( 15.f );
            bombs.push_back( ul );

            bombsCount++;
            isBClicked = true;
        }

        if( !sf::Keyboard::isKeyPressed( sf::Keyboard::B ) && bombsCount < maxCountBombs )
        {
            isBClicked = false;
        }

        // kolizja
        for( int i = 0; i < npcTab.size(); i++ )
        {
            for( int j = 0; j < bullets.size(); j++ )
            {
                if( collision( npcTab[ i ], bullets[ j ] ) )
                {
                    if( npcTab.size() > 1 )
                    {
                        delete npcTab[ i ];
                        npcTab.erase( npcTab.begin()+i );
                        delete bullets[ j ];
                        bullets.erase( bullets.begin()+j );
                    }
                    textPoints.risePoints();
                    for( int k = 0; k < 2; k++ )
                    {
                        int x = rand() % 755;
                        int y = rand() % 553;
                        NPC* npc = new NPC( sf::Vector2f( x, y ), "img/monster.png", sf::Vector2f( 45.f, 47.f ) );
                        npc->setV( 4.f );
                        npcTab.push_back( npc );
                    } // for
                    if( i % 16 == 0 && !bonusBomb )
                    {
                        isBombVisible = true;
                        bonusBomb = new Bullet( sf::Vector2f( npcTab[ i ]->getPosition().x, npcTab[ i ]->getPosition().y ), "img/bombs/uu.png", sf::Vector2f( 29.f, 41.f ), 0 );
                    }

                } // if
            } // for
        } // for
        if( bonusBomb )
        {
            if( collision( bonusBomb, &player ) )
            {
                bombsCount = 0;
                delete bonusBomb;
                bonusBomb = NULL;
                isBombVisible = false;
            }
        }

        for( int i = 0, npcSize = npcTab.size(); i < npcSize; i++ )
        {
            for( int j = 0, bombsSize = bombs.size(); j < bombsSize; j++ )
            {
                if( collision( npcTab[ i ], bombs[ j ] ) && npcSize > 1 )
                {
                    delete npcTab[ i ];
                    npcTab.erase( npcTab.begin()+i );
                    delete bombs[ j ];
                    bombs.erase( bombs.begin()+j );
                    textPoints.risePoints();
                } // if
            } // for
        } // for

        textPoints.text.setString( "Score: " + textPoints.int2str( textPoints.getPoints() ) );

        for( int i = 0; i < npcTab.size(); i++ )
        {
            if( collision( &player, npcTab[ i ] ) )
            {
                player.reduceHPpoints();
                hpLine.setSize( sf::Vector2f( player.getHPpoints() * 3, hpLineY ) );
            } // if
        } // for



        for( int i = 0; i < bullets.size(); i++ )
        {
            bullets[ i ]->move();
        }

        for( int i = 0; i < bombs.size(); i++ )
        {
            bombs[ i ]->move();
        }

        for( int i = 0; i < npcTab.size(); i++ )
        {
            npcTab[ i ]->move();
        }
        window.clear();
        window.draw( background );
        window.draw( player );
        if( isBombVisible )
        {
            window.draw( *bonusBomb );
        }

        for( int i = 0; i < npcTab.size(); i++ )
        {
            window.draw( *npcTab[ i ] );
        }

        for( int i = 0; i < bullets.size(); i++ )
        {
            window.draw( *bullets[ i ] );
        }

        for( int i = 0; i < bombs.size(); i++ )
        {
            window.draw( *bombs[ i ] );
        }

        for( int i = 0; i < bullets.size(); i++ )
        {
            if( bullets[ i ]->getPosition().x < 0 || bullets[ i ]->getPosition().x > 800 || bullets[ i ]->getPosition().y < 0 || bullets[ i ]->getPosition().y > 600 )
            {
                delete bullets[ i ];
                bullets.erase( bullets.begin()+i );
            } // if
        } // for

        for( int i = 0; i < bombs.size(); i++ )
        {
            if( bombs[ i ]->getPosition().x < 0 - bombs[ i ]->getDimensions().x ||
               bombs[ i ]->getPosition().x > 800 + bombs[ i ]->getDimensions().x ||
               bombs[ i ]->getPosition().y < 0 - bombs[ i ]->getDimensions().y ||
               bombs[ i ]->getPosition().y > 600 + bombs[ i ]->getDimensions().y )
            {
                delete bombs[ i ];
                bombs.erase( bombs.begin()+i );
            }
        } // for


        window.draw( textPoints.text );
        textHP.text.setString( "HP: " + textHP.int2str( player.getHPpoints() ) );
        window.draw( viewBullet );
        window.draw( textHP.text );
        textBombs.text.setString( textBombs.int2str( maxCountBombs - bombsCount ) + "/" + textBombs.int2str( maxCountBombs ) );
        window.draw( textBombs.text );
        window.draw( hpLine );

        if( player.getHPpoints() <= 0.f )
        {
            break;
        }

        window.display();
        while( clock.getElapsedTime().asMilliseconds() < 20 );
    } //while

    repeatScore = true;

    if( window.isOpen() )
    {
        return score( window, textPoints, repeatScore );
    }
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

bool menu( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore )
{
    window.clear();

    Playground menuBackground( sf::Vector2f( 0.f, 0.f ), "img/menuBackground.png" );


    Playground startB( sf::Vector2f( 280.f, 141.f) , "img/np01.gif" );
    startB.setDimensions( sf::Vector2f( 220.f, 66.f ) );
    Playground startBLig( sf::Vector2f( 280.f, 141.f ), "img/p01.gif" );
    startB.setDimensions( sf::Vector2f( 220.f, 66.f ) );

    Playground scoreB( sf::Vector2f( 280.f, 217.f ), "img/np02.gif" );
    scoreB.setDimensions( sf::Vector2f( 220.f, 83.f ) );
    Playground scoreBLig( sf::Vector2f( 280.f, 217.f ), "img/p02.gif" );
    scoreB.setDimensions( sf::Vector2f( 220.f, 83.f ) );

    Playground exitB( sf::Vector2f( 280.f, 310.f ), "img/np03.gif" );
    exitB.setDimensions( sf::Vector2f( 220.f, 69.f ) );
    Playground exitBLig( sf::Vector2f( 280.f, 310.f ), "img/p03.gif" );
    exitB.setDimensions( sf::Vector2f( 220.f, 69.f ) );

    window.draw( menuBackground );
    window.draw( startB );
    window.draw( scoreB );
    window.draw( exitB );

    sf::Event event;
    while( window.pollEvent( event ) )
    {
        if( event.type == sf::Event::Closed )
        {
            window.close();
            return false;
        }
    } // while
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
    {
        window.close();
        return false;
    }

    bool isClicked = sf::Mouse::isButtonPressed( sf::Mouse::Left );
    bool isStartMarked = startB.getPosition().x <= sf::Mouse::getPosition( window ).x &&
                        startB.getPosition().x + startB.getDimensions().x >= sf::Mouse::getPosition( window ).x &&
                        startB.getPosition().y <= sf::Mouse::getPosition( window ).y &&
                        startB.getPosition().y + startB.getDimensions().y >= sf::Mouse::getPosition( window ).y;
    if( isStartMarked )
    {
        window.draw( startBLig );
    }


    if( isStartMarked && isClicked )     // start click
    {
        return false;
    }

    isClicked = sf::Mouse::isButtonPressed( sf::Mouse::Left );
    bool isScoreMarked = scoreB.getPosition().x <= sf::Mouse::getPosition( window ).x &&
                        scoreB.getPosition().x + scoreB.getDimensions().x >= sf::Mouse::getPosition( window ).x &&
                        scoreB.getPosition().y <= sf::Mouse::getPosition( window ).y &&
                        scoreB.getPosition().y + scoreB.getDimensions().y >= sf::Mouse::getPosition( window ).y;
    if( isScoreMarked )
    {
        window.draw( scoreBLig );
    }

    if( isScoreMarked && isClicked )     // start click
    {
        score( window, textPoints, repeatScore );
    }

    bool exitIsMarked = exitB.getPosition().x <= sf::Mouse::getPosition( window ).x &&
                        exitB.getPosition().x + exitB.getDimensions().x >= sf::Mouse::getPosition( window ).x &&
                        exitB.getPosition().y <= sf::Mouse::getPosition( window ).y &&
                        exitB.getPosition().y + exitB.getDimensions().y >= sf::Mouse::getPosition( window ).y;
    if( exitIsMarked )
    {
        window.draw( exitBLig );
        if( isClicked )             // exit click
        {
            window.close();
            return false;
        }
    }

    window.display();

    return true;
}

bool score( sf::RenderWindow& window, Playground& textPoints, bool& repeatScore )
{
    Playground background( sf::Vector2f( 0.f, 0.f ), "img/menuBackground.png" );
    textPoints.text.setPosition( 10, 10 );

    bool isPlay = false;
    while( window.isOpen() )
    {
        window.clear();

        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
            {
                window.close();
            }
        } // while
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
        {
            return true;
        }

        if( !isPlay && repeatScore )
        {
            isPlay = enterScore( window, textPoints );
            repeatScore = false;
            textPoints.setScore();
        } // if
        const int numScores = 10;
        window.draw( background );
        Playground scores[ numScores ];
        for( int i = 0; i < numScores; i++ )
        {
            scores[ i ].setFont();
            scores[ i ].text.setPosition( 15, i * 40 + 50 );
            scores[ i ].text.setString( textPoints.int2str( i+1 ) + ". " + textPoints.getScore( &i ) );
            scores[ i ].text.setColor( sf::Color::Black );
            window.draw( scores[ i ].text );
        } // for

        window.draw( textPoints.text );
        window.display();
    }//while isOpen()
}


bool enterScore( sf::RenderWindow& scoreWindow, Playground& textPoints )
{
    scoreWindow.clear();

    Playground background( sf::Vector2f( 0.f, 0.f ), "img/menuBackground.png" );

    std::string before = textPoints.text.getString();
    for( int i = 0; i < before.length(); i++ )          // zwraca same liczby w score
    {
        if( before[ i ]  == ' ' )
        {
            before = before.substr( i, before.length()-1 );
            break;
        }
    } // for
    textPoints.text.setColor( sf::Color::Black );
    textPoints.text.setString( "Enter Your name: " );
    std::string name = "";
    while( scoreWindow.isOpen() )
    {
        sf::Event event;
        while( scoreWindow.pollEvent( event ) )
        {
            if( event.type == sf::Event::TextEntered)
            {
                if( event.text.unicode >= 33 && event.text.unicode <= 126 )
                {
                    name += (char)event.text.unicode;
                    textPoints.text.setString( name );
                    scoreWindow.draw( textPoints );
                } // if
                else if( event.text.unicode == 8 )
                {
                    name = name.substr( 0, name.length() - 1 );
                    textPoints.text.setString( name );
                    scoreWindow.draw( textPoints );

                } // else if
                else if( event.text.unicode == 20 )
                {
                    name += " ";
                    textPoints.text.setString( name );
                    scoreWindow.draw( textPoints );
                } //else if
                break;
            } // switch
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
            {
                if( name != "" )
                {
                    std::string s = textPoints.text.getString() + " " + before;
                    textPoints.text.setString( s );
                }
                else
                {
                    textPoints.text.setString( "" );
                }
                return true;
            } // if
        } // while
        scoreWindow.draw( background );
        scoreWindow.draw( textPoints.text );
        scoreWindow.display();
    } // while

    return false;
}

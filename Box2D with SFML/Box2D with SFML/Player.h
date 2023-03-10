#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

//For updating the score of the player 

class Player {
    Font font;
    Text scoreText;
    int score;

public:
    //Constructor
    Player();
    //Getting the curr score
    int getScore();
    //Increase the score by 1 when brick is destroyed by the ball
    void increaseScore();
    //updating the score
    void update(RenderWindow& window);
    //Drawing
    void draw(RenderWindow& window);
};

#endif
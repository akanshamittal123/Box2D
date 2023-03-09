#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

class Player {
    Font font;
    Text scoreText;
    int score;

public:
    Player();
    int getScore();
    void increaseScore();
    void update(RenderWindow& window);
    void draw(RenderWindow& window);
};

#endif
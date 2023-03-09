#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.h"

using namespace std;
using namespace sf;

class Brick {
    int numBricks;
    float brickWidth;
    float brickHeight;
    vector<b2Body*>bricks;
    Sprite brick;
    Texture brickTex;

public:
    Brick(float brickWidth, float brickHeight);
    void createBricks(float numBricks, b2World& world, RenderWindow& window);
    void destroy(b2World& world, Player& player);
    float getNumBricks();
    void draw(RenderWindow& window);
};
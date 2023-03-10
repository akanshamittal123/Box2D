#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.h"

using namespace std;
using namespace sf;

//Bricks that is meant to be destroyed

class Brick {
    int numBricks;
    float brickWidth;
    float brickHeight;
    vector<b2Body*>bricks;
    Sprite brick;
    Texture brickTex;

public:
    //Constructor
    Brick();
    //creating the bricks
    void createBricks(float numBricks, b2World& world, RenderWindow& window);
    //destroying the bricks after getting hit by the balls
    void destroy(b2World& world, Player& player);
    //getting Bricks
    float getNumBricks();
    //Drawing
    void draw(RenderWindow& window);
};
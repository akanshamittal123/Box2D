#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

class Paddle {
    Sprite paddle;
    Texture paddleTex;
    b2Body* paddleBody;
    float paddleWidth;
    float paddleHeight;

public:
    Paddle(b2World& world);
    void move(float x);
    b2Vec2 getPos();
    b2Body* getBody();
    void draw(RenderWindow& window);
};
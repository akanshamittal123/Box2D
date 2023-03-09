#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

class BoundaryWalls {
    vector<b2Body*>boundaryWalls;
public:
    void createBoundaryWalls(b2World& world, float x, float y);
    void draw(RenderWindow& window);
};

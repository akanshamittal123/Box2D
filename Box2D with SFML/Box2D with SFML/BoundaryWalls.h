#ifndef BOUNDARYWALLS_H
#define BOUNDARYWALLS_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

//boundary wall to prevent balls going out of the window

using namespace std;
using namespace sf;

class BoundaryWalls {
    vector<b2Body*>boundaryWalls;
public:
    //creating the boundaryWalls and pushing it in the vector
    void createBoundaryWalls(b2World& world, float x, float y);
    //getting the Walls
    vector<b2Body*> getWalls();
    //Drawing
    void draw(RenderWindow& window);
};

#endif

#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace sf;

//To handle the collison of bodies
class MyContactListener : public b2ContactListener
{
public:
    vector<b2Body*> balls;
    b2Body* paddleBody;
    vector<b2Body*>boundaryWalls;
    //to store the magnitude of the velocity of the ball
    float velocityMagnitude = 0.f;
    bool hasContact = false;
    // handles different conditions of collision
    void BeginContact(b2Contact* contact)override;
};

#endif

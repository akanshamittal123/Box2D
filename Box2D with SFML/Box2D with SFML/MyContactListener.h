#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace sf;

class MyContactListener : public b2ContactListener
{
public:
    vector<b2Body*> balls;
    b2Body* paddleBody;
    bool hasContact = false;
    void BeginContact(b2Contact* contact)override;
};

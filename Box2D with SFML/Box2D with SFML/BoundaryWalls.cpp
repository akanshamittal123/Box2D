#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "BoundaryWalls.h"

using namespace std;
using namespace sf;


void BoundaryWalls::createBoundaryWalls(b2World& world, float x, float y) {
    b2BodyDef boundaryDef;
    boundaryDef.type = b2_staticBody;
    boundaryDef.position.Set(0.f, 0.f);

    boundaryWalls.push_back(world.CreateBody(&boundaryDef));

    b2PolygonShape boundaryShape1;
    boundaryShape1.SetAsBox(1.f, y);
    b2FixtureDef boundaryFixtureDef;
    boundaryFixtureDef.shape = &boundaryShape1;
    boundaryFixtureDef.friction = 0.8f;
    boundaryWalls[0]->CreateFixture(&boundaryFixtureDef);

    boundaryWalls.push_back(world.CreateBody(&boundaryDef));

    b2PolygonShape boundaryShape2;
    boundaryShape2.SetAsBox(x, 1.f);
    boundaryFixtureDef.shape = &boundaryShape2;
    boundaryWalls[1]->CreateFixture(&boundaryFixtureDef);

    boundaryDef.position.Set(x - 2.f, 0.f);
    boundaryWalls.push_back(world.CreateBody(&boundaryDef));

    b2PolygonShape boundaryShape3;
    boundaryShape3.SetAsBox(1.f, y);
    boundaryFixtureDef.shape = &boundaryShape3;
    boundaryWalls[2]->CreateFixture(&boundaryFixtureDef);
}

void BoundaryWalls::draw(RenderWindow& window) {
    for (int i = 0; i < boundaryWalls.size(); i++) {
        RectangleShape boundaryWallSFML;
        if (i == 1) {
            boundaryWallSFML.setSize(Vector2f{ (float)window.getSize().x, 2.f });
        }
        else {
            boundaryWallSFML.setSize(Vector2f{ 2.f, (float)window.getSize().y });
        }
        boundaryWallSFML.setPosition(boundaryWalls[i]->GetPosition().x, boundaryWalls[i]->GetPosition().y);
        window.draw(boundaryWallSFML);
    }
}


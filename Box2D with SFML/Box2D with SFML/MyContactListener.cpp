#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "MyContactListener.h"

using namespace std;
using namespace sf;


void MyContactListener::BeginContact(b2Contact* contact)
{
    //bodies which are facing collision at the curr time
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    //For each ball
    for (int i = 0; i < balls.size(); i++) {
        //pass any other collision other than that which involves balls
        if (fixtureA->GetBody() != balls[i] && fixtureB->GetBody() != balls[i])continue;
        //between ball and paddle
        if (fixtureA->GetBody() == balls[i]) {
            if (fixtureB->GetBody() == paddleBody) {
                balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
            }
            else {
                bool isThere1 = false , isThere2 = false;
                //with other balls collision
                for (int j = 0; j < balls.size(); j++) {
                    if (j != i && fixtureB->GetBody() == balls[j]) {
                        isThere1 = true;
                        b2Vec2 direction = balls[i]->GetPosition() - balls[j]->GetPosition();
                        direction.Normalize();
                        
                        b2Vec2 velocity = velocityMagnitude * direction;
                        cout << velocity.x << " " << velocity.y << endl;
                        balls[i]->SetLinearVelocity(-velocity);
                        balls[j]->SetLinearVelocity(velocity);
                        break;
                    }
                }
                //with the boundaries
                for (int j = 0; j < boundaryWalls.size(); j++) {
                    if (fixtureB->GetBody() == boundaryWalls[j]) {
                        isThere2 = true;
                        b2Vec2 ballVelocity = balls[i]->GetLinearVelocity();
                        if (j == 0) {
                            ballVelocity.x = abs(ballVelocity.x);
                        }
                        else {
                            if (j == 1) {
                                ballVelocity.y = abs(ballVelocity.y);
                            }
                            else {
                                ballVelocity.x = -abs(ballVelocity.x);
                            }
                        }
                        balls[i]->SetLinearVelocity(ballVelocity);
                        break;
                    }
                }

                //with the bricks
                if (!isThere1 && !isThere2) {
                    balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
                    fixtureB->GetBody()->SetLinearVelocity(b2Vec2{ 2.f, 0.f });
                }
            }
        }
        else {
            //between ball and paddle
            if (fixtureA->GetBody() == paddleBody) {
                balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());

            }
            else {
                bool isThere1 = false, isThere2 =false;
                //with other balls collision
                for (int j = 0; j < balls.size(); j++) {
                    if (j != i && fixtureA->GetBody() == balls[j]) {
                        isThere1 = true;
                        b2ContactEdge* edge = balls[i]->GetContactList();
                        b2Manifold* manifold = edge->contact->GetManifold();
                        b2Vec2 normal = manifold->localNormal;
                        b2Vec2 direction = balls[i]->GetPosition() - balls[j]->GetPosition();
                        direction.Normalize();
                        b2Vec2 velocity = velocityMagnitude * direction;
                        balls[i]->SetLinearVelocity(-velocity);
                        balls[j]->SetLinearVelocity(velocity);
                        break;
                    }
                }
                //with the boundaries
                for (int j = 0; j < boundaryWalls.size(); j++) {
                    if (fixtureA->GetBody() == boundaryWalls[j]) {
                        isThere2 = true;
                        b2Vec2 ballVelocity = balls[i]->GetLinearVelocity();
                        if (j == 0) {
                            ballVelocity.x = abs(ballVelocity.x);
                        }
                        else {
                            if (j == 1) {
                                ballVelocity.y = abs(ballVelocity.y);
                            }
                            else {
                                ballVelocity.x = -abs(ballVelocity.x);
                            }
                        }
                        balls[i]->SetLinearVelocity(ballVelocity);

                        break;
                    }
                }
                //between balls and bricks
                if (!isThere1 && !isThere2) {
                    balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
                    fixtureA->GetBody()->SetLinearVelocity(b2Vec2{ 2.f, 0.f });

                }
            }
        }
    }
}
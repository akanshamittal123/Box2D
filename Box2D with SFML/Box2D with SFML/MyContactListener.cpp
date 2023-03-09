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

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    for (int i = 0; i < balls.size(); i++) {
        if (fixtureA->GetBody() != balls[i] && fixtureB->GetBody() != balls[i])continue;
        if (fixtureA->GetBody() == balls[i]) {
            if (fixtureB->GetBody() == paddleBody) {
                balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
            }
            else {
                bool isThere = false;
                //with other balls collision
                for (int j = 0; j < balls.size(); j++) {
                    if (j != i && fixtureB->GetBody() == balls[j]) {
                        isThere = true;
                        b2ContactEdge* edge = fixtureA->GetBody()->GetContactList();
                        b2Contact* contact = edge->contact;
                        b2Manifold* manifold = (contact->GetManifold());

                        b2Vec2 normal = manifold->localNormal;
                        cout << manifold->points->localPoint.x << " " << manifold->points->localPoint.y << endl;
                        b2Vec2 direction = balls[i]->GetLinearVelocity() - balls[j]->GetLinearVelocity();
                        direction.Normalize();
                        float velocityMagnitude = 100.f;
                        b2Vec2 velocity = velocityMagnitude * direction;
                        cout << velocity.x << " " << velocity.y << endl;
                        balls[i]->SetLinearVelocity(velocity);
                        balls[j]->SetLinearVelocity(-velocity);
                        break;
                    }
                }
                if (!isThere) {
                    balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
                    fixtureB->GetBody()->SetLinearVelocity(b2Vec2{ 2.f, 0.f });
                }
            }
        }
        else {
            if (fixtureA->GetBody() == paddleBody) {
                balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());

            }
            else {
                bool isThere = false;
                for (int j = 0; j < balls.size(); j++) {
                    if (j != i && fixtureA->GetBody() == balls[j]) {
                        isThere = true;
                        b2ContactEdge* edge = balls[i]->GetContactList();
                        b2Manifold* manifold = edge->contact->GetManifold();
                        b2Vec2 normal = manifold->localNormal;
                        b2Vec2 direction = balls[i]->GetLinearVelocity() - balls[j]->GetLinearVelocity();;
                        direction.Normalize();
                        float velocityMagnitude = 100.f;
                        b2Vec2 velocity = velocityMagnitude * direction;
                        balls[i]->SetLinearVelocity(velocity);
                        balls[j]->SetLinearVelocity(-velocity);
                        break;
                    }
                }
                if (!isThere) {
                    balls[i]->SetLinearVelocity(-balls[i]->GetLinearVelocity());
                    fixtureA->GetBody()->SetLinearVelocity(b2Vec2{ 2.f, 0.f });

                }
            }
        }
    }
}
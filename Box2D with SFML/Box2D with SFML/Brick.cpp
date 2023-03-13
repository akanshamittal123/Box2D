#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Brick.h"

using namespace std;
using namespace sf;


Brick::Brick() {
    if (brickTex.loadFromFile("brick.png")) {
        brick.setTexture(brickTex);
    }
    brick.setScale(0.05f, 0.05f);
    brickWidth = brick.getGlobalBounds().width;
    brickHeight = brick.getGlobalBounds().height;
    font.loadFromFile("yess.ttf");
    brickText.setFont(font);
    brickText.setCharacterSize(20);
    brickText.setFillColor(Color::White);
}

void Brick::createBricks(float numBricks, b2World& world, RenderWindow& window) {
    this->numBricks = numBricks;
    for (int i = 0; i < numBricks; i++)
    {
        b2BodyDef brickDef;
        brickDef.type = b2_dynamicBody;
        brickDef.position.Set(rand() % (int)(window.getSize().x), rand() % (int)(window.getSize().y - 150.f));
        b2Body* brickBody = world.CreateBody(&brickDef);
        b2PolygonShape brickShape;
        brickShape.SetAsBox(brickWidth / 2, brickHeight / 2);
        b2FixtureDef brickFixtureDef;
        brickFixtureDef.shape = &brickShape;
        brickFixtureDef.restitution = 1.0f;
        brickFixtureDef.friction = 0.0f;
        brickBody->CreateFixture(&brickFixtureDef);
        bricks.push_back({ brickBody, (rand() % 9) + 1 });
    }
}

void Brick::destroy(b2World& world, Player& player) {
    int count = 0;
    for (int i = 0; i < bricks.size(); i++) {
        b2Vec2 velo = { 2.f, 0.f };
        if (bricks[i].first->GetLinearVelocity() == velo) {
            if (bricks[i].second > 1) {
                bricks[i].second--;
                bricks[i].first->SetLinearVelocity({ 0.f,0.f });
            }
            else {
                player.increaseScore();
                world.DestroyBody(bricks[i].first);
                bricks.erase(bricks.begin() + i);
                break;
            }
        }
    }
}

float Brick::getNumBricks() {
    return numBricks;
}

void Brick::draw(RenderWindow& window) {
    for (int i = 0; i < bricks.size(); i++) {

        brickText.setString(to_string(bricks[i].second));
        brick.setPosition(bricks[i].first->GetPosition().x, bricks[i].first->GetPosition().y);
        brickText.setPosition(bricks[i].first->GetPosition().x + brickWidth/3, bricks[i].first->GetPosition().y + brickHeight/3);
        window.draw(brick);
        window.draw(brickText);
    }
}

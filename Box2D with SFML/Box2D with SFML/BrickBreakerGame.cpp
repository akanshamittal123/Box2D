#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "MyContactListener.h"
#include "Ball.h"
#include "Paddle.h"
#include "Player.h"
#include "Brick.h"
#include "BoundaryWalls.h"

using namespace std;
using namespace sf;

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Brick Breaker Quest");
    window.setFramerateLimit(160);

    // Create the Box2D world
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    b2Vec2 force(0, -100.f);



    // Create the ball and the paddle using Box2D

    Ball ball;

    Paddle paddle(world);

    BoundaryWalls boundaryWalls;
    boundaryWalls.createBoundaryWalls(world, window.getSize().x, window.getSize().y);


    // Create the bricks using Box2D
    Brick brick(60.f, 20.f);
    brick.createBricks(50, world, window);

    Player player;
    MyContactListener contactListener;

    // Game loop
    float timestep = 1.f / 60.f;
    float numBricks = brick.getNumBricks();
    while (window.isOpen() && player.getScore() < numBricks)
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update the Box2D world
        //float deltaTime = clock.restart().asSeconds();
        world.Step(timestep, 6, 2);

        paddle.move(window.getSize().x);
        b2Vec2 paddlePos = paddle.getPos();

        ball.fire(paddlePos.x, paddlePos.y, world, force);

        contactListener.balls = ball.getBalls();
        contactListener.paddleBody = paddle.getBody();
        world.SetContactListener(&contactListener);
        ball.setBalls(contactListener.balls);


        brick.destroy(world, player);

        // Draw the bricks and the paddle and balls
        window.clear();



        ball.draw(window);
        // Update the ball position and play sound if it bounces

        brick.draw(window);

        paddle.draw(window);
        player.update(window);
        player.draw(window);

        boundaryWalls.draw(window);

        // Display the window
        window.display();

    }

    // Cleanup

    return 0;
}
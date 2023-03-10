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
    // Creating the window for rendering
    sf::RenderWindow window(sf::VideoMode(800, 600), "Brick Breaker Quest");
    window.setFramerateLimit(260);

    // Creating the Box2D world
    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);


    // Creating the ball 
    Ball ball;

    // Creating the paddle
    Paddle paddle(world);

    //Defining velocity Magnitude of the balls
    float velocityMag = 100.f;

    //Creating the boundaries
    BoundaryWalls boundaryWalls;
    boundaryWalls.createBoundaryWalls(world, window.getSize().x, window.getSize().y);
    vector<b2Body*>bWalls = boundaryWalls.getWalls();

    // Creating the bricks
    Brick brick;
    brick.createBricks(50, world, window);

    //Defining the player(which has its score)
    Player player;

    //defining the class to care of collision 
    MyContactListener contactListener;
    contactListener.velocityMagnitude = velocityMag;

    //Defining the time step for the box2d to render   
    float timestep = 1.f / 60.f;

    float numBricks = brick.getNumBricks();

    // Game loop
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

        // Updating the Box2D world
        world.Step(timestep, 6, 2);

        //movement of the paddle
        paddle.move(window.getSize().x);

        //the mechanism of firing of the balls
        b2Vec2 paddlePos = paddle.getPos();
        ball.fire(paddlePos.x, paddlePos.y, world,window, velocityMag);

        //setting the contact Listener for bodies
        contactListener.balls = ball.getBalls();
        contactListener.paddleBody = paddle.getBody();
        contactListener.boundaryWalls = bWalls;
        world.SetContactListener(&contactListener);
        ball.setBalls(contactListener.balls);

        //destroying the brick which has been hit by the balls
        brick.destroy(world, player);


        //clearing the window
        window.clear();

        //drawing the bodies
        ball.draw(window);
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
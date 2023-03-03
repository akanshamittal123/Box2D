#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rope");
    window.setFramerateLimit(160);
    // Create the Box2D world
    b2Vec2 gravity(0.1f, 9.8f);
    b2World world(gravity);

    // Create a ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f, 590.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Create a ground shape
    b2PolygonShape groundShape;
    groundShape.SetAsBox(400.0f, 10.0f);

    // Create a ground fixture
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 0.0f;
    groundFixtureDef.friction = 1.0f;
    groundBody->CreateFixture(&groundFixtureDef);

    // Create a rope
    const int NUM_LINKS = 10;
    const float LINK_RADIUS = 10.0f;
    const float LINK_DENSITY = 1.f;
    const float LINK_FRICTION = 0.2f;
    float ROPE_LENGTH = NUM_LINKS * (LINK_RADIUS * 2);
    const float ROPE_START_X = 400.0f;
    const float ROPE_START_Y = 50.0f;

    b2Body* prevBody = nullptr, * mainP = nullptr;
    //vector<b2Body*>segments(10);
    for (int i = 0; i < NUM_LINKS; i++) {
        
        // Create a body definition
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(ROPE_START_X, ROPE_START_Y + i * (2 * LINK_RADIUS));

        b2Body* body = world.CreateBody(&bodyDef);

        // Create a circle shape
        b2CircleShape shape;
        shape.m_radius = LINK_RADIUS;
        
        // Create a fixture definition
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = LINK_DENSITY;
        fixtureDef.friction = LINK_FRICTION;

        // Create a joint definition
        if (prevBody != nullptr) {
            /*b2RevoluteJointDef jointDef;
            jointDef.localAnchorA.Set(0.0f, LINK_RADIUS);
            jointDef.localAnchorB.Set(0.0f, -LINK_RADIUS);
            jointDef.bodyA = prevBody;
            jointDef.bodyB = body;
            world.CreateJoint(&jointDef);*/
            b2DistanceJointDef jointDef;
            jointDef.Initialize(prevBody, body, prevBody->GetWorldCenter(), body->GetWorldCenter());
            jointDef.length = 100.f;
            jointDef.stiffness = 0.0f;
            jointDef.collideConnected = true;
            jointDef.damping = 0.5f;
            /*jointDef.frequencyHz = 2.0f;
            jointDef.dampingRatio = 0.1f;*/
            world.CreateJoint(&jointDef);
        }

        // Create the fixture and joint
        body->CreateFixture(&fixtureDef);

        // Update the previous body
        prevBody = body;
    }

    // Create a circle to represent the end of the rope
    sf::CircleShape end(LINK_RADIUS);
    end.setFillColor(sf::Color::Color(245,245,220));
    end.setOrigin(LINK_RADIUS, LINK_RADIUS);

    // Run the game loop
    sf::Clock clock;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        world.Step(1.0f / 60.f, 8, 3);
        // Clear the window
        window.clear(sf::Color::Color(173,216,250));

        // Draw the ground
        sf::RectangleShape ground(sf::Vector2f(800.0f, 20.0f));
        ground.setFillColor(sf::Color::Color(101,67,33));
        ground.setOrigin(400.0f, 10.0f);
        ground.setPosition(groundBody->GetPosition().x, groundBody->GetPosition().y);
        //ground.setRotation(groundBody->GetAngle() * 180.0f / b2_pi);
        window.draw(ground);

        // Draw the rope
        b2Body* body = prevBody;
        //cout << mainP->GetNext()<< endl;
        for (int i = 0; i < NUM_LINKS; i++) {
            // Get the position of the link
            b2Vec2 pos = body->GetPosition();

            // Create a circle to represent the link
            sf::CircleShape link(LINK_RADIUS);
            link.setFillColor(sf::Color::Color(245, 245, 220));
            link.setOrigin(LINK_RADIUS, LINK_RADIUS);
            link.setPosition(pos.x, pos.y);
            window.draw(link);

            // Update the body
            body = body->GetNext();
        }


        // Draw the end of the rope
        b2Vec2 pos = prevBody->GetPosition();
        end.setPosition(pos.x, pos.y);
        window.draw(end);

        // Update the Box2D world
        /*float dt = clock.restart().asSeconds();
        world.Step(dt, 6, 2);*/

        // Display the window
        window.display();
    }

    return 0;
}

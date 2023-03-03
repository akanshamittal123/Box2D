//#include<iostream>
//#include<string>
//#include"SFML/Graphics.hpp"
//#include"SFML/Window.hpp"
//#include"SFML/System.hpp"
//#include"box2d/box2d.h"
//using namespace sf;
//
//class MyContactListener : public b2ContactListener {
//public:
//    void BeginContact(b2Contact* contact) override {
//        b2Fixture* fixtureA = contact->GetFixtureA();
//        b2Fixture* fixtureB = contact->GetFixtureB();
//
//        // Check if either fixture is a ball
//        if (fixtureA->GetUserData().pointer == reinterpret_cast<uintptr_t>("Ball") ||
//            fixtureB->GetUserData().pointer == reinterpret_cast<uintptr_t>("Ball")) {
//            // Handle ball collision here
//            std::cout << "Ball collided with another object" << std::endl;
//        }
//    }
//
//    void EndContact(b2Contact* contact) override {
//        // Handle end of contact here if necessary
//    }
//
//    // Implement other methods of b2ContactListener as needed
//};
//struct MyFixtureData {
//    std::string myString;
//};
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D + SFML Collision");
//    //window.setFramerateLimit(60);
//    // Set up Box2D world
//    b2Vec2 gravity(0.0f, 4.8f);
//    b2World world(gravity);
//    MyContactListener contactListener;
//    world.SetContactListener(&contactListener);
//
//    // Create ground body
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, 550.0f);
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//
//    b2PolygonShape groundShape;
//    groundShape.SetAsBox(400.0f, 200.0f);
//    b2FixtureDef groundFixtureDef;
//    groundFixtureDef.shape = &groundShape;
//    groundFixtureDef.density = 0.0f;
//    groundFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(const_cast<char*>("Ground"));
//    groundBody->CreateFixture(&groundFixtureDef);
//
//    // Create ball body
//    b2BodyDef ballBodyDef;
//    ballBodyDef.type = b2_dynamicBody;
//    ballBodyDef.position.Set(200.0f, 0.0f);
//    b2Body* ballBody = world.CreateBody(&ballBodyDef);
//    b2CircleShape ballShape;
//    ballShape.m_radius = 20.0f;
//    b2FixtureDef ballFixtureDef;
//    ballFixtureDef.shape = &ballShape;
//    ballFixtureDef.density = 1.0f;
//    ballFixtureDef.restitution = 0.8f;
//    ballFixtureDef.friction = 0.2f;
//
//    ballFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(const_cast<char*>("Ball"));
//
//
//    ballBody->CreateFixture(&ballFixtureDef);
//
//    // Set up SFML circle shape for ball
//    sf::CircleShape ball((20.0f, 20.0f));
//    ball.setFillColor(sf::Color::Green);
//
//    // Main game loop
//    while (window.isOpen()) {
//        // Handle SFML events
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        // Update Box2D world
//        world.Step(1.0f / 60.0f, 8, 3);
//
//        // Update SFML circle shape for ball
//        ball.setPosition(ballBody->GetPosition().x, ballBody->GetPosition().y);
//
//        // Clear the window and draw SFML objects
//        window.clear(sf::Color::White);
//        window.draw(ball);
//        window.display();
//    }
//
//    return 0;
//}
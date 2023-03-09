//#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
//#include "Ground.h"
//#include "Link.h"
//#include "Rope.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Rope Simulator");
//    window.setFramerateLimit(200);
//
//    b2Vec2 gravity(0.1f, 9.81f);
//    b2World world(gravity);
//
//    Ground ground(world, 400.0f, 590.0f, 400.0f, 10.0f);
//
//    Rope rope(world, 10, 400.0f, 100.0f, 1.f, 1.2f);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        world.Step(1.0f / 60.0f, 6, 2);
//
//        window.clear(sf::Color::Color(176,224,230));
//
//        ground.draw(window);
//        rope.draw(window);
//
//        window.display();
//    }
//
//    return 0;
//}
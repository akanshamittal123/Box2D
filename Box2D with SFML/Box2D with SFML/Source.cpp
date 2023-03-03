#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ground {
public:
    Ground(b2World& world, float x, float y, float width, float height) {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(x, y);
        body = world.CreateBody(&groundBodyDef);

        b2PolygonShape groundShape;
        groundShape.SetAsBox(width, height);

        b2FixtureDef groundFixtureDef;
        groundFixtureDef.shape = &groundShape;
        groundFixtureDef.density = 5.0f;
        groundFixtureDef.friction = 10.0f;
        body->CreateFixture(&groundFixtureDef);
    }

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape ground(sf::Vector2f(width * 2.0f, height * 2.0f));
        ground.setFillColor(sf::Color::Color(101, 67, 33));
        ground.setOrigin(width, height);
        ground.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(ground);
    }

private:
    b2Body* body;
    float width = 400.0f;
    float height = 10.0f;
};

class Link {
public:
    Link(b2World& world, b2Body* prevBody, float x, float y, float radius, float density, float friction) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);

        body = world.CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;

        if (prevBody != nullptr) {
            b2DistanceJointDef jointDef;
            jointDef.Initialize(prevBody, body, prevBody->GetWorldCenter(), body->GetWorldCenter());
            jointDef.length = 100.f;
            jointDef.stiffness = 0.0f;
            jointDef.collideConnected = true;
            jointDef.damping = 0.5f;
            world.CreateJoint(&jointDef);
        }

        body->CreateFixture(&fixtureDef);
    }

    void draw(sf::RenderWindow& window) const {
        b2Vec2 pos = body->GetPosition();
        sf::CircleShape link(radius);
        link.setFillColor(sf::Color::Color(205, 133, 63));
        link.setOrigin(radius, radius);
        link.setPosition(pos.x, pos.y);
        window.draw(link);
    }

    b2Body* getBody() const { return body; }

private:
    b2Body* body;
    float radius = 10.0f;
};

class Rope {
public:
    Rope(b2World& world, int numLinks, float startX, float startY, float linkDensity, float linkFriction) {
        const float linkRadius = 10.0f;
        const float ropeLength = numLinks * (linkRadius * 2);
        b2Body* prevBody = nullptr;

        for (int i = 0; i < numLinks; i++) {
            Link link(world, prevBody, startX, startY + i * (2 * linkRadius), linkRadius, linkDensity, linkFriction);
            links.push_back(link);
            prevBody = link.getBody();
        }
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& link : links) {
            link.draw(window);
        }
    }

    std::vector<Link>& getLinks() { return links; }

private:
    std::vector<Link> links;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rope Simulator");
    /* window.setFramerateLimit(120);*/

    b2Vec2 gravity(0.1f, 9.81f);
    b2World world(gravity);

    Ground ground(world, 400.0f, 590.0f, 400.0f, 10.0f);

    Rope rope(world, 10, 400.0f, 100.0f, 1.f, 1.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        world.Step(1.0f / 60.0f, 6, 2);

        window.clear(sf::Color::White);

        ground.draw(window);
        rope.draw(window);

        window.display();
    }

    return 0;
}
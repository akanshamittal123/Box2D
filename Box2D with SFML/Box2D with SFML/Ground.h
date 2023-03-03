#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Ground {
public:
    Ground(b2World& world, float x, float y, float width, float height);

    void draw(sf::RenderWindow& window) const;

private:
    b2Body* body;
    float width = 400.0f;
    float height = 10.0f;
};

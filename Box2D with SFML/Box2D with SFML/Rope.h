#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Link.h"

class Rope {
public:
    Rope(b2World& world, int numLinks, float startX, float startY, float linkDensity, float linkFriction);

    void draw(sf::RenderWindow& window) const;

    std::vector<Link>& getLinks();

private:
    std::vector<Link> links;
};

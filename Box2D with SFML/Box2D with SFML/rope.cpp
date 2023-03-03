#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Rope.h"
#include "Link.h"

Rope::Rope(b2World& world, int numLinks, float startX, float startY, float linkDensity, float linkFriction) {
    const float linkRadius = 10.0f;
    const float ropeLength = numLinks * (linkRadius * 2);
    b2Body* prevBody = nullptr;

    for (int i = 0; i < numLinks; i++) {
        Link link(world, prevBody, startX, startY + i * (2 * linkRadius), linkRadius, linkDensity, linkFriction);
        links.push_back(link);
        prevBody = link.getBody();
    }
}

void Rope::draw(sf::RenderWindow& window) const {
    for (const auto& link : links) {
        link.draw(window);
    }
}

std::vector<Link>& Rope::getLinks() { return links; }
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.h"

using namespace std;
using namespace sf;


Player::Player() {
    font.loadFromFile("yess.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    score = 0;
}

int Player::getScore() {
    return score;
}

void Player::increaseScore() {
    score++;
}

void Player::update(RenderWindow& window) {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width - 10.0f, 10.0f);
}
void Player::draw(RenderWindow& window) {
    window.draw(scoreText);
}

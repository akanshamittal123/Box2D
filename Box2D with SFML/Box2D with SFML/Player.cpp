#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Player.h"

using namespace std;
using namespace sf;

//For updating the score of the player 

//Constructor
Player::Player() {
    font.loadFromFile("yess.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    score = 0;
}

//Getting the curr score
int Player::getScore() {
    return score;
}

//Increase the score by 1 when brick is destroyed by the ball
void Player::increaseScore() {
    score++;
}

//updating the score
void Player::update(RenderWindow& window) {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width - 10.0f, 10.0f);
}

//Drawing
void Player::draw(RenderWindow& window) {
    window.draw(scoreText);
}

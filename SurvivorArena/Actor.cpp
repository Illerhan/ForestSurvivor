#include "Actor.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Actor::Actor()
= default;

void Actor::update(float deltaTime)
{
	sf::FloatRect bounds = sprite_.getGlobalBounds();
	float centerX = bounds.left + bounds.width / 2;
	float centerY = bounds.top + bounds.height / 2;
	hitBoxPosition_ = sf::Vector2f(centerX,centerY);
	hitBox_.setPosition(hitBoxPosition_);
}

void Actor::display(sf::RenderWindow& window)
{
	window.draw(sprite_);
	
}

bool Actor::checkCollision(const sf::RectangleShape& other) const {
	// Get the bounds of the bullet's hitbox and the other rectangle
	sf::FloatRect bulletBounds = hitBox_.getGlobalBounds();
	sf::FloatRect otherBounds = other.getGlobalBounds();

	// Check if the two rectangles intersect
	return bulletBounds.intersects(otherBounds);
}


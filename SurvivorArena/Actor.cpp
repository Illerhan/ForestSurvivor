#include "Actor.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Actor::Actor()
= default;

void Actor::update(float deltaTime)
{
}

void Actor::display(sf::RenderWindow& window)
{
	window.draw(sprite_);

}

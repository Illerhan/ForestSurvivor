#include "Weapon.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

Weapon::Weapon(DmgType type): type_(type)
{
	spriteRectPostion_ = sf::IntRect(0,0,210.f,92.f);
	switch (type_)
	{
	case Simple:
		if (!texture_.loadFromFile("src/sprites/Weapons/Simple.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,210.f,92.f);
		sprite_ = sf::Sprite(texture_,spriteRectPostion_);
		break;
	case DoT:
		if (!texture_.loadFromFile("src/sprites/Weapons/DoT.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,190.f,76.f);
		sprite_ = sf::Sprite(texture_,spriteRectPostion_);
		break;
	case Perforing:
		if (!texture_.loadFromFile("src/sprites/Weapons/Perforing.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		sprite_ = sf::Sprite(texture_,spriteRectPostion_);
		break;
	case Explosive:
		if (!texture_.loadFromFile("src/sprites/Weapons/Explosive.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,256.f,156.f);
		sprite_ = sf::Sprite(texture_,spriteRectPostion_);
		break;
	}
	
	speed_ = 150.f;
	position_ = sf::Vector2f(150.f,250.f);
	sprite_.setTexture(texture_);
	sprite_.setPosition(position_);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(0.5f,0.5f));

	border_.setSize(sf::Vector2f(spriteRectPostion_.width * 0.5f + 4.f, 
								spriteRectPostion_.height * 0.5f + 4.f)); // Border size slightly larger than the sprite
	border_.setFillColor(sf::Color::Transparent); // Make it transparent
	border_.setOutlineColor(sf::Color::Red);      // Red outline color
	border_.setOutlineThickness(2.f);  
}

void Weapon::update(float deltaTime)
{
	sprite_.setTextureRect(spriteRectPostion_);
	sprite_.setPosition(position_);
	border_.setPosition(sprite_.getPosition().x - 2.f, sprite_.getPosition().y - 2.f);
	Actor::update(deltaTime);
}

void Weapon::display(sf::RenderWindow& window)

{
	window.draw(border_);
	Actor::display(window);
}


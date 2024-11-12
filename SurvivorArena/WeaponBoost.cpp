#include "WeaponBoost.h"

#include <iostream>

WeaponBoost::WeaponBoost(sf::Vector2f position): newSpeed_(0), newDmg(0)
{
	int rand = std::rand()%100;
	if( 0 <= rand && rand < 25)
	{
		type_ = Simple;
		if (!texture_.loadFromFile("src/sprites/Weapons/Simple.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,210.f,92.f);
	}

	if( 25 <= rand && rand  < 50)
	{
		type_ = Explosive;
		if (!texture_.loadFromFile("src/sprites/Weapons/Explosive.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,256.f,156.f);
	}
	if(50 <= rand && rand  < 75)
	{
		type_ = DoT;
		if (!texture_.loadFromFile("src/sprites/Weapons/DoT.png")) {
			std::cerr << "Error loading player texture! \n";
		}
		spriteRectPostion_ = sf::IntRect(0,0,190.f,76.f);
	}

	if (rand >=75)
	{
		type_ = Perforing;
		if (!texture_.loadFromFile("src/sprites/Weapons/Perforing.png")) {
			std::cerr << "Error loading player texture! \n";
		}
	}
	
	spriteRectPostion_ = sf::IntRect(0,0,210.f,92.f);
	sprite_ = sf::Sprite(texture_,spriteRectPostion_);
	position_ = position;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position_);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(0.5f,0.5f));
	sf::FloatRect rect = sprite_.getGlobalBounds();
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
	hitbox_ = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
	
}

void WeaponBoost::update(float deltaTime)
{
	lifetime_-= deltaTime;
	if(lifetime_<=0)
		isDead_ = true;
	sf::FloatRect bounds = sprite_.getGlobalBounds();
	float centerX = bounds.left + bounds.width / 2;
	float centerY = bounds.top + bounds.height / 2;
	hitBoxPosition_ = sf::Vector2f(centerX,centerY);
	hitBox_.setPosition(hitBoxPosition_);
	Actor::update(deltaTime);
}

void WeaponBoost::display(sf::RenderWindow& window)
{
	Actor::display(window);
}


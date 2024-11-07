#include "Player.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Bullet.h"
#include "Game.h"

Player::Player()
{
	hitBox_ = sf::RectangleShape{sf::Vector2f(-36,64)};
	if (!texture_.loadFromFile("src/sprites/Run.png")) {
		std::cerr << "Error loading player texture! \n";
	}
	sprite_ = sf::Sprite(texture_,spriteRectPostion_);
	speed_ = 150.f;
	sprite_.setTexture(texture_);
	sprite_.setPosition(position_);
	sprite_.rotate(0);
	sprite_.scale(sf::Vector2f(1.f,1.f));
	sprite_.setOrigin(sprite_.getLocalBounds().width / 2.5, sprite_.getLocalBounds().height / 4);
}

Player::~Player()
= default;

void Player::update(float deltaTime)
{
	if (clock_.getElapsedTime().asSeconds() > 0.1f)
	{
		if(spriteRectPostion_.left == 1024-128)
		{
			spriteRectPostion_.left = 0;
			clock_.restart();
		}
		else
		{
			spriteRectPostion_.left += 128;
			clock_.restart();
		}
	}
	sprite_.setTextureRect(spriteRectPostion_);
	sprite_.setPosition(position_);

	
	Actor::update(deltaTime);
}

void Player::display(sf::RenderWindow& window)
{
	Actor::display(window);
}

void Player::setPostion(int x, int y)
{
	position_.x = x; position_.y = y;
}

void Player::moveUp(float deltaTime)
{
	if (position_.y >= 0 )
		position_.y -=speed_*deltaTime;
}
void Player::moveDown(sf::RenderWindow* window,float deltaTime)
{
	if (position_.y <=window->getSize().y-50)
		position_.y +=speed_*deltaTime;
}

void Player::moveLeft(float deltaTime )
{
	if (lookRight_)
	{
		sprite_.setScale(sf::Vector2f(-1.f,1.f));
		hitBox_ = sf::RectangleShape{sf::Vector2f(36,64)};
		lookRight_ = false;
	}
	if (position_.x >= 20)
		position_.x -=speed_*deltaTime;
}

void Player::moveRight(sf::RenderWindow* window, float deltaTime)
{
	if (!lookRight_)
	{
		sprite_.setScale(sf::Vector2f(1.f,1.f));
		hitBox_ = sf::RectangleShape{sf::Vector2f(-36,64)};
		lookRight_ = true;
	}
	if (position_.x <= window->getSize().x)
		position_.x +=speed_*deltaTime;
}

void Player::shoot(sf::RenderWindow& window)
{
	if(shootClock_.getElapsedTime().asSeconds() >= 0.1)
	{
		sf::Vector2f targetPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		Game::addBullet(new Bullet(position_,targetPosition));
		shootClock_.restart();
	}
}


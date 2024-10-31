#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Actor.h"

class Player : public Actor
{
public:
	Player();
	~Player() override;
	void update(float deltaTime) override;
	void display(sf::RenderWindow& window) override;
	uint8_t get_hp() const { return hp_;}
	void set_hp(uint8_t hp){ hp_ = hp;}
	void setPostion(int x, int y);
	void moveUp(float deltaTime);
	void moveDown(sf::RenderWindow* window,float deltaTime);
	void moveLeft(float deltaTime);
	void moveRight(sf::RenderWindow* window,float deltaTime);
	void shoot(sf::RenderWindow& window);

private:
	uint8_t hp_ = 0;
	bool lookRight_ = true;
	sf::Clock shootClock_;
	sf::RectangleShape hitBox_{sf::Vector2f(-36,64)};
	
		
};

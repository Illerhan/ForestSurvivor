#pragma once
#include <fwd.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
	class RenderWindow;
}

class Actor
{
public:
	sf::Vector2f get_position() const {return position_;}

	float get_speed() const {return speed_;}
	void set_speed(float speed) {speed_ = speed;}
	sf::Vector2f getPosition(){return position_;}
	sf::Sprite getSprite() const {return sprite_;}
	Actor();
	virtual ~Actor() = default;
protected:
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::Vector2f position_;
	float speed_;
	sf::Clock clock_;
	sf::IntRect spriteRectPostion_ = sf::IntRect(0,0,128,128);
	bool isDead_ = false;

public:
	bool isDead() const {return isDead_;}
	
	virtual void update(float deltaTime);
	virtual void display(sf::RenderWindow& window);
};

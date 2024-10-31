#pragma once
#include <vector>
#include <detail/type_vec2.hpp>
#include <SFML/System/ThreadLocal.hpp>

#include "Bullet.h"
#include "Enemy.h"
#include "EnergyBall.h"
#include "Player.h"

class Game
{
public:
	std::vector<Player*> get_players() const
	{
		return players_;
	}
	
	Game();
	~Game();
	void spawnWave();
	void update(float deltaTime, sf::RenderWindow* window);
	void init(sf::RenderWindow* window);
	void close();
	static bool checkCollision(const Bullet& bullet, const Enemy& enemy);
	void addPlayer(Player* player);
	void display(sf::RenderWindow* window);
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void removeBullet(Bullet* bullet);
	static void addEnergyBall(EnergyBall* energyB);
	static void addBullet(Bullet* bullet);
	static void removeEnergyBall(EnergyBall* energyB);
	void removePlayer(Player* player);
	void checkIfDead();

private:
	std::vector<Player*> players_;
	sf::Texture backgroundTexture_;
	sf::Sprite backgroundSprite_;
	std::vector<Enemy*> enemies_;
	int enemiesPerWave_ = 5;
	int currentWave_ = 0;
	float timeSinceLastSpawn_ = 0.0f;
	float spawnInterval_ = 5.0f;
	static std::vector<Bullet*> bullets_;
	static std::vector<EnergyBall*> energyBalls_;
};

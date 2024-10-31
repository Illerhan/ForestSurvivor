#include "Game.h"

#include <iostream>
#include <random>
#include <SFML/Window/Keyboard.hpp>

#include "Follower.h"
#include "Shooters.h"

std::vector<EnergyBall*> Game::energyBalls_;
std::vector<Bullet*> Game::bullets_;

Game::Game(){}

Game::~Game(){}

void Game::spawnWave()
{

	srand(time(NULL));
	
	for (int i = 0; i < enemiesPerWave_; ++i) {
		int enemyType = rand() % 2;
		if (enemyType == 0) {
			Enemy* enemy = new Follower(players_[enemyType], sf::Vector2f(250 + i * 50, 50));
			addEnemy(enemy);
		} else {
			Enemy* enemy = new Shooters(players_[enemyType], sf::Vector2f(250 + i * 50, 50));
			addEnemy(enemy);
		}
	}
	currentWave_++;
}

void Game::init(sf::RenderWindow* window)
{
	
	// Generate background, center and scale to fit the window
	if (!backgroundTexture_.loadFromFile("src/sprites/background.jpg")) {
		std::cerr << "Error loading background image\n";
	}
	backgroundSprite_.setTexture(backgroundTexture_);

	sf::Vector2u windowSize = window->getSize();
	sf::Vector2u textureSize = backgroundTexture_.getSize();
	std::cout << "Window Size: " << windowSize.x << ", " << windowSize.y << "\n";
	std::cout << "Texture Size: " << textureSize.x << ", " << textureSize.y << "\n";
	
	
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	backgroundSprite_.setScale(scaleX, scaleY);
	//

	// Setting up players in the game
	Player* playerOne = new Player();
	playerOne->setPostion(50,50);
	addPlayer(playerOne);
	
	Player* playerTwo = new Player();
	addPlayer(playerTwo);
	//
	
	Follower* enemi1 = new Follower(players_[0], sf::Vector2f(250,250));
	addEnemy(enemi1);

	Shooters* enemi2 = new Shooters(players_[0],sf::Vector2f(250,250));
	addEnemy(enemi2);
}

void Game::update(float deltaTime, sf::RenderWindow* window)
{
	
	for (auto player : players_)
	{
		player->update(deltaTime);
	}
	for (auto enemy : enemies_)
	{
		enemy->update(deltaTime);
	}
	for (auto energyB : energyBalls_)
	{
		energyB->update(deltaTime);
	}
	for (auto bullet : bullets_)
	{
		bullet->update(deltaTime);
	}

	timeSinceLastSpawn_ += deltaTime;
	if (timeSinceLastSpawn_ >= spawnInterval_) {
		spawnWave();
		timeSinceLastSpawn_ = 0.0f; // Reset timer
	}

	for (auto it = bullets_.begin(); it != bullets_.end();) {
		Bullet* bullet = *it;
		bool bulletRemoved = false; // Flag to track if bullet should be removed
        
		for (Enemy* enemy : enemies_) { // Assuming you have a vector of enemies
			if (checkCollision(*bullet, *enemy)) {
				// Handle collision (e.g., remove bullet and enemy)
				it = bullets_.erase(it); // Remove bullet
				bulletRemoved = true;
				removeEnemy(enemy);
				break; // Break inner loop if collision detected
			}
		}
        
		if (!bulletRemoved) {
			++it; // Only increment if bullet is not removed
		}
	}
	checkIfDead();
}

void Game::close()
{
	
}

bool Game::checkCollision(const Bullet& bullet, const Enemy& enemy) {
	return bullet.getSprite().getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds());
}

void Game::display(sf::RenderWindow* window)
{
	window->draw(backgroundSprite_);
	
	for (auto player : players_)
	{
		player->display(*window);
		
	}
	for (auto enemy : enemies_)
	{
		enemy->display(*window);
	}

	for (auto energyB : energyBalls_)
	{
		energyB->display(*window);
	}
	for (auto bullet : bullets_)
	{
		bullet->display(*window);
	}

}

// Add methods to fill vector with new objects created
void Game::addPlayer(Player* player)
{
	players_.push_back(player);
}

void Game::addEnemy(Enemy* enemy)
{
	enemies_.push_back(enemy);
}

void Game::addEnergyBall(EnergyBall* energyB)
{
	energyBalls_.push_back(energyB);
}

void Game::addBullet(Bullet* bullet)
{
	bullets_.push_back(bullet);
}
//

// Remove methods to erase object from vectors when they are dead
void Game::removeEnergyBall(EnergyBall* energyB)
{
	auto iter = std::find(begin(energyBalls_), end(energyBalls_), energyB);
	energyBalls_.erase(iter);

}

void Game::removePlayer(Player* player)
{
	auto iter = std::find(begin(players_), end(players_), player);
	players_.erase(iter);
}

void Game::removeEnemy(Enemy* enemy)
{
	auto iter = std::find(begin(enemies_), end(enemies_), enemy);
	enemies_.erase(iter);
}

void Game::removeBullet(Bullet* bullet)
{
	auto iter = std::find(begin(bullets_), end(bullets_), bullet);
	bullets_.erase(iter);
}

//

// Call remove methods by checking if dead or not, then delete it
void Game::checkIfDead()
{
	for (auto player : players_)
	{
		if(player->isDead())
		{
			removePlayer(player);
			delete player;
		}
		
	}
	for (auto enemy : enemies_)
	{
		if(enemy->isDead())
		{
			removeEnemy(enemy);
			delete enemy;
		}
	}

	for (auto energyB : energyBalls_)
	{
		if(energyB->isDead())
		{
			removeEnergyBall(energyB);
			delete energyB;
		}
	}
	for (auto bullet : bullets_)
	{
		if(bullet->isDead())
		{
			removeBullet(bullet);
			delete bullet;
		}
	}
}
//
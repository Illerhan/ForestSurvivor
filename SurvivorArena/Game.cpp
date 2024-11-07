#include "Game.h"

#include <iostream>
#include <random>
#include <SFML/Window/Keyboard.hpp>

#include "Follower.h"
#include "Shooters.h"
#include "Weapon.h"

std::vector<EnergyBall*> Game::energyBalls_;
std::vector<Bullet*> Game::bullets_;

Game::Game(sf::RenderWindow& window) : window_(&window){}

Game::~Game(){}

void Game::spawnWave()
{
	srand(time(NULL));
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> edgeDist(0, 3);
	std::uniform_real_distribution<float> xDist(0, window_->getSize().x);
	std::uniform_real_distribution<float> yDist(0, window_->getSize().y / 2);
	
	for (int i = 0; i < enemiesPerWave_; ++i) {

		std::uniform_real_distribution<float> xPosDist(0, window_->getSize().x);
		std::uniform_real_distribution<float> yPosDist(0, window_->getSize().y);
		sf::Vector2f spawnPosition;
		int enemyType = rand() % 2;
		int edge = edgeDist(gen);
		switch (edge) {
		case 0: // Top Edge
			spawnPosition = sf::Vector2f(xPosDist(gen), -64);
			break;
		case 1: // Bottom Edge
			spawnPosition = sf::Vector2f(xPosDist(gen), window_->getSize().y + 64);
			break;
		case 2: // Left Edge
			spawnPosition = sf::Vector2f(-36, yPosDist(gen));
			break;
		case 3: // Right Edge
			spawnPosition = sf::Vector2f(window_->getSize().x + 36, yPosDist(gen));
			break;
		default: ;
		}
		if (enemyType == 0) {
			Enemy* enemy = new Follower(players_[enemyType], spawnPosition);
			addEnemy(enemy);
		} else {
			Enemy* enemy = new Shooters(players_[enemyType], spawnPosition);
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
	Weapon* test = new Weapon(Simple);
	addWeapon(test);
	Weapon* test2 = new Weapon(DoT);
	addWeapon(test2);
	// Setting up players in the game
	Player* playerOne = new Player();
	playerOne->setPostion(windowSize.x/2,windowSize.y/2);
	addPlayer(playerOne);
	
	Player* playerTwo = new Player();
	playerTwo->setPostion(windowSize.x/2,windowSize.y/2);
	addPlayer(playerTwo);
	//
	
	spawnWave();
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

	for (auto weapon : weaponsP1_)
	{
		weapon->update(deltaTime);
	}

	for (auto weapon : weaponsP2_)
	{
		weapon->update(deltaTime);
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
	return bullet.checkCollision(enemy.getHitBox());
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

	createInterface();

	for (auto weapon : weaponsP1_)
	{
		weapon->display(*window);
	}
	for (auto weapon : weaponsP2_)
	{
		weapon->display(*window);
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

void Game::addWeapon(Weapon* weapon)
{
	weaponsP1_.push_back(weapon);
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

void Game::removeWeapon(Weapon* weapon)
{
	auto iter = std::find(begin(weaponsP1_), end(weaponsP1_), weapon);
	weaponsP1_.erase(iter);
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

void Game::createInterface()
{
        // Define main rectangle sizes and colors
    sf::RectangleShape leftRectangle(sf::Vector2f(200, 100));
    sf::RectangleShape rightRectangle(sf::Vector2f(200, 100));

    // Set main rectangle positions at the bottom
    leftRectangle.setPosition(50, window_->getSize().y - leftRectangle.getSize().y - 20);
    rightRectangle.setPosition(window_->getSize().x - rightRectangle.getSize().x - 50, 
                               window_->getSize().y - rightRectangle.getSize().y - 20);

    // Set fill colors for the main rectangles
    leftRectangle.setFillColor(sf::Color(200, 200, 250, 200)); // Blue
    rightRectangle.setFillColor(sf::Color(20, 20, 20, 200)); // Red

    // Define the hole size in the center of each rectangle
    sf::Vector2f holeSize(100, 60); // Adjust this to change the size of the "hole"
    sf::Vector2f borderThickness(10, 10); // Thickness of the border around the "hole"

    // Define small rectangles to create a border around the hole
    sf::RectangleShape leftBorderTop(sf::Vector2f(leftRectangle.getSize().x, borderThickness.y));
    sf::RectangleShape leftBorderBottom(sf::Vector2f(leftRectangle.getSize().x, borderThickness.y));
    sf::RectangleShape leftBorderLeft(sf::Vector2f(borderThickness.x, leftRectangle.getSize().y - 2 * borderThickness.y));
    sf::RectangleShape leftBorderRight(sf::Vector2f(borderThickness.x, leftRectangle.getSize().y - 2 * borderThickness.y));

    sf::RectangleShape rightBorderTop(sf::Vector2f(rightRectangle.getSize().x, borderThickness.y));
    sf::RectangleShape rightBorderBottom(sf::Vector2f(rightRectangle.getSize().x, borderThickness.y));
    sf::RectangleShape rightBorderLeft(sf::Vector2f(borderThickness.x, rightRectangle.getSize().y - 2 * borderThickness.y));
    sf::RectangleShape rightBorderRight(sf::Vector2f(borderThickness.x, rightRectangle.getSize().y - 2 * borderThickness.y));

    // Set border positions around the left hole
    leftBorderTop.setPosition(leftRectangle.getPosition());
    leftBorderBottom.setPosition(leftRectangle.getPosition().x, leftRectangle.getPosition().y + leftRectangle.getSize().y - borderThickness.y);
    leftBorderLeft.setPosition(leftRectangle.getPosition().x, leftRectangle.getPosition().y + borderThickness.y);
    leftBorderRight.setPosition(leftRectangle.getPosition().x + leftRectangle.getSize().x - borderThickness.x, leftRectangle.getPosition().y + borderThickness.y);

    // Set border positions around the right hole
    rightBorderTop.setPosition(rightRectangle.getPosition());
    rightBorderBottom.setPosition(rightRectangle.getPosition().x, rightRectangle.getPosition().y + rightRectangle.getSize().y - borderThickness.y);
    rightBorderLeft.setPosition(rightRectangle.getPosition().x, rightRectangle.getPosition().y + borderThickness.y);
    rightBorderRight.setPosition(rightRectangle.getPosition().x + rightRectangle.getSize().x - borderThickness.x, rightRectangle.getPosition().y + borderThickness.y);

    // Set border colors
    sf::Color borderColor(50, 50, 50, 255); // Dark gray for the border
    leftBorderTop.setFillColor(borderColor);
    leftBorderBottom.setFillColor(borderColor);
    leftBorderLeft.setFillColor(borderColor);
    leftBorderRight.setFillColor(borderColor);

    rightBorderTop.setFillColor(borderColor);
    rightBorderBottom.setFillColor(borderColor);
    rightBorderLeft.setFillColor(borderColor);
    rightBorderRight.setFillColor(borderColor);

	sf::RectangleShape leftDivider(sf::Vector2f(borderThickness.x, leftRectangle.getSize().y));
	leftDivider.setPosition(leftRectangle.getPosition().x + leftRectangle.getSize().x / 2 - borderThickness.x / 2, leftRectangle.getPosition().y);
	leftDivider.setFillColor(borderColor);

	sf::RectangleShape rightDivider(sf::Vector2f(borderThickness.x, rightRectangle.getSize().y));
	rightDivider.setPosition(rightRectangle.getPosition().x + rightRectangle.getSize().x / 2 - borderThickness.x / 2, rightRectangle.getPosition().y);
	rightDivider.setFillColor(borderColor);
	
	// Draw main rectangles
	window_->draw(leftRectangle);
	window_->draw(rightRectangle);

	// Draw borders around the "holes"
	window_->draw(leftBorderTop);
	window_->draw(leftBorderBottom);
	window_->draw(leftBorderLeft);
	window_->draw(leftBorderRight);

	window_->draw(rightBorderTop);
	window_->draw(rightBorderBottom);
	window_->draw(rightBorderLeft);
	window_->draw(rightBorderRight);
	
	if (!weaponsP1_.empty()) {
		// Position the first weapon in the left hole of the left rectangle
		weaponsP1_[0]->setPosition(sf::Vector2f(
			leftRectangle.getPosition().x + (leftRectangle.getSize().x / 4) - (holeSize.x / 2),
			leftRectangle.getPosition().y + (leftRectangle.getSize().y - holeSize.y) / 2));

		// Position the second weapon in the right hole of the left rectangle
		if (weaponsP1_.size() > 1) {
			weaponsP1_[1]->setPosition(sf::Vector2f(
				leftRectangle.getPosition().x + (leftRectangle.getSize().x / 4) * 3 - (holeSize.x / 2),
				leftRectangle.getPosition().y + (leftRectangle.getSize().y - holeSize.y) / 2));
		}
	}
	// Draw middle dividers
	window_->draw(leftDivider);
	window_->draw(rightDivider);
}
//
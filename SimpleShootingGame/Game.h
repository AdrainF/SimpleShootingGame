#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "World.h"
#include <sstream>
#include <string>
class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Event sfmlEvents;

	unsigned enemyCountMax;
	float enemySpawnTime;
	float enemySpawnTimeMax;
	unsigned points;
	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	//Player
	Player* player;

	//Player Gui
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::Text gameOverText;
	//Gui
	sf::Text pointText;
	sf::Font font;

	//World / Background
	World* world;
	
	//Private functions
	void update();
	void render();
	void renderGui();
	void poolEvents();
	void playerCollison();
	void initWindow();
	void initVariables();
	void initWorld();
	void initPlayer();
	void initEnemy();
	void initTextures();
	void initGui();
	void updateInputs();
	void updateBullet();
	void updateEnemies();
	void updateCombat();
	void updateGui();


public:
	//Constructor / destructor
	Game();
	virtual ~Game();

	//Functions
	void run();
};


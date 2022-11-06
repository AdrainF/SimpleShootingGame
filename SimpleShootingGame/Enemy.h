#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
class Enemy
{
private:
	//Variables
	sf::CircleShape shape;
	float movmentSpeed;
	sf::Vector2f direction;

	unsigned enemyPoints;

	//Private functions
	void initVariables();
	void initShape(sf::RenderWindow* window);
	void initEnemyPoints();

public:

	//Constuctor / destructor
	Enemy(sf::RenderWindow * window);
	~Enemy();

	//Functuons
	void update();
	void render(sf::RenderTarget* target);
	sf::FloatRect getBounds();
	int getEnemyPoints();
};


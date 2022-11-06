#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
class Player
{
private:
	//Variables
	
	sf::Sprite sprite;
	float movmentSpeed;
	float attacCooldown;
	float attacCooldownMax;
	int hpMax;
	int hp;
	
	

	//Private functions

	void initSprite();
	void initVariables();


public:

	//Constructor / destructor
	Player();
	Player(sf::Texture* texture);
	~Player();

	void move(const float x, const float y);
	void setPossition(float x, float y);
	void update();
	void render(sf::RenderTarget& target);
	sf::Vector2f getPos();
	void updataAttack();
	const bool canAttack();
	sf::FloatRect getGlobalBounds();
	
	//Accessors
	int getHp();
	int getHpMax();
	void setDamage(float points);

};


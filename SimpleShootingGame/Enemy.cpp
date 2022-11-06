#include "Enemy.h"

void Enemy::initVariables()
{
	this->movmentSpeed = 1.f ;

}

void Enemy::initShape(sf::RenderWindow* window)
{	
	this->shape.setRadius(rand()% 20+20);
	this->shape.setPointCount(enemyPoints);
	this->shape.setFillColor(sf::Color( rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	this->shape.setPosition(rand()% window->getSize().x ,0-this->shape.getGlobalBounds().height);

	
	
}

void Enemy::initEnemyPoints()
{
	this->enemyPoints = rand() % 10 + 3;
}


Enemy::Enemy(sf::RenderWindow* window)
{
	this->initVariables();
	this->initEnemyPoints();
	this->initShape(window);
	
}

Enemy::~Enemy()
{
	
}

void Enemy::update()
{
	this->shape.move( 0.f,this->movmentSpeed*(static_cast<float>(enemyPoints)/3));
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

sf::FloatRect Enemy::getBounds()
{
	return shape.getGlobalBounds();
}

int Enemy::getEnemyPoints()
{
	return this->enemyPoints;
}

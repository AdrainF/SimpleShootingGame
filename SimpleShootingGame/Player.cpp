#include "Player.h"


//void Player::initTextures()
//{
//	if (!this->textures.loadFromFile("Textures/ship.png"))
//	{
//		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
//	}
//	
//
//}





void Player::initVariables()
{
	this->movmentSpeed = 3.f;
	this->attacCooldownMax = 10.f;
	this->attacCooldown = this->attacCooldownMax;
	this->hpMax = 10;
	this->hp = hpMax;

}

Player::Player()
{
	
}

Player::Player(sf::Texture* texture)
{
	this->initVariables();
	this->sprite.setTexture(*texture);
	this->sprite.scale(0.1f, 0.1f);
	this->sprite.setPosition(550, 400);
	
}

Player::~Player()
{

}

void Player::move(const float x, const float y)
{
	this->sprite.move(this->movmentSpeed * x, this->movmentSpeed * y);
}

void Player::setPossition(float x, float y)
{

	this->sprite.setPosition(x, y);
}

void Player::update()
{
	this->updataAttack();
}

void Player::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);
}

sf::Vector2f Player::getPos()
{
	return this->sprite.getPosition();
}

void Player::updataAttack()
{
	if (this->attacCooldown<this->attacCooldownMax)
	{
		this->attacCooldown += 0.5f;
	}


}

const bool  Player::canAttack()
{
	if (this->attacCooldown>=this->attacCooldownMax)
	{
		this->attacCooldown = 0.f;
		return true;
	}
	return false;
}

sf::FloatRect Player::getGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

int Player::getHp()
{
	return this->hp;
}

int Player::getHpMax()
{
	return this->hpMax;
}

void Player::setDamage(float points)
{
	this->hp -= static_cast<int> (1.f* points);
	if (this->hp<0)
	{
		this->hp = 0;
	}

	
}

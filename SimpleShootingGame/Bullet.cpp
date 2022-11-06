#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float x, float y, float bulletSpeed )
{
	
	this->sprite.setTexture(*texture);
	this->direction.x = x;
	this->direction.y = y;
	this->movmentSpeed = bulletSpeed;
	this->sprite.setPosition(pos_x,pos_y);

}

Bullet::~Bullet()
{

}

void Bullet::update()
{
	this->sprite.move(this->movmentSpeed * this->direction);

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::FloatRect Bullet::getBounds()
{
	return this->sprite.getGlobalBounds();
}

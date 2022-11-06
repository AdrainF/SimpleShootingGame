#include "World.h"

void World::initShape(sf::Texture* texture)
{
	this->sprite.setTexture(*texture);
}

World::World()
{
}

World::World(sf::Texture* texture)
{
	 this->initShape(texture);

}

World::~World()
{
}

void World::update()
{
}

void World::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

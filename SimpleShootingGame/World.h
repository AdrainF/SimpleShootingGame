#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class World
{
private:

	//Variables
	
	sf::Sprite sprite;

	//Private functions
	void initShape(sf::Texture* texture);
	

public:
	World();
	World(sf::Texture* texture);
	~World();

	void update();
	void render(sf::RenderTarget& target);

};


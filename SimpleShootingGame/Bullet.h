#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Bullet
{
private:
	sf::Sprite sprite;

	sf::Texture* texture;
	sf::Vector2f direction;
	float movmentSpeed;
	

public:
	
	//Constructor / destructor
	Bullet();
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float x, float y, float bulletSpeed);
	~Bullet();

	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
	sf::FloatRect getBounds();

};


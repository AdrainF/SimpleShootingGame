#include "Game.h"
//Private functions
void Game::update()
{
	this->updateInputs();
	this->updateBullet();
	this->player->update();
	this->updateEnemies();
	this->updateCombat();
	this->playerCollison();
	this->updateGui();
}

void Game::render()
{
	this->window->clear();
	this->world->render(*this->window);
	this->player->render(*this->window);
	this->renderGui();
	for (auto* enemy : enemies)
	{
		enemy->render(this->window);
	}


	

	for (auto *bullet : bullets)
	{
		bullet->render(this->window);
	}

	if (this->player->getHp()<=0)
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}

void Game::renderGui()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::poolEvents()
{
	while (this->window->pollEvent(sfmlEvents))
	{
		if (this->sfmlEvents.type==sf::Event::Closed)
		{
			this->window->close();
		}
		if (sf::Event::KeyPressed &&  this->sfmlEvents.key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}

}

void Game::playerCollison()
{

	//Player collison with window frames
	if (this->player->getGlobalBounds().left<=0)
	{
		this->player->setPossition(0.f, this->player->getPos().y);

	}else if (this->player->getGlobalBounds().left+this->player->getGlobalBounds().width>=this->window->getSize().x)
	{
		this->player->setPossition(this->window->getSize().x-this->player->getGlobalBounds().width, this->player->getPos().y);
	}

	if (this->player->getGlobalBounds().top <= 0)
	{
		this->player->setPossition( this->player->getPos().x,0.f);

	}
	else if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height >= this->window->getSize().y)
	{
		this->player->setPossition(this->player->getPos().x, this->window->getSize().y - this->player->getGlobalBounds().height);
	}

	//Player collison with enemies mechanic
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (this->player->getGlobalBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->player->setDamage(this->enemies[i]->getEnemyPoints() / 3.f);
			delete this->enemies[i];
			this->enemies.erase(enemies.begin() + i);
			
			
			
		}
	}


}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Simple Shooting Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
}

void Game::initVariables()
{

}

void Game::initWorld()
{
	this->world = new World(this->textures["Background"]);
}

void Game::initPlayer()
{
	this->player = new Player(this->textures["Player"]);

}

void Game::initEnemy()
{
	this->enemyCountMax = 10;
	this->enemySpawnTimeMax = 20.f;
	this->enemySpawnTime = this->enemySpawnTimeMax;


	
}

void Game::initTextures()
{

	//Textures map
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	this->textures["Player"] = new sf::Texture();
	this->textures["Player"]->loadFromFile("Textures/ship.png");
	this->textures["Background"] = new sf::Texture();
	this->textures["Background"]->loadFromFile("Textures/background1.jpg");
}

void Game::initGui()
{
	//Points Gui
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::INITGUI::LOAD FONT ERROR";
	}
	this->pointText.setFont(font);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setCharacterSize(20);
	this->pointText.setPosition(650, 20);

	this->gameOverText.setFont(font);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setString("Game Over!!!!");
	this->gameOverText.setPosition(this->window->getSize().x/2 -this->gameOverText.getGlobalBounds().width/2, 
								   this->window->getSize().y/2 - this->gameOverText.getGlobalBounds().height);



}

void Game::updateInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->move(-1.f, 0.f);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->move(0.f, 1.f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()==true)
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x+this->player->getGlobalBounds().width/2.f, this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateBullet()
{
	unsigned counter = 0;
	for (auto *bullet : bullets)
	{
		bullet->update();

		if (bullet->getBounds().top+bullet->getBounds().height<0)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(bullets.begin() + counter);
			
			--counter;
		
		}
		++counter;
		
	}
	
}

void Game::updateEnemies()
{
	enemySpawnTime += 0.5f;
	if (this->enemySpawnTime >= this->enemySpawnTimeMax && this->enemies.size()<this->enemyCountMax)
	{
		
			enemies.push_back(new Enemy(this->window));
			enemySpawnTime = 0.f;

		
	}





}

void Game::updateCombat()
{

	for (size_t i = 0; i < enemies.size(); i++)
	{
		bool enemyDel = false;

		enemies[i]->update();

		for (size_t k = 0; k < bullets.size() && enemyDel == false; k++)
		{

			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{

				this->points += this->enemies[i]->getEnemyPoints();
				delete enemies[i];
				this->enemies.erase(enemies.begin() + i);

				delete bullets[k];

				this->bullets.erase(bullets.begin() + k);
				enemyDel = true;
				
			}
		}

		if (enemyDel == false)
		{


			if (enemies[i]->getBounds().top > this->window->getSize().y && enemyDel == false)
			{
				delete enemies[i];
				this->enemies.erase(enemies.begin() + i);
				enemyDel = true;
			}
		}

	}

}

void Game::updateGui()
{
	//Points GUI
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());

	//Player GUI /HP Bar
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(20.f, 20.f);
	this->playerHpBarBack.setFillColor(sf::Color::Yellow);
	this->playerHpBarBack.setSize(sf::Vector2f(300.f, 20.f));
	this->playerHpBarBack.setPosition(20.f, 20.f);
	float hpPercent;
	hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, 20.f));


}

//Constructor / destructor
Game::Game()
{

	this->initWindow();
	this->initVariables();
	this->initTextures();
	this->initWorld();
	this->initPlayer();
	this->initEnemy();
	this->initGui();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	
	//Delete textures
	for (auto &i : textures)
	{
		delete i.second;
	}
	for (auto *bullet : bullets)
	{
		delete bullet;
	}
	//Delete enemies
	for (auto* enemy : enemies)
	{
		delete enemy;
	}

}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->poolEvents();

		if (this->player->getHp()>0)
		{
			this->update();
		}
		
		this->render();


	}
	
}

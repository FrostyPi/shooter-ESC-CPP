#include "Game.h"
//1:00:16, incomplete
#include <iostream>
#include <fstream>

Game::Game(const std::string & config)
{
	init(config);
}

void Game::init(const std::string & path)
{
	//TODO: read in config file here
	//		use the premade PlayerConfig, EnemyConfig, BulletConfig variables
	//std::ifstream fin(path);
	// fin >> m_playerConfig.SR >> m_playerConfig.CR;
	// set up default window parameters
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{
	// TODO: add pause functionality here
	//some systems should function while paused (rendering)
	//some systems shouldn't (movement/input)
	//kekw
	while (m_running)
	{
		m_entities.update();

		//if (!m_paused) 
		//{
		sEnemySpawner();
		sMovement();
		sCollision();
		sLifespan();
		sUserInput(); 
			//perhaps
		//}
		
		sRender();

		// increment current frame
		//may need to be moved when pause implemented
		m_currentFrame++;
	}
}

void Game::setPaused(bool paused)
{
	//TODO
}

void Game::spawnPlayer()   //1:22:08
{
	// TODO: finish adding all properties of the player with values from config

	// we create entity by calling EntityManager.addEntity(tag)
	//this returns a std::shared_ptr<Entity>, so we use "auto" to save typing
	auto entity = m_entities.addEntity("player");

	// middle spawn
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;
	float radius = 32.0f;

	//Give this entity a Transform so it spawns at (200, 200) with velocity (1,1) and angle 0
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	//entity's shape will have radius 32, 8 sides, dark grey fill, red outline, thickness 4
	entity->cShape = std::make_shared<CShape>(radius, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	//input component to the player
	entity->cInput = std::make_shared<CInput>();

	entity->cCollision = std::make_shared<CCollision>(radius);

	//entity is player, set game's player variable to be this
	m_player = entity;
}

// spawn an enemy aT A RANDOM POSITION
void Game::spawnEnemy()
{
	//TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
	// the enemy must be spawned completely within the bounds of the window

	auto entity = m_entities.addEntity("enemy");

	int radius = (rand() % 30) + 16;
	float ex = rand() % (m_window.getSize().x - radius);
	float ey = rand() % (m_window.getSize().y - radius);
	float vx = rand() % (10) - 5;
	float vy = rand() % (10) - 5;
	int vertices = rand() % 9;
	 
	//Give this entity a Transform so it spawns at (200, 200) with velocity (1,1) and angle 0
	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(vx, vy), 0.0f);

	entity->cShape = std::make_shared<CShape>(radius, vertices, sf::Color(0, 255, 0), sf::Color(255, 255, 255), 4.0f);
	entity->cCollision = std::make_shared<CCollision>(radius);

	//record when the most recent enemy was spawneds
	m_lastEnemySpawnTime = m_currentFrame;


}

//spawn small enemies when big one (input enemy e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	//TODO: spawn small enemies at the location of the input enemy e

	/*auto smallEntity = m_entities.addEntity("small");

	smallEntity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(1.0f, 1.0f), 0.0f);

	smallEntity->cShape = std::make_shared<CShape>(e->cShape->circle.getRadius() / 8, e->cShape->circle.getPointCount(), sf::Color(0, 255, 0), sf::Color(255, 255, 255), 4.0f);
	smallEntity->cCollision = std::make_shared<CCollision>(radius);*/

	// when we create the smaller enemy, read values of the original enemy
	// - spawn a number of small enemies == to number of vertices of original enemy
	// - set each small enemy to same colour, half size
	// - enemies worth double points of original enemy
}

// spawns a bullet froma  given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	//TODO:  implement the spawning of a bullet which travles towards targhet
	//			- bullet speed given as scalar
	// 
	// velocity as vector

	auto bullet = m_entities.addEntity("bullet");
	float radius = 10;
	//sets position at player, and velocity has speed four due to normalization of vector. maybe a more efficient solution?
	bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(target.x - entity->cTransform->pos.x, target.y - entity->cTransform->pos.y).normalize()*4, 0.0f);
	

	bullet->cShape = std::make_shared<CShape>(radius, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2.0f);
	bullet->cCollision = std::make_shared<CCollision>(radius);

	bullet->cLifespan = std::make_shared<CLifespan>(120);// for both remaining and total

	
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// TODO:  special weapon
}

void Game::sMovement()
{
	// TODO: implement all entity movement (BULLETS)
	// read m_player->cInput component to determine if the player is moving
	//for (auto b : m_entities.getEntities("bullet")) {
	//	//std::cout << b->cTransform->velocity.x << " " << b->cTransform->velocity.y;
	//	b->cTransform->pos.x += b->cTransform->velocity.x;
	//	b->cTransform->pos.y += b->cTransform->velocity.y;
	//}


	m_player->cTransform->velocity = { 0.0f, 0.0f };

	//implement player movement
	// 
	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5.0f;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5.0f;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 5.0f;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5.0f;
	}

	//	sample movespeed update
	//  TODO: apply this to all relevant entities

	for (auto e : m_entities.getEntities()) 
	{
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += e->cTransform->velocity.y;
	}
	
}

void Game::sLifespan()
{

	for (auto e : m_entities.getEntities())
	{
		if (e->cLifespan == nullptr)
		{
			//std::cout << e->tag();
			continue;
		}
		else
		{
			if (e->cLifespan->remaining > 0)
			{
				e->cLifespan->remaining -= 1;
				
				sf::Color currentColor = e->cShape->circle.getFillColor();
				currentColor.a -= 2;
				e->cShape->circle.setFillColor(currentColor);
				// set ALPHA CHANNEL ACCORDINGHLYe->cShape.
				//e->cShape->circle.setFillColor()

			}
			else 
			{
				e->destroy();
			}
		}
	}

}

void Game::sCollision()
{
	// TODO: implement collisions between entities
	//		  collision radius, not shape radius
	// entity.destroy()

	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			if ((pow(b->cCollision->radius + e->cCollision->radius, 2)) >= (b->cTransform->pos.dist2(e->cTransform->pos)))
			{
				b->destroy();
				e->destroy();
				spawnSmallEnemies(e);
			}

		}

	}

	for (auto e : m_entities.getEntities("enemy")) 
	{
		if (e->cTransform->pos.x > (m_window.getSize().x - e->cCollision->radius) || e->cTransform->pos.x < e->cCollision->radius)
		{
			e->cTransform->velocity.x *= -1.0f;
		}
		if (e->cTransform->pos.y > (m_window.getSize().y - e->cCollision->radius) || e->cTransform->pos.y < e->cCollision->radius)
		{
			e->cTransform->velocity.y *= -1.0f;
		}

		if ((pow(m_player->cCollision->radius + e->cCollision->radius, 2)) >= (m_player->cTransform->pos.dist2(e->cTransform->pos)))
		{
			std::cout << "Colliding" << std::endl;
			e->destroy();
			m_player->cTransform->pos.x = m_window.getSize().x / 2;
			m_player->cTransform->pos.y = m_window.getSize().y / 2;

					//std::cout << "Colliding";
		}
	
	}


	//for (auto e : m_entities.getEntities("enemy"))
	//{
	//	//std::cout << (pow(m_player->cCollision->radius - e->cCollision->radius, 2)) << std::endl;
	//	//std::cout << (m_player->cTransform->pos.dist2(e->cTransform->pos));
	//	if ((pow(m_player->cCollision->radius + e->cCollision->radius, 2)) >= (m_player->cTransform->pos.dist2(e->cTransform->pos)))
	//	{
	//		std::cout << "Colliding" << std::endl;
	//		e->destroy();
	//		m_player->cTransform->pos.x = m_window.getSize().x / 2;
	//		m_player->cTransform->pos.y = m_window.getSize().y / 2;

	//		//std::cout << "Colliding";
	//	}

	//	for (auto b : m_entities.getEntities("bullet"))
	//	{
	//		if ((pow(b->cCollision->radius + e->cCollision->radius, 2)) >= (b->cTransform->pos.dist2(e->cTransform->pos)))
	//		{
	//			b->destroy();
	//			e->destroy();
	//		}
	//	}
		/*for (auto b : m_entities.getEntities("bullet"))
		{

		}*/
			//m_player->cTransform->pos
	
	//for (auto b : m_entities.getEntities("bullet"))
	//{
	//	for (auto e : m_entities.getEntities("enemy"))
	//	{

	//	}
	//}
}

void Game::sEnemySpawner() 
{
	// TODO: code which implements enemy spawning should go here
	//	
	//		use m_currentFrame - m_lastEnemySpawnTime to determine
	//		how long it has been since the last enemy spawned
	if ((m_currentFrame - m_lastEnemySpawnTime) > 120)
	{
		spawnEnemy();
	}
}

void Game::sRender()
{
	// TODO: change the code below to draw ALL of the entities
	//		  sample drawing of the player entity that we have created
	m_window.clear();


	for (auto & e : m_entities.getEntities())
	{
		//m_window.draw(e->cShape->circle);

		//set pos of shape based on entity's transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// set the rotation of the shape based on the entity's transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		// draw the entity's sf::CircleShapes
		//deduct lifespan of bullet
		/*if (e->tag() == "bullet")
		{
			e->cLifespan->remaining -= 1;
		}*/
		m_window.draw(e->cShape->circle);
	}
	m_window.display();

}

void Game::sUserInput()
{
	// TODO: handle user input here
	// note that you should only be setting the player's input component variables here
	// you should not implement the player's movement logic here
	// the movement system will read the variables you set in this function

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		//event triggers when window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		//event triggered when key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				//std::cout << "W Key Pressed\n";
				m_player->cInput->up = true;
				//TODO: set player's input component "up" to true
				break;
			case sf::Keyboard::A:
				//std::cout << "A Key Pressed\n";
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				//std::cout << "S Key Pressed\n";
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				//std::cout << "D Key Pressed\n";
				m_player->cInput->right = true;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				//std::cout << "W Key Released\n";
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				//std::cout << "A Key Released\n";
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				//std::cout << "S Key Released\n";
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				//std::cout << "W Key Released\n";
				m_player->cInput->right = false;
				break;
			default: break;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{  
				//std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// TODO: call spawnBullet here, EDIT TO MAKE IT SO YOU CAN HOLD DOWN LEFT CLICK
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));

			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				//std::cout << "Right Mouse Button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// TODO: call spawnSpecialWeapon
			}
		}	
	}
}
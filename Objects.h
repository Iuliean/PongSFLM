#pragma once
#include <SFML/include/System.hpp>
#include <SFML/include/Graphics.hpp>
#include <math.h>

void setObjectContext(sf::Vector2u newWindow);

class Paddle : public sf::RectangleShape
{
public:
	
	static const int speed = 500;
	static int height;
	static int width;

	Paddle();
	Paddle(int x, int y);

	void MoveLeft();
	void MoveRight();
};

class Ball : public sf::CircleShape
{
private:
	
	bool CollisionWithPlayer(Paddle& player);
	bool CollisionWithWall();
	bool IsOutOfBounds();

public:
	
	sf::Vector2f speed = sf::Vector2f(0.0f, 200.0f);

	Ball();

	void Move();
};
#include "Objects.h"

static sf::Vector2u window;
extern float dt;

void setObjectContext(sf::Vector2u newWindow)
{
	window = newWindow;
}

//Paddle
int Paddle::width = 100;
int Paddle::height = 10;

Paddle::Paddle() : RectangleShape(sf::Vector2f(Paddle::width, Paddle::height))
{
	this->setOrigin(Paddle::width / 2, Paddle::height / 2);
	this->setPosition(0, 0);
	this->setFillColor(sf::Color::Blue);

}

Paddle::Paddle(int x, int y) : RectangleShape(sf::Vector2f(Paddle::width, Paddle::height))
{
	this->setOrigin(Paddle::width / 2, Paddle::height / 2);
	this->setPosition(x, y);
	this->setFillColor(sf::Color::Blue);
}


void Paddle::MoveLeft()
{
	if (this->getPosition().x - Paddle::speed * dt >= 0) // checks if the next position of the paddle is a collision with the edge of the screen
		this->move(-Paddle::speed * dt, 0);
}

void Paddle::MoveRight()
{
	if (this->getPosition().x + Paddle::speed * dt <= window.x) // checks if the next position of the paddle is a collision with the edge of the screen
		this->move(Paddle::speed * dt, 0);
}


//Ball

extern Paddle player1;
extern Paddle player2;

Ball::Ball(): CircleShape(10)
{
	this->setOrigin((2 * this->getPosition().x + this->getRadius()) / 2, (2 * this->getPosition().y + this->getRadius()) / 2);
	this->setPosition(window.x / 2, window.y / 2);
	this->setFillColor(sf::Color::Red);
}

bool Ball::CollisionWithWall()
{
	if (this->getPosition().x + this->speed.x * dt < 0 || this->getPosition().x + this->speed.x * dt > window.x)
		return true;
	else
		return false;
}

bool Ball::CollisionWithPlayer(Paddle& player)
{
	sf::FloatRect currPos = this->getGlobalBounds();
	sf::FloatRect nextPos = currPos;
	
	nextPos.left = currPos.left + (this->speed.x * dt);
	nextPos.top = currPos.top + (this->speed.y * dt);

	if (nextPos.intersects(player.getGlobalBounds()))
		return true;
	else 
		return false;
		
}

bool Ball::IsOutOfBounds()
{
	sf::Vector2f position = this->getPosition();

	if (position.x > window.x || position.x < 0 || position.y > window.y || position.y < 0)
		return true;
	else
		return false;
}

void Ball::Move()
{
	if (this->CollisionWithPlayer(player1))
	{
		float distance = std::abs(player1.getPosition().x - this->getPosition().x);
		float speedModifier = 400 * distance / (Paddle::width / 2);
		
		this->speed.y = this->speed.y * -1.0f;
		
		if (this->getPosition().x > player1.getPosition().x)
			this->speed.x =  speedModifier;

		else
			this->speed.x = -speedModifier;

	}
	
	if (this->CollisionWithPlayer(player2))
	{
		float distance = std::abs(player2.getPosition().x - this->getPosition().x);
		float speedModifier = 400 * distance / (Paddle::width / 2);
		
		this->speed.y = this->speed.y * -1.0f;
		
		if (this->getPosition().x > player2.getPosition().x)
			this->speed.x =  speedModifier;

		else
			this->speed.x = -speedModifier;

	}

	
	if (this->CollisionWithWall())
	{
		this->speed.x *= -1;
	}

	if (this->IsOutOfBounds())
	{
		this->setPosition(window.x / 2, window.y / 2);
		this->speed = sf::Vector2f (0.0f, 200.0f);
	}

	this->move(this->speed * dt);
}

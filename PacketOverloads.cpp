#include "PacketOverloads.h"

//Vector2

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& vector)
{
	return packet << vector.x << vector.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector)
{
	return packet >> vector.x >> vector.y; 
}

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f vector)
{
	return packet << vector.x << vector.y;
}

//Paddle

sf::Packet& operator <<(sf::Packet& packet, Paddle& paddle)
{
	return packet << paddle.getPosition();
}

void operator >> (sf::Packet& packet, Paddle& paddle)
{
	sf::Vector2f position;
	packet >> position;
	paddle.setPosition(position);
}


//Ball

sf::Packet& operator <<(sf::Packet& packet, Ball& ball)
{
	return packet << ball.getPosition();
}

void operator >>(sf::Packet& packet, Ball& ball)
{
	sf::Vector2f position;
	packet >> position;
	ball.setPosition(position);
}
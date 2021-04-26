#pragma once
#include "Objects.h"
#include <SFML/include/Network.hpp>
//sf::Packet overloads

//Vector2

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f& vector);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector);

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f vector);

//Paddle

sf::Packet& operator <<(sf::Packet& packet, Paddle& paddle);

void operator >>(sf::Packet& packet, Paddle& paddle);

//Ball

sf::Packet& operator <<(sf::Packet& packet, Ball& ball);

void operator >>(sf::Packet& packet, Ball& ball);
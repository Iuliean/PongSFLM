#pragma once
#include <SFML/include/Network.hpp>
#include <vector>

#include "Objects.h"

void setServerContext(sf::Vector2u newWindow);

class Server
{
private:
	
	Ball ball;
	sf::TcpListener listener;
	std::vector<sf::TcpSocket*> players;
	int PORT;

public:
	
	Server(int port);
	~Server();

	void WaitForPlayers();
	void Start();
	void SendData();

};

class Client
{
private:
	
	int playerNumber;
	sf::TcpSocket serverSocket;

	void SendInput(std::string direction);
	void GetObjectPositions(Ball& ball);

public:
	
	Client(std::string ip, int port);
	~Client();

	void Start();


};


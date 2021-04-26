#include <iostream>

#include "ServerAndClient.h"
#include "PacketOverloads.h"

static sf::Vector2u window;
Paddle	player1;
Paddle	player2;
float dt;

void setServerContext(sf::Vector2u newWindow)
{
	setObjectContext(newWindow);
	window  = newWindow;
	player1 = Paddle (window.x / 2, window.y - 10);
	player2 = Paddle (window.x / 2, 10);
}

 //Server
Server::Server(int port)
{
	this->PORT = port;
}

Server::~Server()
{
	for (auto client : this->players)
	{
		delete client;
	}
}

//Sends data regading all objects (the two paddles and the ball)
void Server::SendData()
{
	for (auto client : this->players)
	{
		sf::Packet packetData;
		
		packetData << player1;
		packetData << player2;
		packetData << this->ball;
		
		client->send(packetData);
		client->receive(packetData);
	}
}

void Server::Start()
{
	
	sf::Clock dt_clock;

	while (true)
	{
		dt = dt_clock.restart().asSeconds();

		//Receivin player movement and moving the according paddle
		for (auto client : this->players)
		{
			//The packet should contain and int indicating the player and a string indicating the direction in which he moved
			sf::Packet input;
			if (client->receive(input) == sf::Socket::Done)
			{
				int player;
				std::string intermediate;
				char movement;

				input >> player;
				input >> intermediate;

				movement = intermediate[0];
				
				if (player == 1)
				{
					switch (movement)
					{
					case 'L':
						player1.MoveLeft();
						client->send(input);
						break;
					case 'R':
						player1.MoveRight();
						client->send(input);
						break;
					case 'N':
						client->send(input);
					}
				}
				else
				{
					if (player == 2)
					{

						switch (movement)
						{
						case 'L':
							player2.MoveLeft();
							client->send(input);
							break;
						case 'R':
							player2.MoveRight();
							client->send(input);
							break;
						case 'N':
							client->send(input);
						}
					}
					else
					{
						client->send(input);
					}
				}
			}

			//Updating the ball object
			this->ball.Move();
		}
		
		this->SendData();
	}
}

void Server::WaitForPlayers()
{
	if (this->listener.listen(PORT) != sf::Socket::Done)
	{
		std::cout << "Could not bind listener";
	}
	else
	{
		while (this->players.size() < 2)
		{
			sf::TcpSocket* client = new sf::TcpSocket;

			if (listener.accept(*client) != sf::Socket::Done)
			{
				std::cout << "Could not connect";
			}
			else
			{
				//Sending information about which client is the respective player
				int player;
				sf::Packet packet;
				player = this->players.size() + 1;

				packet << player;
				client->send(packet);
				client->receive(packet);

				this->players.push_back(client);
			}
		}
	}

}

//Client

//Makes the initial connection to the server and waits for a player number to be assigend to it
Client::Client(std::string ip, int port)
{
	sf::Packet packet;

	this->serverSocket.connect(ip, port);
	this->serverSocket.receive(packet);

	packet >> this->playerNumber;

	if (this->playerNumber == 1 || this->playerNumber == 2)
	{
		packet << "OK";
		serverSocket.send(packet);
	}
}

Client::~Client()
{
	serverSocket.disconnect();
}

void Client::GetObjectPositions(Ball& ball)
{
	sf::Packet objectsPacket;
	this->serverSocket.receive(objectsPacket);

	objectsPacket >> player1;
	objectsPacket >> player2;
	objectsPacket >> ball;

	this->serverSocket.send(objectsPacket);
}

//Creates inputPacket and sends it to the server
void Client::SendInput(std::string direction)
{
	sf::Packet inputPacket;
	
	inputPacket << this->playerNumber;
	inputPacket << direction;

	this->serverSocket.send(inputPacket);
	this->serverSocket.receive(inputPacket);
}

void Client::Start()
{
	Ball ball;
	sf::RenderWindow window(sf::VideoMode(500, 500), "PONG!!");

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		//windwo event loop
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::EventType::Closed:
				window.close();
			}
		}

		//Data sending and receiving
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->SendInput("L");
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				this->SendInput("R");
			else
				this->SendInput("N");
		}
		
		this->GetObjectPositions(ball);

		window.clear();
		window.draw(player1);
		window.draw(player2);
		window.draw(ball);
		window.display();
	}
}
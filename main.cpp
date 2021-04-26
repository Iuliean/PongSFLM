#include <iostream>
#include <string.h>
#include <thread>


#include "ServerAndClient.h"
#include "PacketOverloads.h"

void startServer(int PORT)
{
    sf::Vector2u windowSize(500, 500);

    setServerContext(windowSize);
    Server server(PORT);

    std::cout << "Waiting for connections..\n";
    server.WaitForPlayers();

    std::cout << "Starting the game";
    server.Start();
}

int main()
{
    const int PORT = 25565;

    int input;

    std::cout << "1.To host a game\n2.To join a game\n";
    std::cin >> input;

    if (input == 1)
    {
        std::thread serverThread(startServer, PORT);
        Client client("localhost", PORT);
        client.Start();
        serverThread.join();
    }
    else
    {
        std::cout << "Enter server ip: ";
        
        std::string ip;
        std::cin >> ip;

        Client client(ip, PORT);
        client.Start();
    }

    return 0;
}
#include "server.h"

Server::Server(char* port)
{
    
    m_connectionServer = new Connection(NULL, port);
    m_connectionServer->InitServer();
    my_terminal = Terminal(m_connectionServer->getSocket());
}

Server::~Server()
{
    printf("Closing server\n");
}

int Server::runServer()
{
    m_connectionClient = my_terminal.Connect();


    //Cette partie l� c'est pour tester la connection, � enlever plus tard.
    char recvBuffer[DEFAULT_BUFLEN];
    m_connectionClient->receiveMessage(recvBuffer);
    printf("Message re�u par le serveur: %s\n", recvBuffer);
    return 0;
}
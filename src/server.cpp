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


    //Cette partie là c'est pour tester la connection, à enlever plus tard.
    char recvBuffer[DEFAULT_BUFLEN];
    m_connectionClient->receiveMessage(recvBuffer);
    printf("Message reçu par le serveur: %s\n", recvBuffer);
    return 0;
}
#include "server.h"

Server::Server(char* port)
{
    
    my_terminal = new Terminal(NULL, port);
}

Server::~Server()
{
    printf("Closing server\n");
}

void Server::readSockets()
{
    fd_set readingSet;
    FD_ZERO(&readingSet);
    fd_set writingSet;
    FD_ZERO(&writingSet);

    for (int i = 0; i < m_connectionsClients.size(); i++) {
        FD_SET(m_connectionsClients[i]->getSocket(), &readingSet);
    }

    char recvBuffer[DEFAULT_BUFLEN];

    int ret = select(0, &readingSet, &writingSet, nullptr, nullptr);
    if (ret > 0) 
    {
        for (int i = 0; i < m_connectionsClients.size(); i++) {
            if (FD_ISSET(m_connectionsClients[i]->getSocket(), &readingSet)) {
                m_connectionsClients[i]->receiveMessage(recvBuffer);
                printf("Message recu par le serveur: %s\n", recvBuffer);
            }
        }
    }
}

int Server::runServer()
{
    m_connectionsClients.push_back(new Connection(my_terminal->Connect()));
    while (TRUE) {
        readSockets();
    }

    /*
    //Cette partie là c'est pour tester la connection, à enlever plus tard.
    char recvBuffer[DEFAULT_BUFLEN];
    m_connectionClient->receiveMessage(recvBuffer);
    printf("Message reçu par le serveur: %s\n", recvBuffer);*/
    return 0;
}
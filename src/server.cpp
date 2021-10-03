#include "server.h"

Server::Server(char* port)
{
    
    m_terminal = new Terminal(NULL, port);
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

    FD_SET(m_terminal->getSocket(), &readingSet);

    for (std::vector<Connection*>::iterator it = m_connectionsClients.begin(); it != m_connectionsClients.end(); it++) {
        FD_SET((*it)->getSocket(), &readingSet);
    }
    char recvBuffer[DEFAULT_BUFLEN];

    int ret = select(0, &readingSet, &writingSet, nullptr, nullptr);
    if (ret > 0) 
    {
        if (FD_ISSET(m_terminal->getSocket(), &readingSet)) {
            m_connectionsClients.push_back(new Connection(m_terminal->Connect()));
        }

        for (std::vector<Connection*>::iterator it = m_connectionsClients.begin(); it != m_connectionsClients.end(); it++) {
            if (FD_ISSET((*it)->getSocket(), &readingSet)) {
                (*it)->receiveMessage(recvBuffer);
                printf("Message recu par le serveur: %s\n", recvBuffer);
            }
        }
    }
}

int Server::Update()
{
    while (TRUE) {
        readSockets();
    }
    return 0;
}
#include "client.h"


Client::Client(char* addr, char* port)
{
    m_connection = new Connection(addr,port);
}

Client::~Client()
{
    printf("Closing client\n");
}


int Client::Update() {
    
    while (TRUE) {
        readSocket();
    }
    //Cette partie là c'est pour tester la connection, à enlever plus tard.
    return 0;
}

void Client::readSocket()
{
    fd_set readingSet;
    FD_ZERO(&readingSet);
    fd_set writingSet;
    FD_ZERO(&writingSet);

    FD_SET(m_connection->getSocket(), &readingSet);

    char recvBuffer[DEFAULT_BUFLEN];

    int ret = select(0, &readingSet, &writingSet, nullptr, nullptr);
    if (ret > 0)
    {
        if (FD_ISSET(m_connection->getSocket(), &readingSet)) {
            m_connection->receiveMessage(recvBuffer);
            printf("Message recu par le client: %s\n", recvBuffer);
        }
    }
}

void Client::sendMessage(char* message)
{
    m_connection->sendMessage(message);
}

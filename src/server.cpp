#include "server.h"
#include "server.h"
#include "server.h"

Server::Server(std::string port) : m_quit(false)
{
    m_terminal = new Terminal("", port);
    m_threadNetwork = std::thread(&Server::Update, this);
}

Server::~Server()
{
    m_threadNetwork.join();
    std::cout << "Closing server\n";
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
    TIMEVAL tv = { 0,0 };

    int ret = select(0, &readingSet, &writingSet, nullptr, &tv);
    if (ret > 0) 
    {
        if (FD_ISSET(m_terminal->getSocket(), &readingSet)) {
            m_connectionsClients.push_back(new Connection(m_terminal->Connect()));
            std::cout << "Client connecte\n";
        }
        for (std::vector<Connection*>::iterator it = m_connectionsClients.begin(); it != m_connectionsClients.end();) {
            if (FD_ISSET((*it)->getSocket(), &readingSet)) {
                int i_Result = (*it)->receiveMessage(recvBuffer);
                if (i_Result > 0) {
                    std::cout << "Broadcasting message: " << recvBuffer << std::endl;
                    broadcast(recvBuffer, (*it));
                }
                else{ 
                    if (WSAGetLastError() == 10054) {
                        std::cout << "Client disconnected\n";
                        it = m_connectionsClients.erase(it);
                        continue;
                    }
                }
            }
            ++it;
        }
    }
}

void Server::broadcast(const std::string message)
{
    for (std::vector<Connection*>::iterator it = m_connectionsClients.begin(); it != m_connectionsClients.end(); it++) {
        (*it)->sendMessage(message);
    }
}

void Server::broadcast(const std::string message, const Connection* origin)
{
    for (std::vector<Connection*>::iterator it = m_connectionsClients.begin(); it != m_connectionsClients.end(); it++) {
        if((*it)!= origin) (*it)->sendMessage(message);
    }
}

int Server::Update()
{
    while (!m_quit) {
        readSockets();
    }
    return 0;
}

void Server::Quit()
{
    m_quit = true;
    
}

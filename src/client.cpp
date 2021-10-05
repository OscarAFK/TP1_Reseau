#include "client.h"


Client::Client(std::string addr, std::string port) : quit(FALSE)
{
    m_connection = new Connection(addr,port);
    m_threadNetwork = std::thread(&Client::Update, this);
}

Client::~Client()
{
    m_threadNetwork.join();
    std::cout << "Closing client\n";
}


int Client::Update() {
    
    while (!quit) {
        readSocket();
    }
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
    TIMEVAL tv = { 0,0 };

    int ret = select(0, &readingSet, &writingSet, nullptr, &tv);
    if (ret > 0)
    {
        if (FD_ISSET(m_connection->getSocket(), &readingSet)) {
            int i_Result = m_connection->receiveMessage(recvBuffer);
            if (i_Result > 0) {
                std::cout << "Message from server: " << recvBuffer << std::endl;
            }
            else {
                if (WSAGetLastError() == 10054) {
                    std::cout << "Server disconnected\n";
                    m_connection = nullptr;
                    Quit();
                }
            }
        }
    }
}

void Client::sendMessage(const std::string message)
{
    m_connection->sendMessage(message);
}

bool Client::isServerUp()
{
    return m_connection!=nullptr;
}

void Client::Quit()
{
    quit = true;
}

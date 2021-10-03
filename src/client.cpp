#include "client.h"


Client::Client(char* addr, char* port)
{
    m_connection = new Connection(addr,port);
    m_connection->ConnectToServer();
}

Client::~Client()
{
    printf("Closing client\n");
}


int Client::runClient() {
    

    //Cette partie là c'est pour tester la connection, à enlever plus tard.
    m_connection->sendMessage("Hello World");
    return 0;
}


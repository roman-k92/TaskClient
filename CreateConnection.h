#pragma once

#include <iostream>
#include <string>
#include <cstring> 
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <chrono>
#include <ctime>
#include <sstream> 
#include <iomanip>

class CreateConnection
{
private:
    const char* m_host;

    std::string m_clientName;
    uint16_t m_port;
    int m_periodSec;

    int connectTCP();

public:
    CreateConnection();

    int setInputParameters(std::string clientName, uint16_t port, int periodSec);
    int sendMessage();
};


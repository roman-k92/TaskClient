#include <iostream>
#include <string>

#include "CreateConnection.h"

int main(int argc, char* argv[])
{
    std::string clientName = "";
    uint16_t port = 0;
    int periodSec = 0;

    
    // Check input parameters
    if (argc < 4)
    {
        std::cout << "Incorrect the input parameters!\n";
        return 0;
    }
    else
    {
        clientName = argv[1];
        port = std::stoi(argv[2]);
        periodSec = std::stoi(argv[3]);
    }

    std::cout << "Input parameters are " << clientName << "; " << port << "; " << periodSec << std::endl;

    CreateConnection cc;
    int status = cc.setInputParameters(clientName, port, periodSec);
    if (status < 0)
    {
        std::cout << "Input data are incorrect, status = " << status << std::endl;
        return 0;
    }

    status = cc.sendMessage();
    if (status < 0)
    {
        std::cout << "Couldn't send a message, status = " << status << std::endl;
    }

    return 0;
}
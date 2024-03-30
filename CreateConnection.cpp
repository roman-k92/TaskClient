#include "CreateConnection.h"

CreateConnection::CreateConnection()
    : m_host("192.168.56.106")
{
}

int CreateConnection::setInputParameters(std::string clientName, uint16_t port, int periodSec)
{
    if (clientName.empty() )
    {
        std::cout << "The client name is empty";
        return -1;
    }
    else if (port < 1)
    {
        std::cout << "Incorrect a port number";
        return -1;
    }
    else if (periodSec < 1)
    {
        std::cout << "Incorrect a period";
        return -1;
    }

    m_clientName = clientName;
    m_port = port;
    m_periodSec = periodSec;

    return 0;

}

int CreateConnection::connectTCP()
{
    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);
    inet_pton(AF_INET, m_host, &sin.sin_addr); // IP-����� � �������� �����

    int s = socket(AF_INET, SOCK_STREAM, 0); // ���������� ������

    int connectStatus = connect(s, (struct sockaddr*)&sin, sizeof(sin));

    if (connectStatus < 0)
    {
        std::cout << "Couldn't create a connection";

        return -1;
    }

    return s;
}

int CreateConnection::sendMessage()
{
    while (true)
    {
        sleep(m_periodSec);

        int s = connectTCP();
        if (s < 0)
        {
            std::cout << "Troubles with a TCP connection\n";
            return -1;
        }

        // �������� ������� �����
        std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();

        // ������������� � ������������ �� ����� Unix 01.01.1970
        std::chrono::milliseconds currMs = std::chrono::duration_cast<std::chrono::milliseconds>(currTime.time_since_epoch());
              
        // �������������� � ������ ���, ����� �����
        // ����� ������� � ��������� �������
        std::chrono::time_point<std::chrono::system_clock> dt(currMs);
        time_t tt = std::chrono::system_clock::to_time_t(dt);

        // �������������� ���� � ������� � ������ ������
        // F - %Y-%m-%d; T - %H:%M:%S
        std::stringstream ss;
        ss << std::put_time(std::localtime(&tt), "%F %T");

        // ������� ������ ������������, ����� ����� ��� ������ � ���
        int mSec = currMs.count() % 1000;

        // ���������� ����� � �� ��� ��������� �����������
        std::string outMs = "";
        if (mSec == 0)
        {
            outMs = "000";
        }

        else if (mSec < 10)
        {
            outMs = "00" + std::to_string(mSec);
        }
        else if (mSec < 100)
        {
            outMs = "0" + std::to_string(mSec);
        }
        else
        {
            outMs = std::to_string(mSec);
        }

        // �������� ������
        std::string outStr = "[" + ss.str() + "." + outMs + "] " + m_clientName;

        // �������� ������
        ssize_t send = write(s, outStr.data(), outStr.size() );
        
        // ����� � �������
        std::cout << "You sent " << outStr << "\t" << send << " bytes" << std::endl;
    
        close(s);
    }
    
    return 0;
}
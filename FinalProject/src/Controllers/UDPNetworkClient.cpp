/**
 *  @file   UDPNetworkClient.cpp
 *  @brief  UDP Network Client class that handles sending and receiving commands.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#include "UDPNetworkClient.hpp"
#include <iostream>
#include <Utils/CommandPacket.hpp>
#include <Commands/Brush.hpp>
#include "Utils/CommandFactory.hpp"

// Default Constructor
UDPNetworkClient::UDPNetworkClient(std::string username, unsigned short port) {
    m_username = username;
    m_port = port;
    m_socket.bind(m_port);
    m_socket.setBlocking(false);
}

// Default Destructor
UDPNetworkClient::~UDPNetworkClient() {
    std::cout << "Client destructor called" << std::endl;
}

// Join a server
// For this function, we will setup the server for which we will attempt to communicate
int UDPNetworkClient::joinServer(sf::IpAddress serverAddress, unsigned short serverPort) {
    std::cout << "UDPClient(" << m_username << ") will attempt to join server: " << std::endl;
    m_serverIpAddress = serverAddress;
    m_serverPort = serverPort;
    return 1;
}

// Send data to server
bool UDPNetworkClient::sendCommand(CommandPacket *data) {
    sf::Packet p;
    sf::Uint32 x = data->coordinates.x;
    sf::Uint32 y = data->coordinates.y;
    int type = static_cast<int>(data->type);

    // Pack the packet
    p << type << m_username << x << y << data->color.r << data->color.g << data->color.b << data->brushSize;

    if (m_socket.send(p, m_serverIpAddress, m_serverPort) == sf::Socket::Done) {
        std::cout << "Client(" << m_username << ") sending packet" << std::endl;
        return true;
    } else {
        std::cout << "Client error? Wrong IP?" << std::endl;
        return false;
    }
}


// Receive data from the server
bool UDPNetworkClient::receiveData(sf::Image *image, CommandFactory *factory) {
    sf::IpAddress copyAddress = m_serverIpAddress;
    unsigned short copyPort = m_serverPort;

    sf::Packet temp;

    CommandPacket receivedData;
    sf::Int8 r, g, b;   // to store sf::Color
    sf::Uint32 x, y;    // to store coordinates
    int bs, type;       // store brush size and command type
    std::string uname;

    if (m_socket.receive(temp, copyAddress, copyPort) == sf::Socket::Done) {

        if (temp >> type >> uname >> x >> y >> r >> g >> b >> bs) {
            std::cout << std::endl << "Packet received from " << uname << std::endl;
        }

        receivedData.coordinates.x = x;
        receivedData.coordinates.y = y;
        receivedData.brushSize = bs;
        receivedData.type = static_cast<CommandType>(type);

        sf::Color receivedColor(r, g, b);
        receivedData.color = receivedColor;

        factory->getCommand(&receivedData);

        return true;
    }
    return false;
}

// Return our username
std::string UDPNetworkClient::getUsername() {
    return m_username;
}

// Set our username
int UDPNetworkClient::setUsername(std::string name) {
    m_username = name;
    return 1;
}


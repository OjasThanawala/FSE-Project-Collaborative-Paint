/**
 *  @file   UDPNetworkServer.cpp
 *  @brief  UDP Network Server that communicates with Clients.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#include "UDPNetworkServer.hpp"
#include <iostream>
#include <Types/CommandType.hpp>


// Here we are going to 'name' our server and specify the address and port.
// It might seem a little weird to specify our own address, but we will want
// to use this information so we know where data is being received from.
// The port again we get to choose, as long as it is not previously being used
// we can use it.
UDPNetworkServer::UDPNetworkServer(std::string name, sf::IpAddress address, unsigned short port) {
    m_name = name;
    m_ipAddress = address;
    m_port = port;
}

// Our destructor
UDPNetworkServer::~UDPNetworkServer() {}

// Start the server
//
// Here we are going to start a non-blocking UDP server.
// We'll bind to a port to see if it is available. If it is,
// then we are going to run the server forever.
int UDPNetworkServer::start() {
    std::cout << "Starting UDP Network server" << std::endl;
    // Attempt to bind to a port
    int status;
    status = (m_socket.bind(m_port) != sf::Socket::Done);
    if (status) {
        std::cout << "Unable to bind -- Error: " << status << std::endl;
        return status;
    }
    // display IpAddress and port the server is running on
    std::cout << "--------------------" << std::endl;
    std::cout << "Server IpAddress:" << m_ipAddress << std::endl;
    std::cout << "Server Port:" << m_port << std::endl;
    std::cout << "--------------------" << std::endl;

    // wait for first client to join
    std::cout << std::endl << std::endl << "Waiting for the first client to join" << std::endl;
    bool idleMode = true;
    while (idleMode) {
        sf::Packet temp;
        sf::IpAddress senderIp;
        unsigned short senderPort;
        if (m_socket.receive(temp, senderIp, senderPort) == sf::Socket::Done) {
            int type;
            std::string client;
            m_activeClients[senderPort] = senderIp;
            temp >> type >> client;
            std::cout << std::endl << "First Client connected: " << client << std::endl;
            idleMode = false;
        }
    }

    // Start the server
    // as other possible states.
    m_start = true;

    m_socket.setBlocking(false);

    // Start a server that will run forever
    while (m_start) {
        sf::Packet temp;
        sf::IpAddress senderIp;
        unsigned short senderPort;
        // If the server receives a message
        // then we want to broadcast that message out to
        // all potential folks who have joined our server.
        if (m_socket.receive(temp, senderIp, senderPort) == sf::Socket::Done) {
            int type;
            std::string clientName;
            if (temp >> type >> clientName) {
                std::cout << "\tI(the server) received packet from " << clientName << std::endl;
            }

            if (static_cast<CommandType>(type) == CommandType::CONNECT) {
                std::cout << "Connected a First time joiner: " << clientName << std::endl;
                handleClientJoining(senderPort, senderIp);
                m_activeClients[senderPort] = senderIp;
                continue;
            }
            if (static_cast<CommandType>(type) == CommandType::DISCONNECT) {
                std::cout << "Disconnecting client: " << clientName << std::endl;
                m_activeClients.erase(senderPort);
                continue;
            }

            m_packetHistory.push_back(temp);
            std::cout << "total messages: " << m_packetHistory.size() << std::endl;

            std::map<unsigned short, sf::IpAddress>::iterator ipIterator;
            for (ipIterator = m_activeClients.begin(); ipIterator != m_activeClients.end(); ipIterator++) {
                if (ipIterator->first != senderPort) {
                    m_socket.send(temp, ipIterator->second, ipIterator->first);
                }
            }
        }

        if (m_activeClients.empty()) {
            std::cout << std::endl << "All clients disconnected!" << std::endl;
            stop();
        }

    } // End our server while loop
    return 0;
}

// Stops the server from running and removes all clients
void UDPNetworkServer::stop() {
    std::cout << std::endl << "Stopping the server." << std::endl;
    m_start = false;
}


// Typically we'll want to update the client to get the log
// of all of the things that have happened.
void UDPNetworkServer::handleClientJoining(unsigned short clientPort, sf::IpAddress clientIpAddress) {
    std::cout << std::endl << "Updating new client's canvas!" << std::endl;
//     Iterate through every message sent and send it to the client.
    for (auto &i : m_packetHistory) {
        m_socket.send(i,
                      clientIpAddress,
                      clientPort);
    }
}





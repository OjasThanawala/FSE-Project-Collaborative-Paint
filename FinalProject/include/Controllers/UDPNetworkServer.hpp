/**
 *  @file   UDPNetworkServer.hpp
 *  @brief  Server Interface.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#ifndef UDP_NETWORK_SERVER_HPP
#define UDP_NETWORK_SERVER_HPP

// Include our Third-Party SFML Header
#include <SFML/Network.hpp>

// Our Command library
#include "Utils/Command.hpp"

// Other standard libraries
#include <string>
#include <vector>

// Create a non-blocking UDP server
class UDPNetworkServer{
public:
    // Default Constructor
    UDPNetworkServer(std::string name,sf::IpAddress address, unsigned short port);
    // Default Destructor
    ~UDPNetworkServer();
    // Start the server
    int start();
    // Stops the server from running and removes all clients
    void stop();

private:

    // What to do when the client joins the server
    void handleClientJoining(unsigned short clientPort, sf::IpAddress clientIpAddress);
	// Name for our server
	std::string m_name; 
    // Flag for if the server should stop.
    bool m_start;
    // Ip Address for our UDP Server
    sf::IpAddress m_ipAddress;
    unsigned short m_port;
    // A UDP Socket for our server
    sf::UdpSocket m_socket;
    // A data structure to hold all of the clients.
    std::map<unsigned short, sf::IpAddress> m_activeClients;
    // A data structure to hold all of the packets received
    std::vector<sf::Packet> m_packetHistory;
};

#endif

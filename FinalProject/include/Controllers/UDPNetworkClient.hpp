/**
 *  @file   UDPNetworkClient.hpp
 *  @brief  Client interface.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#ifndef UDP_NETWORK_CLIENT_HPP
#define UDP_NETWORK_CLIENT_HPP

// Include our Third-Party SFML Header
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

// Other standard libraries
#include <string>
#include <vector>

class Command;

class App;

class CommandPacket;

class CommandFactory;

// Create a non-blocking UDPClient
// This client will provide a way to connect with some server
// and send information to that server.
class UDPNetworkClient {
public:
    // Default Constructor
    UDPNetworkClient(std::string username, unsigned short port);

    // Default Destructor
    ~UDPNetworkClient();

    // Our client can attempt a UDP connection to join
    // any server so long as we know the server address and the server port.
    // Once joined, we can send commands.
    int joinServer(sf::IpAddress serverAddress, unsigned short serverPort);

    // Send data to server
    bool sendCommand(CommandPacket *);

    // Receive data from the server
    bool receiveData(sf::Image *, CommandFactory *);

    // Get username
    std::string getUsername();

    // Set username
    int setUsername(std::string name);

    // Get IPAddress
    sf::IpAddress getIpAddress();

    // Get client Port
    int getPort();

private:
    // Information about our user and connection
    std::string m_username;
    // The port which we will try to communicate from
    unsigned short m_port;
    // Our clients IP Address
    sf::IpAddress m_ipAddress;
    // The server port which we will try to send information through
    unsigned short m_serverPort;
    // The server Ip address for which we will send information to.
    sf::IpAddress m_serverIpAddress;
    // A UDP Socket for our client to create an end-to-end communication
    // with another machine in the world.
    sf::UdpSocket m_socket;
};

#endif

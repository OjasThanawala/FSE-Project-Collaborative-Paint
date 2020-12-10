/**
 *  @file   CommandPacket.hpp
 *  @brief  Command packet data is used as an input to CommandFactory based on the CommandType.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#ifndef COMMANDDATA_HPP
#define COMMANDDATA_HPP

#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include "Types/CommandType.hpp"

class CommandPacket {
    public:
        CommandType type;
        sf::Vector2i coordinates;
        sf::Color color;
        int brushSize;
};

#endif //APP_COMMANDDATA_HPP

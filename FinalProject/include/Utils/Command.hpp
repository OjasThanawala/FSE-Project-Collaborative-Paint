/**
 *  @file   Command.hpp
 *  @brief  Represents an actionable command by the user.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
// Include standard library C++ libraries.
#include <string>
// Project header files

// The command class
class Command{

public:
	// Destructor for a command
	virtual ~Command();
	// method to execute a command
	virtual bool execute() = 0;
	// method to get pixel coordinates where commands need to be executed (applicable to select commands only)
	virtual sf::Vector2i getCoordinates() = 0;
	// method to get command color
    virtual sf::Color getColor() = 0;
    // method to get brushSize
    virtual int getBrushSize() = 0;
};



#endif

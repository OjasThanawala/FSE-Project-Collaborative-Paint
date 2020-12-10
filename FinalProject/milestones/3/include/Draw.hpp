/** 
 *  @file   Draw.hpp 
 *  @brief  Drawing actions interface. 
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
// Project header files
#include "Command.hpp"

// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
class Draw : Command{
	bool execute(std::string commandDescription);
	bool undo(std::string commandDescription);
};

#endif

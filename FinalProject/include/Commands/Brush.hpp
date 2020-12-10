/** 
 *  @file   Brush.hpp
 *  @brief  Drawing actions interface.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
#ifndef BRUSH_H
#define BRUSH_H

// Include our Third-Party SFML header
// #include ...
#include <SFML/Graphics.hpp>
// Include standard library C++ libraries.
#include <string>
#include <utility>
// Project header files
#include "Utils/Command.hpp"

// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
// 
// In our Draw class note that we have also explicitly marked the
// functions as 'override' to indicate that these functions are
// overriding the behavior of functions in a base class 
// that are implemented as virtual.
class Brush : public Command {
private:
    sf::Color m_prevColor;

protected:
    sf::Vector2i m_coordinate;
    sf::Image *m_image;
    sf::Color m_color;
    int brushSize;
public:
    Brush(const Brush &D);

    Brush &operator=(const Brush &D);

    Brush(sf::Vector2i m_coordinate, sf::Image *m_image, sf::Color color, int brushSize) : m_coordinate(m_coordinate),
                                                                                           m_image(m_image),
                                                                                           m_color(color),
                                                                                           brushSize(brushSize) {}

    bool execute() override;

    sf::Vector2i getCoordinates() override;

    sf::Color getColor() override;

    int getBrushSize() override;
};

#endif

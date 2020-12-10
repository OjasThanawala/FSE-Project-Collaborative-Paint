/** 
 *  @file   BrushUndo.hpp
 *  @brief  Undo actions interface.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
#ifndef BRUSHUNDO_H
#define BRUSHUNDO_H

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
// Project header files
#include "Utils/Command.hpp"

class BrushUndo : public Command {
private:


protected:
    sf::Vector2i m_coordinate;
    sf::Image *m_image;
    sf::Color m_color;
    int brushSize;

public:
    BrushUndo(sf::Vector2i m_coordinate, sf::Image *m_image, sf::Color color, int brushSize) : m_coordinate(
            m_coordinate),
                                                                                               m_image(m_image),
                                                                                               m_color(color),
                                                                                               brushSize(brushSize) {}

    bool execute() override;

    sf::Vector2i getCoordinates() override;

    sf::Color getColor() override;

    int getBrushSize() override;
};

#endif

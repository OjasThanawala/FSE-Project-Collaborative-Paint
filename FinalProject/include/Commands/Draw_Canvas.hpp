/**
 *  @file   Draw_Canvas.cpp
 *  @brief  Drawing Canvas interface.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#ifndef APP_DRAW_CANVAS_H
#define APP_DRAW_CANVAS_H

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
// Include standard library C++ libraries.
#include <string>
#include <utility>
// Project header files
#include "Utils/Command.hpp"


class Draw_Canvas : public Command {

protected:
    sf::Image *m_image;
    sf::Texture *m_texture;
    sf::Color m_color;
public:
    Draw_Canvas(const Draw_Canvas &D);

    ~Draw_Canvas();

    Draw_Canvas &operator=(const Draw_Canvas &D);

    Draw_Canvas(sf::Image *m_image, sf::Texture *m_texture, sf::Color color) : m_image(m_image),
                                                                               m_texture(m_texture), m_color(color) {}

    bool execute() override;

    sf::Vector2i getCoordinates() override;

    sf::Color getColor() override;

    int getBrushSize() override;
};


#endif

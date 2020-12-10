/**
 *  @file   Draw_Canvas.cpp
 *  @brief  Drawing of the entire canvas.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
// Project header files
#include "Draw_Canvas.hpp"

/*! \brief 	N/A
*
*/
bool Draw_Canvas::execute() {
    m_image->create(600, 400, m_color);
    m_texture->loadFromImage(*m_image);
    return true;
}

Draw_Canvas::Draw_Canvas(const Draw_Canvas &D) {
    m_image = D.m_image;
    m_texture = D.m_texture;
    m_color = D.m_color;
}


Draw_Canvas &Draw_Canvas::operator=(const Draw_Canvas &D) {
    m_image = D.m_image;
    m_texture = D.m_texture;
    m_color = D.m_color;

    return *this;
}

// Getter function for pixel coordinates.
sf::Vector2i Draw_Canvas::getCoordinates() {
    sf::Vector2i temp;
    temp.x = 3000;
    temp.y = 3000;
    return temp;
}

// Getter function for color of the pixel.
sf::Color Draw_Canvas::getColor() {
    return m_color;
}

// Getter function to get the size of the brush.
int Draw_Canvas::getBrushSize() {
    return 0;
}


Draw_Canvas::~Draw_Canvas() {}


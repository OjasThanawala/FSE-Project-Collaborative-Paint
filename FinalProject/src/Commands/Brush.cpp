/** 
 *  @file   Brush.cpp
 *  @brief  Brush implementation, all drawing actions are commands.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
#include <iostream>

// Include standard library C++ libraries.
// Project header files
#include "Brush.hpp"

//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wsign-compare"
/*! \brief 	N/A
*		
*/
bool Brush::execute() {
    m_prevColor = m_image->getPixel(m_coordinate.x, m_coordinate.y);
    int i = m_coordinate.x - brushSize < 0 ? 0 : m_coordinate.x - brushSize;
    int iTo =
            m_coordinate.x + brushSize > static_cast<int>(m_image->getSize().x) ? static_cast<int>(m_image->getSize().x)
                                                                                : m_coordinate.x + brushSize;
    while (i <= iTo) {
        int j = m_coordinate.y - brushSize < 0 ? 0 : m_coordinate.y - brushSize;
        int jTo = m_coordinate.y + brushSize > static_cast<int>(m_image->getSize().y)
                  ? static_cast<int>(m_image->getSize().y) : m_coordinate.y + brushSize;
        while (j <= jTo) {
            m_image->setPixel(i, j, m_color);
            j++;
        }
        i++;
    }
    return true;
}

Brush::Brush(const Brush &D) {
    m_coordinate = D.m_coordinate;
    m_image = D.m_image;
    m_color = D.m_color;
}


Brush &Brush::operator=(const Brush &D) {
    m_coordinate = D.m_coordinate;
    m_image = D.m_image;
    m_color = D.m_color;

    return *this;
}

// Getter function for pixel coordinates.
sf::Vector2i Brush::getCoordinates() {
    return m_coordinate;
}

// Getter function for color of the pixel.
sf::Color Brush::getColor() {
    return m_prevColor;
}

// Getter function to get the size of the brush.
int Brush::getBrushSize() {
    return brushSize;
}


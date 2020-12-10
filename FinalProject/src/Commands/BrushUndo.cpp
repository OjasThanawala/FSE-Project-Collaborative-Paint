/** 
 *  @file   Brush_Undo.cpp
 *  @brief  Undo command for all pixels.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

// Include standard library C++ libraries.
#include <SFML/Graphics/Color.hpp>
// #include ...
// Project header files
#include "BrushUndo.hpp"

/*! \brief 	N/A
*		
*/
bool BrushUndo::execute() {
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


sf::Vector2i BrushUndo::getCoordinates() {
    return m_coordinate;
}

sf::Color BrushUndo::getColor() {
    return m_color;
}


int BrushUndo::getBrushSize() {
    return brushSize;
}

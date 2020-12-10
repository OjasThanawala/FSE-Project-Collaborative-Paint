/**
 *  @file   CommandFactory.cpp
 *  @brief  Implementation of CommandFactory.hpp.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
#include <iostream>
#include "Utils/CommandFactory.hpp"
#include "Utils/CommandPacket.hpp"
#include "Brush.hpp"
#include "App.hpp"

/*! \brief 	The getCommand function is used to create a
* command based on the packet received and execute it.
*
*/
void CommandFactory::getCommand(CommandPacket *data) {

    switch (data->type) {
        case CommandType::BRUSH_UNDO: {
            m_app->Undo();
            break;
        }
        case CommandType::BRUSH: {
            m_app->AddCommand(new Brush(data->coordinates, m_app->m_image, data->color, data->brushSize));
            m_app->ExecuteCommand();
            break;
        }
        case CommandType::DRAW_CANVAS: {
            m_app->m_color = data->color;
            m_app->paintImage();
            break;
        }
        case CommandType::REDO: {
            m_app->Redo();
            break;
        }
        case CommandType::CONNECT:
        case CommandType::DISCONNECT:
            break;
    }
}


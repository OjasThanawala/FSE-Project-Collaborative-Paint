/** 
 *  @file   main.cpp
 *  @brief  Main class of the program.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <typeinfo>
// Include standard library C++ libraries.
#include <cassert>
#include <Utils/CommandPacket.hpp>
// Project header files
#include "App.hpp"
#include "Utils/Command.hpp"
#include "Draw_Canvas.hpp"
#include "BrushUndo.hpp"

App::App() {
}

/*! \brief 	When we draw, we would prefer to add
*		a command to a data structure.
*		
*/
void App::AddCommand(Command *c) {
//	 TODO: You may refactor as needed
    m_commands.push(c);
}

/*! \brief 	We should execute commands in a data structure
*		Perhaps we will have to modify the logic in our
*		loop!
*		
*/
void App::ExecuteCommand() {
    while (!m_redo.empty()) {
        m_redo.pop();
    }
    m_commands.top()->execute();
}


/*! \brief This function is used to undo a command on the screen.
 *
 */
void App::Undo() {
    if (!m_commands.empty()) {
        // The command to undo (target command)
        Command *targetCommand = m_commands.top();

        // Create undo command and execute
        m_redo.push(targetCommand);
        auto *temp = new class BrushUndo(targetCommand->getCoordinates(), this->m_image,
                                         this->m_bg_color, targetCommand->getBrushSize());
        temp->execute();
        std::cout << "Undo Executed at: " << temp->getCoordinates().x << "," << temp->getCoordinates().y << std::endl;
        // Remove target command
        m_commands.pop();
    }
}

/*! \brief This function is used to redo a command on the screen.
 *
 */
void App::Redo() {
    if (!m_redo.empty()) {
        m_redo.top()->execute();
        m_commands.push(m_redo.top());
        std::cout << "Redo Executed" << std::endl;
        m_redo.pop();
    } else {
        std::cout << "Nothing to Redo!" << std::endl;
    }
}

/*! \brief 	The paint_image function is used to color the entire
* canvas based on the color selected by the user.
*/
void App::paintImage() {
    Command *draw_obj_paint = new Draw_Canvas(this->m_image, this->m_texture, this->m_color);
    draw_obj_paint->execute();
    this->m_bg_color = this->m_color;
    while (!m_commands.empty()) {
        m_commands.pop();
    }
    while (!m_redo.empty()) {
        m_redo.pop();
    }
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*		
*/
sf::Image &App::GetImage() {
    return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*		
*/
sf::Texture &App::GetTexture() {
    return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*		
*/
sf::RenderWindow &App::GetWindow() {
    return *m_window;
}

/*! \brief 	Destroy we manually call at end of our program.
*		
*/
void App::Destroy() {
    delete m_image;
    delete m_sprite;
    delete m_texture;
}

/*! \brief 	Initializes the App and sets up the main
*		rendering window(i.e. our canvas.)
*/
void App::Init(void (*initFunction)(App *app_test)) {

    //Canvas Variables
    m_window = nullptr;
    m_image = new sf::Image;
    m_sprite = new sf::Sprite;
    m_texture = new sf::Texture;
    m_color = sf::Color::Red;
    m_bg_color = sf::Color::White;
    m_commands.push(new Draw_Canvas(this->m_image, this->m_texture, this->m_bg_color));
    m_gui_window = nullptr;

    // Create our window
    m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Collaborative Paint - Version 2", sf::Style::Titlebar);
    m_window->setVerticalSyncEnabled(true);
    // Create an image which stores the pixels we will update
    m_image->create(600, 400, m_bg_color);
    assert(m_image != nullptr && "m_image != nullptr");
    // Create a texture which lives in the GPU and will render our image
    m_texture->loadFromImage(*m_image);
    assert(m_texture != nullptr && "m_texture != nullptr");
    // Create a sprite which is the entity that can be textured
    m_sprite->setTexture(*m_texture);
    assert(m_sprite != nullptr && "m_sprite != nullptr");
    // Set our initialization function to perform any user
    // initialization
    m_initFunc = initFunction;
}


/*! \brief 	Set a callback function which will be called
		each iteration of the main loop before drawing.
*		
*/

void App::UpdateCallback(void (*updateFunction)(App *app_test, UDPNetworkClient *me, CommandFactory *commandFactory)) {
    m_updateFunc = updateFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop after update.
*		
*/

void App::DrawCallback(void (*drawFunction)(App *app_test, CommandFactory *commandFactory)) {
    m_drawFunc = drawFunction;
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*		
*/

void
App::Loop(void (*gui_loop)(App *app_test, UDPNetworkClient *me), UDPNetworkClient *me, CommandFactory *commandFactory) {

    // Call the init function
    m_initFunc(this);

    // Start the main rendering loop
    while (m_window->isOpen() && m_gui_window->isOpen()) {
        // Initialize gui
        m_gui_loop = gui_loop;
        m_gui_loop(this, me);
        // Clear the window
        m_window->clear();
        // Updates specified by the user
        m_updateFunc(this, me, commandFactory);
        // Additional drawing specified by user
        m_drawFunc(this, commandFactory);
        // Update the texture
        // Note: This can be done in the 'draw call'
        // Draw to the canvas
        m_window->draw(*m_sprite);
        // Display the canvas
        m_window->display();
    }
}





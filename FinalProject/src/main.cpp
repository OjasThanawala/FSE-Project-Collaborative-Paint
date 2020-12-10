/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

// Compile: Use a CMakeLists.txt or you can try compiling with:
// C:/MinGW64/bin/g++ -I C:/Users/urvak/Documents/FSE/SFML-2.5.1/include/ -I ./include/ -L C:/Users/urvak/Documents/FSE/SFML-2.5.1/lib/ -std=c++17 src/*.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system
// g++ -std=c++17 ./src/*.cpp -I./include/ -o App -lsfml-graphics -lsfml-window -lsfml-system
// cppcheck --enable=all *.cpp --suppress=missingIncludeSystem
// Note:	If your compiler does not support -std=c++17, 
//		then try -std=c++14 then -std=c++11.
//		
// HOW TO RUN
//
// ./App

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <Brush.hpp>
#include <Utils/CommandPacket.hpp>
#include <Utils/CommandFactory.hpp>
// Project header files
#include "App.hpp"
#include "Utils/Command.hpp"
#include "Draw_Canvas.hpp"
#include "UDPNetworkServer.hpp"
#include "UDPNetworkClient.hpp"
#include "Types/CommandType.hpp"

// NUKLEAR - for our GUI
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION

#include "Ext/nuklear.h"
#include "Ext/nuklear_sfml_gl2.h"

enum {
    BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN
};
static int op = RED;
struct nk_context *ctx;
int brushSize = 1;

/*! \brief 	Call any initailization functions here.
*		This might be for example setting up any
*		global variables, allocating memory,
*		dynamically loading any libraries, or
*		doing nothing at all.
*		
*/
void initialization(App *app_test) {
    std::cout << "Starting the App" << std::endl;
    std::cout << "Welcome!!" << std::endl;
    std::cout << "Use the following keys to change to use features\n" << std::endl;
    std::cout << "1 -- Change color to Black" << std::endl;
    std::cout << "2 -- Change color to White" << std::endl;
    std::cout << "3 -- Change color to Red" << std::endl;
    std::cout << "4 -- Change color to Green" << std::endl;
    std::cout << "5 -- Change color to Blue" << std::endl;
    std::cout << "6 -- Change color to Yellow" << std::endl;
    std::cout << "7 -- Change color to Magenta" << std::endl;
    std::cout << "8 -- Change color to Cyan" << std::endl;
    std::cout << "Z -- Undo last action" << std::endl;
    std::cout << "Y -- Redo lst undone action" << std::endl;
    std::cout << ", -- Increase brush size" << std::endl;
    std::cout << ". -- Decrease brush size" << std::endl;
    std::cout << "Press Space to clear canvas and change background color to current color selected" << std::endl;
    std::cout << "Press escape key to exit" << std::endl;

    /*  GUI
        We are creating a GUI context, and it needs
        to attach to our 'window'.
    */
    sf::ContextSettings settings(24, 8, 4, 2, 2);
    app_test->m_gui_window = new sf::RenderWindow(sf::VideoMode(400, 600), "GUI Window", sf::Style::Default,
                                                  settings);
    app_test->m_gui_window->setVerticalSyncEnabled(true);
    app_test->m_gui_window->setActive(true);
    app_test->m_gui_window->setPosition(sf::Vector2i(200, 150));
    glViewport(0, 0, app_test->m_gui_window->getSize().x, app_test->m_gui_window->getSize().y);
    ctx = nk_sfml_init(app_test->m_gui_window);
    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();

}


/*! \brief 	The drawGUILayout function is used to render our GUI.
* It includes a section to choose colors, and a slidebar to select
* the brush size.
*/
void drawGUILayout(App *app_test, struct nk_context *ctx) {
    /* GUI */
    if (nk_begin(ctx, "GUI for Collaborative Paint", nk_rect(50, 50, 280, 500),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        // Choosing color of the pixel
        nk_layout_row_dynamic(ctx, 30, 2);
        nk_label(ctx, "Choose Color:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 33, 2);
        if (nk_option_label(ctx, "red", op == RED)) {
            op = RED;
        }
        if (nk_option_label(ctx, "black", op == BLACK)) {
            op = BLACK;
        }
        if (nk_option_label(ctx, "green", op == GREEN)) {
            op = GREEN;
        }
        if (nk_option_label(ctx, "blue", op == BLUE)) {
            op = BLUE;
        }
        if (nk_option_label(ctx, "white", op == WHITE)) {
            op = WHITE;
        }
        if (nk_option_label(ctx, "yellow", op == YELLOW)) {
            op = YELLOW;
        }
        if (nk_option_label(ctx, "magenta", op == MAGENTA)) {
            op = MAGENTA;
        }
        if (nk_option_label(ctx, "cyan", op == CYAN)) {
            op = CYAN;
        }

        // Choosing Brush Size
        nk_layout_row_dynamic(ctx, 100, 2);
        nk_label(ctx, "Choose Brush Size:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 2, 1);
        nk_slider_int(ctx, 1, &brushSize, 10, 1);
    }
    nk_end(ctx);

}

/*! \brief 	The gui loop function which handles initialization
*		and will be executed until the main window is closed.
*
*/
void gui_loop(App *app_test, UDPNetworkClient *me) {
    // OpenGL is the background rendering engine,
    // so we are going to clear our GUI graphics system.
    app_test->m_gui_window->setActive(true);
    app_test->m_gui_window->clear();
    glClear(GL_COLOR_BUFFER_BIT);
    nk_sfml_render(NK_ANTI_ALIASING_ON);
    app_test->m_gui_window->display();
}

/*! \brief 	The choose_color_gui loop function which handles choosing
*		color from the gui window that will be used to draw
*		on the canvas.
*/
void choose_color_gui(App *app_test) {
    if (op == RED) {
        app_test->m_color = sf::Color::Red;
    }
    if (op == BLACK) {
        app_test->m_color = sf::Color::Black;
    }
    if (op == GREEN) {
        app_test->m_color = sf::Color::Green;
    }
    if (op == BLUE) {
        app_test->m_color = sf::Color::Blue;
    }
    if (op == WHITE) {
        app_test->m_color = sf::Color::White;
    }
    if (op == YELLOW) {
        app_test->m_color = sf::Color::Yellow;
    }
    if (op == MAGENTA) {
        app_test->m_color = sf::Color::Magenta;
    }
    if (op == CYAN) {
        app_test->m_color = sf::Color::Cyan;
    }
}


/*! \brief 	The update function presented can be simplified.
*		I have demonstrated two ways you can handle events,
*		if for example we want to add in an event loop.
*		
*/
void update(App *app_test, UDPNetworkClient *me, CommandFactory *commandFactory) {
    sf::Event event{};
    while (app_test->m_window->pollEvent(event)) {
        // Capture any keys that are released
        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::Z: {
                    if (!app_test->m_commands.empty()) {
                        CommandPacket data;
                        data.type = CommandType::BRUSH_UNDO;

                        app_test->Undo();
                        me->sendCommand(&data);
                    } else {
                        std::cout << "Nothing to undo" << std::endl;
                    }
                    break;
                }
                case sf::Keyboard::Y: {
                    CommandPacket data;
                    data.type = CommandType::REDO;

                    app_test->Redo();
                    me->sendCommand(&data);
                    break;
                }
                case sf::Keyboard::Period:
                    if (brushSize < 10) {
                        brushSize++;
                        std::cout << "Brush size increased to " << brushSize << std::endl;
                    } else {
                        std::cout << "Max brush size reached" << std::endl;
                    }
                    break;
                case sf::Keyboard::Comma:
                    if (brushSize > 1) {
                        brushSize--;
                        std::cout << "Brush size decreased to " << brushSize << std::endl;
                    } else {
                        std::cout << "Min brush size reached" << std::endl;
                    }
                    break;

                case sf::Keyboard::Escape: {
                    CommandPacket data;
                    data.type = CommandType::DISCONNECT;
                    me->sendCommand(&data);
                    exit(EXIT_SUCCESS);
                }

                case sf::Keyboard::Space: {
                    CommandPacket data;
                    data.type = CommandType::DRAW_CANVAS;
                    data.color = app_test->m_color;
                    me->sendCommand(&data);
                    app_test->paintImage();
                    break;
                }
                case sf::Keyboard::Num1:
                case BLACK:
                    op = BLUE;
                    std::cout << "Black color selected" << std::endl;
                    app_test->m_color = sf::Color::Black;
                    break;

                case sf::Keyboard::Num2:
                case WHITE:
                    op = WHITE;
                    std::cout << "White color selected" << std::endl;
                    app_test->m_color = sf::Color::White;
                    break;

                case sf::Keyboard::Num3:
                case RED:
                    op = RED;
                    std::cout << "Red color selected" << std::endl;
                    app_test->m_color = sf::Color::Red;
                    break;

                case sf::Keyboard::Num4:
                case GREEN:
                    op = GREEN;
                    std::cout << "Green color selected" << std::endl;
                    app_test->m_color = sf::Color::Green;
                    break;

                case sf::Keyboard::Num5:
                case BLUE:
                    op = BLUE;
                    std::cout << "Blue color selected" << std::endl;
                    app_test->m_color = sf::Color::Blue;
                    break;

                case sf::Keyboard::Num6:
                case YELLOW:
                    op = YELLOW;
                    std::cout << "Yellow color selected" << std::endl;
                    app_test->m_color = sf::Color::Yellow;
                    break;

                case sf::Keyboard::Num7:
                case MAGENTA:
                    op = MAGENTA;
                    std::cout << "Magenta color selected" << std::endl;
                    app_test->m_color = sf::Color::Magenta;
                    break;

                case sf::Keyboard::Num8:
                case CYAN:
                    op = CYAN;
                    std::cout << "Cyan color selected" << std::endl;
                    app_test->m_color = sf::Color::Cyan;
                    break;

                default:
                    break;
            }
        }
    }

    nk_input_begin(ctx);
    while (app_test->m_gui_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            nk_sfml_shutdown();
            app_test->m_gui_window->close();
            exit(EXIT_SUCCESS);
        }
            // Capture any keys that are released
        else if (event.type == sf::Event::KeyReleased) {
            std::cout << "Key Pressed" << std::endl;
            // Check if the escape key is pressed.
            if (event.key.code == sf::Keyboard::Escape) {
                nk_sfml_shutdown();
                app_test->m_gui_window->close();
                exit(EXIT_SUCCESS);
            }
        }
        nk_sfml_handle_event(&event);
    }

    // Complete input from nuklear GUI
    nk_input_end(ctx);

    // Draw our GUI
    drawGUILayout(app_test, ctx);

    // variable to store coordinates of mouse click
    sf::Vector2i coordinate;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        coordinate = sf::Mouse::getPosition(app_test->GetWindow());
        app_test->mouseX = coordinate.x;
        app_test->mouseY = coordinate.y;
        if (app_test->GetWindow().hasFocus()) {
            if (app_test->m_image->getSize().x > unsigned(sf::Mouse::getPosition(app_test->GetWindow()).x) &&
                app_test->m_image->getSize().y > unsigned(sf::Mouse::getPosition(app_test->GetWindow()).y)) {

                if (app_test->mouseX == app_test->pmouseX && app_test->mouseY == app_test->pmouseY) {
                    std::cout << "Repeated clicks" << coordinate.x << "," << coordinate.y << std::endl;
                } else {
                    std::cout << "Pixel Drawn at: " << coordinate.x << "," << coordinate.y << std::endl;
                }

                // choosing color from GUI
                choose_color_gui(app_test);

                // Create command to execute locally
                Command *brush_obj = new Brush(coordinate, app_test->m_image, app_test->m_color, brushSize);

                // Create Brush command data to send to server and ultimately, other connected clients
                CommandPacket commandToBeSent;
                commandToBeSent.brushSize = brushSize;
                commandToBeSent.type = CommandType::BRUSH;
                commandToBeSent.color = app_test->m_color;
                commandToBeSent.coordinates = coordinate;
                // Send Command Data
                me->sendCommand(&commandToBeSent);

                // Execute Command
                app_test->AddCommand(brush_obj);
                app_test->ExecuteCommand();
                app_test->pmouseX = app_test->mouseX;
                app_test->pmouseY = app_test->mouseY;

            } else {
                std::cout << "You are drawing outside the canvas" << std::endl;
            }
        }


    }
    // Listen for incoming packets from other clients
    // If received, CommandFactory will create the suitable command and return it.
    me->receiveData(app_test->m_image, commandFactory);
}


/*! \brief 	The draw call 
*		
*/
void draw(App *app_test, CommandFactory *factory) {
    // Static variable
    static int refreshRate = 0;
    ++refreshRate;    // Increment

    if (refreshRate > 10) {
        app_test->GetTexture().loadFromImage(app_test->GetImage());
        refreshRate = 0;
    }
}

/*! \brief 	The entry point into our program.
*		
*/
int main() {

    std::string role;

    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    if (role[0] == 's') {
        unsigned short port;
        std::cout << "Enter the port number for Server: " << std::endl;
        std::cin >> port;
        std::cout << std::endl << std::endl << "--------INITIALISING SERVER--------" << std::endl << std::endl;

        UDPNetworkServer server("Paint Factory Server", sf::IpAddress::getLocalAddress(), port);
        // Create a server
        // Run the server on local network for now
        server.start();

    } else if (role[0] == 'c') {
        // Create a client and have them join
        std::string uname;
        unsigned short port;
        unsigned short sPort;
        std::cout << "Enter your username:";
        std::cin >> uname;
        std::cout << "Enter client port: ";
        std::cin >> port;
        std::cout << std::endl << std::endl << "--------INITIALISING CLIENT--------" << std::endl << std::endl;
        UDPNetworkClient me(uname, port);

        std::cout << "Enter Server port: ";
        std::cin >> sPort;

        me.joinServer(sf::IpAddress::getLocalAddress(), sPort);
        me.setUsername(uname);

        // Send Connect command to connect to the server
        CommandPacket data;
        data.type = CommandType::CONNECT;
        me.sendCommand(&data);

        App *app = new App();

        // Pass this factory wherever we need to create commands from CommandPacket object
        CommandFactory commandFactory(app);
        // Call any setup function
        // Passing a function pointer into the 'init' function.
        // of our application.
        app->Init(&initialization);
        // Setup your keyboard
        app->UpdateCallback(&update);
        // Setup the Draw Function
        app->DrawCallback(&draw);
        // Call the main loop function
        app->Loop(&gui_loop, &me, &commandFactory);
        // Destroy our app
        app->Destroy();
        nk_sfml_shutdown();
    }
    return 0;
}
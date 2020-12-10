/**
 *  @file   main_test.cpp
 *  @brief  Unit Tests for our program
 *  @author Mike and Ojas Thanawala
 *  @date   2020-10-22
 ***********************************************/

#define CATCH_CONFIG_MAIN

#include "Ext/catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <Commands/Draw_Canvas.hpp>
#include <Controllers/UDPNetworkServer.hpp>
#include <Controllers/UDPNetworkClient.hpp>
#include <CommandType.hpp>
#include <CommandPacket.hpp>
#include <CommandFactory.hpp>
#include <thread>
#include <chrono>
// Project header files
#include "App.hpp"
#include "Brush.hpp"


void initialization([[maybe_unused]] App *app_test) {
    std::cout << "Starting the App" << std::endl;
}

void define_variables(App *app_test) {
    app_test->m_window = nullptr;
    app_test->m_image = new sf::Image;
    app_test->m_sprite = new sf::Sprite;
    app_test->m_texture = new sf::Texture;
}



/*! \brief 	Initialize and destroy the program
*
*/
TEST_CASE("init and destroy") {
    App app_test;
    app_test.Init(&initialization);
    // Destroy our app
    app_test.Destroy();
}

/*! \brief 	Checking if drawing a pixel on canvas is done with Red color
*
*/
TEST_CASE("Check drawing pixel color") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::Red);
    app_test->Destroy();
}


/*! \brief 	Testing drawing a with different brush sizes
*
*/
TEST_CASE("Check drawing different brush sizes") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    int brushSize = 1;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, brushSize);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    for (int i = coordinate.x - brushSize; i <= coordinate.x + brushSize; i++) {
        for (int j = coordinate.y - brushSize; j <= coordinate.y + brushSize; j++) {
            REQUIRE(app_test->GetImage().getPixel(i, j) == sf::Color::Red);
        }
    }
    coordinate.x = 200;
    coordinate.y = 200;
    brushSize = 2;
    Command *draw_test2 = new Brush(coordinate, app_test->m_image, sf::Color::Red, brushSize);
    app_test->AddCommand(draw_test2);
    app_test->ExecuteCommand();
    for (int i = coordinate.x - brushSize; i <= coordinate.x + brushSize; i++) {
        for (int j = coordinate.y - brushSize; j <= coordinate.y + brushSize; j++) {
            REQUIRE(app_test->GetImage().getPixel(i, j) == sf::Color::Red);
        }
    }
    app_test->Destroy();

}


/*! \brief 	Checking if clearing canvas is done with Red color
*
*/
TEST_CASE("Check clearing canvas") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    Command *canvas_test = new Draw_Canvas(app_test->m_image, app_test->m_texture, sf::Color::Red);
    app_test->AddCommand(canvas_test);
    app_test->ExecuteCommand();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::Red);
    app_test->Destroy();
}


/*! \brief 	Checking if clearing canvas removes drwan pixel
*
*/
TEST_CASE("Check clearing canvas should remove anything drawn") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    Command *canvas_test = new Draw_Canvas(app_test->m_image, app_test->m_texture, sf::Color::White);
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    app_test->AddCommand(canvas_test);
    app_test->ExecuteCommand();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    app_test->Destroy();
}


/*! \brief 	Checking if executing an undo command makes the colored pixel white
*
*/
TEST_CASE("Check Undo changes pixel color to white") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    app_test->Undo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    app_test->Destroy();
}



/*! \brief 	Testing undoing a with different brush sizes
*
*/
TEST_CASE("Check undoing different brush sizes") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    int brushSize = 1;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, brushSize);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    for (int i = coordinate.x - brushSize; i <= coordinate.x + brushSize; i++) {
        for (int j = coordinate.y - brushSize; j <= coordinate.y + brushSize; j++) {
            REQUIRE(app_test->GetImage().getPixel(i, j) == sf::Color::Red);
        }
    }
    coordinate.x = 200;
    coordinate.y = 200;
    brushSize = 2;
    Command *draw_test2 = new Brush(coordinate, app_test->m_image, sf::Color::Red, brushSize);
    app_test->AddCommand(draw_test2);
    app_test->ExecuteCommand();
    for (int i = coordinate.x - brushSize; i <= coordinate.x + brushSize; i++) {
        for (int j = coordinate.y - brushSize; j <= coordinate.y + brushSize; j++) {
            REQUIRE(app_test->GetImage().getPixel(i, j) == sf::Color::Red);
        }
    }
    app_test->Destroy();

}


/*! \brief 	Checking Undoing after clearing canvas does nothing
*
*/
TEST_CASE("Undoing clearing canvas should not be performed") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 100;
    Command *canvas_test = new Draw_Canvas(app_test->m_image, app_test->m_texture, sf::Color::White);
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    app_test->AddCommand(canvas_test);
    app_test->ExecuteCommand();
    app_test->Undo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    app_test->Destroy();
}

/*! \brief 	Checking if executing the Redo command makes the white pixel Red
*
*/
TEST_CASE("Check Redo changes pixel color to Red") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 200;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    app_test->Undo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    app_test->Redo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::Red);
    app_test->Destroy();
}

/*! \brief 	Checking if initializing an object of App class results in correct image size.
*
*/
TEST_CASE("Check Image dimensions - using Init function") {
    App *app_test = new App();
    unsigned int width = 600;
    unsigned int height = 400;
    app_test->Init(&initialization);
    REQUIRE(app_test->GetImage().getSize().x == width);
    REQUIRE(app_test->GetImage().getSize().y == height);
    app_test->Destroy();
}

/*! \brief 	Checking if creating an image using App class variables results in correct image size.
*
*/
TEST_CASE("Check Image dimensions - part 2") {
    App *app_test = new App();
    unsigned int width = 600;
    unsigned int height = 400;
    define_variables(app_test);

    app_test->m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2");
    app_test->m_image->create(600, 400, sf::Color::White);
    app_test->m_initFunc = &initialization;
    REQUIRE(app_test->GetImage().getSize().x == width);
    REQUIRE(app_test->GetImage().getSize().y == height);
    app_test->Destroy();
}

/*! \brief 	Test to check that if an Undo is called on a pixel "X" and then another pixel "Y" is drawn,
 * the "X" pixel is not coloured Red if Redo is called after drawing "Y" pixel.
*
*/
TEST_CASE("Redo does nothing after drawing a pixel") {
    App *app_test = new App();
    app_test->Init(&initialization);
    sf::Vector2i coordinate;
    coordinate.x = 100;
    coordinate.y = 200;
    Command *draw_test = new Brush(coordinate, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test);
    app_test->ExecuteCommand();
    app_test->Undo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    sf::Vector2i coordinate_2;
    coordinate_2.x = 150;
    coordinate_2.y = 250;
    Command *draw_test_2 = new Brush(coordinate_2, app_test->m_image, sf::Color::Red, 1);
    app_test->AddCommand(draw_test_2);
    app_test->ExecuteCommand();
    REQUIRE(app_test->GetImage().getPixel(coordinate_2.x, coordinate_2.y) == sf::Color::Red);

    // Checking if pixel on which Undo was executed, before drawing another pixel, does not turn Red if
    // Redo is called after drawing another pixel.
    app_test->Redo();
    REQUIRE(app_test->GetImage().getPixel(coordinate.x, coordinate.y) == sf::Color::White);
    app_test->Destroy();
}


/*! \brief 	Server that the clients will connect to.
*
*/
class thread_obj_server {
public:
    void operator()(int x) {
        UDPNetworkServer server("Server Name", sf::IpAddress::getLocalAddress(), x);
        server.start();
    }
};

/*! \brief 	Client which will receive the data.
*
*/
class thread_receiver_client {
public:
    int operator()(int x) {
        std::this_thread::sleep_for (std::chrono::seconds(3));
        UDPNetworkClient me("Receiver Client ", 50000 + x);
        me.joinServer(sf::IpAddress::getLocalAddress(), 50000);

        // Connect and disconnect from server
        CommandPacket data;
        data.type = CommandType::CONNECT;
        me.sendCommand(&data);

        std::this_thread::sleep_for (std::chrono::seconds(5));

        App app;
        app.Init(&initialization);
        CommandFactory commandFactory(&app);

        REQUIRE(me.receiveData(&app.GetImage(), &commandFactory) == true);
        std::this_thread::sleep_for (std::chrono::seconds(2));

        data.type = CommandType::DISCONNECT;
        me.sendCommand(&data);

        return 0;
    }
};

/*! \brief 	Client which will send the data.
*
*/
class thread_sender_client {
public:
    int operator()(int x) {

        UDPNetworkClient me("Sender Client " , 50000 + x);
        me.joinServer(sf::IpAddress::getLocalAddress(), 50000);

        // Connect and disconnect from server
        CommandPacket data;
        data.type = CommandType::CONNECT;
        me.sendCommand(&data);
        std::this_thread::sleep_for (std::chrono::seconds(5));

        data.type = CommandType::DRAW_CANVAS;
        data.color = sf::Color::Green;
        REQUIRE(me.sendCommand(&data) == true);
        std::this_thread::sleep_for (std::chrono::seconds(2));

        data.type = CommandType::DISCONNECT;
        me.sendCommand(&data);

        return 0;
    }
};

/*! \brief 	Test to check whether the client which is connected to the server is able to send and receive messages
* to and from other clients connected to the server. Every client and the server will run on a separate thread
*
*/
TEST_CASE("Networking test") {
    std::thread server(thread_obj_server(), 50000);
    std::thread client1(thread_sender_client(), 1);
    std::thread client2(thread_receiver_client(), 2);

    client1.join();
    client2.join();
    server.detach();
}




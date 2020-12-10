/**
 *  @file   main_test.cpp 
 *  @brief  Unit Tests for our program
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "ext/catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
// Project header files
#include "App.hpp"
#include "Utils/Command.hpp"
#include "Draw.hpp"


void initialization(void){
    std::cout << "Starting the App" << std::endl;
}
 
/*! \brief  Initialize and destroy the program
*       
*/
TEST_CASE("init and destroy"){  
    App::Init(&initialization);
    // Destroy our app
    App::Destroy();
}

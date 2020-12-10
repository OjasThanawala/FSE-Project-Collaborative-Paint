/**
 *  @file   App.hpp
 *  @brief  App class interface
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/
#ifndef APP_HPP 
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Include standard library C++ libraries.
#include <stack>

// Forward declarations
class Command;
class CommandFactory;
class UDPNetworkClient;

class App{
public:
// Member variables
	// Queue stores the next command to do.
	std::stack<Command*> m_commands;
	// Stack that stores the last action to occur.
	std::stack<Command*> m_redo;
	// Main image	
	sf::Image* m_image;
	// Create a sprite that we overaly
	// on top of the texture.
	sf::Sprite* m_sprite;
	// Texture sent to the GPU for rendering
	sf::Texture* m_texture;
	// Our rendering window
    sf::RenderWindow* m_window;

    // Color of the pixel
    sf::Color m_color;
    //Color of the background image
    sf::Color m_bg_color;

    // Our rendering GUI window
    sf::RenderWindow* m_gui_window;

// Member functions
	void (*m_initFunc)(App*);
	void (*m_updateFunc)(App*, UDPNetworkClient*, CommandFactory*);
	void (*m_drawFunc)(App*, CommandFactory*);
    void (*m_gui_loop)(App*, UDPNetworkClient*);

public:
    // Default constructor which is hidden in the Singleton
    App();

    // Member Variables
	unsigned int pmouseX, pmouseY, mouseX, mouseY;

	// Member functions
	void 	AddCommand(Command* c);
	void 	ExecuteCommand();
    void    Undo();
    void    Redo();
    void    paintImage();
	sf::Image& GetImage();
	sf::Texture& GetTexture();
	sf::RenderWindow& GetWindow();

	void Destroy();
	void Init(void (*initFunction)(App*));
	void UpdateCallback(void (*updateFunction)(App*, UDPNetworkClient*, CommandFactory*));
	void DrawCallback(void (*drawFunction)(App*, CommandFactory*));
	void Loop(void (*gui_loop)(App*, UDPNetworkClient*), UDPNetworkClient*, CommandFactory*);
};


#endif

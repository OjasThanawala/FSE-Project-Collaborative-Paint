/** 
 *  @file   App.hpp 
 *  @brief  App class interface
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef APP_HPP 
#define APP_HPP

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include "Command.hpp"
// Project header files
// #include ...

// Singleton for our Application called 'App'.
class App{
private:
// Member variables
	// Queue stores the next command to do.
	static std::queue<Command*> m_commands;
	// Stack that stores the last action to occur.
	static std::stack<Command*> m_undo;
	// Main image	
	static sf::Image* m_image;
	// Create a sprite that we overaly
	// on top of the texture.
	static sf::Sprite* m_sprite;
	// Texture sent to the GPU for rendering
	static sf::Texture* m_texture;

// Member functions
	// Default constructor which is hidden in the Singleton
	App();
	// Store the address of our funcion pointer
	// for each of the callback functions.	
	static void (*m_initFunc)(void);
	static void (*m_updateFunc)(void);
	static void (*m_drawFunc)(void);

public:
// Member Variables	
	// Keeps track of the previous mouse and current mouse positions
	// 'pmouse' is where the mouse previously was.
	// 'mouse' records where the mouse currently is.
	static unsigned int pmouseX, pmouseY, mouseX, mouseY;
	static sf::RenderWindow* m_window;
// Member functions
	void 	AddCommand(Command* c);
	void 	ExecuteCommand();
	static 	sf::Image& GetImage();
	static 	sf::Texture& GetTexture();
	static 	sf::RenderWindow& GetWindow();

	static void Destroy();
	static void Init(void (*initFunction)(void));
	static void UpdateCallback(void (*updateFunction)(void));
	static void DrawCallback(void (*drawFunction)(void));
	static void Loop();

};


#endif

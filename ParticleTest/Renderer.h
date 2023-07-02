#pragma once

#include "Particles.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include <iomanip>

class Renderer
{
private:
	//window variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;
	sf::Text game_info;

	int window_height;
	int window_width;

	int num_of_particles;

	int fps;
	int counter;
	sf::Clock clock;
	sf::Clock click_clock;
	sf::Time time;

	int particles_per_click = 2;

	std::stringstream stream;
	std::string friction_str;

	Particles particles;
	PARTICLE_T* particle_list;

	sf::Vector2i mousePos;
	bool mouse_not_released;

	//Booleans
	bool running;

	//private functions
	void initVariables();
	void initWindow();

public:
	//Constructors and Deconstructors
	Renderer();
	virtual ~Renderer();

	//Getters
	bool isRunning();
	
	//Update functions
	void pollEvents();
	void incrementPPC();

	void update();
	void render();
};


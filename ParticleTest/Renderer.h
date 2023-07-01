#pragma once

#include "Particles.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Renderer
{
private:
	//window variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	int window_height;
	int window_width;

	int num_of_particles;

	Particles particles;
	PARTICLE_T* particle_list;

	sf::CircleShape drawable = sf::CircleShape(2.0);

	sf::Vector2i mousePos;

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

	void update();
	void render();
};


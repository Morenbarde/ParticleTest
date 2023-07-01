#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cmath>

const int MAX_PARTICLES = 10000;

typedef struct Particle{
	float x;
	float y;
	float x_velocity;
	float y_velocity;
	sf::CircleShape circle;
	struct Particle *next;
	struct Particle *prev;
} PARTICLE_T;

class Particles
{
private:
	int num_of_particles;
	PARTICLE_T* first_particle;
	PARTICLE_T* last_particle;
	PARTICLE_T* current_particle;
	float particle_radius = 2.0;

	float xdist;
	float ydist;
	float xnormal;
	float ynormal;
	float distance_to_mouse;
	float GLOBAL_DECCELERATION = 2;
	int MOUSE_PUSH_RADIUS = 200;
	int MOUSE_PUSH_FORCE = 20;
	float friction = 0.008;
	float acceleration;
	float vertical_acceleration;
	float horizontal_acceleration;

public:

	//Getters
	int getNumOfParticles();
	PARTICLE_T* getFirstParticle();
	int getMouseStrength();
	int getMouseRadius();
	float getFriction();

	//Setters
	void incrementMouseStrength(int s);
	void incrementMouseRadius(int r);
	void incrementFriction(float f);

	bool addParticle(int x, int y, int x_velocity, int y_velocity, sf::Color color);
	bool addParticle(int x, int y, int x_velocity, int y_velocity);

	void accelerateParticles(float x, float y);

	void resetParticles();

	void updateParticles(sf::Vector2u window_size, sf::Vector2i mousePos);
};


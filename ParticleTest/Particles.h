#pragma once

#include <SFML/Graphics.hpp>

const int MAX_PARTICLES = 10000;

typedef struct Particle{
	float x;
	float y;
	float x_velocity;
	float y_velocity;
	sf::Color color;
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

	float xdist;
	float ydist;
	float xnormal;
	float ynormal;
	float distance_to_mouse;
	const float GLOBAL_DECCELERATION = 2;
	const float MOUSE_PUSH_RADIUS = 200;
	const float MOUSE_PUSH_FORCE = 20;
	float acceleration;

public:

	//Getters
	int getNumOfParticles();
	PARTICLE_T* getFirstParticle();

	bool addParticle(int x, int y, int x_velocity, int y_velocity, sf::Color color);
	bool addParticle(int x, int y, int x_velocity, int y_velocity);

	void resetParticles();

	void updateParticles(sf::Vector2u window_size, sf::Vector2i mousePos);
};


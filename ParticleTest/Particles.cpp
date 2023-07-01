#include "Particles.h"

#include <iostream>
#include <cmath>

int Particles::getNumOfParticles()
{
	return this->num_of_particles;
}

PARTICLE_T* Particles::getFirstParticle()
{
	return this->first_particle;
}

int Particles::getMouseStrength()
{
	return this->MOUSE_PUSH_FORCE;
}

int Particles::getMouseRadius()
{
	return this->MOUSE_PUSH_RADIUS;
}

void Particles::incrementMouseStrength(int s)
{
	this->MOUSE_PUSH_FORCE += s;
	std::cout << "Mouse Force: " << MOUSE_PUSH_FORCE << "\n";
}

void Particles::incrementMouseRadius(int r)
{
	this->MOUSE_PUSH_RADIUS += r;
	std::cout << "Mouse Radius: " << MOUSE_PUSH_RADIUS << "\n";
}

bool Particles::addParticle(int x, int y, int x_velocity, int y_velocity, sf::Color color)
{
	bool possibility = false;

	if (this->num_of_particles < MAX_PARTICLES) {

		if (this->num_of_particles == 0) {
			this->first_particle = new PARTICLE_T;
			this->last_particle = first_particle;
		}
		else {
			this->last_particle->next = new PARTICLE_T;
			this->last_particle->next->prev = last_particle;
			this->last_particle = this->last_particle->next;
		}

		this->last_particle->x = x;
		this->last_particle->y = y;
		this->last_particle->x_velocity = x_velocity;
		this->last_particle->y_velocity = y_velocity;
		this->last_particle->color = color;

		this->num_of_particles += 1;
		possibility = true;
	}
	std::cout << "Number of Particles: " << num_of_particles << "\n";

	return possibility;
}

bool Particles::addParticle(int x, int y, int x_velocity, int y_velocity)
{
	bool possibility = false;

	if (this->num_of_particles < MAX_PARTICLES) {
		
		if (this->num_of_particles == 0) {
			this->first_particle = new PARTICLE_T;
			this->last_particle = first_particle;
		} else {
			this->last_particle->next = new PARTICLE_T;
			this->last_particle->next->prev = last_particle;
			this->last_particle = this->last_particle->next;
		}
		
		this->last_particle->x = x;
		this->last_particle->y = y;
		this->last_particle->x_velocity = x_velocity;
		this->last_particle->y_velocity = y_velocity;
		this->last_particle->color = sf::Color::White;

		this->num_of_particles += 1;
		possibility = true;
	}
	std::cout << "Number of Particles: " << num_of_particles << "\n";

	return possibility;
}

void Particles::accelerateParticles(float x, float y)
{
	if (x == 0 && y == 0) {
		this->horizontal_acceleration = 0;
		this->vertical_acceleration = 0;
	}
	else {
		this->horizontal_acceleration += x;
		this->vertical_acceleration += y;
	}
}

void Particles::resetParticles()
{
	this->num_of_particles = 0;
}

void Particles::updateParticles(sf::Vector2u window_size, sf::Vector2i mousePos)
{
	int window_x = window_size.x;
	int window_y = window_size.y;
	this->current_particle = this->first_particle;
	

	for (int i = 0; i < num_of_particles; i++) {

		xdist = this->current_particle->x - mousePos.x;
		ydist = this->current_particle->y - mousePos.y;
		distance_to_mouse = sqrt((xdist * xdist) + (ydist * ydist));
		xnormal = xdist / distance_to_mouse;
		ynormal = ydist / distance_to_mouse;

		if (distance_to_mouse <= MOUSE_PUSH_RADIUS) {
			acceleration = MOUSE_PUSH_FORCE / distance_to_mouse;
			this->current_particle->x_velocity += xnormal * acceleration;
			this->current_particle->y_velocity += ynormal * acceleration;
		}
		this->current_particle->x_velocity = this->current_particle->x_velocity - (this->current_particle->x_velocity * 0.008)
			+ this->horizontal_acceleration;
		this->current_particle->y_velocity = this->current_particle->y_velocity - (this->current_particle->y_velocity * 0.008)
			+ this->vertical_acceleration;

		this->current_particle->x += this->current_particle->x_velocity;
		this->current_particle->y += this->current_particle->y_velocity;

		if (this->current_particle->x > (window_x - 20)) {
			this->current_particle->x_velocity *= (-1);
			this->current_particle->x = window_x - 20;
		}
		else if (this->current_particle->x < 20) {
			this->current_particle->x_velocity *= (-1);
			this->current_particle->x = 20;
		}

		if (this->current_particle->y > (window_y - 40)) {
			this->current_particle->y_velocity *= (-1);
			this->current_particle->y = window_y - 40;
		}
		else if (this->current_particle->y < 20) {
			this->current_particle->y_velocity *= (-1);
			this->current_particle->y = 20;
		}

		this->current_particle = this->current_particle->next;
	}
}

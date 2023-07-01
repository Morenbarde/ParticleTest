#include "Renderer.h"

void Renderer::initVariables()
{
	this->running = true;
}

void Renderer::initWindow()
{
	this->window_width = 1800;
	this->window_height = 900;

	this->videoMode.height = this->window_height;
	this->videoMode.width = this->window_width;

	this->window = new sf::RenderWindow(this->videoMode, "Particle Tester", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(60);
}

Renderer::Renderer()
{
	this->initVariables();
	this->initWindow();
}

Renderer::~Renderer()
{
	this->running = false;
	this->window->close();
}

bool Renderer::isRunning()
{
	return this->running;
}

void Renderer::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->~Renderer();
			break;
		case sf::Event::KeyPressed:
			break;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//sf::Color particle_color = sf::Color::White;
			particles.addParticle(this->mousePos.x + 1, this->mousePos.y + 1, 0, 0);
			particles.addParticle(this->mousePos.x + 1, this->mousePos.y - 1, 0, 0);
			particles.addParticle(this->mousePos.x - 1, this->mousePos.y + 1, 0, 0);
			particles.addParticle(this->mousePos.x - 1, this->mousePos.y - 1, 0, 0);
			particles.addParticle(this->mousePos.x + 1, this->mousePos.y, 0, 0);
			particles.addParticle(this->mousePos.x - 1, this->mousePos.y, 0, 0);
			particles.addParticle(this->mousePos.x, this->mousePos.y + 1, 0, 0);
			particles.addParticle(this->mousePos.x, this->mousePos.y - 1, 0, 0);
		}
	}
}

void Renderer::update()
{
	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->pollEvents();
	particles.updateParticles(this->window->getSize(), this->mousePos);
	this->num_of_particles = particles.getNumOfParticles();
}

void Renderer::render()
{
	if (isRunning()) {
		this->particle_list = particles.getFirstParticle();
		this->window->clear(sf::Color::Black);
		for (int i = 0; i < this->num_of_particles; i++) {
			drawable = sf::CircleShape(2.0);
			drawable.setFillColor(this->particle_list->color);
			drawable.setPosition(round(this->particle_list->x), round(this->particle_list->y));
			this->window->draw(drawable);
			this->particle_list = this->particle_list->next;
		}
		this->window->display();
	}
}

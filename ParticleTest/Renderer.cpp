#include "Renderer.h"

void Renderer::initVariables()
{
	this->running = true;

	this->font.loadFromFile("Game_Of_Squids.ttf");

	this->game_info.setFont(font);
	this->game_info.setString("Number of Particles: 0    Mouse Strength: " + std::to_string(particles.getMouseStrength()) + 
		"    Mouse Radius: " + std::to_string(particles.getMouseRadius()));
	this->game_info.setCharacterSize(20);
	this->game_info.setStyle(sf::Text::Bold);
	this->game_info.setPosition(50, this->window_height-30);
}

void Renderer::initWindow()
{
	this->window_width = 1600;
	this->window_height = 900;

	this->videoMode.height = this->window_height;
	this->videoMode.width = this->window_width;

	this->window = new sf::RenderWindow(this->videoMode, "Particle Tester", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	this->window->setFramerateLimit(60);
}

Renderer::Renderer()
{
	this->initWindow();
	this->initVariables();
}

//TODO When Running this, exception occurs, don't know why
Renderer::~Renderer()
{
	this->window->close();
	this->running = false;
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
			this->window->close();
			this->running = false;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::R) {
				particles.resetParticles();
			}
			if (event.key.code == sf::Keyboard::W) {
				particles.accelerateParticles(0, -0.01);
			}
			if (event.key.code == sf::Keyboard::A) {
				particles.accelerateParticles(-0.01, 0);
			}
			if (event.key.code == sf::Keyboard::S) {
				particles.accelerateParticles(0, 0.01);
			}
			if (event.key.code == sf::Keyboard::D) {
				particles.accelerateParticles(0.01, 0);
			}
			if (event.key.code == sf::Keyboard::Up) {
				particles.incrementMouseStrength(2);
			}
			if (event.key.code == sf::Keyboard::Down) {
				particles.incrementMouseStrength(-2);
			}
			if (event.key.code == sf::Keyboard::Left) {
				particles.incrementMouseRadius(-10);
			}
			if (event.key.code == sf::Keyboard::Right) {
				particles.incrementMouseRadius(10);
			}
			break;
		case sf::Event::KeyReleased:
			particles.accelerateParticles(0, 0);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//sf::Color particle_color = sf::Color::White;
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;
			particles.addParticle(this->mousePos.x + 5, this->mousePos.y + 5, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x + 5, this->mousePos.y - 5, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x - 5, this->mousePos.y + 5, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x - 5, this->mousePos.y - 5, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x + 5, this->mousePos.y, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x - 5, this->mousePos.y, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x, this->mousePos.y + 1, 0, 0, sf::Color(r, g, b, 255));
			particles.addParticle(this->mousePos.x, this->mousePos.y - 1, 0, 0, sf::Color(r, g, b, 255));
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
			drawable.setFillColor(this->particle_list->color);
			drawable.setPosition(round(this->particle_list->x), round(this->particle_list->y));
			this->window->draw(drawable);
			this->particle_list = this->particle_list->next;
		}

		this->game_info.setString("Number of Particles: " + std::to_string(particles.getNumOfParticles()) + "    Mouse Strength : " 
			+ std::to_string(particles.getMouseStrength()) + "    Mouse Radius: " + std::to_string(particles.getMouseRadius()));
		this->window->draw(game_info);

		this->window->display();
	}
}

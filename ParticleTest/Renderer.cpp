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

	this->counter = 0;
	this->fps = 0;

	stream << std::fixed << std::setprecision(3) << particles.getFriction();
	friction_str = stream.str();
}

void Renderer::initWindow()
{
	this->window_width = 1600;
	this->window_height = 900;

	this->videoMode.height = this->window_height;
	this->videoMode.width = this->window_width;

	this->window = new sf::RenderWindow(this->videoMode, "Particle Tester", sf::Style::Titlebar | sf::Style::Close);
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
			if (event.key.code == sf::Keyboard::Period) {
				particles.incrementFriction(0.001);
				stream.str("");
				stream << std::fixed << std::setprecision(3) << particles.getFriction();
				friction_str = stream.str();
			}
			if (event.key.code == sf::Keyboard::Comma) {
				particles.incrementFriction(-0.001);
				stream.str("");
				stream << std::fixed << std::setprecision(3) << particles.getFriction();
				friction_str = stream.str();
			}
			if (event.key.code == sf::Keyboard::Space) {
				incrementPPC();
			}
			break;
		case sf::Event::KeyReleased:
			particles.accelerateParticles(0, 0);
		}

		time = click_clock.getElapsedTime();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time.asSeconds() > 0.01) {
			click_clock.restart();
			//sf::Color particle_color = sf::Color::White;
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;

			if (particles_per_click == 8) {
				particles.addParticle(this->mousePos.x + 5, this->mousePos.y, 0, 0, sf::Color(r, g, b, 255));
				particles.addParticle(this->mousePos.x - 5, this->mousePos.y, 0, 0, sf::Color(r, g, b, 255));
				particles.addParticle(this->mousePos.x, this->mousePos.y + 5, 0, 0, sf::Color(r, g, b, 255));
				particles.addParticle(this->mousePos.x, this->mousePos.y - 5, 0, 0, sf::Color(r, g, b, 255));
			}
			if (particles_per_click >= 4) {
				particles.addParticle(this->mousePos.x + 5, this->mousePos.y + 5, 0, 0, sf::Color(r, g, b, 255));
				particles.addParticle(this->mousePos.x - 5, this->mousePos.y + 5, 0, 0, sf::Color(r, g, b, 255));
			} 
			if (particles_per_click >= 2) {
				particles.addParticle(this->mousePos.x - 5, this->mousePos.y - 5, 0, 0, sf::Color(r, g, b, 255));
			}
			particles.addParticle(this->mousePos.x + 5, this->mousePos.y - 5, 0, 0, sf::Color(r, g, b, 255));
			
			
			
		}
	}
}

void Renderer::incrementPPC()
{
	if (this->particles_per_click >= 8) {
		particles_per_click = 1;
	}
	else {
		particles_per_click *= 2;
	}
}

void Renderer::update()
{
	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->pollEvents();
	particles.updateParticles(this->window->getSize(), this->mousePos);
	this->num_of_particles = particles.getNumOfParticles();

	counter += 1;
	time = clock.getElapsedTime();
	if (time.asSeconds() >= 1) {
		fps = counter;
		counter = 0;
		clock.restart();
	}
}

void Renderer::render()
{
	if (isRunning()) {
		this->particle_list = particles.getFirstParticle();
		this->window->clear(sf::Color::Black);
		for (int i = 0; i < this->num_of_particles; i++) {
			this->particle_list->circle.setPosition((this->particle_list->x), (this->particle_list->y));
			this->window->draw(this->particle_list->circle);
			this->particle_list = this->particle_list->next;
		}

		this->game_info.setString("Number of Particles: " + std::to_string(particles.getNumOfParticles()) + "    Mouse Strength : "
			+ std::to_string(particles.getMouseStrength()) + "    Mouse Radius: " + std::to_string(particles.getMouseRadius())
			+ "    Friction: " + friction_str + "    PPC: " + std::to_string(particles_per_click) + "    FPS: " + std::to_string(fps));
		this->window->draw(game_info);

		this->window->display();
	}
}

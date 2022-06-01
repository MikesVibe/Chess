#include "stdafx.h"
#include "App.h"

App::App()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();


	this->run();
}

App::~App()
{
	delete window;
}



void App::endApplication()
{
	std::cout << "Ending Application!\n";
}

void App::updateDt()
{
	/*Updates the dt variable with he time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart().asSeconds();
}

void App::updateWindowEvents()
{
    while (this->window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void App::update()
{
	this->updateWindowEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application End
	else
	{
		this->window->close();
		this->endApplication();
	}

}

void App::render()
{
	this->window->clear();
	//Render items
	if (!this->states.empty())
		this->states.top()->render(this->window);


	this->window->display();
}

void App::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}


void App::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
}

void App::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void App::initWindow()
{
	/*Create a SFML window*/

	if (this->gfxSettings.fullscreen)
	{
		this->window = new  sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings);
	}

	else
	{
		this->window = new  sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);
	}


	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void App::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	ifs.close();
}

void App::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;

}

void App::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}
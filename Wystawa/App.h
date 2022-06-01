#pragma once
#include "MainMenuState.h"

class App
{
public:
	App();
	~App();


	void endApplication();

	void updateDt();
	void updateWindowEvents();
	void update();
	void render();
	void run();


private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;
	std::stack<State*> states;
	std::map <std::string, int> supportedKeys;



	void initVariables();
	void initGraphicsSettings();
	void initWindow();

	void initKeys();
	void initStateData();
	void initStates();


};


#pragma once
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	//Variables
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	int chosenGame;

};

class State
{
private:


protected:
	//Variables
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>*supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	bool gameover;
	float keytime;
	float keytimeMax;
	float gridSize;


	//Mouse pos
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Protected functions
	virtual void initKeybinds() = 0;

public:
	//Constructors and Destructors
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePos();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;



};


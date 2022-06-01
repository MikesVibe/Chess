#pragma once
#include "State.h"
#include "Gui.h"

class GameSelectState : public State
{
public:
	GameSelectState(StateData* state_data);
	virtual ~GameSelectState();

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
private:

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();

	//Variables
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	//std::vector<int> games;

};


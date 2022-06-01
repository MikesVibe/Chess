#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "SettingsState.h"
#include "ChessGameState.h"
#include "GameSelectState.h"
#include "Gui.h"

enum class AvilableGames { Snake = 0, Chess };


class MainMenuState : public State
{
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);

private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	//AvilableGames chosenGame;
	std::map<std::string, gui::Button*>buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

	void pushProperState();
};

#endif // MAINMENUSTATE_H
#pragma once
#include "Gui.h"

class PauseMenu
{
private:
	//Menu text
	sf::Font& font;
	sf::Text menuText;

	//Menu background
	sf::RectangleShape background;
	sf::RectangleShape container;

	//Menu buttons
	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	//Accessors
	std::map<std::string, gui::Button*>& getButtons();
	const bool isButtonPressed(const std::string key);

	//Functions
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};


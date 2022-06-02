#pragma once
#include "Gui.h"

class GameOverMenu
{
public:
	GameOverMenu(sf::RenderWindow& window, sf::Font& font);
	~GameOverMenu();

	//Accessors
	std::map<std::string, gui::Button*>& getButtons();
	const bool isButtonPressed(const std::string key);

	void setText(std::string endText);

	//Functions
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

private:
	//Menu text
	sf::Font& font;
	std::map<std::string, sf::Text*> texts;
	//sf::Text menuText;
	//sf::Text scoreGained;
	//sf::Text maxScoreGained;

	//Menu background
	sf::RectangleShape background;
	sf::RectangleShape container;

	//Menu buttons
	std::map<std::string, gui::Button*> buttons;

	//Initializer Functions
	void initButtons();
	void initTexts();



};



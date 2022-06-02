#include "stdafx.h"
#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init Background
	this->background.setSize
	(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	)
	);
	this->background.setFillColor(sf::Color(0, 0, 0, 230));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y) / 2.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(0, window.getSize().y / 4.f);

	
	this->initButtons();
	this->initTexts();
}

GameOverMenu::~GameOverMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& GameOverMenu::getButtons()
{
	return this->buttons;
}

const bool GameOverMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOverMenu::setText(std::string endText)
{
	this->texts["TITLE"]->setString(endText);

}


void GameOverMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 80.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, 50,
		sf::Color(0, 102, 255, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

//Functions
void GameOverMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void GameOverMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(*this->texts["TITLE"]);
	//target.draw(*this->texts["SCORE"]);
	//target.draw(*this->texts["MAX_SCORE"]);
}


//Initializer Functions
void GameOverMenu::initButtons()
{
	float space_between_buttons = 60.f;
	float width = 250.f;
	float height = 60.f;
	float  text_offset_y = height / 2.f;
	unsigned text_size = static_cast<unsigned>(text_offset_y);

	this->buttons["QUIT"] = new gui::Button(
		(this->container.getSize().x / 2.f) + (space_between_buttons / 2.f),
		this->container.getPosition().y + (this->container.getSize().y * 3.f) / 4.f ,
		width,
		height,
		text_offset_y,
		&this->font, "BACK TO MENU", text_size,
		sf::Color(0, 102, 255, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::White, sf::Color::White, sf::Color::White
	);

	//this->buttons["RESTART"] = new gui::Button(
	//	(this->container.getSize().x / 2.f) - (space_between_buttons / 2.f) - width,
	//	this->container.getPosition().y + (this->container.getSize().y * 3.f) / 4.f ,
	//	width,
	//	height,
	//	text_offset_y,
	//	&this->font, "TRY AGAIN", text_size,
	//	sf::Color(0, 102, 255, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
	//	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
	//	sf::Color::White, sf::Color::White, sf::Color::White

	//);
}

void GameOverMenu::initTexts()
{
	float space_between_texts = 60.f;
	float width = 250.f;

	this->texts["TITLE"] = new sf::Text();
	//this->texts["SCORE"] = new sf::Text();
	//this->texts["MAX_SCORE"] = new sf::Text();

	//Init text
	this->texts["TITLE"]->setFont(this->font);
	this->texts["TITLE"]->setFillColor(sf::Color(255, 255, 255, 200));
	this->texts["TITLE"]->setCharacterSize(80);
	this->texts["TITLE"]->setString("Game Over");
	this->texts["TITLE"]->setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->texts["TITLE"]->getGlobalBounds().width / 2.f,
		this->container.getPosition().y + this->container.getSize().y / 4.f - this->texts["TITLE"]->getGlobalBounds().height
	);

	/*this->texts["SCORE"]->setFont(this->font);
	this->texts["SCORE"]->setFillColor(sf::Color(255, 255, 255, 200));
	this->texts["SCORE"]->setCharacterSize(60);
	this->texts["SCORE"]->setString("SCORE");

	this->texts["SCORE"]->setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f + 
		(space_between_texts / 2.f),

		this->container.getPosition().y + this->container.getSize().y / 4.f * 2.f - this->texts["SCORE"]->getGlobalBounds().height
	);

	this->texts["MAX_SCORE"]->setFont(this->font);
	this->texts["MAX_SCORE"]->setFillColor(sf::Color(255, 255, 255, 200));
	this->texts["MAX_SCORE"]->setCharacterSize(60);
	this->texts["MAX_SCORE"]->setString("BEST SCORE");

	this->texts["MAX_SCORE"]->setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f -
		(space_between_texts / 2.f) - width,

		this->container.getPosition().y + this->container.getSize().y / 4.f * 2.f- this->texts["MAX_SCORE"]->getGlobalBounds().height*/
	//);
}



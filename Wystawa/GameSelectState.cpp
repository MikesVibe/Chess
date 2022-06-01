#include "stdafx.h"
#include "GameSelectState.h"

GameSelectState::GameSelectState(StateData* state_data)
	: State(state_data)
{
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initVariables();
	this->initGui();
}

GameSelectState::~GameSelectState()
{
}


void GameSelectState::updateInput(const float& dt)
{

}

void GameSelectState::updateGui(const float& dt)
{
	/*Updates all the gui elements in the state and handles their functionality.*/
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Button finctionality
	//Quit the Gamepinguin site
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER!!!!!!!!!!!!!!!!!
		//this->stateData->chosenGame = this->dropDownLists["GAME_SELECT"]->getActiveElementId();
		//std::cout << "Selected: " << this->dropDownLists["GAME_SELECT"]->getActiveElementId() << std::endl;

	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}


}

void GameSelectState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);
	this->updateGui(dt);
}

void GameSelectState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);


	for (auto& it : this->buttons)
	{
		it.second->render(*target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(*target);
	}

	//Debuging thing
   //Text mouseText;
   //mouseText.setPosition(this->mousePosView.x, this->mousePosView.y + 80);
   //mouseText.setFont(this->font);
   //mouseText.setCharacterSize(20);
   //stringstream ss;
   //ss << this->mousePosView.x << " " << this->mousePosView.y;
   //mouseText.setString(ss.str());

   //target->draw(mouseText);


}

void GameSelectState::initVariables()
{
}

void GameSelectState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Backgrounds/bg1.png"))
	{
		throw("ERROR::GAME_SELECT_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
	}


	this->background.setTexture(&this->backgroundTexture);

}

void GameSelectState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Changa-VariableFont_wght.ttf"))
	{
		throw("ERROR::GAME_SELECT_STATE::COULD NOT LOAD FONT");
	}
}

void GameSelectState::initKeybinds()
{
	std::ifstream ifs("Config/gameselectstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}

void GameSelectState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		1550.f, 880.f, 250.f, 80.f,
		&this->font, "Back", 50,
		sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new gui::Button(
		1350.f, 880.f, 250.f, 80.f,
		&this->font, "Apply", 50,
		sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//for (auto& i : this->modes)
	//{
	//	modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	//}

	std::vector<std::string> games;
	games.push_back("Chees");
	//games.push_back("Snake");

	this->dropDownLists["GAME_SELECT"] = new gui::DropDownList(800.f, 450.f, 200.f, 50.f, font, games.data(), games.size());
}

#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	
	pushProperState();
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePos();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

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

//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Backgrounds/bg1.png"))
	{
		throw("ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
	}


	this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Changa-VariableFont_wght.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(
		265.f, 480.f, 320.f, 65.f,
		&this->font, "New Game", 65,
		sf::Color(0, 102, 255, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	//this->buttons["GAME_SELECT_STATE"] = new gui::Button(
	//	300.f, 580.f, 250.f, 50.f,
	//	&this->font, "Selector", 50,
	//	sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
	//	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	//);

	//this->buttons["SETTINGS_STATE"] = new gui::Button(
	//	300.f, 680.f, 250.f, 50.f,
	//	&this->font, "Settings", 50,
	//	sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
	//	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	//);

	//this->buttons["EDITOR_STATE"] = new gui::Button(
	//	300.f, 780.f, 250.f, 50.f,
	//	&this->font, "Editor", 50,
	//	sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
	//	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	//);

	this->buttons["EXIT_STATE"] = new gui::Button(
		300.f, 880.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MainMenuState::pushProperState()
{
	this->stateData->chosenGame = 1;
	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new ChessGameState(this->stateData));

		//switch (this->stateData->chosenGame)
		//{
		//case 1:
		//{
		//	this->states->push(new SnakeGameState(this->stateData));
		//}
		//case 2:
		//{
		//	this->states->push(new ChessGameState(this->stateData));
		//}
		//default:
		//{
		//	std::cout << "ERROR::MAINMENUSTATE::Could not load proper game" << std::endl;
		//}
		//}
	}

	////Selector
	//if (this->buttons["GAME_SELECT_STATE"]->isPressed())
	//{
	//	this->states->push(new GameSelectState(this->stateData));
	//}

	////Settings
	//if (this->buttons["SETTINGS_STATE"]->isPressed())
	//{
	//	this->states->push(new SettingsState(this->stateData));
	//}


	//Quit the Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

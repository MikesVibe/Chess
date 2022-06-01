#include "stdafx.h"

#include "State.h"

//Constructors and Destructors
State::State(StateData* state_data)
{
    this->stateData = state_data;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->gameover = false;
    this->keytime = 0.f;
    this->keytimeMax = 3.f;
    this->gameStateName = "SnakeGameState";
}

 State::~State()
{
}
 //Accessors
 const bool& State::getQuit() const
 {
     return this->quit;
 }

 const bool State::getKeytime()
 {
     if (this->keytime >= this->keytimeMax)
     {
         this->keytime = 0.f;
         return true;
     }

     return false;
 }

 //Functions
void State::endState()
 {
     this->quit = true;
 }

 void State::pauseState()
 {
     this->paused = true;
 }

 void State::unpauseState()
 {
     this->paused = false;
 }

 void State::updateMousePos()
 {
     this->mousePosScreen = sf::Mouse::getPosition();
     this->mousePosWindow = sf::Mouse::getPosition(*this->window);
     this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

 }

 void State::updateKeytime(const float& dt)
 {
     if (this->keytime < this->keytimeMax)
         this->keytime += 10.f * dt;
 }

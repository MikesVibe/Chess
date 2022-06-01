#pragma once
#include "Square.h"

class SideNumbersPanel : public sf::Drawable
{
public:
	SideNumbersPanel(sf::Font& font, GridData& gridData);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Text text_vertical[8];
	sf::Text text_horizontal[8];

};


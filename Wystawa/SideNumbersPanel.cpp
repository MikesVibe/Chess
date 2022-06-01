#include "stdafx.h"
#include "SideNumbersPanel.h"

SideNumbersPanel::SideNumbersPanel(sf::Font& font, GridData& gridData)
{

	for (int i = 0; i < 8; i++)
	{
		this->text_vertical[i].setFont(font);
		this->text_vertical[i].setString(static_cast<char>(49 + i));
		this->text_vertical[i].setPosition(
			gridData.gridOffset.x - (gridData.tileSize.x / 2.f),
			(gridData.gridOffset.y + gridData.wholeGridSize.y - (gridData.tileSize.y / 2.f)) - (gridData.tileSize.y * (i))
		);
		this->text_vertical[i].setCharacterSize(static_cast<unsigned int>(gridData.tileSize.x / 5.f));

		//std::cout << "Pos Y: " << (gridData.gridOffset.y - (gridData.tileSize.y / 2.f)) + (gridData.tileSize.y * i) << "\n";
	}

	for (int i = 0; i < 8; i++)
	{
		this->text_horizontal[i].setFont(font);
		this->text_horizontal[i].setString(static_cast<char>(65 + i));

		this->text_horizontal[i].setCharacterSize(static_cast<unsigned int>(gridData.tileSize.x / 5.f));
		this->text_horizontal[i].setPosition(
			gridData.gridOffset.x - (gridData.tileSize.x / 2.f) + (gridData.tileSize.x * (i + 1)) - static_cast<float>(gridData.tileSize.x / 10.f),
			gridData.gridOffset.y + gridData.wholeGridSize.y //+ (gridData.tileSize.y / 2.f)
		);
		//std::cout << "Pos Y: " << (gridData.gridOffset.y - (gridData.tileSize.y / 2.f)) + (gridData.tileSize.y * i) << "\n";
	}


}

void SideNumbersPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < 8; i++)
	{
		target.draw(this->text_vertical[i]);
		target.draw(this->text_horizontal[i]);
	}
}

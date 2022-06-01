#include "stdafx.h"
#include "Square.h"

Square::Square()
{
}

Square::Square(GridData* grid_data, sf::Vector2i pos_on_grid)
	:gridData(grid_data), posOnGrid(pos_on_grid)
{
	////DEBUGING
	//std::cout << "New square created\n";
	//std::cout << "Grid data: " <<
	//	this->gridData->gridOffset.x << " " << this->gridData->gridOffset.y << " " <<
	//	pos_on_grid.x << " " << pos_on_grid.y << " " <<
	//	this->gridData->tileSize.x << " " << this->gridData->tileSize.y << std::endl;

	this->background.setSize(grid_data->tileSize);
	this->setPositionOnGrid(pos_on_grid);

}

Square::~Square()
{
	//delete this->gridData;
}


//Accessors
const sf::Color& Square::getFillColor() const
{
	return this->background.getFillColor();
}
const sf::Vector2i Square::getPositionOnGrid() const
{
	return this->posOnGrid;
}

const sf::FloatRect Square::getGlobalBounds() const
{
	return this->background.getGlobalBounds();
}

//Modifiers
void Square::setFillColor(sf::Color color)
{
	this->background.setFillColor(color);
}
void Square::setPositionOnGrid(sf::Vector2i pos_on_grid, sf::Vector2f offset)
{
	this->posOnGrid = pos_on_grid;

	this->background.setPosition(
		static_cast<float>(this->posOnGrid.x) * this->gridData->tileSize.x + this->gridData->gridOffset.x + offset.x,
		static_cast<float>(this->posOnGrid.y) * this->gridData->tileSize.y + this->gridData->gridOffset.y + offset.y
	);
}

void Square::setTexture(sf::Texture* texture, sf::IntRect int_rect)
{
	this->background.setTexture(texture);
	this->background.setTextureRect(int_rect);

}

//Functions
void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->background);
}

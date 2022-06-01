#include "stdafx.h"
#include "Grid.h"


//--------------------GRID--------------------//
Grid::Grid(GridData* grid_data)
	: gridData(grid_data)
{
	sf::Color color;
	this->grid.resize(this->gridData->gridSize.x, std::vector<Square*>());
	for (unsigned x = 0; x < this->gridData->gridSize.x; x++)
	{
		this->grid[x].resize(this->gridData->gridSize.y, NULL);

		for (unsigned y = 0; y < this->gridData->gridSize.y; y++)
		{
			this->grid[x][y] = new Square(this->gridData, sf::Vector2i(x, y));

			color = ((x + y) % 2) ? sf::Color(238, 238, 210, 255) : sf::Color(118, 150, 86, 255);
			this->grid[x][y]->setFillColor(color);

			////DEBUGING
			//std::cout << "New square created\n";
			//std::cout << "Grid data: " <<
			//	this->gridData->gridOffset.x << " " << this->gridData->gridOffset.y << " " <<
			//	this->gridData->gridSize.x << " " << this->gridData->gridSize.y << " " <<
			//	this->gridData->tileSize.x << " " << this->gridData->tileSize.y << std::endl;
		
		}
	}
}

Grid::~Grid()
{
	//delete this->gridData;
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned x = 0; x < this->gridData->gridSize.x; x++)
	{
		for (unsigned y = 0; y < this->gridData->gridSize.y; y++)
		{
			target.draw(*this->grid[x][y]);
		}
	}
}



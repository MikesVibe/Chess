#include "stdafx.h"
#include "PossibleMove.h"



Move::Move(GridData* grid_data, sf::Vector2i pos_on_grid)
{
	this->gridData = grid_data;
	this->posOnGrid = pos_on_grid;

	float radius = 20.f;
	this->shape.setRadius(radius);
	this->shape.setFillColor(sf::Color::Green);
	
	////DEBUGING
	//std::cout << "New square created\n";
	//std::cout << "Grid data: " <<
	//	this->gridData->gridOffset.x << " " << this->gridData->gridOffset.y << " " <<
	//	pos_on_grid.x << " " << pos_on_grid.y << " " <<
	//	this->gridData->tileSize.x << " " << this->gridData->tileSize.y << std::endl;

	this->shape.setPosition(
		static_cast<float>(this->posOnGrid.x) * this->gridData->tileSize.x + this->gridData->gridOffset.x + this->gridData->tileSize.x / 2.f - radius,
		static_cast<float>(this->posOnGrid.y) * this->gridData->tileSize.y + this->gridData->gridOffset.y + this->gridData->tileSize.y / 2.f - radius
	);
	
}

//Accessors
//const sf::Vector2i& Move::getPosOnGrid() const
//{
//	return this->posOnGrid;
//}

void Move::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

void Move::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape);
}

//---------------------------Possible Moves---------------------------//

PossibleMove::PossibleMove()
{
}

PossibleMove::PossibleMove(std::vector<Move*> _possible_moves)
{
	this->initVariables();
	for (auto var : _possible_moves)
	{
		this->possibleMoves.emplace_back(var);

	}
}

PossibleMove::PossibleMove(GridData* grid_data)
	:gridData(grid_data)
{
	this->initVariables();

}

PossibleMove::~PossibleMove()
{
}

void PossibleMove::add(sf::Vector2i pos_on_grid)
{
	this->possibleMoves.emplace_back(new Move(this->gridData, pos_on_grid));
}

void PossibleMove::remove(sf::Vector2i pos_on_grid)
{
	for (int i = 0; i < possibleMoves.size(); i++)
	{
		if (possibleMoves[i]->getPositionOnGrid() == pos_on_grid)
		{
			auto iterator = std::remove(begin(possibleMoves), end(possibleMoves), possibleMoves[i]);
			possibleMoves.erase(iterator, end(possibleMoves));

			return;
		}
	}
}

void PossibleMove::remove(int index)
{
	auto iterator = std::remove(begin(possibleMoves), end(possibleMoves), possibleMoves[index]);
	possibleMoves.erase(iterator, end(possibleMoves));
}

void PossibleMove::clear()
{
	this->possibleMoves.clear();
}

void PossibleMove::printMovesToConsole()
{
	for (auto move : this->possibleMoves)
	{
		std::cout << "Possible move: " << move->getPositionOnGrid().x << ", " << move->getPositionOnGrid().y << std::endl;
	}
	std::cout << std::endl;
}

const bool& PossibleMove::contains(sf::Vector2i grid_pos) const
{
	for (auto& i : this->possibleMoves)
	{
		if (i->getPositionOnGrid() == grid_pos)
		{
			//std::cout << "Match!!!" << std::endl;
			return true;

		}
	}
	return false;
}



const int& PossibleMove::getSize() const
{
	return this->possibleMoves.size();
}

const std::vector<Move*>& PossibleMove::getPossibleMoves() const
{
	return this->possibleMoves;
}

void PossibleMove::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : this->possibleMoves)
	{
		i->draw(target, states);
	}
}

void PossibleMove::initVariables()
{
	this->possibleMoves.reserve(64);
}


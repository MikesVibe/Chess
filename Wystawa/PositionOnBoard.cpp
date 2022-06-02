#include "stdafx.h"
#include "PositionOnBoard.h"

PositionOnBoard::PositionOnBoard()
{
	this->saveMove();

	//this->displayInConsole(matrixAfter);
	//this->displayInConsole(matrixBefore);
}

const bool& PositionOnBoard::isEmpty(sf::Vector2i position) const
{
	if (this->matrixAfter[position.y][position.x] == 0)
		return true;

	return false;
}

const bool& PositionOnBoard::isEnemy(int type1, int type2) const
{
	if (type1 * type2 < 0)
		return true;

	return false;
}


const int& PositionOnBoard::getType(sf::Vector2i position) const
{
	return this->matrixAfter[position.y][position.x];
}

const int& PositionOnBoard::getType(MatrixToUse matrix, sf::Vector2i position) const
{
	if(matrix == MatrixToUse::AFTER)
		return this->matrixAfter[position.y][position.x];

	return this->matrixBefore[position.y][position.x];
}

void PositionOnBoard::displayInConsole(MatrixToUse matrix)
{
	//Displaing matrix in the console
	int i, j;

	if (matrix == MatrixToUse::BEFORE)
	{
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				std::cout << std::setw(2) << this->matrixBefore[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}
	else
	{
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				std::cout << std::setw(2) << this->matrixAfter[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}

	
}

void PositionOnBoard::movePiece(sf::Vector2i old_grid_pos, sf::Vector2i new_grid_pos)
{
	//std::cout << "Position: " << old_grid_pos.x << ", " << old_grid_pos.y << std::endl;
	//std::cout << "Position: " << new_grid_pos.x << ", " << new_grid_pos.y << std::endl << std::endl;

	std::swap(
		this->matrixAfter[new_grid_pos.y][new_grid_pos.x],
		this->matrixAfter[old_grid_pos.y][old_grid_pos.x]
	);
}

void PositionOnBoard::beatPiece(sf::Vector2i old_grid_pos, sf::Vector2i new_grid_pos)
{
	this->matrixAfter[new_grid_pos.y][new_grid_pos.x] = this->matrixAfter[old_grid_pos.y][old_grid_pos.x];
	this->matrixAfter[old_grid_pos.y][old_grid_pos.x] = 0;
}

void PositionOnBoard::deletePiece(sf::Vector2i grid_pos)
{
	this->matrixAfter[grid_pos.y][grid_pos.x] = 0;
}

void PositionOnBoard::placePiece(sf::Vector2i grid_pos, int piece_type)
{
	this->matrixAfter[grid_pos.y][grid_pos.x] = piece_type;
}

sf::Vector2i PositionOnBoard::findPositionOfKing()
{
	return sf::Vector2i();
}

void PositionOnBoard::saveMove()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->matrixBefore[i][j] = this->matrixAfter[i][j];
		}
	}
}

void PositionOnBoard::undoMove()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->matrixAfter[i][j] = this->matrixBefore[i][j];
		}
	}
}

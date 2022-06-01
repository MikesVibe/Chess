#include "stdafx.h"
#include "Knight.h"

Knight::Knight()
{
}

Knight::Knight(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type)
	: Piece(grid_data, piece_position, pos_on_grid, texture, type)
{
}

void Knight::getSemiLegalMoves(PositionOnBoard* piece_position, PossibleMove& possible_moves)
{
	//Tables with possible moves
	int changeInX[8] = { 2,2,-2,-2,1,1,-1,-1 };
	int changeInY[8] = { 1,-1,1,-1,2,-2,2,-2 };
	sf::Vector2i new_position;

	for (int i = 0; i < 8; i++)
	{
		new_position = sf::Vector2i(
			this->getPositionOnGrid().x + changeInX[i],
			this->getPositionOnGrid().y + changeInY[i]
		);

		if (this->isInsideBoard(new_position))
		{
			if (piece_position->isEmpty(new_position))
				addPossibleMove(possible_moves, new_position);
			else if (piece_position->isEnemy(this->type, piece_position->getType(new_position)))
				this->addPossibleMove(possible_moves, new_position);
		}
	}
}

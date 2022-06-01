#include "stdafx.h"
#include "Bishop.h"

Bishop::Bishop()
{
}

Bishop::Bishop(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type)
	: Piece(grid_data, piece_position, pos_on_grid, texture, type)
{
}

void Bishop::getSemiLegalMoves(PositionOnBoard* piece_position, PossibleMove& possible_moves)
{
	sf::Vector2i new_position;


	int changeInX[4] = {  1,-1,-1, 1};
	int changeInY[4] = { -1,-1, 1, 1};

	//Loop setting direction
	//At first it goes through all diagonnals then it goes through staright lines
	for (int loop = 0; loop < 4; loop++)
	{
		new_position = this->getPositionOnGrid();

		//Loop for moves in one directions
		for (int i = 1; i < 8; i++)
		{
			new_position.x += changeInX[loop];
			new_position.y += changeInY[loop];

			if (isInsideBoard(new_position) && piece_position->isEmpty(new_position))
			{
				this->addPossibleMove(possible_moves, new_position);
			}
			else if (this->isInsideBoard(new_position) && piece_position->isEnemy(this->type, piece_position->getType(MatrixToUse::AFTER, new_position)))
			{
				this->addPossibleMove(possible_moves, new_position);
				break;
			}
			else
				break;
		}
	}
}
//this->isEnemy(piece_position->getType(new_position))
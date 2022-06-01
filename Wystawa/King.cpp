#include "stdafx.h"
#include "King.h"

King::King()
{
	this->wasMoved = false;
	this->castlingPossible = false;
}

King::King(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type)
	: Piece(grid_data, piece_position, pos_on_grid, texture, type)
{
	this->wasMoved = false;
	this->castlingPossible = false;
}

void King::getSemiLegalMoves(PositionOnBoard* piece_position, PossibleMove& possible_moves)
{
	sf::Vector2i new_position;


	int changeInX[8] = { 1,-1,-1, 1, 1, 0,-1, 0 };
	int changeInY[8] = { -1,-1, 1, 1, 0,-1, 0, 1 };

	//Loop setting direction
	//At first it goes through all diagonnals then it goes through staright lines
	for (int loop = 0; loop < 8; loop++)
	{
		new_position = this->getPositionOnGrid();

		new_position.x += changeInX[loop];
		new_position.y += changeInY[loop];

		if (this->isInsideBoard(new_position))
		{
			//Check if new position square is empty, or if there is enemy
			if (!piece_position->isEnemy(this->type, piece_position->getType(MatrixToUse::AFTER, new_position)) && !piece_position->isEmpty(new_position))
				continue;

			//Check if square is not covered
			if (!isInCheck(piece_position, new_position, this->type))
			{
				this->addPossibleMove(possible_moves, new_position);
			}
			
			
		}
	}
	bool temp = false;

	temp = isValidCastling(piece_position, Castling::Long, this->type);
	temp = isValidCastling(piece_position, Castling::Short, this->type);


	if (isValidCastling(piece_position, Castling::Long, this->type))
		return;
}

const bool& King::getWasMoved() const
{
	return this->wasMoved;
}

void King::setWasMoved(bool was_moved)
{
	this->wasMoved = was_moved;
}

bool King::isInCheck(PositionOnBoard* board, sf::Vector2i position, int type)
{
	//Checks all directions and if it finds openent which can attack directly it returns true

	sf::Vector2i new_position = position;


	const int changeInX[8] = { 1,-1,-1, 1, 1, 0,-1, 0 };
	const int changeInY[8] = { -1,-1, 1, 1, 0,-1, 0, 1 };

	//Loop setting direction
	//At first it goes through all diagonnals then it goes through staright lines
	for (int loop = 0; loop < 8; loop++)
	{
		new_position = position;
		//new_position = this->getPositionOnGrid();

		//Loop for moves in one direction
		for (int i = 1; i < 8; i++)
		{
			new_position.x += changeInX[loop];
			new_position.y += changeInY[loop];

			if (position.x == 1 && position.y == 6)
			{
				std::cout << "";
			}

			//Check if next move is inside board
			if (!isInsideBoard(new_position))
				break;

			//If square on new position is empty check next square
			if (board->isEmpty(new_position))
				continue;



			int piece_type = board->getType(MatrixToUse::AFTER, new_position);
			if (!board->isEnemy(type, piece_type))
				break;

			piece_type = abs(piece_type);


			//Checks for queen attacks
			if (piece_type == 2)
				return true;

			//Checking for pieces which can attack diagonally
			if (loop < 4)
			{
				//Bishop
				if (piece_type == 3)
					return true;

				//if enemy piece is not a pawn or if its further away than 1 square
				if (i != 1 || piece_type != 6)
					break;

				//Check for side in which pawn can attack
				(type < 0) ? new_position.y-- : new_position.y++;
				if (position.y == new_position.y)
					return true;
			}
			if (loop >= 4)
			{
				//Rook
				if (piece_type == 5)
					return true;
			}

			break;
		}
	}

	//Tables with possible moves for knight
	const int changeInX2[8] = {2,2,-2,-2,1,1,-1,-1};
	const int changeInY2[8] = {1,-1,1,-1,2,-2,2,-2};

	for (int i = 0; i < 8; i++)
	{
		new_position = sf::Vector2i(
			position.x + changeInX2[i],
			position.y + changeInY2[i]
		);

		if (isInsideBoard(new_position))
		{
			int piece_type = board->getType(MatrixToUse::AFTER, new_position);
			if (board->isEnemy(type, piece_type))
			{
				piece_type = abs(piece_type);

				if (piece_type == 4)
					return true;
			}
		}
	}

	return false;
}

bool King::isInCheck(PositionOnBoard* board, sf::Vector2i kingPostion, PieceColor kingColor)
{
	if(kingColor == PieceColor::WHITE)
		return isInCheck(board, kingPostion, 1);
	else
		return isInCheck(board, kingPostion, -1);

}

bool King::isValidCastling(PositionOnBoard* board, Castling castling, int type)
{
	if(this->wasMoved)
		return false;

	
	sf::Vector2i position = this->getPositionOnGrid();

	if (castling == Castling::Long)
	{
		if (this->isInCheck(board, position, type))
			return false;
		position.x = position.x - 1;
		if (this->isInCheck(board, position, type))
			return false;
		position.x = position.x - 1;
		if (this->isInCheck(board, position, type))
			return false;

		return true;
	}
	if (castling == Castling::Short)
	{
		if (this->isInCheck(board, position, type))
			return false;
		position.x = position.x + 1;
		if (this->isInCheck(board, position, type))
			return false;
		position.x = position.x + 1;
		if (this->isInCheck(board, position, type))
			return false;
	
	
		return true;
	}


	return false;
}

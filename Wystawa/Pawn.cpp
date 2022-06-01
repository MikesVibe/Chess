#include "stdafx.h"
#include "Pawn.h"

Pawn::Pawn()
{
}

Pawn::Pawn(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type)
	: Piece(grid_data, piece_position, pos_on_grid, texture, type)
{
}

Pawn::~Pawn()
{

}

void Pawn::getSemiLegalMoves(PositionOnBoard* piece_position, PossibleMove& possible_moves)
{
	

	sf::Vector2i new_pos, left, right;

	new_pos = this->moveForward(this->getPositionOnGrid());
	if (this->isInsideBoard(new_pos))
	{
		//Check for beating pieces
		left = sf::Vector2i(new_pos.x - 1, new_pos.y);
		right = sf::Vector2i(new_pos.x + 1, new_pos.y);
		if (piece_position->isEnemy(this->type, piece_position->getType(left)))
			this->addPossibleMove(possible_moves, left);
		if (piece_position->isEnemy(this->type, piece_position->getType(right)))
			this->addPossibleMove(possible_moves, right);

		//new_pos = this->getPositionOnGrid();
		////En passant
		//left = sf::Vector2i(new_pos.x - 1, new_pos.y);
		//right = sf::Vector2i(new_pos.x + 1, new_pos.y);
		//if (this->canEnPassant(left))
		//	this->addPossibleMove(possible_moves, left);
		//if (this->canEnPassant(right))
		//	this->addPossibleMove(possible_moves, right);

		//Reset position
		new_pos = this->getPositionOnGrid();
		//Double move
		for (int i = 0; i < 2; i++)
		{
			//Select direction of moving
			new_pos = this->moveForward(new_pos);
			if (piece_position->isEmpty(new_pos))
			{
				this->addPossibleMove(possible_moves, new_pos);
			}
			else
				break;

			if (this->firstMoveAvilale == false)
				break;
		}
	}
}

bool Pawn::isEnPassantPossible(int round)
{
	if (round == (this->enPassantRound + 1) && this->enPassantPossible)
	{
		//std::cout << "Piece\n";
		//std::cout << "Position: " << this->posOnGrid.x + 1 << ", " << this->posOnGrid.y + 1<< "\n";
		//std::cout << "Round saved: " << this->enPassantRound << " is en passant possible: " << this->enPassantPossible << "\n";
		//std::cout << "Round passed to function: " << round << "\n";

		return true;
	}

	return false;

}

void Pawn::activateEnPassant(int round)
{
	this->enPassantRound = round;
	this->enPassantPossible = true;
}

void Pawn::sendNerbyPieces(Piece* left, Piece* right)
{
}



sf::Vector2i Pawn::moveForward(sf::Vector2i position)
{
	(this->type < 0) ? position.y++ : position.y--;

	return position;
}

//bool Pawn::canEnPassant(sf::Vector2i position)
//{
//	//if (
//	//	this->isEnemy(position) && 
//	//	abs(this->boardAsText->getType(position)) == 6 &&
//	//	this->gwt
//	//	)
//	//{
//
//
//	//}
//
//
//	return false;
//}

void Pawn::checkForMove(sf::Vector2i position)
{

}

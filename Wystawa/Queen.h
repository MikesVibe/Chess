#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:

	Queen();
	Queen(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type);
	
	void getSemiLegalMoves(PositionOnBoard* piece_position, PossibleMove& possible_moves);


};


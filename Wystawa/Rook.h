#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook();
	Rook(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type);

	std::vector<sf::Vector2i> getSemiLegalMovesPositions(PositionOnBoard* piece_position);
	const bool& getWasMoved() const;

	void setWasMoved(bool was_moved);

private:
	bool wasMoved;
};


#pragma once
#include "Piece.h"

enum class Castling { Long = 0, Short };

class King : public Piece
{
public:

	King();
	King(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type);

	std::vector<sf::Vector2i> getSemiLegalMovesPositions(PositionOnBoard* piece_position);
	const bool& getWasMoved() const;

	void setWasMoved(bool was_moved);
	static bool isInCheck(PositionOnBoard* board, sf::Vector2i position, int type);
	static bool isInCheck(PositionOnBoard* board, sf::Vector2i kingPostion, PieceColor kingColor);
	bool isValidCastling(PositionOnBoard* board, Castling castling, int type);

private:
	bool wasMoved;
	bool castlingPossible;
};


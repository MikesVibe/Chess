#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:

	Pawn();
	Pawn(GridData* grid_data, PositionOnBoard* piece_position, sf::Vector2i pos_on_grid, sf::Texture* texture, int type);

	~Pawn();

	std::vector<sf::Vector2i> getSemiLegalMovesPositions(PositionOnBoard* piece_position);

	bool isEnPassantPossible(int round);
	void activateEnPassant(int round);
	void sendNerbyPieces(Piece* left, Piece* right);

private:

	sf::Vector2i moveForward(sf::Vector2i position);
	//bool canAttack(sf::Vector2i position);
	//bool canEnPassant(sf::Vector2i position);
	void checkForMove(sf::Vector2i position);

	int enPassantRound = 0;
	bool enPassantPossible = false;

};


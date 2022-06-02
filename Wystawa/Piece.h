#pragma once
#include "Square.h"
#include "PositionOnBoard.h"
#include "PossibleMove.h"


enum class PieceColor { BLACK = -1, WHITE = 1 };

class MoveMade
{
public:
	MoveMade(sf::Vector2i before, sf::Vector2i after);

	std::string getMoveString();
	const sf::Vector2i& getMoveBefore()const;
	const sf::Vector2i& getMoveAfter()const;

private:
	//TypeOfMove moveType;
	sf::Vector2i before;
	sf::Vector2i after;
};

class MovesHistory
{
public:
	enum class Color { Black = 0, White };


	MovesHistory();
	~MovesHistory();

	void addMove(sf::Vector2i before, sf::Vector2i after, int type);
	const MoveMade& getLastMove()const;
	void printMoves();

private:
	std::vector<MoveMade*> movesBlack;
	std::vector<MoveMade*> movesWhite;
};

class Piece : public Square
{
public:
	Piece();
	Piece(GridData* grid_data, PositionOnBoard* board_in_text, sf::Vector2i pos_on_grid, sf::Texture* texture, int type);
	~Piece();

	//Accessors
	const bool doesContain(sf::Vector2f& mouse_pos) const;
	const bool& isSelected() const;
	const int& getType() const;
	const PieceColor& getPieceColor() const;
	const bool& isDestroyed() const;
	const bool& isTemporarlyDisabled() const;
	const bool& isFirstMoveAvialble() const;


	//Modifiers
	void destroy(bool destroy = true);
	void temporaryDisable(bool destroy = true);
	void setSelect(bool select = true);
	void setPositionOnGrid(sf::Vector2i pos_on_grid);
	void firstMoveMade();


	//Functions
	static bool isInsideBoard(sf::Vector2i position);
	bool isEnemy(int type_of_another_piece);

	void addPossibleMove(PossibleMove& possible_moves, sf::Vector2i position);
	virtual std::vector<sf::Vector2i> getSemiLegalMovesPositions(PositionOnBoard* piece_position) = 0;

	void update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

	GridData* gridData;
	sf::Texture* texture;

	sf::Vector2f squareOffset;
	sf::RectangleShape shape;

	int type;
	bool selected;
	bool destroyed;
	bool temporarlyDisabled;
	//bool enPassantActive;
	bool firstMoveAvilale;
	PieceColor pieceColor;

	std::vector<sf::Vector2i> possibleMoves;

private:

	void initVariables();
	void initShape();




};


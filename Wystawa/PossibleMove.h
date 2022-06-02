#pragma once
#include "Square.h"

class Move : public Square
{
public:
	Move(GridData* grid_data, sf::Vector2i pos_on_grid);

	//Accessors
	//const sf::Vector2i& getPosOnGrid()const;

	void render(sf::RenderTarget& target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::CircleShape shape;
	GridData* gridData;
};


class PossibleMove : public sf::Drawable
{
public:
	PossibleMove();
	PossibleMove(std::vector<Move*> _possible_moves);
	PossibleMove(GridData* grid_data);
	~PossibleMove();

	void add(sf::Vector2i pos_on_grid);
	void remove(sf::Vector2i pos_on_grid);
	void remove(int index);
	void clear();
	void printMovesToConsole();

	const bool& contains(sf::Vector2i grid_pos) const;
	const int& getSize() const;
	const std::vector<Move*>& getPossibleMoves() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	GridData* gridData;
	std::vector<Move*> possibleMoves;


private:
	void initVariables();



};


#include "stdafx.h"
#include "Piece.h"



Piece::Piece()
{


	this->gridData = NULL;
	this->texture = NULL;
	this->posOnGrid = sf::Vector2i(0,0);
	this->type = 0;
	this->destroyed = false;
	this->temporarlyDisabled = false;

	this->initVariables();
}

Piece::Piece(GridData* grid_data, PositionOnBoard* board_in_text, sf::Vector2i pos_on_grid, sf::Texture* texture, int type)
{
	this->initVariables();


	this->gridData = grid_data;
	this->posOnGrid = pos_on_grid;
	this->type = type;
	this->texture = texture;

	if (type < 0)
		this->pieceColor = PieceColor::BLACK;
	else
		this->pieceColor = PieceColor::WHITE;



	this->initShape();

	this->setPositionOnGrid(pos_on_grid);
	//this->PossibleMove = new PossibleMove(this->gridData);
}

Piece::~Piece()
{
	delete this->gridData;
	delete this->texture;
}


//Accessors
const bool Piece::doesContain(sf::Vector2f& mouse_pos) const
{
	if (this->shape.getGlobalBounds().contains(mouse_pos))
	{
		return true;
	}
	return false;
}

const bool& Piece::isSelected() const
{
	return this->selected;
}

const int& Piece::getType() const
{
	return this->type;
}

const PieceColor& Piece::getPieceColor() const
{
	return this->pieceColor;
}

const bool& Piece::isDestroyed() const
{
	return this->destroyed;
}

const bool& Piece::isTemporarlyDisabled() const
{
	return this->temporarlyDisabled;
}

const bool& Piece::isFirstMoveAvialble() const
{
	return this->firstMoveAvilale;
}

//Modifiers

void Piece::destroy(bool destroy)
{
	this->destroyed = destroy;
}

void Piece::temporaryDisable(bool destroy)
{
	this->temporarlyDisabled == destroy;
}

void Piece::setSelect(bool select)
{
	this->selected = select;
}

void Piece::setPositionOnGrid(sf::Vector2i pos_on_grid)
{
	//this->boardAsText = piece_position;
	this->posOnGrid = pos_on_grid;

	this->shape.setPosition(
		static_cast<float>(this->posOnGrid.x) * this->gridData->tileSize.x + this->gridData->gridOffset.x + this->squareOffset.x,
		static_cast<float>(this->posOnGrid.y) * this->gridData->tileSize.y + this->gridData->gridOffset.y + this->squareOffset.y
	);
}

void Piece::firstMoveMade()
{
	this->firstMoveAvilale = false;
}

bool Piece::isInsideBoard(sf::Vector2i position)
{
	if (
		position.x < 8 &&
		position.x >= 0 &&
		position.y < 8 &&
		position.y >= 0
		)
		return true;

	return false;
}

bool Piece::isEnemy(int type_of_another_piece)
{
	if (this->type * type_of_another_piece < 0)
		return true;

	return false;
}

void Piece::addPossibleMove(PossibleMove& possible_moves, sf::Vector2i position)
{
	possible_moves.add(position);
}


//Functions
void Piece::update()
{
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->shape);
}

//Initializer functions
void Piece::initVariables()
{
	this->type = 0;
	this->destroyed = false;
	this->firstMoveAvilale = true;
	this->selected = false;
	this->gridData = NULL;
	this->texture = NULL;
	this->posOnGrid = sf::Vector2i(0, 0);
	this->squareOffset = sf::Vector2f(-8.f, 0.f);

}


void Piece::initShape()
{
	this->shape.setSize(this->gridData->tileSize);

	sf::Vector2i texture_pos;
	texture_pos = sf::Vector2i(abs(this->type) - 1, 0);

	if (type < 0)
		texture_pos.y = 1;
	this->shape.setTexture(this->texture);
	this->shape.setTextureRect(sf::IntRect(306 * texture_pos.x, 306 * texture_pos.y, 306, 306));
	//this->shape.setFillColor(sf::Color::Red);

}


MovesHistory::MovesHistory()
{
	this->movesBlack.reserve(50);
	this->movesWhite.reserve(50);
}

MovesHistory::~MovesHistory()
{
	for (int i = 0; i < this->movesWhite.size(); i++)
	{
		delete this->movesWhite[i];
	}

	for (int i = 0; i < this->movesBlack.size(); i++)
	{
		delete this->movesBlack[i];
	}
}

void MovesHistory::addMove(sf::Vector2i before, sf::Vector2i after, int type)
{
	Color color;
	color = (type > 0) ? Color::White : Color::Black;

	if (color == Color::Black)
		this->movesBlack.emplace_back(new MoveMade(before, after));
	else
		this->movesWhite.emplace_back(new MoveMade(before, after));

}

const MoveMade& MovesHistory::getLastMove() const
{
	return (this->movesWhite.size() > this->movesBlack.size()) ? *this->movesWhite.at(this->movesWhite.size() - 1) : *this->movesBlack.at(this->movesBlack.size() - 1);
}

void MovesHistory::printMoves()
{
	for (int i = 0; i < this->movesWhite.size(); i++)
	{

		if (this->movesWhite.size() != this->movesBlack.size() && i == this->movesBlack.size())
		{
			std::cout << "Round " << i + 1 << ": " << this->movesWhite[i]->getMoveString() << "\t" << "XX XX" << "\n";

		}
		else
		{
			std::cout << "Round " << i + 1 << ": " << this->movesWhite[i]->getMoveString() << "\t" << this->movesBlack[i]->getMoveString() << "\n";
		}
	}
}

MoveMade::MoveMade(sf::Vector2i before, sf::Vector2i after)
{
	this->before = before;
	this->after = after;
}

std::string MoveMade::getMoveString()
{

	std::string before_string = "";
	before_string.push_back(static_cast<char>(65 + before.x));
	before_string.push_back(8 - before.y + 48);

	std::string after_string = "";
	after_string.push_back(static_cast<char>(65 + after.x));
	after_string.push_back(8 - after.y + 48);

	return before_string + " " + after_string;
}

const sf::Vector2i& MoveMade::getMoveBefore() const
{
	return this->before;
}

const sf::Vector2i& MoveMade::getMoveAfter() const
{
	return this->after;
}

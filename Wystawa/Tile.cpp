#include "stdafx.h"
#include "Tile.h"

Tile::Tile(unsigned grid_pos_x, unsigned grid_pos_y, float size, sf::Color color, float shift_x, float shift_y)
	: size(size)
{
	this->tile.setFillColor(color);
	this->tile.setSize(sf::Vector2f(size, size));
	this->tile.setPosition((static_cast<float>(grid_pos_x) * size) + shift_x, (static_cast<float>(grid_pos_y) * size) + shift_y);

}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->tile);
}

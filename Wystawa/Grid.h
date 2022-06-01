#pragma once
#include "Square.h"


class Grid : public sf::Drawable
{
public:
	Grid(GridData* grid_data);
	~Grid();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	GridData* gridData;
	std::vector< std::vector<Square*>> grid;

};


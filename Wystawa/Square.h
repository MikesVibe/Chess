#pragma once


struct GridData
{
	GridData() {};
	sf::Vector2f gridOffset;
	sf::Vector2f tileSize;
	sf::Vector2f wholeGridSize;
	sf::Vector2u gridSize;
};


class Square : public sf::Drawable
{
public:
	Square();
	Square(GridData* grid_data, sf::Vector2i pos_on_grid);
	~Square();

	//Accessors
	const sf::Color& getFillColor()const;
	const sf::Vector2i getPositionOnGrid()const;
	const sf::FloatRect getGlobalBounds()const;


	//Modifiers
	void setFillColor(sf::Color color);
	void setPositionOnGrid(sf::Vector2i pos_on_grid, sf::Vector2f offset = sf::Vector2f(0.f, 0.f));
	void setTexture(sf::Texture* texture, sf::IntRect int_rect);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


protected:
	sf::Vector2i posOnGrid;

private:
	GridData* gridData;
	sf::RectangleShape background;

};
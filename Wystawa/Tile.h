#pragma once
class Tile :
	public sf::Drawable
{
public:
	Tile(unsigned grid_pos_x, unsigned grid_pos_y, float size, sf::Color color, float shift_x = 0, float shift_y = 0);
	~Tile();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float size;
	sf::RectangleShape tile;
	sf::Texture tileTexture;


};


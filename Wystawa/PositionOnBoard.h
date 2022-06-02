#pragma once

enum class MatrixToUse{ BEFORE = 0, AFTER };

class PositionOnBoard
{
public:
	PositionOnBoard();

	const bool& isEmpty(sf::Vector2i position) const;
	const bool& isEnemy(int type1, int type2) const;

	const int& getType(sf::Vector2i position) const;
	const int& getType(MatrixToUse matrix, sf::Vector2i position) const;

	void displayInConsole(MatrixToUse matrix);

	void movePiece(sf::Vector2i old_grid_pos, sf::Vector2i new_grid_pos);
	void beatPiece(sf::Vector2i old_grid_pos, sf::Vector2i new_grid_pos);
	void deletePiece(sf::Vector2i grid_pos);
	void placePiece(sf::Vector2i grid_pos, int piece_type);
	sf::Vector2i findPositionOfKing();

	void saveMove();
	void undoMove();

private:
	int matrixAfter[8][8] =
	{
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  0,
		 3,  0,  0,  0,  0,  0,  0,  0,
		 0,  0,  0,  0,  0,  0,  0,  2,
		-1,  0,  0,  0,  0,  0,  0,  0,
	};

	//int matrix[8][8] =
	//{
	//	 -5,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  -1,  0,
	//	 -4,  0,  2,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  -6,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  3,  3,  -6,  0,  -6,  0,  0,
	//	 0,  0,  0,  0,  6,  0,  0,  0,
	//	 0,  0,  0,  2,  0,  0,  0,  0,
	//};
	//int matrixAfter[8][8] =
	//{
	//	-5, -4, -3, -2, -1, -3, -4, -5,
	//	-6, -6, -6, -6, -6, -6, -6, -6,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 6,  6,  6,  6,  6,  6,  6,  6,
	//	 5,  4,  3,  2,  1,  3,  4,  5
	//};
	//int matrixAfter[8][8] =
	//{
	//	-5, -4, -3,  0, -1, -3, -4, -5,
	//	-6, -6,  0,  0,  0, -6, -6, -6,
	//	 0,  0,  0,  0, -6,  0,  0,  0,
	//	 3,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  6,  0,
	//	 0,  0,  0,  0,  0,  6,  0,  0,
	//	 6,  6,  6,  0,  6,  0,  0,  6,
	//	 5,  4,  3,  2,  1,  3,  4,  5
	//};

	//int matrixAfter[8][8] =
	//{
	//	-5, -4, -3, -2, -1, -3, -4, -5,
	//	-6, -6, -6,  0, -6, -6, -6, -6,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 0,  0,  0,  0,  0,  0,  0,  0,
	//	 6,  6,  6,  0,  6,  6,  6,  6,
	//	 5,  0,  0,  0,  1,  0,  0,  5
	//};
	int matrixBefore[8][8];
};


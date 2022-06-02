#pragma once
#include "State.h"
#include "Grid.h"
#include "King.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "PositionOnBoard.h"
#include "PossibleMove.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "SideNumbersPanel.h"

struct OnPassantMove
{
	bool wasOnPassantMoveMade;
	int roundOfOnPassantMove;
	sf::Vector2i position;
};

enum class GameStatus {ONGOING=0, STALEMATE, CHECKMATE};

class ChessGameState : public State
{
public:
	ChessGameState(StateData* state_data);
	~ChessGameState();
	
	
	//Functions
	const PieceColor whosMove() const;
	const int whosMoveInt() const;

	int findIndexOfPiece(sf::Vector2i grid_pos);
	int findIndexOfSelectedPiece();
	sf::Vector2i findPositionOfKing(PieceColor color);
	void select(Piece* piece);
	void unselect(Piece* piece);
	std::vector<sf::Vector2i> findLegalMovesPositions(Piece* piece);
	void nextPlayersTurn();
	void makeMove(Piece * &piece, sf::Vector2i new_grid_pos, bool will_be_undone = false);
	void tryToMakeMove(Piece* piece, sf::Vector2i new_grid_pos);

	//DEBUG
	std::string getGridPosString(sf::Vector2i grid_pos);
	void printGridPos(sf::Vector2i grid_pos);
	void renderMouseCordinates(sf::RenderTarget& target);
	void printPosition(sf::Vector2i position);
	GameStatus checkForGameStatus(PieceColor color);

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updateChessPiecesVector();
	void updatePauseMenuButtons();
	void updateGameOverMenuButtons();
	void update(const float& dt);

	void render(sf::RenderTarget* target = NULL);

private:
	//Private Variables
	sf::RectangleShape background;
	sf::Font font;
	sf::Texture chessPieceTexture;

	//Board / Grid
	Grid* grid;
	GridData gridData;
	SideNumbersPanel* sideNumbersPanel;
	MovesHistory movesMade;

	PositionOnBoard* boardAsText;
	PossibleMove possibleMoves;
	PieceColor playersTurn;
	int round = 0;
	OnPassantMove onPassantMove;

	std::vector<Piece*> chessPieces;
	bool figureIsSelected;

	GameOverMenu* gameOverMenu;
	PauseMenu* pmenu;
	
private:
	//Priavte Functions
	sf::Vector2i mousePositionToGrid(sf::Vector2f& mouse_pos);

	//Init Functions
	void initVariables();
	void initTextures();
	void initBackground();
	void initFonts();
	void initKeybinds();

	//Game stuff
	void initBoardAsText();
	void initGridData();
	void initGrid();
	void initGridSquareNumbers();
	void initChessPieces();
	void initPossibleMove();

	//Menus
	void initPauseMenu();
	void initGameOverMenu();

	template <class T> void createPiece(T, sf::Vector2i position)
	{
		this->chessPieces.emplace_back(
			new T(
				&this->gridData,
				this->boardAsText,
				position,
				&this->chessPieceTexture,
				this->boardAsText->getType(position)
			)
		);
	}
};


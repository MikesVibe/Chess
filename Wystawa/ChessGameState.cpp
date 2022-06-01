#include "stdafx.h"
#include "ChessGameState.h"

ChessGameState::ChessGameState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initTextures();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();


	this->initBoardAsText();
	this->initGridData();
	this->initGrid();
	this->initGridSquareNumbers();
	this->initChessPieces();
	this->initPossibleMove();

	//Menus
	this->initPauseMenu();
	this->initGameOverMenu();

}

ChessGameState::~ChessGameState()
{
	delete this->possibleMoves;
	delete this->boardAsText;
	delete this->pmenu;
	delete this->gameOverMenu;
	delete this->grid;
	delete this->sideNumbersPanel;
}

const PieceColor ChessGameState::whosMove() const
{
	return this->playersTurn;
}

const int ChessGameState::whosMoveInt() const
{
	return static_cast<int>(playersTurn);
}

int ChessGameState::findIndexOfPiece(sf::Vector2i grid_pos)
{
	/*
	Searches for index of a Pieces in vector.
	Uses the X and Y value in the matrix to identify.
	*/
	for (int i = 0; i < static_cast<int>(this->chessPieces.size()); i++)
	{
		if(this->chessPieces[i]->getPositionOnGrid() == grid_pos)// && this->chessPieces[i]->getShow())
			return i;
	}

	return -1;
}

int ChessGameState::findIndexOfSelectedPiece()
{
	for (int i = 0; i < static_cast<int>(this->chessPieces.size()); i++)
	{
		if (this->chessPieces[i]->isSelected())
			return i;
	}

	return -1;
}

sf::Vector2i ChessGameState::findPositionOfKing(PieceColor color)
{
	for (int i = 0; i < static_cast<int>(this->chessPieces.size()); i++)
	{
		if (this->chessPieces[i]->getType() == static_cast<int>(color))// && this->chessPieces[i]->getShow())
			return this->chessPieces[i]->getPositionOnGrid();
	}


	return sf::Vector2i(-1,-1);
}

void ChessGameState::select(Piece* piece)
{
	piece->setSelect(true);
	this->figureIsSelected = true;
}

void ChessGameState::unselect(Piece* piece)
{
	this->possibleMoves->clear();
	piece->setSelect(false);
	this->figureIsSelected = false;
}

void ChessGameState::findLegalMoves(Piece* piece)
{
	//std::cout << "Is king in check: " << dynamic_cast<King*>(piece)->isInCheck(boardAsText, piece->getPositionOnGrid(), piece->getType()) << std::endl;

	this->possibleMoves->clear();

	//Find legal moves for pawn
	if (abs(piece->getType()) == 6)
	{
		//This shity thing is what I used to send nerby Pawns refrences to the pawn which is searching for semi legal moves
		//I could not figure out any other way to send this refrences to the pawn 
		sf::Vector2i* pleft, * pright, var;
		Pawn* pawn;
		var = piece->getPositionOnGrid();
		sf::Vector2i left, right;
		
		if (var.x - 1 < 0)
			pleft = NULL;
		else
		{
			left = sf::Vector2i(var.x - 1, var.y);
			pleft = &left;
		}

		if (var.x + 1 > 7)
			pright = NULL;
		else
		{ 
			right = sf::Vector2i(var.x + 1, var.y);
			pright = &right;
		}

		int index = this->findIndexOfPiece(left);
		if (pleft != NULL && index != -1 && abs(this->chessPieces[index]->getType()) == 6 && piece->isEnemy(this->chessPieces[index]->getType()))
		{
			left.y += (static_cast<int>(this->whosMove()) * -1);
			pawn = dynamic_cast<Pawn*>(this->chessPieces[index]);
			if (pawn->isEnPassantPossible(this->round))
			{
				this->possibleMoves->add(left);
				this->onPassantMove.roundOfOnPassantMove = this->round;
				this->onPassantMove.wasOnPassantMoveMade = true;
				this->onPassantMove.position = left;
			}
		}

		index = this->findIndexOfPiece(right);
		if (pright != NULL && index != -1 && abs(this->chessPieces[index]->getType()) == 6 && piece->isEnemy(this->chessPieces[index]->getType()))
		{
			right.y += (static_cast<int>(this->whosMove()) * -1);
			pawn = dynamic_cast<Pawn*>(this->chessPieces[index]);
			if (pawn->isEnPassantPossible(this->round))
			{
				possibleMoves->add(right);
				this->onPassantMove.roundOfOnPassantMove = this->round;
				this->onPassantMove.wasOnPassantMoveMade = true;
				this->onPassantMove.position = right;
			}
		}
	}

	//Finding semilegal moves
	piece->getSemiLegalMoves(this->boardAsText, *this->possibleMoves);

	std::vector<Move*> _possbile_moves = possibleMoves->getPossibleMoves();


	sf::Vector2i king_pos = findPositionOfKing(piece->getPieceColor());

	//Check if king would be in check after any of semi legeal moves
	for (int i = 0; i < possibleMoves->getSize(); i++)
	{

		//TODO
		//Make a move, check if after this move king is in check
		//if yes than remove it from possible moves list
		//else undo this move but do not delete it from possible moves list

		//this->boardAsText->saveMove();

		this->makeMove(piece, _possbile_moves[i]->getPositionOnGrid(), true);

		if (abs(piece->getType()) == 1)
			king_pos = _possbile_moves[i]->getPositionOnGrid();

		

		if (King::isInCheck(this->boardAsText, king_pos, piece->getPieceColor()))
		{
			//auto iterator = remove(begin(_possbile_moves), end(_possbile_moves), _possbile_moves[i]);
			//_possbile_moves.erase(iterator, end(_possbile_moves));
			this->possibleMoves->remove(_possbile_moves[i]->getPositionOnGrid());
		}
		this->boardAsText->undoMove();


		//this->boardAsText->undoMove();
	}

	for (int i = 0; i < this->chessPieces.size(); i++)
	{
		if(this->chessPieces[i]->isTemporarlyDisabled())
			this->chessPieces[i]->temporaryDisable(false);
	}
}

void ChessGameState::nextPlayersTurn()
{
	if (this->playersTurn == PieceColor::WHITE)
		this->playersTurn = PieceColor::BLACK;
	else
		this->playersTurn = PieceColor::WHITE;
}

std::string ChessGameState::getGridPosString(sf::Vector2i grid_pos)
{
	std::stringstream ss;
	//grid_pos.x += 97;
	//grid_pos.y += 1;
	ss << grid_pos.x << ", " << grid_pos.y <<"\n";

	return ss.str();
}

void ChessGameState::makeMove(Piece*& piece, sf::Vector2i new_grid_pos, bool will_be_undone)
{
	/*
	This function is responsible for moving piecies on graphic board and text board
	If a piece was beaten it removes it changes its "destroyed" variable and returns index fo this piece
	*/
	sf::Vector2i old_grid_pos = piece->getPositionOnGrid();
	int index_to_return = -1;
	//Check for EnPassant
	if (
		this->onPassantMove.roundOfOnPassantMove != -1 &&
		this->onPassantMove.wasOnPassantMoveMade == true &&
		this->onPassantMove.roundOfOnPassantMove == this->round &&
		this->onPassantMove.position == new_grid_pos
		)
	{
		sf::Vector2i possition_of_enemy_pawn = new_grid_pos;
		int piece_type = 6;

		possition_of_enemy_pawn.y += this->whosMoveInt();
		piece_type *= this->whosMoveInt();

		////DEBUG
		//std::cout << "moveInt: " << this->whosMoveInt() << "\n";
		//std::cout << "Round: " << this->round << "\n";
		//std::cout << "On Passant round: " << this->onPassantMove.roundOfOnPassantMove << "\n";
		//std::cout << "On Passant: " << this->onPassantMove.wasOnPassantMoveMade << "\n";
		//std::cout << "Position of enemy pawn: (" << possition_of_enemy_pawn.x + 1 << ", " << possition_of_enemy_pawn.y + 1 << ")\n";
		//std::cout << "Destination of enPassant: (" << this->onPassantMove.position.x + 1 << ", " << this->onPassantMove.position.y + 1 << ")\n";

		index_to_return = this->findIndexOfPiece(possition_of_enemy_pawn);

		if(will_be_undone)
			this->chessPieces[index_to_return]->temporaryDisable();
		else
			this->chessPieces[index_to_return]->destroy();

		this->boardAsText->deletePiece(old_grid_pos);
		this->boardAsText->deletePiece(possition_of_enemy_pawn);
		this->boardAsText->placePiece(new_grid_pos, piece_type);

		if (!will_be_undone)
		{
			this->onPassantMove.wasOnPassantMoveMade = false;
			this->onPassantMove.roundOfOnPassantMove = -1;
		}

	}
	//Check for Standard Move
	else if (this->boardAsText->isEmpty(new_grid_pos))
	{
		//Checks if on position we want to place a peace is something placed
		//If there nothing on a new spot it places there a peace
		this->boardAsText->movePiece(old_grid_pos, new_grid_pos);
	}
	else if(!(this->boardAsText->isEmpty(new_grid_pos))) //Check for Standard Move with beating enemy piece
	{
		index_to_return = this->findIndexOfPiece(new_grid_pos);
		if (will_be_undone)
			this->chessPieces[index_to_return]->temporaryDisable();
		else
			this->chessPieces[index_to_return]->destroy();

		this->boardAsText->beatPiece(old_grid_pos, new_grid_pos);
	}
}

void ChessGameState::tryToMakeMove(Piece* piece, sf::Vector2i new_grid_pos)
{
	if (!this->possibleMoves->contains(new_grid_pos))
		return;


	sf::Vector2i old_grid_pos = piece->getPositionOnGrid();
	
	this->makeMove(piece, new_grid_pos);
	this->boardAsText->saveMove();
	this->movesMade.addMove(old_grid_pos, new_grid_pos, piece->getType());
	
	this->isGameOver(piece->getPieceColor());

	//this->movesMade.printMoves();

	//Moving pieces graphically 
	piece->setPositionOnGrid(new_grid_pos);

	//This is needed to determine if En Passant will be possible
	if (abs(piece->getType()) == 6 )
	{
		Pawn* pawn = dynamic_cast<Pawn*>(piece);
		pawn->activateEnPassant(this->round);
	}
	this->round++;

	//First move was made
	if (piece->isFirstMoveAvialble())
		piece->firstMoveMade();


	this->nextPlayersTurn();
}

//
//const sf::Vector2i& ChessGameState::findPositionOfKing(int type) const
//{
//	for (auto& piece : chessPieces)
//	{
//		if (piece->getType() == type)
//			return piece->getPositionOnGrid();
//	}
//
//	return sf::Vector2i();
//}

//DEBUG
void ChessGameState::printGridPos(sf::Vector2i grid_pos)
{
	std::cout << static_cast<char>(grid_pos.x + 97) << grid_pos.y + 1 << "\n";
}

void ChessGameState::renderMouseCordinates(sf::RenderTarget& target)
{
//Debuging thing
sf::Text mouseText;
mouseText.setPosition(this->mousePosView.x + 10.f, this->mousePosView.y + 20.f);
mouseText.setFont(this->font);
mouseText.setCharacterSize(30);
std::stringstream ss;
ss << this->getGridPosString(static_cast<sf::Vector2i>(this->mousePosView));
mouseText.setString(ss.str());
target.draw(mouseText);
}

void ChessGameState::printPosition(sf::Vector2i position)
{
	std::cout << static_cast<char>(65 + position.x) << 8 - position.y << "\n";
}

bool ChessGameState::isGameOver(PieceColor color)
{
	return false;
}

//---------------------Update Functions---------------------//

void ChessGameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void ChessGameState::updatePlayerInput(const float& dt)
{
	//Mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		std::cout << "Grid POSITION: " << this->mousePositionToGrid(this->mousePosView).x 
			<< ", " << this->mousePositionToGrid(this->mousePosView).y << "\n";

		//Is something selected
		if (this->figureIsSelected)
		{
			Piece* selected_piece = this->chessPieces[this->findIndexOfSelectedPiece()];

			this->tryToMakeMove(selected_piece, this->mousePositionToGrid(this->mousePosView));
			this->unselect(selected_piece);
		}
		//Iterate through all chess pieces and check if any of them is on current position of mouse
		else
		{
			for(auto chess_piece : this->chessPieces)
			{
				if (chess_piece->isDestroyed())
					continue;

				if (
					chess_piece->doesContain(this->mousePosView) &&
					chess_piece->getType() * static_cast<int>(this->whosMove()) > 0
					)
				{
					this->select(chess_piece);
					this->findLegalMoves(chess_piece);
					break;
				}
				else
					this->unselect(chess_piece);
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		this->boardAsText->displayInConsole(MatrixToUse::BEFORE);
		this->boardAsText->displayInConsole(MatrixToUse::AFTER);
	}
}

void ChessGameState::updateChessPiecesVector()
{
	//Delete beated pieces from vector

	//auto iterator = remove_if(begin(this->chessPieces), end(this->chessPieces), [](Piece* chess_piece)
	//	{
	//		return chess_piece->isDestroyed();
	//	});
	//this->chessPieces.erase(iterator, end(this->chessPieces));
}	

void ChessGameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void ChessGameState::updateGameOverMenuButtons()
{
	if (this->gameOverMenu->isButtonPressed("QUIT"))
		this->endState();

}

void ChessGameState::update(const float& dt)
{
	this->updateMousePos();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused && !this->gameover) //Unpaused update 
	{
		this->updatePlayerInput(dt);
		//this->updateChessPiecesVector();
	}
	else if (this->paused && !this->gameover) //Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	else
	{
		this->gameOverMenu->update(this->mousePosView);
		//this->updateGameOverMenuButtons();
	}
}

//---------------------End of Update Functions---------------------//
//---------------------Render Functions---------------------//
void ChessGameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//Drawing background
	target->draw(this->background);

	//Drawing board
	target->draw(*this->grid);


	target->draw(*this->sideNumbersPanel);


	//Drawing chess pieces
	for (int i = 0; i < static_cast<int>(this->chessPieces.size()); i++)
	{
		if (this->chessPieces[i]->isDestroyed())
			continue;

		target->draw(*this->chessPieces[i]);
	}

	target->draw(*this->possibleMoves);

	//this->renderMouseCordinates(*this->window);

	if (this->paused) //Paused menu render
	{
		this->pmenu->render(*target);
	}

	if (this->gameover) //Game over menu render
	{
		this->gameOverMenu->render(*target);
	}
}


//---------------------End of Render Functions---------------------//
//---------------------Private Functions---------------------//


sf::Vector2i ChessGameState::mousePositionToGrid(sf::Vector2f& mouse_pos)
{
	/*
	Converts the mouse position, to the grid position.
	*/
	sf::Vector2i var;
	var = sf::Vector2i(
		static_cast<int>(floor((static_cast<float>(mouse_pos.x) - this->gridData.gridOffset.x) / this->gridData.tileSize.x)),
		static_cast<int>(floor((static_cast<float>(mouse_pos.y) - this->gridData.gridOffset.y) / this->gridData.tileSize.y))
	);

	return var;

}

//---------------------End of Private Functions---------------------//
//---------------------Init Functions---------------------//

void ChessGameState::initVariables()
{
	this->paused = false;
	this->gameover = false;
	figureIsSelected = false;
	this->chessPieces.reserve(64);
	this->playersTurn = PieceColor::WHITE;

	this->onPassantMove.wasOnPassantMoveMade = false;
	this->onPassantMove.roundOfOnPassantMove = -1;
	this->onPassantMove.position = sf::Vector2i(0, 0);

}

void ChessGameState::initTextures()
{
	if(!this->chessPieceTexture.loadFromFile("Resources/ChessGame_Textures/chess_pieces_sheet.png"))
	{
	throw("ERROR::Pieces::FAILED_TO_LOAD_CHESSGAME_TEXTURE");
	}
}

void ChessGameState::initBackground()
{
	this->background.setSize(static_cast<sf::Vector2f>(this->stateData->window->getSize()));
	this->background.setFillColor(sf::Color(60, 60, 60));
}

void ChessGameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Changa-VariableFont_wght.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void ChessGameState::initKeybinds()
{
	std::ifstream ifs("Config/chess_gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void ChessGameState::initBoardAsText()
{
	this->boardAsText = new PositionOnBoard();

}

void ChessGameState::initGridData()
{
	this->gridData.gridSize = sf::Vector2u(8U, 8U);
	this->gridData.tileSize = sf::Vector2f(102.f, 102.f);

	this->gridData.wholeGridSize = sf::Vector2f(
		(gridData.gridSize.x * gridData.tileSize.x),
		(gridData.gridSize.y * gridData.tileSize.y)
	);

	this->gridData.gridOffset = sf::Vector2f(
		this->stateData->window->getSize().x / 2.f - this->gridData.wholeGridSize.x / 2.f,
		this->stateData->window->getSize().y / 2.f - this->gridData.wholeGridSize.y / 2.f
	);
}

void ChessGameState::initGrid()
{
	this->grid = new Grid(&this->gridData);
}

void ChessGameState::initGridSquareNumbers()
{
	//std::cout << this->gridData.gridOffset.x << ", " << this->gridData.gridOffset.y << "\n";

	sideNumbersPanel = new SideNumbersPanel(this->font, this->gridData);

}

void ChessGameState::initChessPieces()
{
	int row, column;

	for (row = 0; row < static_cast<int>(this->gridData.gridSize.x); row++)
	{
		for (column = 0; column < static_cast<int>(this->gridData.gridSize.y); column++)
		{

			if (this->boardAsText->getType(MatrixToUse::AFTER, sf::Vector2i(column, row)) != 0)
			{
				switch (abs(this->boardAsText->getType(MatrixToUse::AFTER, sf::Vector2i(column, row))))
				{
				case 1:
					createPiece(King(), sf::Vector2i(column, row));
					break;
				case 2:
					createPiece(Queen(), sf::Vector2i(column, row));
					break;
				case 3:
					createPiece(Bishop(), sf::Vector2i(column, row));
					break;
				case 4:
					createPiece(Knight(), sf::Vector2i(column, row));
					break;
				case 5:
					createPiece(Rook(), sf::Vector2i(column, row));
					break;
				case 6:
					createPiece(Pawn(), sf::Vector2i(column, row));
					break;
				}
			}
		}
	}
}

void ChessGameState::initPossibleMove()
{
	this->possibleMoves = new PossibleMove(&this->gridData);
}

void ChessGameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void ChessGameState::initGameOverMenu()
{
	this->gameOverMenu = new GameOverMenu(*this->window, this->font);

	/*this->gameOverMenu->addButton("RESTART", 600.f, "Restart");
	this->gameOverMenu->addButton("QUIT", 800.f, "Quit");*/
}


//---------------------End ofInit Functions---------------------//


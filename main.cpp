/**
 * Created by Ryzeon
 * Project: Trabajo Final Programacion I
 * Date: 11/06/22 @ 18:23
 * Twitter: @Ryzeon_ 😎
 * Github: github.ryzeon.me
 */
#include <iostream>
#include <ctime>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <limits>
// This are libs for using in thread.sleep();
#include <chrono>
#include <thread>

using namespace std;
using namespace System;

string RESET_COLOR = "\033[m";
string MAIN_COLOR = "\033[1;32m";

struct PiecePosition
{
	char letter;
	int num;

	int* fetch() const
	{
		return new int[2]{
			(letter - 64) - 1,
			num - 1
		};
	};

	string to_string()
	{
		string text = "[";
		text += (char)letter;
		text += ",";
		text += std::to_string(num);
		text += "]";
		return text;
	}

	bool IsEmpty()
	{
		return this->letter == 'N';
	}

	bool equals(PiecePosition pos) const
	{
		//   Debug     cout << "Verificando si " << pos.letter << " = " << letter << " con " << pos.num << " = " << num << endl;
		return pos.letter == letter && num == pos.num;
	}

	PiecePosition prev()
	{

	}

	PiecePosition next()
	{
	}

	PiecePosition up()
	{
	}

	PiecePosition down()
	{
	}
};

struct GamePlayer
{
	string name;
	int color;
	int amountOfPieces;
	int amountOfPiecesInBoard;
	int identifier;
	PiecePosition pieceToMove = {
		'N', 0
	};

	string getColor()
	{
		return "\033[0;3" + to_string(color) + "m";
	}

	void resetPieceMove()
	{
		pieceToMove = {
			'N',
			0
		};
	}

	void addPiece()
	{
		amountOfPieces--;
		amountOfPiecesInBoard++;
	}
};

struct GameBoard
{
	int board[7][7];
	GamePlayer players[2];

	GamePlayer getPlayer(int n)
	{
		return players[n];
	}
};

struct Game
{
	bool test = true;
	GameBoard board;
	GamePlayer winner;
	bool ended;
	int currentPhase;

	int currentTurn = 0;

	int nextTurn()
	{
		bool c = currentTurn;
		return !c;
	}
} game;

void welcomeScreen();

void winnerScreen();

void printGameInstructions();

void menu();

void initGame();

void drawGame(const string& message = "x");

bool isColorAvailable(int color);

bool isValidName(const string& input);

void cleanConsole();

string askForPlayerName(string question, string wrongAnswer);

int askForColor(string question, string wrongAnswer);

PiecePosition
askForAMovement(GamePlayer& player, const string& ask = "poner en el tablero", const bool& checkSelf = false);

string getColorOfDotFromBoard(string input, int locI, int locJ);

PiecePosition* getPiecesPosition(const GamePlayer& player);

GamePlayer getPlayerByPiece(PiecePosition piecePosition);

void putPiece(PiecePosition piecePosition, GamePlayer& player);

bool isMovementValid(GamePlayer& player, PiecePosition movement);

bool isMovementMakeAWindmill(GamePlayer& player, PiecePosition movement);

bool takePlayerPiece(GamePlayer& taker, PiecePosition pieceToTake);

void startNextPhase();

bool checkCurrentPhase();

bool hasAnAdjacentPieze(PiecePosition pos, GamePlayer& player);

bool canMove(const GamePlayer& player);

bool checkWinner();

void printWord(const string& text)
{
	for (char i : text)
	{
		cout << i;
		this_thread::sleep_for(chrono::milliseconds(6));
	}
	cout << endl;
}

void putRandomPieces(int maxPieces)
{
	int counta = 1, count = 1;
	while (counta <= maxPieces && count <= maxPieces)
	{
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				int numer = game.board.board[i][j];
				if (numer == 88 || numer == 99 || numer == 1 || numer == 2)
				{
					continue;
				}
				bool xd = rand() % 2;
				char iC = (char)(i + 1 + 64);
				int xdxdd = j + 1;
				GamePlayer* ga;
				if (xd)
				{
					if (counta <= maxPieces)
					{
						ga = &game.board.players[0];
						putPiece({
							         iC,
							         xdxdd
						         }, *ga);
						// cout << "poniendo en posicion ju1 (" << i << ", " << j << ")" << " -> " << numer << endl;
						counta++;
					}
					else
					{
						// cout << "el jugador 1 ya tiene 9 " << endl;
					}
				}
				else
				{
					if (count <= maxPieces)
					{
						// cout << "poniendo en posicion ju2 (" << i << ", " << j << ")" << " -> " << numer << endl;
						ga = &game.board.players[1];
						putPiece({
							         iC,
							         xdxdd
						         }, *ga);
						count++;
					}
					else
					{
						// cout << "el jugador 2 ya tiene 9 " << endl;
					}
				}
			}
		}
	}
	//    drawGame();

	//    putPiece('A', 1, game.board.players[0]);
	//    putPiece('D', 2, game.board.players[0]);
	//    putPiece('F', 2, game.board.players[0]);
	//    putPiece('B', 2, game.board.players[0]);
	//
	//    putPiece('G', 1, game.board.players[1]);
	//    putPiece('G', 4, game.board.players[1]);
	//    putPiece('C', 5, game.board.players[1]);
	//    putPiece('B', 6, game.board.players[1]);
}

int main()
{
	system("color 0F"); // Allow using the other colors :jeje:
	int array[62][74] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 1, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 0, 1, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 1, 1, 4, 4, 4, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 4, 1, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 1, 3, 3, 3, 3, 3, 3, 1, 5, 5, 2, 5, 5, 5, 1, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 3, 3, 3, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 5, 5, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 5, 5, 0, 0, 1, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 4, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 3, 3, 4, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 1, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 1, 2, 0, 0, 1, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 1, 4, 2, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 0, 1, 4, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 4, 4, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 3, 3, 3, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};


	//Color Index
	//0---->WHITE---->-1
	//1---->BLACK---->-16777216
	//2---->GRAY---->-8355712
	//3---->YELLOW---->-256
	//4---->DARKGRAY---->-12566464
	//5---->RED---->-65536







	Console::SetWindowSize(200, 62);
    for (int i = 0; i < 62; ++i) {
        for (int j = 0; j < 74; ++j) {
			Console::SetCursorPosition(j, i);
			int val = array[i][j];
			if (val == 0) {
				Console::ForegroundColor = ConsoleColor::White;
			
			}
			if (val == 1) {
				Console::ForegroundColor = ConsoleColor::Black;

			}
			if (val == 2) {
				Console::ForegroundColor = ConsoleColor::Gray;
			
			}
			if (val == 3) {
				Console::ForegroundColor = ConsoleColor::Yellow;
			
			}
			if (val == 4) {
				Console::ForegroundColor = ConsoleColor::DarkGray;
			
			}
			if (val == 5) {
				Console::ForegroundColor = ConsoleColor::Red;

			}
			if (val == 6) {
				Console::ForegroundColor = ConsoleColor::Red;

			}
			if (val == 7) {
				Console::ForegroundColor = ConsoleColor::Yellow;

			}
			// if (val == 5) {
			// 	Console::ForegroundColor = ConsoleColor::Black;
			//
			// }
			// if (val == 6) {
			// 	Console::ForegroundColor = ConsoleColor::Cyan;
			//
			// }
			// if (val == 3 || val == 4)
			// {
			// 	Console::ForegroundColor = ConsoleColor::Gray;
			// 	
			// }
			// if (val == 2) {
			// 	Console::ForegroundColor = ConsoleColor::Yellow;
			//
			// }
			// if (val == 5 || val == 1) {
			// 	Console::ForegroundColor = ConsoleColor::Yellow;
			//
			// }
			cout << (char)219;

        }
    }


//	game.test = true; // Put game.test = true for test game, only for fast deploy :ojito:
//	if (game.test)
//	{
//		initGame();
//	}
//	else
//	{
//		welcomeScreen();
//	}
	system("pause");
	getch();
	return 0;
}

void welcomeScreen()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Allow UF-16 characters
	// wprintf -> I use wprintf for can print ascii characters
	wprintf(
		L"┌───────────────────────────────┐\n"
		L"│       :                  :    │\n"
		L"│     -*=+:              :**+-  │\n"
		L"│     .=#*=*-.         .**++=.  │\n"
		L"│        -#+++-:     .+#++=.    │\n"
		L"│          :*++*=- .+#+=+:      │\n"
		L"│            :+*+#*#+++-        │\n"
		L"│             :######-          │\n"
		L"│           .+++###+#=          │\n"
		L"│          ===*###*+*+*=        │\n"
		L"│        :+=*#+:-==-=+*+#=      │\n"
		L"│      .==+#&+=:-==:-==+++#=    │\n"
		L"│     .=+#*-+=-:-+-:-== :=+*#.  │\n"
		L"│       -- +==::+-*:--+   ::    │\n"
		L"│         .+--::::::&&+:        │\n"
		L"│         .:::::::::---.        │\n"
		L"│───────────────────────────────│\n"
		L"│        Juego del Molino       │\n"
		L"├───────────────────────────────┤\n"
		L"│ Grupo 6:                      │\n"
		L"│ Alex Avila Asto (U20221A322)  │\n"
		L"│ Carlos Lara Talla (U202114534)│\n"
		L"└───────────────────────────────┘\n"
	);
	_setmode(_fileno(stdout), _O_TEXT); // Reset character mode
	cout << MAIN_COLOR << "Cargando...." << RESET_COLOR << "\n";
	this_thread::sleep_for(chrono::milliseconds(3000));
	cleanConsole();
	printGameInstructions();
}

void winnerScreen()
{
}

void menu()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(
		L"━━┃┃━━━━━━━━━━━━━━━━━━━━━━┃┃━━━━┃┃━━━━━━━━━━━━━┃┃━━━━━━━━━━━\n"
		L"━━┃┃┏┓┏┓┏━━┓┏━━┓┏━━┓━━━━┏━┛┃┏━━┓┃┃━━━━━┏┓┏┓┏━━┓┃┃━┏┓┏━┓━┏━━┓\n"
		L"┏┓┃┃┃┃┃┃┃┏┓┃┃┏┓┃┃┏┓┃━━━━┃┏┓┃┃┏┓┃┃┃━━━━━┃┗┛┃┃┏┓┃┃┃━┣┫┃┏┓┓┃┏┓┃\n"
		L"┃┗┛┃┃┗┛┃┃┃━┫┃┗┛┃┃┗┛┃━━━━┃┗┛┃┃┃━┫┃┗┓━━━━┃┃┃┃┃┗┛┃┃┗┓┃┃┃┃┃┃┃┗┛┃\n"
		L"┗━━┛┗━━┛┗━━┛┗━┓┃┗━━┛━━━━┗━━┛┗━━┛┗━┛━━━━┗┻┻┛┗━━┛┗━┛┗┛┗┛┗┛┗━━┛\n"
		L"━━━━━━━━━━━━┏━┛┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
		L"━━━━━━━━━━━━┗━━┛━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
		L"\n"
		L"           ┌───────── Elije una opcion ─────────┐\n"
		L"           │ 1.- Nueva Partida                  │\n"
		L"           │ 2.- Salir                          │\n"
		L"           └────────────────────────────────────┘\n"
	);
	_setmode(_fileno(stdout), _O_TEXT);
	int choose;
	bool done = false;
	while (!done)
	{
		int value;
		cout << ">> ";
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ingrese un valor valido!" << endl;
		}
		else if (value >= 1 && value <= 2)
		{
			done = true;
			choose = value;
		}
		else
		{
			cout << "Ingrese un valor valido!" << endl;
		}
	}
	if (choose == 1)
	{
		initGame();
	}
	else
	{
		cout << "Gracias por jugar!" << endl;
		system("pause");
	}
}

void printGameInstructions()
{
	cout
		<< "---------------------------------------------------INSTRUCCIONES----------------------------------------------------"
		<< endl;
	printWord(
		"En la primera fase del juego, cada jugador en su turno coloca una de sus 9 fichas sobre cualquiera de los puntos.");
	printWord(
		"del tablero que estan libres. Durante esta fase no es posible mover las fichas ya situadas en el tablero.");
	cout << "\n";
	printWord(
		"Una vez colocadas las 18 fichas sobre el tablero comienza la segunda fase, durante la cual cada jugador en su");
	printWord("turno mueve una de sus fichas a un punto adyacente libre a traves de alguna de las lineas del tablero.");
	printWord("Si no puede hacerlo, ha perdido el juego.");
	cout << "\n";
	printWord(
		"Cada jugador, cuando incorpora una ficha al tablero o la desplaza, debe intentar completar un molino o 3 en raya,");
	printWord(
		"es decir, una secuencia de 3 fichas del mismo color situadas sobre los 3 puntos de una misma linea. Cada vez que");
	printWord(
		"se completa un molino, el jugador debe capturar una ficha adversaria, que es sacada del tablero y ya no volvera a");
	printWord(
		"ser jugada. Siempre que se completa un molino se realiza una captura, incluso aunque el molino haya sido completado");
	printWord("previamente y se repita de nuevo al retornar una misma ficha a un punto que ocupaba anteriormente.");
	cout << "\n";
	printWord(
		"El jugador que realiza la captura elige la ficha a capturar entre todas las fichas del adversario que no forman");
	printWord("parte de ningun molino.");
	printWord(
		"En el caso de que todas las fichas del rival formen parte de algun molino, elige libremente entre todas ellas.");
	cout << "\n";
	printWord(
		"Cuando un jugador dispone unicamente de 3 fichas sobre el tablero como consecuencia de haber sufrido 6 capturas,");
	printWord(
		"comienza la tercera fase del juego en la que se permite el \"vuelo\", de tal manera que las fichas de dicho jugador");
	printWord(
		"pueden saltar libremente a cualquier punto vacio del tablero, no solo a los adyacentes, es decir, desde cualquier");
	printWord("punto hasta cualquier punto vacante.");
	printWord("Tan pronto como le quiten otra ficha, habra perdido el juego.");
	cout << "\n";
	printWord(
		"Final del juego Un jugador vence la partida cuando el rival solo tiene 2 fichas o cuando no puede realizar ningun");
	printWord("movimiento por estar todas sus fichas bloqueadas.");
	cout
		<< "--------------------------------------------------------------------------------------------------------------------"
		<< endl;
	cout << "\n" << MAIN_COLOR << "Presiona una tecla para continuar..." << RESET_COLOR;
	_getch();
	cleanConsole();
	menu();
}

void initGame()
{
	srand(time(NULL));
	game.board = GameBoard{
		{
			{0, 99, 99, 0, 99, 99, 0},
			{99, 0, 99, 0, 99, 0, 99},
			{99, 99, 0, 0, 0, 99, 99},
			{0, 0, 0, 88, 0, 0, 0}, // 99 because it's a blank value
			{99, 99, 0, 0, 0, 99, 99},
			{99, 0, 99, 0, 99, 0, 99},
			{0, 99, 99, 0, 99, 99, 0}
		},
		{
			GamePlayer{
				"Player1",
				game.test ? 2 : 0,
				9,
				0,
				1
			},
			GamePlayer{
				"Player2",
				game.test ? 3 : 0,
				9,
				0,
				2
			}
		}
	};
	game.ended = false;
	game.winner = GamePlayer{
		"None"
	};
	game.currentPhase = 0;
	if (!game.test)
	{
		for (int i = 0; i < 2; ++i)
		{
			fflush(stdin);
			string ask;
			ask += "Jugador #";
			ask += to_string(i + 1);
			ask += " ingrese su nombre >> ";
			string name = askForPlayerName(ask, "Ingresa un nombre correcto!");
			int color = askForColor("Elije un color entre [1-6] >> ", "Ingrese un valor correcto!");
			game.board.players[i].name = name;
			game.board.players[i].color = color;
		}
	}
	cleanConsole();
	//    putRandomPieces();
	//    PiecePosition *pieces1 = getPiecesPosition(game.board.players[0]);
	//    PiecePosition *pieces2 = getPiecesPosition(game.board.players[1]);
	//    for (int i = 0; i < 9; ++i) {
	//        cout << "Jugador #1" << pieces1[i].to_string() << endl;
	//    }
	//    for (int i = 0; i < 9; ++i) {
	//        cout << "Jugador #2" << pieces2[i].to_string() << endl;
	//    }
	bool firstPlayerStart = rand() > (RAND_MAX / 2);
	GamePlayer* startPlayer;
	if (firstPlayerStart)
	{
		startPlayer = &game.board.players[0];
	}
	else
	{
		startPlayer = &game.board.players[1];
	}
	game.currentTurn = (startPlayer->identifier) - 1;
	drawGame(startPlayer->getColor() + startPlayer->name + " comienza!" + RESET_COLOR);
	startNextPhase();
	putRandomPieces(8);
	while (!game.ended)
	{
		if (checkWinner())
		{
			return;
		}
		GamePlayer* playerTurn;
		playerTurn = &game.board.players[game.currentTurn];
		checkWinner();
		if (game.currentPhase >= 2)
		{
			playerTurn->pieceToMove = askForAMovement(*playerTurn, "mover en el tablero", true);
		}
		PiecePosition piecePosition = askForAMovement(*playerTurn);
		if (isMovementValid(*playerTurn, piecePosition))
		{
			putPiece(piecePosition, *playerTurn);
			game.currentTurn = game.nextTurn();
		}
		else
		{
			cout << "Ingresa una posicion valida!" << endl;
		}
		if (checkCurrentPhase())
		{
			startNextPhase();
		}
	}
	winnerScreen();
}

void cleanConsole()
{
	system("CLS");
}

bool isColorAvailable(int color)
{
	for (auto& player : game.board.players)
	{
		if (color == player.color)
		{
			return false;
		}
	}
	return true;
}

bool isValidName(const string& input)
{
	for (auto& player : game.board.players)
	{
		if (input == player.name)
		{
			return false;
		}
	}
	return true;
}

string askForPlayerName(string question, string wrongAnswer)
{
	bool done = false;
	string finalValue;
	while (!done)
	{
		string value;
		cout << question;
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << wrongAnswer << endl;
		}
		else if (value.empty())
		{
			cout << wrongAnswer << endl;
		}
		else if (value.length() > 8)
		{
			cout << "El maximo de caracteres permitidos es 8." << endl;
		}
		else if (!isValidName(value))
		{
			cout << "El nombre ya esta en uso!" << endl;
		}
		else
		{
			done = true;
			finalValue = value;
		}
	}
	return finalValue;
}

int askForColor(string question, string wrongAnswer)
{
	bool done = false;
	int finalValue;
	while (!done)
	{
		int value;
		cout << question;
		cin >> value;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << wrongAnswer << endl;
		}
		else if (value >= 1 && value <= 6)
		{
			if (!(isColorAvailable(value)))
			{
				cout << "Ese color no esta disponible!" << endl;
			}
			else
			{
				done = true;
				finalValue = value;
			}
		}
		else
		{
			cout << wrongAnswer << endl;
		}
	}
	return finalValue;
}

PiecePosition askForAMovement(GamePlayer& player, const string& ask, const bool& checkSelf)
{
	PiecePosition pos{};
	bool done = false;
	while (!done)
	{
		char letter, row;
		cout << player.getColor() << player.name << " ingrese la posicion a " << ask << " (Ejemplo: A1) >> "
			<< RESET_COLOR;
		cin >> letter >> row;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ingresa una valor correcto!" << endl;
		}
		else
		{
			letter = toupper(letter);
			int posLetter = (letter - 64) - 1;
			int posRow = (row - 48) - 1;
			if ((posLetter >= 0 && posLetter <= 6) && (posRow >= 0 && posRow <= 6))
			{
				pos = PiecePosition{
					letter,
					(posRow + 1)
				};
				if (player.pieceToMove.letter == 'N')
				{
					if (!checkSelf)
					{
						done = true;
					}
					else
					{
						if (game.board.board[posLetter][posRow] == player.identifier)
						{
							done = true;
						}
						else
						{
							cout << "No puedes mover una ficha que no es tuya!!" << endl;
						}
					}
				}
				else
				{
					if (!player.pieceToMove.equals(pos))
					{
						done = true;
					}
					else
					{
						cout << "No puedes ingresar la misma ficha que quieres mover!" << endl;
					}
				}
			}
			else
			{
				cout << "Ingresa una valor correcto!" << endl;
			}
		}
	}
	return pos;
}

string getColorOfDotFromBoard(string input, int locI, int locJ)
{
	int loc = game.board.board[locI][locJ];
	if (loc == 99 || loc == 88)
	{
		return input;
	}
	if (loc == 1)
	{
		return game.board.players[0].getColor() + input + RESET_COLOR;
	}
	else if (loc == 2)
	{
		return game.board.players[1].getColor() + input + RESET_COLOR;
	}
	else
	{
		return input;
	}
}

void putPiece(PiecePosition piecePosition, GamePlayer& player)
{
	int* pos = piecePosition.fetch();
	cout << "Updating to " << player.identifier << " in " << pos[0] << " , " << pos[2] << endl;
	game.board.board[pos[0]][pos[1]] = player.identifier;

	bool add = true;
	if (player.pieceToMove.letter != 'N')
	{
		add = false;
		int* posBefore = player.pieceToMove.fetch();
		cout << "Updating to 0" << " in " << posBefore[0] << " , " << posBefore[2] << endl;
		game.board.board[posBefore[0]][posBefore[1]] = 0; // Clean the move piece
		player.resetPieceMove(); // Reset Move
	}

	if (add)
	{
		player.addPiece();
	}

	// Render
	drawGame();
}

PiecePosition* getPiecesPosition(const GamePlayer& gamePlayer)
{
	PiecePosition* pieces = new PiecePosition[gamePlayer.amountOfPiecesInBoard];
	int index = 0;
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			int number = game.board.board[i][j];
			if (number == 99 || number == 88 || number == 0)
			{
				continue;
			}
			if (number == gamePlayer.identifier)
			{
				int letter = (i + 1) + 64;
				pieces[index] = PiecePosition{
					(char)letter,
					(j + 1)
				};
				index++;
			}
		}
	}
	return pieces;
}

GamePlayer getPlayerByPiece(PiecePosition piecePosition)
{
	int* pos = piecePosition.fetch();
	int onBoard = game.board.board[pos[0]][pos[1]];
	return onBoard == 1 ? game.board.players[0] : onBoard == 2 ? game.board.players[1] : GamePlayer{"NONE"};
}

void drawGame(const string& message)
{
	cleanConsole();
	cout << "     | A |   | B |   | C |      | D |      | E |   | F |   | G |" << endl;
	cout << "\n";
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 0) + "                      " +
		getColorOfDotFromBoard("*@@@*", 3, 0) + "                      " + getColorOfDotFromBoard("*@@@*", 6, 0) +
		"  ---" << endl;
	cout << " 1   " + getColorOfDotFromBoard("*@@@*", 0, 0) + "----------------------" +
		getColorOfDotFromBoard("*@@@*", 3, 0) + "----------------------" +
		getColorOfDotFromBoard("*@@@*", 6, 0) + "   1 " << endl;
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 0) + "                      " +
		getColorOfDotFromBoard("*@@@*", 3, 0) + "                      " + getColorOfDotFromBoard("*@@@*", 6, 0) +
		"  ---" << endl;
	// End fila 1
	cout << "       |                          |                          |    " << endl;
	cout << "       |                          |                          |    " << endl;
	// Start fila 2 -> 1,1 1,3 1,5
	cout << "---    |     " + getColorOfDotFromBoard("*@@@*", 1, 1) + "              " +
		getColorOfDotFromBoard("*@@@*", 3, 1) + "              " + getColorOfDotFromBoard("*@@@*", 5, 1) +
		"     |    ---" << endl;
	cout << " 2     |     " + getColorOfDotFromBoard("*@@@*", 1, 1) + "--------------" +
		getColorOfDotFromBoard("*@@@*", 3, 1) + "--------------" + getColorOfDotFromBoard("*@@@*", 5, 1) +
		"     |     2 " << endl;
	cout << "---    |     " + getColorOfDotFromBoard("*@@@*", 1, 1) + "              " +
		getColorOfDotFromBoard("*@@@*", 3, 1) + "              " + getColorOfDotFromBoard("*@@@*", 5, 1) +
		"     |    ---" << endl;
	// End fila 2
	cout << "       |       |                  |                  |       |    " << endl;
	cout << "       |       |                  |                  |       |    " << endl;
	// Start fila 3 -> 2,2 2,3 2,4
	cout << "---    |       |     " + getColorOfDotFromBoard("*@@@*", 2, 2) + "      " +
		getColorOfDotFromBoard("*@@@*", 3, 2) + "      " + getColorOfDotFromBoard("*@@@*", 4, 2) +
		"     |       |    ---" << endl;
	cout << " 3     |       |     " + getColorOfDotFromBoard("*@@@*", 2, 2) + "------" +
		getColorOfDotFromBoard("*@@@*", 3, 2) + "------" + getColorOfDotFromBoard("*@@@*", 4, 2) +
		"     |       |     3 " << endl;
	cout << "---    |       |     " + getColorOfDotFromBoard("*@@@*", 2, 2) + "      " +
		getColorOfDotFromBoard("*@@@*", 3, 2) + "      " + getColorOfDotFromBoard("*@@@*", 4, 2) +
		"     |       |    ---" << endl;
	// End fila 3
	cout << "       |       |       |                     |       |       |    " << endl;
	cout << "       |       |       |                     |       |       |    " << endl;
	cout << "       |       |       |                     |       |       |    " << endl;
	// Start fila 4 -> 3,0 3,1 3,2 -> 3,4 3,5 3,6
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 3) + "   " + getColorOfDotFromBoard("*@@@*", 1, 3) +
		"   " + getColorOfDotFromBoard("*@@@*", 2, 3) + "                 " +
		getColorOfDotFromBoard("*@@@*", 4, 3) + "   " + getColorOfDotFromBoard("*@@@*", 5, 3) + "   " +
		getColorOfDotFromBoard("*@@@*", 6, 3) + "  ---" << endl;
	cout << " 4   " + getColorOfDotFromBoard("*@@@*", 0, 3) + "---" + getColorOfDotFromBoard("*@@@*", 1, 3) +
		"---" + getColorOfDotFromBoard("*@@@*", 2, 3) + "                 " +
		getColorOfDotFromBoard("*@@@*", 4, 3) + "---" + getColorOfDotFromBoard("*@@@*", 5, 3) + "---" +
		getColorOfDotFromBoard("*@@@*", 6, 3) + "   4 " << endl;
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 3) + "   " + getColorOfDotFromBoard("*@@@*", 1, 3) +
		"   " + getColorOfDotFromBoard("*@@@*", 2, 3) + "                 " +
		getColorOfDotFromBoard("*@@@*", 4, 3) + "   " + getColorOfDotFromBoard("*@@@*", 5, 3) + "   " +
		getColorOfDotFromBoard("*@@@*", 6, 3) + "  ---" << endl;
	// End fila 4
	cout << "       |       |       |                     |       |       |    " << endl;
	cout << "       |       |       |                     |       |       |    " << endl;
	cout << "       |       |       |                     |       |       |    " << endl;
	// Start fila 5 -> 4,2 - 4,3 - 4,4
	cout << "---    |       |     " + getColorOfDotFromBoard("*@@@*", 2, 4) + "      " +
		getColorOfDotFromBoard("*@@@*", 3, 4) + "      " + getColorOfDotFromBoard("*@@@*", 4, 4) +
		"     |       |    ---" << endl;
	cout << " 5     |       |     " + getColorOfDotFromBoard("*@@@*", 2, 4) + "------" +
		getColorOfDotFromBoard("*@@@*", 3, 4) + "------" + getColorOfDotFromBoard("*@@@*", 4, 4) +
		"     |       |     5 " << endl;
	cout << "---    |       |     " + getColorOfDotFromBoard("*@@@*", 2, 4) + "      " +
		getColorOfDotFromBoard("*@@@*", 3, 4) + "      " + getColorOfDotFromBoard("*@@@*", 4, 4) +
		"     |       |    ---" << endl;
	// End fila 5 cv
	cout << "       |       |                  |                  |       |    " << endl;
	cout << "       |       |                  |                  |       |    " << endl;
	// Start fila 6 -> 5,1 5,3 5,5
	cout << "---    |     " + getColorOfDotFromBoard("*@@@*", 1, 5) + "              " +
		getColorOfDotFromBoard("*@@@*", 3, 5) + "              " + getColorOfDotFromBoard("*@@@*", 5, 5) +
		"     |    ---" << endl;
	cout << " 6     |     " + getColorOfDotFromBoard("*@@@*", 1, 5) + "--------------" +
		getColorOfDotFromBoard("*@@@*", 3, 5) + "--------------" + getColorOfDotFromBoard("*@@@*", 5, 5) +
		"     |     6 " << endl;
	cout << "---    |     " + getColorOfDotFromBoard("*@@@*", 1, 5) + "              " +
		getColorOfDotFromBoard("*@@@*", 3, 5) + "              " + getColorOfDotFromBoard("*@@@*", 5, 5) +
		"     |    ---" << endl;
	// End fila 6
	cout << "       |                          |                          |    " << endl;
	cout << "       |                          |                          |    " << endl;
	// Start fila 7 -> 6,0 6,3 6,6
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 6) + "                      " +
		getColorOfDotFromBoard("*@@@*", 3, 6) + "                      " +
		getColorOfDotFromBoard("*@@@*", 6, 6) + "  ---" << endl;
	cout << " 7   " + getColorOfDotFromBoard("*@@@*", 0, 6) + "----------------------" +
		getColorOfDotFromBoard("*@@@*", 3, 6) + "----------------------" +
		getColorOfDotFromBoard("*@@@*", 6, 6) + "   7 " << endl;
	cout << "---  " + getColorOfDotFromBoard("*@@@*", 0, 6) + "                      " +
		getColorOfDotFromBoard("*@@@*", 3, 6) + "                      " +
		getColorOfDotFromBoard("*@@@*", 6, 6) + "  ---" << endl;
	// End fila 7
	cout << "\n     | A |   | B |   | C |      | D |      | E |   | F |   | G |\n" << endl;
	for (int i = 0; i < 2; ++i)
	{
		cout << game.board.players[i].getColor() << game.board.players[i].name << " -> Informacion!" << RESET_COLOR;
		if (i == 0)
		{
			cout << "         |         ";
		}
		else
		{
			cout << endl;
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			GamePlayer player = game.board.players[j];
			cout << player.getColor();
			switch (i)
			{
			case 0:
				{
					cout << "Piezas disponibles: " << player.amountOfPieces;
					cout << RESET_COLOR;
					if (j == 0)
					{
						cout << "           |         ";
					}
					else
					{
						cout << endl;
					}
					break;
				}
			case 1:
				{
					cout << "Piezas en el tablero: " << player.amountOfPiecesInBoard;
					cout << RESET_COLOR;
					if (j == 0)
					{
						cout << "         |         ";
					}
					else
					{
						cout << endl;
					}
					break;
				}
			}
		}
	}
	if (!message.empty() && message != "X")
	{
		cout << MAIN_COLOR << "\nConsola:" << endl;
		cout << MAIN_COLOR << message << RESET_COLOR << endl;
	}
}

bool isMovementValid(GamePlayer& player, PiecePosition movement)
{
	int* moves = movement.fetch();
	int pieceInBoard = game.board.board[moves[0]][moves[1]];
	if (pieceInBoard == 99 || pieceInBoard == 88)
	{
		// Return because this value is an invalid movement on board.
		return false;
	}
	switch (game.currentPhase)
	{
	case 1:
		{
			return pieceInBoard == 0; // Free space
		}
	case 2:
		{
			if (pieceInBoard == 1 || pieceInBoard == 2)
			{
				return false; // No puede mover la pieza a un lugar donde ya esta una pieza
			}
			break;
		}
	case 3:
		{
			return pieceInBoard == 0;
			break;
		}
	}
	return true;
}

bool isMovementMakeAWindmill(GamePlayer player, PiecePosition movement)
{
	return false;
}

bool takePlayerPiece(GamePlayer taker, PiecePosition pieceToTake)
{
	GamePlayer ownerPiece = getPlayerByPiece(pieceToTake);
	if (ownerPiece.name == taker.name)
	{
		return false; // Return false because its same player and cannot take this own piece.
	}
	ownerPiece.amountOfPiecesInBoard = ownerPiece.amountOfPiecesInBoard - 1;
	int* pos = pieceToTake.fetch();
	game.board.board[pos[0]][pos[1]] = 0; // Clean board space
	return true;
}

void startNextPhase()
{
	if (game.currentPhase >= 3)
	{
		checkWinner(); // Check Winner
		// Max is 3 pahse
		return;
	}
	game.currentPhase++;
	switch (game.currentPhase)
	{
	case 1:
		printWord(MAIN_COLOR + "La primera fase ha comenzado, colocen sus fichas!" + RESET_COLOR);
		break;
	case 2:
		printWord(MAIN_COLOR + "La segunda fase ha comenzado, solo puedes colocar ficha si esta adyacente" +
			RESET_COLOR);
		break;
	case 3:
		printWord(MAIN_COLOR + "La tercera fase ha comenzado, el primero que tenga 2 fichas pierde!" + RESET_COLOR);
		break;
	}
}

bool checkCurrentPhase()
{
	switch (game.currentPhase)
	{
	case 1:
		return game.board.players[0].amountOfPiecesInBoard == 9 && game.board.players[1].amountOfPiecesInBoard == 9;
	case 2:
		break;
	case 3:
		break;
	}
	return false;
}

bool hasAnAdjacentPiece(PiecePosition position, GamePlayer& player)
{
	return true;
}

bool canMove(const GamePlayer& player)
{
	return true;
}

bool checkWinner()
{
	bool done = false;
	if (game.ended)
	{
		return true;
	}

	// Check if are any player on the board with 2 pieces.
	for (const GamePlayer& player : game.board.players)
	{
		if (done)
		{
			// Avoid check loop
			continue;
		}
		if (player.amountOfPiecesInBoard <= 2 || !canMove(player))
		{
			done = true;
			game.ended = true;
			int playerWinner = player.identifier == 1 ? 0 : 1;
			game.winner = game.board.players[playerWinner];
			return true;
		}
	}
	return false;
}

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "GOL.h"
using namespace std;
#include"Tile.h"
class Board
{
private:
Player lions[2];
static const int _BOARD_SIZE = 52;
Tile _tiles[2][_BOARD_SIZE];
static const int _MAX_PLAYERS = 2;
int _player_count;
int _player_position[_MAX_PLAYERS];
void displayTile(int player_index, int pos);
void displayTileWIP(int player_index, int pos);
void initializeTiles(int player_index);
bool isPlayerOnTile(int player_index, int pos); //checks to see if the specified player is on the specified position
bool isPlayerOnTileWIP(int player_index, int pos); 
public:
Board();
Board(int player_count);
void displayTrack(int player_index);
void initializeBoard();
void initalizeBoardWIP(bool);
void intializeBoardIfPlayersChooseSameBoard();
void displayBoard();
void displayTrackIfPlayersChoseSameBoard(int);
void TileEffects(int,int,int,int);
void movePlayerBackwards(int);
void displayBoardIfBothplayersChooseTheSamePosition();
//need a player function called lions, also need to print the menu

bool movePlayer(int player_index);//moves the player 1 space,then checks to see if it is at the end
int getPlayerPosition(int player_index) const; //gets what tile the specified player is on the board
// do an if statement to check if both player positions match, if they do, they play a minigame

bool printIntro();
string getPlayerColor(int player_index, int pos);
void printMenu(bool);
void endGame();
};
#endif
#pragma once
#ifndef Game_h
#define Game_h

#include"Libraries.h"
#include"Player.h"
using namespace std;

// Header including implementation of the Game class, the main class which operate the whole program

enum Status// It consists of possible statuts of the game
{
	Win,
	Killed_enemy,
	Killed_obstacle,
	Killed_diamond,
	Underway
};

class Game
{
	string map_name;// name if map
	int column;// number of columns
	int row;// number of rows
	Player* p;// pointer to the player
	bool status;// status of the game
	vector<Object*> data_tab;// Vector of objects
	

public:
	
	Status stat;
	Game(string m);
	void loading_map(string file_location);
	void showing_map();
	void moving(char key);
	void gravitation();
	void enemy_moving();
	void killing_player();
	bool win_game();
	~Game();
	
};

#endif

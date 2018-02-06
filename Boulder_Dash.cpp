#include"Libraries.h"
#include"Game.h"
#include<windows.h>

using namespace std;

int Boulder_Dash()
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, 2);//Welcoming sentences
	cout << "                               BOULDER DASH GAME                             " << endl;
	SetConsoleTextAttribute(color, 11);
	cout << endl;
	cout << "                   In this game You will personate to the miner.             " << endl;
	cout << "                  You will have to collect diamonds in old mines.            " << endl;
	SetConsoleTextAttribute(color, 12);
	cout << endl;
	cout << "                                BUT BE AWARE!!!                              " << endl;
	SetConsoleTextAttribute(color, 11);
	cout << endl;
	cout << "                      You can meet some troubles in your way.                " << endl;
	cout << "    Try to ommit this problems and escape from the mine with treasure!!!     " << endl << endl << endl;
	SetConsoleTextAttribute(color, 15);

	cout << "       To read help please enter      [H] and accept it using ENTER.         " << endl;
	cout << "       To start the game please enter [S] and accept it using ENTER.         " << endl;
	cout << "       To exit the game please enter  [E] and accept it using ENTER.         " << endl;

	while (1)
	{
		Game Level_1("First Map");//Creating Level
		char key;
		cin >> key;
		switch (key)//Choosing option
		{
		case 'H'://Showing help
			system("cls");
			cout << "                       Elements presented in game                            " << endl << endl;
			SetConsoleTextAttribute(color, 9);
			cout << "     P - Player. You can steer Player using arrows.                          " << endl << endl;
			SetConsoleTextAttribute(color, 4);
			cout << "     # - Wall. It's boarder of mine. You can do nothing with that.           " << endl << endl;
			SetConsoleTextAttribute(color, 14);
			cout << "     - - Ground. You can erase it when you step on it.                       " << endl << endl;
			SetConsoleTextAttribute(color, 11);
			cout << "     * - Diamond. You can collect it when you step on it.                    " << endl;
			cout << "                   but when diamond falls on your head the game is over.     " << endl << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "     o - Stone. You can move it into free space,                             " << endl;
			cout << "                   but when stone falls on your head the game is over.       " << endl << endl;
			SetConsoleTextAttribute(color, 5);
			cout << "     E - Enemy. Better avoid this creature,                                  " << endl;
			cout << "                    but what happends if stone or diamond fall on enemy?     " << endl << endl;
			SetConsoleTextAttribute(color, 10);
			cout << "     D - Door. Only one way to escape mine. Of course, if you have diamonds. " << endl << endl;
			SetConsoleTextAttribute(color, 13);
			cout << "     K - Key. You can open doors using this item.                            " << endl << endl;
			SetConsoleTextAttribute(color, 15);
			cout << "          To start the game please enter [S] and accept it using ENTER.      " << endl;
			break;

		case 'S'://Starting the game

			system("cls");
			cout << "                                     LEVEL 1                                             " << endl << endl;
			cout << "                            Choose difficulty level:                                     " << endl << endl;
			cout << "                                      LOW [L]                                            " << endl;
			cout << "                                    MEDIUM [M]                                           " << endl;
			cout << "                                     HIGH [H]                                            " << endl;
			Level_1.loading_map("Map1.txt");
			int level;
			char l;
			l = getch();
			switch (l)//Choosing level
			{
			case 'L': level = 150; break;
			case 'M': level = 50; break;
			case 'H': level = 0; break;
			}

			while (1)//Game loop
			{
				char k;
				while (!kbhit())//If buffor is empty, all methods without moving player
				{
					if (Level_1.stat != Underway || k == 'E')break;
					COORD coodr = { 0,0 };//Clering screen
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coodr);
					Level_1.showing_map();
					if (Level_1.win_game() == true)break;
					Level_1.gravitation();
					Level_1.enemy_moving();
					Level_1.killing_player();
					Sleep(level);

				}
				if (Level_1.stat != Underway || k == 'E')break;
				while (kbhit())//Only moving of the player method
				{
					while (k = getch())
					{
						Level_1.moving(k);
						break;
					}
				}
				if (Level_1.stat != Underway || k == 'E')break;
			}
			system("cls");
			switch (Level_1.stat)//Showing status of the game
			{
			case Killed_diamond: cout << endl << "                GAME OVER. Diamond killed You!!!                  " << endl << endl; break;
			case Killed_enemy: cout << endl << "                 GAME OVER. Enemy killed You!!!                   " << endl << endl; break;
			case Killed_obstacle: cout << endl << "               GAME OVER. Obstacle killed You!!!                  " << endl << endl; break;
			case Win: cout << endl << "                  YOU WIN!!! CONGRATULATION                       " << endl << endl; break;
			}
			cout << "          To read help please enter        [H] and accept it using ENTER.      " << endl;
			cout << "          To restart the game please enter [S] and accept it using ENTER.      " << endl;
			cout << "          To exit the game please enter    [E] and accept it using ENTER.      " << endl;
			break;
		case'E': return 0;  break;//Exiting the game
		}
	}
}


#include"Game.h"
#include"Diamond.h"
#include"Door.h"
#include"Empty space.h"
#include"Game.h"
#include"Ground.h"
#include"Obstacle.h"
#include"Player.h"
#include"Wall.h"
#include"Enemy.h"
#include"Key.h"
#include<windows.h>

using namespace std;

Game::Game(string m)// Constructo of the Game class
{
	column=0;
	row=0;
	map_name = m;
	status = false;
	stat = Underway;

}
void Game::loading_map(string file_location)// Loading map from the file
{

	fstream map;
	map.open(file_location, ios::in);

	if (map.good() == false)
		cout << "Couldn't open map file!" << endl;

	getline(map, map_name);// Getting name, number of rows, columns and diamons
	map >> column;
	map >> row;
	int nd;// number of diamonds
	map >> nd;

	char sign;
	map.get(sign);
	for (int i = 0; i < row; i++)// Creating a vector of objects and adding new Objects to the vector with proper coordinates
	{
		for (int j = 0; j < column; j++)
		{
			map.get(sign);
			switch (sign)
			{
			case '#': data_tab.push_back(new Wall(i, j)); break;
			case 'o': data_tab.push_back(new Obstacle(i, j)); break;
			case 'P': p = new Player(i, j, nd); data_tab.push_back(p); break;
			case '*': data_tab.push_back(new Diamond(i, j)); break;
			case 'D': data_tab.push_back(new Door(i, j)); break;
			case '-': data_tab.push_back(new Ground(i, j)); break;
			case ' ': data_tab.push_back(new Empty_space(i, j)); break;
			case 'E': data_tab.push_back(new Enemy(i, j)); break;
			case 'K': data_tab.push_back(new Key(i, j)); break;
			}
		}
	}
	map.close();
}
void Game::showing_map()// Drawing map on the screen
{
	int i = 0;
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it)// Drawing every element in proper column and row
	{
		if (i == column - 1)
		{
			cout << endl;
			(*it)->draw();
			i = 1;
		}
		else
		{
			(*it)->draw();
			i++;
		}
	}
	cout << endl;
	HANDLE colour;
	colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 15);
	p->diamonds_number();//Showing number of diamonds and keys
	p->keys_number();
}
void Game::moving(char k)// Methods that enable moving player in pointed direction
{
	double ox = p->x;// Old coordinates
	double oy = p->y;
	p->move(k);//Changing coordinates of player
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it)
	{
		if ((*it)->x == p->x && (*it)->y == p->y)//Searching for element which have the same coordintes 
		{
			switch ((*it)->type)
			{
			case Object_Type::wall: //If it is a wall, returning to the old coordinates
				p->x = ox; p->y = oy; break;
			case Object_Type::ground://If it is a ground, deleting it, and creating empty space in place of the player	
				delete (*it);
				(*it) = new Empty_space(ox, oy);
				iter_swap(it, find(data_tab.begin(), data_tab.end(), p));//Changing itterator with pointer to the player
				break;
			case Object_Type::door: //If it is a door, checking if player has key or proper number of diamonds
				if (p->diamonds_number()<=0||p->keys_number()>0)
				{
					(*it)->open();// opening doors
					delete (*it);// deleting it, and creating empty space in place of the player
					(*it) = new Empty_space(ox, oy);
					iter_swap(it, find(data_tab.begin(), data_tab.end(), p));//Changing itterator with pointer to the player
					if (p->diamonds_number() <= 0)stat = Win;//if this is the end door, changing status of the game
					p->keys_reduce();// reducing number of keys
					system("cls");
					break;
				}
				else p->x = ox; p->y = oy; break;
			case Object_Type::diamond:// If it is a diamond, collect it and and change into empty space
				p->collecting(diamond);
				delete (*it);
				(*it) = new Empty_space(ox, oy);
				iter_swap(it, find(data_tab.begin(), data_tab.end(), p));
				break;
			case Object_Type::obstacle://If it is an obstacle
				
				if (k == 80 || k == 72)//Disable moving up or down
				{
					p->x = ox; p->y = oy; break;
				}
				else
				{
					double oox = (*it)->x;// old coordinates
					double ooy = (*it)->y;
					double noy;
					
					if(k == 77) noy = ooy + 1;// changing coordinates accoriding to the direction
					else noy = ooy - 1;
					bool is_empty = false;// status od the next place

					for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
					{
						if (((*itt)->x == oox && ((*itt)->y == noy)) && ((*itt)->type == Object_Type::empty_space))//Checking if next place is empty
						{
							delete (*itt);
							(*itt) = new Obstacle(oox, noy);
							is_empty = true;
						}
					}
					if (is_empty)//If next place is empty, moving obstacle
					{
						delete (*it);
						(*it) = new Empty_space(oox, ooy);
						(*it)->x = ox;
						(*it)->y = oy;
						iter_swap(it, find(data_tab.begin(), data_tab.end(), p));
					}
					else//If next place isn't empty
					{
						p->x = ox;
						p->y = oy;
					}
				}
				break;
			
			case Object_Type::empty_space: // If it is an empty space, change the place with playe
				(*it)->x = ox;
				(*it)->y = oy;
				iter_swap(it, find(data_tab.begin(), data_tab.end(), p)); break;
			case Object_Type::enemy:// If it is an enemy, change status of the game
				status = true;
				break;
			case Object_Type::key:// If it is a key, collect it and and change into empty space
				p->collecting(key);
				delete (*it);
				(*it) = new Empty_space(ox, oy);
				iter_swap(it, find(data_tab.begin(), data_tab.end(), p));
				break;
			}

		}
	}
}
void Game::gravitation()// Methods that add gravitation feature to the diamonds and obstacles
{
	double ox;//helping coordiantes
	double oy;
	double nx;
	double px;
	bool is_empty = false;// status of the next space
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it)
	{

		switch ((*it)->type)
		{

		case Object_Type::obstacle:
			if ((*it)->is_moved == false)//Checking if object move once
			{
				ox = (*it)->x;
				oy = (*it)->y;
				nx = ox + 1;

				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if ((((*itt)->x == nx) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::empty_space))//If place under obstacle is empty, changing place of obstacle
					{
						delete (*itt);
						(*itt) = new Obstacle(nx, oy);
						(*itt)->is_moved = true;
						is_empty = true;
						px = nx + 1;
					}
					if ((((*itt)->x == px) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::player) && (is_empty == true))//If place under obstacle is player, killing player
					{
						stat = Killed_obstacle;
					}
					if ((((*itt)->x == px) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::enemy) && (is_empty == true))//If place under obstacle is enemy, killing enemy and creating diamond
					{
						delete (*itt);
						(*itt) = new Diamond(px, oy);
					}
				}
				if (is_empty)//changing place of obstacle
				{
					delete (*it);
					(*it) = new Empty_space(ox, oy);
					is_empty = false;
				}
				break;
			}
			else break;

		case Object_Type::diamond://The same method like in obstacle 
			if ((*it)->is_moved == false)
			{
				ox = (*it)->x;
				oy = (*it)->y;
				nx = ox + 1;

				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if ((((*itt)->x == nx) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::empty_space))
					{
						delete (*itt);
						(*itt) = new Diamond(nx, oy);
						(*itt)->is_moved = true;
						is_empty = true;
						px = nx + 1;
					}
					if ((((*itt)->x == px) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::player) && (is_empty == true))
					{
						stat = Killed_diamond;
					}
					if ((((*itt)->x == px) && ((*itt)->y == oy)) && ((*itt)->type == Object_Type::enemy) && (is_empty == true))
					{
						delete (*itt);
						(*itt) = new Diamond(px, oy);
					}
				}
				if (is_empty)
				{
					delete (*it);
					(*it) = new Empty_space(ox, oy);
					is_empty = false;
				}
				break;
			}
			else break;
		}
	}
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it) (*it)->is_moved = false;// changing status of objects, that enable dynamic of the game
}
void Game::enemy_moving()//Methods that enable moving of the enemy
{
	double ox, oy, nx, ny;//Helping coordinates
	bool is_moving=false;//Status of moving
	int d=1;
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it)
	{
		if ((*it)->type == Object_Type::enemy && ((*it)->is_moved == false))
		{
			ox = (*it)->x;
			oy = (*it)->y;
			if ((*it)->enemy_go_down == true)//If enemy should go down
			{
				(*it)->move(Down);//changing coordinates in proper direction
				nx = (*it)->x;
				ny = (*it)->y;
				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if (((*itt)->x == nx) && ((*itt)->y == ny) && (((*itt)->type == Object_Type::empty_space)))//Changing place if next place is empty
					{
						delete (*itt);
						(*itt) = new Enemy(nx, ny);
						(*itt)->is_moved = true;
						is_moving = true;
					}
				}
				if (!is_moving)//If next place isn't empty, change direction of enemy moving
				{
					(*it)->enemy_go_right = true;
					(*it)->enemy_go_down = false;
					(*it)->move(Up);
				}
			}
			if ((*it)->enemy_go_right == true)//If enemy should go right, the same comments in previous steps
			{
				(*it)->move(Right);
				nx = (*it)->x;
				ny = (*it)->y;
				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if (((*itt)->x == nx) && ((*itt)->y == ny) && (((*itt)->type == Object_Type::empty_space)))
					{
						delete (*itt);
						(*itt) = new Enemy(nx, ny);
						(*itt)->is_moved = true;
						is_moving = true;
						(*itt)->enemy_go_down = false;
						(*itt)->enemy_go_right = true;
					}
				}
				if (!is_moving)
				{
					(*it)->enemy_go_right = false;
					(*it)->enemy_go_up = true;
					(*it)->move(Left);
				}
			}
			if ((*it)->enemy_go_up == true)//If enemy should go up, the same comments in previous steps
			{
				(*it)->move(Up);
				nx = (*it)->x;
				ny = (*it)->y;
				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if (((*itt)->x == nx) && ((*itt)->y == ny) && (((*itt)->type == Object_Type::empty_space)))
					{
						delete (*itt);
						(*itt) = new Enemy(nx, ny);
						(*itt)->is_moved = true;
						is_moving = true;
						(*itt)->enemy_go_down = false;
						(*itt)->enemy_go_up = true;
					}
				}
				if (!is_moving)
				{
					(*it)->enemy_go_left = true;
					(*it)->enemy_go_up = false;
					(*it)->move(Down);
				}
			}
			if ((*it)->enemy_go_left == true)//If enemy should go left, the same comments in previous steps
			{
				(*it)->move(Left);
				nx = (*it)->x;
				ny = (*it)->y;
				for (vector<Object*>::iterator itt = data_tab.begin(); itt != data_tab.end(); ++itt)
				{
					if (((*itt)->x == nx) && ((*itt)->y == ny) && (((*itt)->type == Object_Type::empty_space)))
					{
						delete (*itt);
						(*itt) = new Enemy(nx, ny);
						(*itt)->is_moved = true;
						is_moving = true;
						(*itt)->enemy_go_down = false;
						(*itt)->enemy_go_left = true;
					}
				}
				if (!is_moving)
				{
					(*it)->enemy_go_left = false;
					(*it)->enemy_go_down = true;
					(*it)->move(Right);
				}
			}
			if (is_moving)//changing place
			{
				delete (*it);
				(*it) = new Empty_space(ox, oy);
				is_moving = false;
			}
		}
	}
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it) (*it)->is_moved = false;// changing status of objects, that enable dynamic of the game
}
void Game::killing_player()//Checking if in the space of enemy is player
{
	double px = p->x;//old coordinates
	double py = p->y;
	
	for (vector<Object*>::iterator it = data_tab.begin(); it != data_tab.end(); ++it)
	{
		if ((*it)->x == (px + 1) && (*it)->y == py && (*it)->type == Object_Type::enemy)//If player is in the space of the enemy, changing status
		{
			stat = Killed_enemy;
		}
		if ((*it)->x == (px - 1) && (*it)->y == py && (*it)->type == Object_Type::enemy)
		{
			stat = Killed_enemy;
		}
		if ((*it)->x == px && (*it)->y == (py+1) && (*it)->type == Object_Type::enemy)
		{
			stat = Killed_enemy;
		}
		if ((*it)->x == px && (*it)->y == (py-1) && (*it)->type == Object_Type::enemy)
		{
			stat = Killed_enemy;
		}
	}

}
bool Game::win_game()//Returning status of the game
{
	return status;
}
Game::~Game()//Clearing
{
	data_tab.clear();
	if (data_tab.empty());
	else { cout << "Error in clearing vector!!!" << endl; }
}
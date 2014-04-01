#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "globals.h"

using namespace std; 

struct position {
	int x;
	int y;
};

class Player {
	public:
	bool is_armed;
	int score;
	position p;
	Player();
};

Player::Player(){
	is_armed = false;
	score = 0;
	p.x = 0;
	p.y = 0;
}

class Game {
	public: 
		int** board;
		int size;
		bool is_live;
		Player player;
		Game(int n);
		~Game();
		void PrintBoard();
		void InitializeBoard();
		void Display();
		void OutputInfo();
		string getMove();
};

Game::Game(int n){
	size = n;
	board = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		board[i] = new int[size];
	}
	is_live = true;
	player = Player();
	Game::InitializeBoard();
}
Game::~Game(){
	for (int i = 0; i < size; ++i)
	{
		delete[] board[i];
	}
	delete[] board;
}

void Game::InitializeBoard(){
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = UNEXPLORED_ROOM;
		}
	}

	int num_weapons = (int)(size*size*0.15);
	int num_enemies = (int)(size*size*0.15);
	int num_pit_traps = (int)(size*size*0.05);
	int num_golds = (int)(size*size*0.15);
	cout << "Weapons: " << num_weapons << " Enemies: " << num_enemies << " Pit Traps: " << num_pit_traps << " Gold: " << num_golds << endl;

	//insert all weapons:
	int count = 0;
	while (count < num_weapons){
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(board[i][j] = UNEXPLORED_ROOM){
					double r = ((double) rand() / (RAND_MAX));
					if(r <= 0.15){
						board[i][j] = WEAPON*UNEXPLORED_ROOM;
						count++;
					}

				}
				if(count == num_weapons)
					break;
			}
			if(count == num_weapons)
				break;
		}
	}
	//insert enemies:
	count = 0;
	while (count < num_enemies){
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(board[i][j] = UNEXPLORED_ROOM){
					double r = ((double) rand() / (RAND_MAX));
					if(r <= 0.15){
						board[i][j] = WUMPUS*UNEXPLORED_ROOM;
						count++;
					}

				}
				if(count == num_enemies)
					break;
			}
			if(count == num_enemies)
				break;
		}
	}

	//insert gold:
	count = 0;
	while (count < num_golds){
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(board[i][j] = UNEXPLORED_ROOM){
					double r = ((double) rand() / (RAND_MAX));
					if(r <= 0.15){
						board[i][j] = GOLD*UNEXPLORED_ROOM;
						count++;
					}

				}
				if(count == num_golds)
					break;
			}
			if(count == num_golds)
				break;
		}
	}

	//insert pit_traps:
	count = 0;
	while (count < num_pit_traps){
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(board[i][j] = UNEXPLORED_ROOM){
					double r = ((double) rand() / (RAND_MAX));
					if(r <= 0.05){
						board[i][j] = TRAP*UNEXPLORED_ROOM;
						count++;
					}
				}
				if(count == num_pit_traps)
					break;
			}
			if(count == num_pit_traps)
				break;
		}
	}

	//insert starting point
	count = 0;
	while (count < 1){
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(board[i][j] = UNEXPLORED_ROOM){
					double r = ((double) rand() / (RAND_MAX));
					if(r <= (1.0/(size*size))){
						board[i][j] = ENTRANCE;
						player.p.x = j;
						player.p.y = i;
						count++;
						return;
					}

				}
			}
		}
	}

}

void Game::PrintBoard(){
	for (int i = 0; i < size+2; ++i)
	{
		for (int j = 0; j < size+2; ++j)
		{
			if(i==0 || j ==0 || i==size+1 || j==size+1){
				cout << "#";
			}
			else if (i-1==player.p.y && j-1==player.p.x){
				cout << "@";
			}
			else
			{
				int val = board[i-1][j-1];
				if(val%UNEXPLORED_ROOM == 0){
					cout << "?";
				}
				else {
					switch (val){
						case EXPLORED_ROOM:
							cout << ".";
						break;
						case ENTRANCE:
							cout << "^";
						break;
						case WEAPON:
							cout << "W";
						break;
						case GOLD:
							cout << "$";
						break;
						default:
							cout << "?";
						break;
					}
				}
			}
		}
		cout << endl;
	}
}

void Game::Display(){
	system("clear");
	bool wumpus_near = false;
	bool trap_near = false;
	int px = player.p.x;
	int py = player.p.y;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int x = px + j - 1;
			int y = py + i - 1;
			if(x == px && y == py){
				cout << "@";
			}
			else if(x<0 || y < 0 || x > (size-1) || y > (size-1)){
				cout << "#";
			} 
			else{
				int val = board[y][x];
				if(val%UNEXPLORED_ROOM == 0){
					cout << "?";
					if(val%WUMPUS == 0)
						wumpus_near = true;
					if(val%TRAP == 0)
						trap_near = true;
				}
				else {
					switch (val){
						case EXPLORED_ROOM:
							cout << ".";
						break;
						case ENTRANCE:
							cout << "^";
						break;
						case WEAPON:
							cout << "W";
						break;
						case GOLD:
							cout << "$";
						break;
						case PLAYER:
							cout << "@";
						break;
						default:
						break;
					}
				}
			}
		}
		cout << endl;
	}
	if (wumpus_near)
		cout << "You smell a foul stench in the air...\n";
	if (trap_near)
		cout << "Howling winds fill the room...\n";
	Game::OutputInfo();
}

void Game::OutputInfo(){
	int val = board[player.p.y][player.p.x];
	if(val % UNEXPLORED_ROOM == 0){
		if(val == UNEXPLORED_ROOM){
			player.score+=1;
			board[player.p.y][player.p.x] = EXPLORED_ROOM;
		}
		else {
			board[player.p.y][player.p.x] /= UNEXPLORED_ROOM;
		}
	}

	switch (val){
		case WEAPON:
			cout << "Cast before you in a rock a sword awaits to be looted...\n";
		break;
		case WUMPUS:
			cout << "Overwhelmed in the stench of a Wumpus, which stands before you ready to eat you...\n";
			if(player.is_armed){
				cout << "You raise your sword and slay the Wumpus!\n";
				player.score +=10;
			}
			else{
				cout << "The Wumpus eats you...\n";
				is_live = false;
			}
		break;
		case TRAP:
			cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahhhhhhhhhh noooooooooooooooooo Splat! You died.\n";
			is_live = false;
		break;
		case GOLD:
			cout << "Before you lies the gold of adventure seekers who have recently fed a Wumpus...\n";
		break;
		case ENTRANCE:
			cout << "You see the cave entrance here. You wish to run away???\n";
		break;
		case EXPLORED_ROOM:
			cout << "Nothing to see here...\n";
		break;
	}
	if(is_live){
		cout << player.score << " points earned. ";
		if(player.is_armed)
			cout << "You are armed and dangerous.\n";
		else
			cout << "You are weaponless.\n";
	}
}

void PrintHelp(){
	cout << "Help:\n";
	cout << "? -- help to show this list of moves a player can make\n";
	cout << " N -- move north 1 space - cannot move north if the cave ends (outside of grid)\n";
	cout << " S -- move south 1 space - cannot move south if the cave ends (outside of grid)\n";
	cout << " E -- move east 1 space - cannot move east if the cave ends (outside of grid)\n";
	cout << " W -- moves west 1 space - cannot move west if the cave ends (outside of grid)\n";
	cout << " L -- loot either gold or weapon in the room\n";
	cout << " R -- run out of the cave entrance and head to the local inn to share your tale\n";
	cout << " X -- this is a hard exit out of the game. The game ends with no points awarded.\n";
	cout << endl;

}

string Game::getMove(){
	bool valid = false;
	while(!valid){
		cout << "Enter move (? for help) > ";
		string move;
		cin >> move;
		if(move == "?")
			PrintHelp();
		if(move == "n" || move=="N"){
			if(player.p.y == 0)
				cout << "There is a wall in the way...\n";
			else
				return "N";
		}
		if(move == "s" || move == "S"){
			if(player.p.y == size-1)
				cout << "There is a wall in the way...\n";
			else
				return "S";

		}
		if(move == "e" || move== "E"){
			if(player.p.x == size-1)
				cout << "There is a wall in the way...\n";
			else
				return "E";
		}
		if(move == "w" || move == "W"){
			if(player.p.x == 0)
				cout << "There is a wall in the way...\n";
			else
				return "W";

		}
		if(move == "r" || move == "R"){
			if(board[player.p.y][player.p.x] == ENTRANCE){
				cout << "You exit the cave and head to the inn. The locals stare in awe at the gold you have collected as you tell them the tales of your adventure.\n";
				return "R";
			}
			else 
				cout << "You are not at the cave entrance.";
		}
		if(move == "l" || move == "L"){
			if(board[player.p.y][player.p.x] % WEAPON == 0 || board[player.p.y][player.p.x] % GOLD == 0){
				return "L";
			}
			else 
				cout << "Nothing to loot...\n";
		}
		if(move == "x" || move == "X"){
			exit(0);
		}
	}
}

int main(int argc, char const *argv[])
{
	srand(time(NULL)); /* seed random number generator */
	int n; //size of cave

	//only argument should be the size of the cave (N)
	if (argc != 2) {
		cout << "Usage: ./cave N (size of cave between 10 and 20)\n";
		return 1;
	}
	n = atoi(argv[1]);
	Game game(n);
	game.Display();
	while(game.is_live){
		string move = game.getMove();
		if(move == "N")
			game.player.p.y -= 1;
		else if(move == "S")
			game.player.p.y += 1;
		else if(move == "E")
			game.player.p.x += 1;
		else if (move == "W")
			game.player.p.x -= 1;
		else if (move == "R")
			game.is_live = false;
		else if (move == "L")
		{
			if(game.board[game.player.p.y][game.player.p.x] % WEAPON == 0){
				game.player.is_armed = true;
				cout << "You retrieve the sword.\n";
				game.player.score += 5;
			}
			else{
				cout << "You loot some gold.\n";
				game.player.score += 5;
			}
			game.board[game.player.p.y][game.player.p.x] = EXPLORED_ROOM;
		}
		cout << "here\n";
		game.Display();
	}
	cout << "Game Over. Your score: " << game.player.score << endl;
	return 0;
}





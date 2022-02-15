#include <iostream>
#include <vector>
using namespace std;

int x_score = 0;
int o_score = 0;

int factorial(int num)
{
	int factorial=1;
	cout<<" Enter Number To Find Its Factorial:  ";
	cin>>num;
	for (int a=1;a<=num;a++) {
		factorial=factorial*a;
	}
	return factorial;
}

int startup()
{
	int players;
	int selection;
	system("clear");
	cout << "╔══════ Welcome ══════╗" << endl;
	cout << "║                     ║" << endl;
	cout << "║  How Many Players?  ║" << endl;
	cout << "║                     ║" << endl;
	cout << "║  1: single player   ║" << endl;
	cout << "║  2: multiplayer     ║" << endl;
	cout << "║  3: No Players      ║" << endl;
	cout << "║                     ║" << endl;
	cout << "║                     ║" << endl;
	cout << "╚═════════════════════╝" << endl;
	cin >> selection;
	players = selection;
	if (selection == 3)
		players = 0;
	else if (selection > 3 || selection < 1)
	{
		startup();
	}
	return players;
}

bool isTie(char grid[3][3])
{
	bool tie = true;
	for (int i =0; i < 3;i++)
	{
		for (int o = 0; o < 3; o++)
		{
			if (grid[i][o] == ' ')
			{
				tie = false;
				return tie;
			}
		}
	}
	return tie;
}

void drawBoard(char grid[3][3])
{
	system("clear");
	cout << " X: " << x_score << "\tO: " << o_score <<endl;
	cout << "┌───┬───┬───┐\n";
	for (int i = 0; i < 3; i++)
	{
		cout << "│";
		for (int o = 0; o < 3; o++)
		{
			cout << " "<<grid[i][o] << " │";	
		}
		//cout << "|";
		cout << "\n";
		if (i == 2)
		{
			cout <<"└───┴───┴───┘\n";
		}else
		{
			cout << "├───┼───┼───┤\n";
		}
	}
}

string boardConvert(char board[3][3])
{
	string out;
	for (int i = 0; i < 3; i++)
	{
		for (int o = 0; o < 3; o++)
		{
			out += board[i][o];
		}
	}
	return out;
}

char findWinner(char board[3][3])
{
	char winner = ' ';
	for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (y == 1)
				{
					if (board[x][y+1] == board[x][y] && board[x][y-1] == board[x][y])
					{
						winner = board[x][y];
					}
				}
				if (x == 1)
				{
					if (board[x+1][y] == board[x][y] && board[x-1][y] == board[x][y])
					{
						winner = board[x][y];
					}
				}
				if (x == 1 && y == 1)
				{
					
					if (board[x+1][y+1] == board[x][y] && board[x-1][y-1] == board[x][y])
					{
						winner = board[x][y];
					}
					if (board[x-1][y+1] == board[x][y] && board[x+1][y-1] == board[x][y])
					{
						winner = board[x][y];
					}
				}
			}
		}
		return winner;
}

void evaluateTree(char board[3][3], char turn, int &score,int maxDepth = 0, char first = false)
{
	static char switchTurn = turn;
	static int depth = 0;
	if (first)
	{
		depth = 0;
		switchTurn = turn;
		cout << "Evaluating Line...\n";
	}
	
	char opposition;
	if (turn == 'X')
		opposition = 'O';
	else
		opposition = 'X';

	if (findWinner(board) == turn)
	{
		score++;
		cout << "Win Calculated.\n\tNew Score: " << score << endl << "\tDepth Searched: " << depth << endl;
	}else if (findWinner(board) == opposition)
	{
		score--;
		cout << "Lose Calculated.\n\tNew Score: " << score << endl << "\tDepth Searched: " << depth << endl;
	}else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int o = 0; o < 3; o++)
			{
				if (board[i][o] == ' ')
				{
					cout << "No win detected, Filling next empty spot: " << i << " " << o << endl;
					if (depth > maxDepth)
						return;
					depth++;
					board[i][o] = switchTurn;
					if (switchTurn == 'X')
						switchTurn = 'O';
					else
						switchTurn = 'X';
					

					evaluateTree(board, turn, score, maxDepth);
					break;
				}
			}
			
		}
	}

	
}

int aiMove(char board[3][3], char turn)
{
	
	vector<int> scores;
	vector<int> locations;

	int b = 0;
	for (int i = 0; i < 3; i ++)
	{
		for (int o = 0; o < 3; o++)
		{
			if (board[i][o] == ' ')
			{
				b++;
				cout << "Found Empty Location: " << b << endl;
				locations.push_back(b);
				scores.push_back(0);
				evaluateTree(board, turn, scores[scores.size()-1],9, true);
			}
		}
	}

	int best = 0;
	int bestScore = -122122;
	
	for (int i = 0; i < scores.size(); i++)
	{
		if (scores[i] > bestScore)
		{
			bestScore = scores[i];
			best = i;
		}

	}
	cout << "Best move found: " << locations[best] << endl;
	cin.get();
	return locations[best];

	
}

int main() {

	//3x3 array of characters
	//each spot will be a X, O or empty
	char board[3][3] = 
	{
		{' ',' ',' '},
		{' ',' ',' '},
		{' ',' ',' '}
	};

	char turn = 'X';
	char winner = ' ';
	int players = startup();
	//a loop that will keep going until someone wins
	while (winner == ' ')
	{
		//draw the board
		system("clear");
		drawBoard(board);

		//a loop to keep asking the user to pick a move until they pick one that isnt taken
		int input = 0;
		do
		{
			cout << "Pick a move 1 - 9 that isnt taken:\n";
			switch (players){
			case 0:
				input = aiMove(board, turn);
			break;
			case 2:
				cin >> input;
			break;
			default:
				cin >> input;
			break;
			}
			input--;
		}while (board[input/3][input%3] != ' ');
		
		
		board[input/3][input%3] = turn;
		
		//check for winner by scanning board for 3 in a row
		winner = findWinner(board);

		//switch turns
		if (turn == 'X')
			turn = 'O';
		else
			turn = 'X';
	}

	//anounce winner
	drawBoard(board);
	cout << winner << "'s Win!\n";
	
	char answer;
	cout << "Play Again? (y/n)\n";
	cin >> answer;
	
	if (answer == 'y'){
		main();
	}

	return 0;
}

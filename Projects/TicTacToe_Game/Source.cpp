#include <conio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <thread>


#define _number_of_columns 4
#define _number_of_rows 4
#define _number_of_boards 4
using namespace std;




struct Action
{
	int _Board, _Row, _Column;
	Action()
	{
		_Board = 0;
		_Row = 0;
		_Column = 0;
	}

	Action(const Action& _tmp)
	{
		_Board = _tmp._Board;
		_Row = _tmp._Row;
		_Column = _tmp._Column;
	}
};

struct Game_Boards
{
	int*** _Mark;
	int _Last_Player;
	int _Winner;

	Game_Boards()
	{
		int board = 0, row = 0, column = 0;
		_Mark = new int**[_number_of_boards - 1];
		for (board = 0; board < _number_of_boards; board++)
		{
			_Mark[board] = new int*[_number_of_rows - 1];
			for (row = 0; row < _number_of_rows; row++)
			{
				_Mark[board][row] = new int[_number_of_columns - 1];
			}
		}

		for (board = 0; board < _number_of_boards; board++)
		{
			for (row = 0; row < _number_of_rows; row++)
			{
				for (column = 0; column < _number_of_columns; column++)
				{
					_Mark[board][row][column] = 0;
				}
			}
		}
		_Last_Player = 0;
		_Winner = 0;
	}

	Game_Boards(const Game_Boards& _tmp)
	{
		int board = 0, row = 0, column = 0;
		_Mark = new int**[_number_of_boards - 1];
		for (board = 0; board < _number_of_boards; board++)
		{
			_Mark[board] = new int*[_number_of_rows - 1];
			for (row = 0; row < _number_of_rows; row++)
			{
				_Mark[board][row] = new int[_number_of_columns - 1];
			}
		}

		for (board = 0; board < _number_of_boards; board++)
		{
			for (row = 0; row < _number_of_rows; row++)
			{
				for (column = 0; column < _number_of_columns; column++)
				{
					_Mark[board][row][column] = _tmp._Mark[board][row][column];
				}
			}
		}
		_Last_Player = _tmp._Last_Player;
		_Winner = _tmp._Last_Player;
	}

};

class Game
{
private:
	Game_Boards _Boards;
	int Node_Counter = 0;
	int All_Node_Counter = 0;

public:
	Game();
	~Game() {};
	int Change_Player_Mark(int _player_mark);
	void Print_Boards(Game_Boards _boards);
	Action Get_Action_From_User();

	bool Set_Action(Game_Boards &_boards, Action _action, int _player_mark, bool _print);
	bool Clear_Action(Game_Boards &_boards, Action _action, int _player_mark);

	bool Check_Boards_For_Ending_Game(Game_Boards &_boards);
	bool Check_Cube_Columns_For_Ending_Game(Game_Boards &_boards);
	bool Check_Cube_Diagonal_Lines_For_Ending_Game(Game_Boards &_boards);
	bool Check_Draw_For_Ending_Game(Game_Boards &_boards);
	int Evaluation(Game_Boards &_boards, int _player_mark);

	Action Best_Action(Game_Boards _boards, int _player_mark, int _depth);

	int MiniMax_AlphaBeta(Game_Boards _boards, int _depth, int _alpha, int _beta, bool _maximizingPlayer);

	Action Random_Player(Game_Boards &_boards, int _player_mark);
	void Playing();

};

Game::Game()
{
	Print_Boards(_Boards);
	Playing();
}

int Game::Change_Player_Mark(int _player_mark)
{
	if (_player_mark == 1)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

void Game::Print_Boards(Game_Boards _boards)
{
	int board = 0, row = 0, column = 0;

	for (board = 0; board < _number_of_boards; board++)
	{
		cout << "\n Board Number: " << board;
		cout << "\n ========== \n";
		for (row = 0; row < _number_of_rows; row++)
		{
			for (column = 0; column < _number_of_columns; column++)
			{
				cout << " " << _boards._Mark[board][row][column] << " ";
			}
			cout << endl;
		}
		cout << " ========== \n";
	}
}

Action Game::Get_Action_From_User()
{
	int board = 0, row = 0, column = 0;
	Action tmp_action;
	cout << "\n ============================================== ";
	cout << "\n Which board would you like to make a move on (0-" << _number_of_boards - 1 << "): ";
	cin >> board;
	while (0 > board || board >= _number_of_boards)
	{
		cout << " ... !!! WRONG: Out of range !!! ... \n";
		cout << " Which board would you like to make a move on (0-" << _number_of_boards - 1 << "): ";
		cin >> board;
	}

	cout << " Which row you would like to insert in (0-" << _number_of_rows - 1 << "): ";
	cin >> row;
	while (0 > row || row >= _number_of_rows)
	{
		cout << " ... !!! WRONG: Out of range !!! ... \n";
		cout << " Which row you would like to insert in (0-" << _number_of_rows - 1 << "): ";
		cin >> row;
	}

	cout << " Which column you would like to insert in (0-" << _number_of_columns - 1 << "): ";
	cin >> column;
	while (0 > column || column >= _number_of_columns)
	{
		cout << " ... !!! WRONG: Out of range !!! ... \n";
		cout << " Which column you would like to insert in (0-" << _number_of_columns - 1 << "): ";
		cin >> column;
	}


	tmp_action._Board = board;
	tmp_action._Row = row;
	tmp_action._Column = column;

	return tmp_action;	
}

bool Game::Set_Action(Game_Boards &_boards, Action _action, int _player_mark, bool _print)
{

	if (_boards._Mark[_action._Board][_action._Row][_action._Column] == 0)
	{
		_boards._Mark[_action._Board][_action._Row][_action._Column] = _player_mark;
		if (_print == true)
		{
			
			
			cout << " ... !!! Player" << _player_mark << ": Marked the \" board = " << _action._Board <<
				" , row  = " << _action._Row << " , column = " << _action._Column << " \" !!! ... \n";
		}

		return true;
	}
	else
	{
		if (_print == true)
		{
			
			cout << " ... !!! Player" << _player_mark << " WRONG: the \" board = " << _action._Board <<
				" , row  = " << _action._Row << " , column = " << _action._Column << " \"Has marked !!! ... \n";
		}
		return false;
	}
}

bool Game::Clear_Action(Game_Boards &_boards, Action _action, int _player_mark)
{
	if (_boards._Mark[_action._Board][_action._Row][_action._Column] == _player_mark)
	{
		_boards._Mark[_action._Board][_action._Row][_action._Column] = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::Check_Boards_For_Ending_Game(Game_Boards &_boards)
{
	int board = 0, row = 0, column = 0;
	int tmp_mark = 0;
	for (board = 0; board < _number_of_boards; board++)
	{
		row = 0, column = 0;
		//Check Row
		for (column = 0; column < _number_of_columns; column++)
		{
			tmp_mark = _boards._Mark[board][row][column];
			if (tmp_mark != 0)
			{
				for (int r = 0; r < _number_of_rows; r++)
				{
					if (_boards._Mark[board][r][column] != tmp_mark)
					{
						break;
					}
					if (r == _number_of_rows - 1)
					{
						_boards._Winner = tmp_mark;
						return true;
					}
				}
			}
		}
		row = 0, column = 0;

		//Check Column
		for (row = 0; row < _number_of_rows; row++)
		{
			tmp_mark = _boards._Mark[board][row][column];
			if (tmp_mark != 0)
			{
				for (int c = 0; c < _number_of_columns; c++)
				{
					if (_boards._Mark[board][row][c] != tmp_mark)
					{
						break;
					}
					if (c == _number_of_columns - 1)
					{
						_boards._Winner = tmp_mark;
						return true;
					}
				}
			}
		}
		row = 0, column = 0;

		//Check Diagonal
		row = 0, column = 0;
		tmp_mark = _boards._Mark[board][row][column];
		if (tmp_mark != 0)
		{
			for (int diagonal = 0; diagonal < _number_of_rows; diagonal++)
			{

				if (_boards._Mark[board][diagonal][diagonal] != tmp_mark)
				{
					break;
				}
				if (diagonal == _number_of_rows - 1)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
			}
		}

		row = 0, column = _number_of_columns - 1;
		tmp_mark = _boards._Mark[board][row][column];
		if (tmp_mark != 0)
		{
			for (int row = 0; row < _number_of_rows; row++)
			{

				if (_boards._Mark[board][row][column] != tmp_mark)
				{
					break;
				}
				if (row == _number_of_rows - 1)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
				column--;
			}
		}
		row = 0, column = 0;


	}

	return false;
}

bool Game::Check_Cube_Columns_For_Ending_Game(Game_Boards &_boards)
{
	int board = 0, row = 0, column = 0;
	int tmp_mark = 0;
	for (row = 0; row < _number_of_rows; row++)
	{
		for (column = 0; column < _number_of_columns; column++)
		{
			tmp_mark = _boards._Mark[board][row][column];
			if (tmp_mark != 0)
			{
				for (int b = 0; b < _number_of_boards; b++)
				{
					if (_boards._Mark[b][row][column] != tmp_mark)
					{
						break;
					}
					if (b == _number_of_boards - 1)
					{
						_boards._Winner = tmp_mark;
						return true;
					}
				}
			}

		}
	}
}

bool Game::Check_Cube_Diagonal_Lines_For_Ending_Game(Game_Boards &_boards)
{
	int board = 0, row = 0, column = 0;
	int tmp_mark = 0;


	board = 0, row = 0, column = 0;
	tmp_mark = _boards._Mark[board][row][column];
	if (tmp_mark != 0)
	{
		for (int b = 0; b < _number_of_boards; b++)
		{
			if (_boards._Mark[b][row][column] != tmp_mark)
			{
				break;
			}
			if (b == _number_of_boards - 1)
			{
				_boards._Winner = tmp_mark;
				return true;
			}
			row++;
			column++;
		}
	}

	board = 0, row = _number_of_rows - 1, column = _number_of_columns - 1;
	tmp_mark = _boards._Mark[board][row][column];
	if (tmp_mark != 0)
	{
		for (int b = 0; b < _number_of_boards; b++)
		{
			if (_boards._Mark[b][row][column] != tmp_mark)
			{
				break;
			}
			if (b == _number_of_boards - 1)
			{
				_boards._Winner = tmp_mark;
				return true;
			}
			row--;
			column--;
		}
	}



	board = 0, row = 0, column = _number_of_columns - 1;
	tmp_mark = _boards._Mark[board][row][column];
	if (tmp_mark != 0)
	{
		for (int b = 0; b < _number_of_boards; b++)
		{
			if (_boards._Mark[b][row][column] != tmp_mark)
			{
				break;
			}
			if (b == _number_of_boards - 1)
			{
				_boards._Winner = tmp_mark;
				return true;
			}
			row++;
			column--;
		}
	}

	board = 0, row = _number_of_rows - 1, column = 0;
	tmp_mark = _boards._Mark[board][row][column];
	if (tmp_mark != 0)
	{
		for (int b = 0; b < _number_of_boards; b++)
		{
			if (_boards._Mark[b][row][column] != tmp_mark)
			{
				break;
			}
			if (b == _number_of_boards - 1)
			{
				_boards._Winner = tmp_mark;
				return true;
			}
			row--;
			column++;
		}
	}

	//*************************

	board = 0, row = 0, column = 0;
	for (row = 0; row < _number_of_rows; row++)
	{
		board = 0, column = 0;
		tmp_mark = _boards._Mark[board][row][column];
		if (tmp_mark != 0)
		{
			for (int diagonal = 0; diagonal < _number_of_columns; diagonal++)
			{
				if (_boards._Mark[diagonal][row][diagonal] != tmp_mark)
				{
					break;
				}
				if (diagonal == _number_of_columns - 1)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
			}
		}
		
	}

	board = 0, row = 0, column = _number_of_columns - 1;
	for (row = 0; row < _number_of_rows - 1; row++)
	{
		board = 0, column = _number_of_columns - 1;
		tmp_mark = _boards._Mark[board][row][column];

		if (tmp_mark != 0)
		{
			for (int diagonal = _number_of_columns - 1; diagonal > -1; diagonal--)
			{
				if (_boards._Mark[diagonal][row][diagonal] != tmp_mark)
				{
					break;
				}
				if (diagonal == 0)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
			}
		}
	}

	board = 0, row = 0, column = 0;
	for (column = 0; column < _number_of_columns; column++)
	{
		board = 0, row = 0;
		tmp_mark = _boards._Mark[board][row][column];
		if (tmp_mark != 0)
		{
			for (int diagonal = 0; diagonal < _number_of_rows; diagonal++)
			{
				if (_boards._Mark[diagonal][diagonal][column] != tmp_mark)
				{
					break;
				}
				if (diagonal == _number_of_rows - 1)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
			}
		}
	}

	board = 0, row = _number_of_rows - 1, column = 0;
	for (column = 0; column < _number_of_columns; column++)
	{
		row = _number_of_rows - 1;
		tmp_mark = _boards._Mark[board][row][column];
		if (tmp_mark != 0)
		{
			for (int diagonal = _number_of_rows -1; diagonal > -1; diagonal--)
			{
				if (_boards._Mark[diagonal][diagonal][column] != tmp_mark)
				{
					break;
				}
				if (diagonal == 0)
				{
					_boards._Winner = tmp_mark;
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::Check_Draw_For_Ending_Game(Game_Boards &_boards)
{
	int board = 0, row = 0, column = 0;
	int tmp_mark = 0;

	for (board = 0; board < _number_of_boards; board++)
	{
		for (row = 0; row < _number_of_rows; row++)
		{
			for (column = 0; column < _number_of_columns; column++)
			{
				tmp_mark = _boards._Mark[board][row][column];
				if (tmp_mark == 0)
				{
					return false;
				}
			}
		}
	}
	_boards._Winner = 0;
	return true;
}

int Game::Evaluation(Game_Boards &_boards, int _player_mark)
{
	if (Check_Boards_For_Ending_Game(_boards) == true)
	{
		if (_player_mark == _boards._Winner)
		{
			return +10;
		}
		else if(Change_Player_Mark(_player_mark) == _boards._Winner)
		{
			return -10;
		}
	}
	else if (Check_Cube_Columns_For_Ending_Game(_boards) == true)
	{
		if (_player_mark == _boards._Winner)
		{
			return +10;
		}
		else if (Change_Player_Mark(_player_mark) == _boards._Winner)
		{
			return -10;
		}
	}
	else if (Check_Cube_Diagonal_Lines_For_Ending_Game(_boards) == true)
	{
		if (_player_mark == _boards._Winner)
		{
			return +10;
		}
		else if (Change_Player_Mark(_player_mark) == _boards._Winner)
		{
			return -10;
		}
	}
	else
	{
		return 0;
	}
		
}

Action Game::Best_Action(Game_Boards _boards, int _player_mark, int _depth)
{
	int board = 0, row = 0, column = 0;
	int best_value = -INT_MAX;
	Action tmp_action;
	Action best_action;
	Game_Boards tmp_boards = _boards;
	int tmp_alpha = -INT_MAX;
	int tmp_beta = INT_MAX;
	int tmp_mark = 0;
	int _counter = 1;
	tmp_boards._Last_Player = _player_mark;
	Node_Counter = 0;
	for (board = 0; board < _number_of_boards; board++)
	{
		for (row = 0; row < _number_of_rows; row++)
		{
			for (column = 0; column < _number_of_columns; column++)
			{
				tmp_mark = _boards._Mark[board][row][column];
				if (tmp_mark == 0)
				{
					tmp_action._Board = board;
					tmp_action._Row = row;
					tmp_action._Column = column;
					Set_Action(tmp_boards, tmp_action, _player_mark, false);
					Node_Counter++;
					All_Node_Counter++;
					int tmp_value = MiniMax_AlphaBeta(tmp_boards, _depth, tmp_alpha, tmp_beta, false);

					Clear_Action(tmp_boards, tmp_action, _player_mark);
					
					//cout << " " << _counter << ": " << tmp_value << endl;
					//_counter++;


					if (tmp_value > best_value)
					{
					    best_action = tmp_action ;
						best_value = tmp_value;
					}
				}

			}
		}
	}

	return best_action;
}


int Game::MiniMax_AlphaBeta(Game_Boards _boards, int _depth, int _alpha, int _beta, bool _maximizingPlayer)
{
	int score = Evaluation(_boards, _boards._Last_Player);
	if (score != 0 || _depth == 0)
	{
		return score;
	}
	if (Check_Draw_For_Ending_Game(_Boards) == true)
	{
		return 0;
	}
	else
	{
		int board = 0, row = 0, column = 0;
		bool Break = false;
		Action tmp_action;

		int tmp_mark = 0;

		if (_maximizingPlayer == true)
		{
			int tmp_bestValue = -INT_MAX;
			for (board = 0; board < _number_of_boards && Break == false; board++)
			{
				for (row = 0; row < _number_of_rows && Break == false; row++)
				{
					for (column = 0; column < _number_of_columns && Break == false; column++)
					{

						tmp_mark = _boards._Mark[board][row][column];
						if (tmp_mark == 0)
						{
							tmp_action._Board = board;
							tmp_action._Row = row;
							tmp_action._Column = column;
							Set_Action(_boards, tmp_action, _boards._Last_Player, false);

							All_Node_Counter++;
							Node_Counter++;

							int child_value = MiniMax_AlphaBeta(_boards, _depth - 1, _alpha, _beta, !_maximizingPlayer);
							tmp_bestValue = max(tmp_bestValue, child_value);
							_alpha = max(_alpha, tmp_bestValue);
							Clear_Action(_boards, tmp_action, _boards._Last_Player);

							if (_alpha >= _beta)
							{
								Break = true;
								break;
							}

						}
					}
				}
			}
			return tmp_bestValue;
		}

		else if (_maximizingPlayer == false)
		{
			int tmp_bestValue = INT_MAX;
			for (board = 0; board < _number_of_boards && Break == false; board++)
			{
				for (row = 0; row < _number_of_rows && Break == false; row++)
				{
					for (column = 0; column < _number_of_columns && Break == false; column++)
					{

						tmp_mark = _boards._Mark[board][row][column];
						if (tmp_mark == 0)
						{
							tmp_action._Board = board;
							tmp_action._Row = row;
							tmp_action._Column = column;
							Set_Action(_boards, tmp_action, Change_Player_Mark(_boards._Last_Player), false);


							int child_value = MiniMax_AlphaBeta(_boards, _depth - 1, _alpha, _beta, !_maximizingPlayer);
							tmp_bestValue = min(tmp_bestValue, child_value);
							_beta = min(_beta, tmp_bestValue);
							Clear_Action(_boards, tmp_action, Change_Player_Mark(_boards._Last_Player));

							if (_alpha >= _beta)
							{
								Break = true;
								break;
							}

						}
					}
				}
			}
			return tmp_bestValue;
		}

	}

}





Action Game::Random_Player(Game_Boards &_boards, int _player_mark)
{
	int board, row , column;
	Action tmp_action;
	Game_Boards tmp_boards = _boards;
	bool exit = false;
	srand((unsigned)time(NULL));
	board = rand() % _number_of_boards;
	row = rand() % _number_of_rows;
	column = rand() % _number_of_columns;

	tmp_action._Board = board;
	tmp_action._Row = row;
	tmp_action._Column = column;

	while (Set_Action(tmp_boards, tmp_action, _player_mark, false) == false)
	{
		Clear_Action(tmp_boards, tmp_action, _player_mark);
		//srand((unsigned)time(NULL));
		board = rand() % _number_of_boards;
		row = rand() % _number_of_rows;
		column = rand() % _number_of_columns;

		tmp_action._Board = board;
		tmp_action._Row = row;
		tmp_action._Column = column;
	}
	return tmp_action;
}

void Game::Playing()
{
	int turn = 0;
	int Result;

	do
	{
		cout << "\n Which one do you want to start (1: User , 2: PC) : ";
		cin >> turn;
	} while (turn != 1 && turn != 2);
	
	
	Action tmp_action;
	
	
	
	
	int depth = 1;
	int _counter = 1;
	
	do
	{
		if (turn == 1)
		{
			system("cls");
			Print_Boards(_Boards);

			
			using namespace std::chrono_literals;
			auto start = chrono::high_resolution_clock::now();

			//tmp_action = Best_Action(_Boards, turn, 2);
			//Set_Action(_Boards, tmp_action, turn, true);


			/*tmp_action = Random_Player(_Boards, turn);
			Set_Action(_Boards, tmp_action, turn, true);*/

			do
			{
				tmp_action = Get_Action_From_User();	

			} while (Set_Action(_Boards, tmp_action, turn, true) == false);
			
			
			auto end = chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = end - start;
			if (elapsed.count() > 60000)
			{
				cout << "\n ... !!! Time Out: Player " << turn << " lose the game  !!! ... \n";
				_getch();
				return;
			}


			cout << " ... !!! Press any key to continue !!! ... \n";
			//_getch();

			turn = 2;
		}
		else if (turn == 2)
		{
			system("cls");
			Print_Boards(_Boards);
			if (_counter % 5 == 0)
			{
				depth++;
			}

			using namespace std::chrono_literals;
			auto start = chrono::high_resolution_clock::now();

			tmp_action = Best_Action(_Boards, turn,2);
			Set_Action(_Boards, tmp_action, turn, true);

			cout << "\n ... !!! All node till now: " << All_Node_Counter << "\tand\t All node for this action: " << Node_Counter << " !!! ... \n";

			auto end = chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsed = end - start;

			if (elapsed.count() > 60000)
			{
				cout << "\n ... !!! Time Out: Player " << turn << " lose the game  !!! ... \n";
				_getch();
				return;
			}

			

			cout << " ... !!! Press any key to continue !!! ... \n";
			//_getch();
			turn = 1;
		}
		
		_counter++;
		Result = Evaluation(_Boards, turn);
		//cout << " ... !!! Press any key to continue !!! ... \n";
		//_getch();

	} while (Result != 10 && Result != -10 && Check_Draw_For_Ending_Game(_Boards) != true);

	system("cls");
	Print_Boards(_Boards);

	if (Result != 0)
	{
		cout << "\n ... !!! All node till now: " << All_Node_Counter << "\tand\t All node for this action: " << Node_Counter << " !!! ... \n";
		cout << " ... !!! Player " << _Boards._Winner << " won the game !!! ... \n";
		return;
	}

	else if (Result == 0 && Check_Draw_For_Ending_Game(_Boards) == true)
	{
		cout << " ... !!! No one could win the game !!! ... \n";
		return;
	}
	else
	{
		cout << " ... !!! WRONG : We have some BUGS ... Press any key to continue !!! ... \n";
		_getch();
	}

	
	
}


int main()
{

	Game MyGame;

	_getch();
	return 0;
}
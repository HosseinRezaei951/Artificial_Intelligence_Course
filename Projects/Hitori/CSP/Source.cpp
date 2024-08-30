#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <thread>
#include <stack>
#include <conio.h>
#include <vector>
using namespace std;

//_Size => dar vaghe haman bode matris vorodi(matris dadehye asli mibashd)
#define _Size 10
int node_counter = 0;


//moatghayere dakhelie har selol az matris dade asli
struct _node
{
	int Value;
	
	//Domins
	bool _zero;
	bool _one;

	//copy constructor
	_node(const _node& tmp)
	{
		Value = tmp.Value;
		_zero = tmp._zero;
		_one = tmp._one;
	}

	//constructor
	_node()
	{
		Value = 0;
		_zero = true;
		_one = true;
	}


};

//sakhteman dade dar nazar gerefte shode baraye in ghesmate poroje yek 
//struct az noe matris 2 bodeie az jense _node mibashd ke yek 
//constructor mamoli va yek copy constructor niz
//baraye an tarif shode ast
struct Node
{
	_node** Matrix;
	int Last_i;
	int Last_j;

	int cleared_cell_counter;
	//copy constructor
	Node(const Node& tmp)
	{
		//Build Matrix
		Matrix = new _node*[_Size];
		for (int i = 0; i < _Size; i++)
		{
			Matrix[i] = new _node[_Size];
		}


		//Initiating Matrix 
		for (int i = 0; i < _Size; i++)
		{
			for (int j = 0; j < _Size; j++)
			{
				Matrix[i][j] = tmp.Matrix[i][j];
			}
		}
		Last_i = tmp.Last_i;
		Last_j = tmp.Last_j;
		cleared_cell_counter = tmp.cleared_cell_counter;
	}

	//constructor
	Node()
	{
		//Build Matrix
		Matrix = new _node*[_Size];
		for (int i = 0; i < _Size; i++)
		{
			Matrix[i] = new _node[_Size];
		}

		Last_i = 1;
		Last_j = 1;
		cleared_cell_counter = 0;
	}

};


//baraye soholat dar kar yek class be name bazi tarif shodeh ast ta tamami
//tavabe morede nazar daron on tarif shavad va dar adres dehi ve meghdar dehi dochar eshtebah nashvim
class Hitori
{
private:
	//Orginal Data
	Node _Data;

	//Stack for dfs algorithm
	stack<Node> _DFS_Stack;

public:
	//Constructor
	Hitori();

	//Initialiser 
	void Initialization();

	//Function for printing matrix
	void PrintMatrix(Node _State);
	void PrintResult(Node _State);


	//DFS algorithm
	void SimpleBacktrack();

	//Successor Functions
	queue<Node> Successor(Node _State);
	void UpdateDomains(Node &_State,int i, int j);
	void MRV_Search(Node _State, int &_i, int &_j); 


	//Constraints Function 
	bool ValidToClear(Node _State, int i, int j);
	bool ValidToStay(Node _State, int i, int j);
	bool CheckSurround(Node _State, int i, int j);

	//IsGoal Functions
	bool IsGoal(Node _State);
	bool IsValid(Node _State, int i, int j);
};


//farakhanie tabe Initialization va PrintMatrix baraye khandane etelate 
//sample worodi va hmintor print kardane an
Hitori::Hitori()
{
	Initialization();

	cout << "\n ===> Orginal Data:";
	PrintMatrix(_Data);

	//_getch();
}


//output: void
//input: -nothing-
//khandane file sample dade ha az adres morede nazar va megdar dehi motgayere
//mojod dar gesmate private class asli(Hitori)
void Hitori::Initialization()
{
	//Import DATA
	ifstream File;
	File.open("Data/sample2.txt");

	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			File >> _Data.Matrix[i][j].Value;
		}
	}
}


//output: void
//input: Node State (yek struct havi matris dade)
//khandane matris vorodi va chap on
void Hitori::PrintMatrix(Node _State)
{
	cout << "\n ================= \n";
	for (int i = 1; i < _Size; i++)
	{
		cout << " ";
		for (int j = 1; j < _Size; j++)
		{
			cout << _State.Matrix[i][j].Value << " ";
		}
		cout << "\t";
		for (int j = 1; j < _Size; j++)
		{
			
			cout << "{" << _State.Matrix[i][j]._zero << "," << _State.Matrix[i][j]._one << "}" << " ";
		}
		cout << endl;
	}
	

	cout << " ================= \n";
	
	//_getch();
}


//output: void
//input: Node State (yek struct havi matris dade)
//chap natayej
void Hitori::PrintResult(Node _State)
{
	PrintMatrix(_State);
	printf("\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*	how many node produced till now : %d \n", node_counter);
	printf("*	how many cells cleared till now on this node : %d \n", _State.cleared_cell_counter);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}


//output : void
//input : -nothing-
//algorithm SimpleBacktrack tebgh osol mojod dar hosh masnoei tarrahi va pyade sazi shode ast 
void Hitori::SimpleBacktrack()
{
	//Check is the first state goal ?!
	if (IsGoal(_Data) == true)
	{
		cout << "\n ===> End Game !!!";
		PrintResult(_Data);
		return;
	}
	else
	{
		//push first state in dfs stack
		_DFS_Stack.push(_Data);
		node_counter++;


		while (_DFS_Stack.empty() == false)
		{
			//cout << "\n Stack Size = " << _DFS_Stack.size();
			//tmp node for doing algorithm on it & get the first 
			//element of stack 
			Node tmp(_DFS_Stack.top());
			_DFS_Stack.pop();

     		//cout << "\n father node: ";
			//PrintMatrix(tmp);
			

			//Check IsGoal on first node
			if (IsGoal(tmp) == true)
			{
				cout << "\n ===> End Game !!!";
				PrintResult(tmp);
				return;
			}
			else
			{
				//Find total neighbor states
				queue<Node> Neighbor_States = Successor(tmp);

				//Adding all funded neighbor states to main stack
				while (Neighbor_States.empty() == false)
				{
					node_counter++;

					_DFS_Stack.push(Neighbor_States.front());
					Neighbor_States.pop();
				}
				
			}

		}

		//if there is no any node to search and find true neighbors there is not answer to game
		if (_DFS_Stack.empty() == true)
		{
			cout << "\n ===> Game didn't have any solution !!!";
			return;
		}
	}

}


//output : vector<Node> (safe tamami hamsaye haye node vorodi)
//input : Node State (yek struct havi matris dade)
//Successor motabegh ba algorithm SimpleBacktrack trahi va pyade sazi shode ast
queue<Node> Hitori::Successor(Node _State)
{
	//out put queue
	queue<Node> TotalStates;
	Node tmp_node(_State);
	

	int tmpPointer_i = _State.Last_i;
	int tmpPointer_j = _State.Last_j;
	//cout << "\n " << tmpPointer_i << " , " << tmpPointer_j;
	
	
	if (_State.Last_i == 0 && _State.Last_j == 0)
	{
		return TotalStates;
	}
	else
	{
		tmpPointer_j++;
		if (tmpPointer_j == _Size)
		{
			tmpPointer_j = 1;
			tmpPointer_i++;
			if (tmpPointer_i == _Size)
			{
				tmpPointer_i = 0;
				tmpPointer_j = 0;
			}
		}
		
		

		
		if (tmp_node.Matrix[_State.Last_i][_State.Last_j]._zero == true)
		{
			Node tmp(_State);
			tmp.Matrix[_State.Last_i][_State.Last_j].Value = 0;
			UpdateDomains(tmp, _State.Last_i, _State.Last_j);
			//MRV_Search(tmp, tmpPointer_i, tmpPointer_j);
			//cout << "\n " << tmpPointer_i << " , " << tmpPointer_j;
			tmp.Last_i = tmpPointer_i;
			tmp.Last_j = tmpPointer_j;
			tmp.cleared_cell_counter++;
			TotalStates.push(tmp);
			//PrintMatrix(tmp);
			//if (ValidToClear(tmp_node, _State.Last_i, _State.Last_j) == true)
			//{
			//	Node tmp(_State);
			//	tmp.Matrix[_State.Last_i][_State.Last_j].Value = 0;
			//	UpdateDomains(tmp, _State.Last_i, _State.Last_j);
			//	//MRV_Search(tmp, tmpPointer_i, tmpPointer_j);
			//	cout << "\n " << tmpPointer_i << " , " << tmpPointer_j;
			//	tmp.Last_i = tmpPointer_i;
			//	tmp.Last_j = tmpPointer_j;
			//	TotalStates.push(tmp);
			//	PrintMatrix(tmp);
			//	
			//}
			
		}
		

		if (tmp_node.Matrix[_State.Last_i][_State.Last_j]._one == true)
		{
			Node tmp(_State);
			tmp.Matrix[_State.Last_i][_State.Last_j].Value = _Data.Matrix[_State.Last_i][_State.Last_j].Value;
			UpdateDomains(tmp, _State.Last_i, _State.Last_j);
			//MRV_Search(tmp, tmpPointer_i, tmpPointer_j);
			//cout << "\n " << tmpPointer_i << " , " << tmpPointer_j;
			tmp.Last_i = tmpPointer_i;
			tmp.Last_j = tmpPointer_j;
		
			TotalStates.push(tmp);
			//PrintMatrix(tmp);

			//if (ValidToStay(tmp_node, _State.Last_i, _State.Last_j) == true)
			//{
			//	Node tmp(_State);
			//	tmp.Matrix[_State.Last_i][_State.Last_j].Value = _Data.Matrix[_State.Last_i][_State.Last_j].Value;
			//	UpdateDomains(tmp, _State.Last_i, _State.Last_j);
			//	//MRV_Search(tmp, tmpPointer_i, tmpPointer_j);
			//	cout << "\n " << tmpPointer_i << " , " << tmpPointer_j;
			//	tmp.Last_i = tmpPointer_i;
			//	tmp.Last_j = tmpPointer_j;
			//	TotalStates.push(tmp);
			//	PrintMatrix(tmp);

			//}

		}
		
		
		//_getch();
		return TotalStates;
	}
	
}


//output : void
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//update kardane sayere damane haye node vorodi motanaseb ba selole[i,j]
void Hitori::UpdateDomains(Node &_State, int i, int j)
{
	if (_State.Matrix[i][j].Value == 0) // we should delete all _zero domains from neighbors
	{
		_State.Matrix[i][j]._one = false;
		//delete right
		if (j + 1 < _Size)
		{
			_State.Matrix[i][j+1]._zero = false;
		}

		//delete left
		if (j - 1 > 0)
		{
			_State.Matrix[i][j-1]._zero = false;
		}

		//delete down
		if (i + 1 < _Size)
		{
			_State.Matrix[i+1][j]._zero = false;
		}

		//delete up
		if (i - 1 > 0)
		{
			_State.Matrix[i-1][j]._zero = false;
		}

	}
	else // we should delete all _one domains from neighbors
	{
		_State.Matrix[i][j]._zero = false;
		int _value;
		_value = _State.Matrix[i][j].Value;
		if (_value != 0)
		{
			//delete vertical
			if (i < (_Size - 1))
			{
				int second_i = i + 1;
				while (second_i < _Size)
				{
					if (_State.Matrix[second_i][j].Value == _value)
					{
						_State.Matrix[second_i][j]._one = false;
					}
					second_i++;
				}

			}
			if (i > 1)
			{
				int second_i = i - 1;
				while (second_i > 0)
				{
					if (_State.Matrix[second_i][j].Value == _value)
					{
						_State.Matrix[second_i][j]._one = false;
					}
					second_i--;
				}

			}


			//delete horizontal
			if (j < (_Size - 1))
			{
				int second_j = j + 1;
				while (second_j < _Size)
				{
					if (_State.Matrix[i][second_j].Value == _value)
					{
						_State.Matrix[i][second_j]._one = false;
					}
					second_j++;
				}
			}
			if (j > 1)
			{
				int second_j = j - 1;
				while (second_j > 0)
				{
					if (_State.Matrix[i][second_j].Value == _value)
					{
						_State.Matrix[i][second_j]._one = false;
					}
					second_j--;
				}
			}

		}

	}
}


//output : void
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//yaftan mogheyate meghdare kamine dar damene ha 
void Hitori::MRV_Search(Node _State, int &_i, int &_j)
{
	int Last_i = _i;
	int Last_j = _j;
	int MinimumDomain = 3;
	int tmp_Min;

	for (int i = Last_i; i < _Size; i++)
	{
		for (int j = Last_j; j < _Size; j++)
		{
			tmp_Min = 0;
			if (_State.Matrix[i][j]._zero == true)
			{
				tmp_Min++;
			}
			if (_State.Matrix[i][j]._one == true)
			{
				tmp_Min++;
			}
			if (tmp_Min == 2)
			{
				_i = i;
				_j = j;
				return;
			}
		}
	}
	_i = 0;
	_j = 0;
	return;
}


//output : bool (true ==> valid to Clear , false ==> not not valid to Clear)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//barrsi inke aya selole morede nazar ba mogheyate [i,j] mitavanad dar node morede nazar 
//bedone eshtebah hazf(syah) shavad ya na ?!
bool Hitori::ValidToClear(Node _State, int i, int j)
{
	//check right
	if (j + 1 < _Size && _State.Matrix[i][j + 1].Value == 0)
	{
		return false;
	}

	//check left
	else if (j - 1 > 0 && _State.Matrix[i][j - 1].Value == 0)
	{
		return false;
	}

	//check down
	else if (i + 1 < _Size && _State.Matrix[i + 1][j].Value == 0)
	{
		return false;
	}

	//check up
	else if (i - 1 > 0 && _State.Matrix[i - 1][j].Value == 0)
	{
		return false;
	}

	//check surrounded-up
	else if (CheckSurround(_State, i - 1, j) == true)
	{
		return false;
	}

	//check surrounded-down
	else if (CheckSurround(_State, i + 1, j) == true)
	{
		return false;
	}

	//check surrounded-right
	else if (CheckSurround(_State, i, j + 1) == true)
	{
		return false;
	}

	//check surrounded-left
	else if (CheckSurround(_State, i, j - 1) == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//output : bool (true ==> valid to stay , false ==> not not valid to stay)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//barrsi inke aya selole morede nazar ba mogheyate [i,j] mitavanad dar node morede nazar 
//bedone eshtebah baghi bemanad ya na ?!
bool Hitori::ValidToStay(Node _State, int i, int j)
{
	int _value;
	_value = _State.Matrix[i][j].Value;
	if (_value != 0)
	{
		//check vertical
		if (i < (_Size - 1))
		{
			int second_i = i + 1;
			while (second_i < _Size)
			{
				if (_State.Matrix[second_i][j].Value == _value)
				{
					return false;
				}
				second_i++;
			}

		}
		if (i > 1)
		{
			int second_i = i - 1;
			while (second_i > 0)
			{
				if (_State.Matrix[second_i][j].Value == _value)
				{
					return false;
				}
				second_i--;
			}

		}


		//check horizontal
		if (j < (_Size - 1))
		{
			int second_j = j + 1;
			while (second_j < _Size)
			{
				if (_State.Matrix[i][second_j].Value == _value)
				{
					return false;
				}
				second_j++;
			}
		}
		if (j > 1)
		{
			int second_j = j - 1;
			while (second_j > 0)
			{
				if (_State.Matrix[i][second_j].Value == _value)
				{
					return false;
				}
				second_j--;
			}
		}

	}
	return true;
}


//output : bool (true ==> Surround with black cells , false ==> not Surround with black cells)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//CheckSurround motabegh ba IsValid trahi va pyade sazi shode ast
bool Hitori::CheckSurround(Node _State, int i, int j)
{
	//left-up corner
	if (i - 1 == 0 && j - 1 == 0 && (_State.Matrix[i + 1][j].Value == 0 && _State.Matrix[i][j + 1].Value == 0))
	{
		return true;
	}
	//up wall corner
	else if (i - 1 == 0 && (j - 1 > 0 && j + 1 < _Size) && (_State.Matrix[i][j - 1].Value == 0 && _State.Matrix[i][j + 1].Value == 0 && _State.Matrix[i + 1][j].Value == 0))
	{
		return true;
	}
	//right-up corner
	else if (i - 1 == 0 && j + 1 == _Size && (_State.Matrix[i + 1][j].Value == 0 && _State.Matrix[i][j - 1].Value == 0))
	{
		return true;
	}
	//right wall corner
	else if (j + 1 == _Size && (i - 1 > 0 && i + 1 < _Size) && (_State.Matrix[i + 1][j].Value == 0 && _State.Matrix[i - 1][j].Value == 0 && _State.Matrix[i][j - 1].Value == 0))
	{
		return true;
	}
	//right-down corner
	else if (i + 1 == _Size && j + 1 == _Size && (_State.Matrix[i - 1][j].Value == 0 && _State.Matrix[i][j - 1].Value == 0))
	{
		return true;
	}
	//down wall corner
	else if (i + 1 == _Size && (j - 1 > 0 && j + 1 < _Size) && (_State.Matrix[i][j - 1].Value == 0 && _State.Matrix[i][j + 1].Value == 0 && _State.Matrix[i - 1][j].Value == 0))
	{
		return true;
	}
	//left-down corner
	else if (i + 1 == _Size && j - 1 == 0 && (_State.Matrix[i - 1][j].Value == 0 && _State.Matrix[i][j + 1].Value == 0))
	{
		return true;
	}
	//left wall corner
	else if (j - 1 == 0 && (i - 1 > 0 && i + 1 < _Size) && (_State.Matrix[i + 1][j].Value == 0 && _State.Matrix[i - 1][j].Value == 0 && _State.Matrix[i][j + 1].Value == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}


//output : bool (true ==> the input is goal , false ==> the input isnt goal)
//input : Node State(matris dade asli)
//IsGoal motabegh ba function haye mojod dar algorithm ha trahi va pyade sazi shode ast
bool Hitori::IsGoal(Node _State)
{
	int index = 0;
	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			index = _State.Matrix[i][j].Value;
			if (index != 0)
			{
				//check vertical
				if (i < (_Size - 1))
				{
					int second_i = i + 1;
					while (second_i < _Size)
					{
						if (_State.Matrix[second_i][j].Value == index)
						{
							return false;
						}
						second_i++;
					}

				}
				if (i > 1)
				{
					int second_i = i - 1;
					while (second_i > 0)
					{
						if (_State.Matrix[second_i][j].Value == index)
						{
							return false;
						}
						second_i--;
					}

				}
				


				//check horizontal
				if (j < (_Size - 1))
				{
					int second_j = j + 1;
					while (second_j < _Size)
					{
						if (_State.Matrix[i][second_j].Value == index)
						{
							return false;
						}
						second_j++;
					}
				}
				if (j > 1)
				{
					int second_j = j - 1;
					while (second_j > 0)
					{
						if (_State.Matrix[i][second_j].Value == index)
						{
							return false;
						}
						second_j--;
					}
				}

			}
			else
			{
				if (IsValid(_State, i, j) == false)
				{
					return false;
				}
			}

		}
	}
	return true;

}


//output : bool (true ==> valid to clear cell , false ==> not valid to clear cell)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//IsValid motabegh ba Successor , FindNeighbors trahi va pyade sazi shode ast
bool Hitori::IsValid(Node _State, int i, int j)
{
	//check right
	if (j + 1 < _Size && _State.Matrix[i][j + 1].Value == 0)
	{
		return false;
	}

	//check left
	else if (j - 1 > 0 && _State.Matrix[i][j - 1].Value == 0)
	{
		return false;
	}

	//check down
	else if (i + 1 < _Size && _State.Matrix[i + 1][j].Value == 0)
	{
		return false;
	}

	//check up
	else if (i - 1 > 0 && _State.Matrix[i - 1][j].Value == 0)
	{
		return false;
	}

	//check surrounded-up
	else if (CheckSurround(_State, i - 1, j) == true)
	{
		return false;
	}

	//check surrounded-down
	else if (CheckSurround(_State, i + 1, j) == true)
	{
		return false;
	}

	//check surrounded-right
	else if (CheckSurround(_State, i, j + 1) == true)
	{
		return false;
	}

	//check surrounded-left
	else if (CheckSurround(_State, i, j - 1) == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	Hitori MyHitori;
	{
		using namespace std::chrono_literals;
		auto start = chrono::high_resolution_clock::now();

		MyHitori.SimpleBacktrack();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;

		printf(" ==> time is : %f ms \n", elapsed.count());
    }
	

	_getch();
	return 0;
}
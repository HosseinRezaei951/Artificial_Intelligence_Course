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



//sakhteman dade dar nazar gerefte shode baraye in ghesmate poroje yek 
//struct az noe matris 2 bodeie az jense integer mibashd hamintor motanaseb 
//ba algorithm haye Greedy va A* 2 motaghayere "h" va "cost" niz az jense integer
//dar nazar gerefte shodeh ast ke yek constructor mamoli va yek 
//copy constructor niz baraye an tarif shode ast
struct Node
{
	int** Matrix;
	int h;
	int cost;
	int cleared_cell_counter;
	int Children_counter;
	//copy constructor
	Node(const Node& tmp)
	{
		//Build Matrix
		Matrix = new int*[_Size];
		for (int i = 0; i < _Size; i++)
		{
			Matrix[i] = new int[_Size];
		}


		//Initiating Matrix 
		for (int i = 0; i < _Size; i++)
		{
			for (int j = 0; j < _Size; j++)
			{
				Matrix[i][j] = tmp.Matrix[i][j];
			}
		}
		h = tmp.h;
		cost = tmp.cost;
		cleared_cell_counter = tmp.cleared_cell_counter;
		Children_counter = tmp.Children_counter;
	}

	//constructor
	Node()
	{
		//Build Matrix
		Matrix = new int*[_Size];
		for (int i = 0; i < _Size; i++)
		{
			Matrix[i] = new int[_Size];
		}

		//Clear Matrix 
		for (int i = 0; i < _Size; i++)
		{
			for (int j = 0; j < _Size; j++)
			{
				Matrix[i][j] = 0;
			}
		}
		h = 0;
		cost = 0;
		cleared_cell_counter = 0;
		Children_counter = 0;

	}

};


//output: void
//input: vector<Node> q (safi az node haye dade)
//peymayesh safe mojod dar vorodi va print kardane etelate "h , cost" marbot be  har node
void PrintQueue(vector<Node> q)
{
	cout << endl;
	for (int i = 0; i < q.size(); i++)
	{
		cout << " h = " << q[i].h << " cost = " << q[i].cost << " ||";		
	}
	cout << endl;
}

//output: void
//input: vector<Node> q (safi az node haye dade)
//peymayesh safe mojod dar vorodi va sort kardane eleman haye an bar asase "h" har node
void sortVector(vector<Node> &v)
{
	int min_h = INT_MAX;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].h <= min_h)
		{
			min_h = v[i].h;
			Node tmp(v[i]);
			v.erase(v.begin() + i);
			v.emplace(v.begin(), tmp);
		}
	}
}


//output: void
//input: vector<Node> q (safi az node haye dade)
//peymayesh safe mojod dar vorodi va sort kardane eleman haye an bar asase "h+cost" har node
void sortVector2(vector<Node> &v)
{
	int min_h = INT_MAX;
	for (int i = 0; i < v.size(); i++)
	{
		if ((v[i].h+ v[i].cost)<= min_h)
		{
			min_h = (v[i].h + v[i].cost);
			Node tmp(v[i]);
			v.erase(v.begin() + i);
			v.emplace(v.begin(), tmp);

		}
	}
}


//baraye soholat dar kar yek class be name bazi tarif shodeh ast ta tamami
//tavabe morede nazar daron on tarif shavad va dar adres dehi ve meghdar dehi dochar eshtebah nashvim
class Hitori
{
private:
	//Orginal Data
	Node Data;

	//Priority-Queue for bfs algorithms
	vector<Node> Priority_Queue;

public:

	//Constructor
	Hitori();

	//Initialiser 
	void Initialization();

	//Function for printing matrix
	void PrintMatrix(Node State);
	
	//Functions for A* algorithm 
	void A_Star();
	void Cost(queue<Node> &TotalNeighbors);
	void Heuristic2(queue<Node> &TotalNeighbors);

	//Functions for Greedy algorithm 
	void Greedy();
	void Heuristic(queue<Node> &TotalNeighbors);
	
	//IsGoal Functions
	bool IsGoal(Node State);
	bool CheckSurround(Node State, int i, int j);

	//Successor Functions
	queue<Node> Successor(Node State);
	bool IsValid(Node State, int i, int j);
	bool FindNeighbors(Node State, int i, int j, queue<Node> &TotalNeighbors);


	void PrintResult(Node State);
};

void Hitori::PrintResult(Node State)
{
	PrintMatrix(State);
	printf("\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("*	how many node produced till now : %d \n", node_counter);
	printf("*	how many children this node has : %d \n", State.Children_counter);
	printf("*	how many cells cleared till now on this node : %d \n", State.cleared_cell_counter);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
}


//farakhanie tabe Initialization va PrintMatrix baraye khandane etelate 
//sample worodi va hmintor print kardane an
Hitori::Hitori()
{
	Initialization();
	PrintMatrix(Data);
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
			File >> Data.Matrix[i][j];
		}
	}

}


//output: void
//input: Node State (yek struct havi matris dade)
//khandane matris vorodi va chap on
void Hitori::PrintMatrix(Node State)
{
	cout << "\n ================= \n";
	for (int i = 1; i < _Size; i++)
	{
		cout << " ";
		for (int j = 1; j < _Size; j++)
		{
			cout << State.Matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << " ================= \n";
	//_getch();
}


//output : void
//input : -nothing-
//algorithm A* tebgh osol mojod dar hosh masnoei tarrahi va pyade sazi shode ast 
void Hitori::A_Star()
{
	//Check is the first state goal ?!
	if (IsGoal(Data) == true)
	{
		cout << " ===> End Game !!!" << endl;
		PrintResult(Data);
		return;
	}
	else
	{
		//push first state in Priority queue
		Priority_Queue.push_back(Data);
		node_counter++;

		while (Priority_Queue.empty() == false)
		{
			//tmp node for doing algorithm on it & get the first 
			//element of queue 
			Node tmp(Priority_Queue.front());
			Priority_Queue.erase(Priority_Queue.begin());

			//Check IsGoal on first node
			if (IsGoal(tmp) == true)
			{
				cout << " ===> End Game !!!" << endl;
				PrintResult(tmp);
				return;
			}
			else
			{
				//Find total neighbor states
				queue<Node> Neighbor_States = Successor(tmp);

				//Applying Heuristic Functions on All neighbors
				Heuristic(Neighbor_States);
				//Heuristic2(Neighbor_States);


				//Applying Cost "G(n)" Function on All neighbors
				Cost(Neighbor_States);

				//Adding all funded neighbor states to main queue
				while (Neighbor_States.empty() == false)
				{
					Neighbor_States.front().cleared_cell_counter++;

					Priority_Queue.push_back(Neighbor_States.front());
					Neighbor_States.pop();

					tmp.Children_counter++;
					node_counter++;

				}

				//sorting Priority Queue
				sortVector2(Priority_Queue);

				//PrintResult(tmp);
				//_getch();
			}
		}

		//if there is no any node to search and find true neighbors there is not answer to game
		if (Priority_Queue.empty() == true)
		{
			cout << " ===> Game didn't have any solution !!!" << endl;
			return;
		}
	}
}


//output : void
//input : -nothing-
//algorithm Greedy tebgh osol mojod dar hosh masnoei tarrahi va pyade sazi shode ast 
void Hitori::Greedy()
{
	//Check is the first state goal ?!
	if (IsGoal(Data) == true)
	{
		cout << " ===> End Game !!!" << endl;
		PrintResult(Data);
		return;
	}
	else
	{
		//push first state in Priority queue
		Priority_Queue.push_back(Data);
		node_counter++;

		while (Priority_Queue.empty() == false)
		{
			//tmp node for doing algorithm on it & get the first 
			//element of queue 
			Node tmp(Priority_Queue.front());
			Priority_Queue.erase(Priority_Queue.begin());
			
			//Check IsGoal on first node
			if (IsGoal(tmp) == true)
			{
				cout << " ===> End Game !!!" << endl;
				PrintResult(tmp);
				return;
			}
			else
			{
				//Find total neighbor states
				queue<Node> Neighbor_States = Successor(tmp);

				//Applying Heuristic Functions on All neighbors
				Heuristic(Neighbor_States);
				//Heuristic2(Neighbor_States);
				
				//Adding all funded neighbor states to main queue
				while (Neighbor_States.empty() == false)
				{
					Neighbor_States.front().cleared_cell_counter++;
					tmp.Children_counter++;
					node_counter++;

					Priority_Queue.push_back(Neighbor_States.front());
					Neighbor_States.pop();
				}

				//sorting Priority Queue
				sortVector(Priority_Queue);

				//PrintResult(tmp);
				//_getch();
			}

		}

		//if there is no any node to search and find true neighbors there is not answer to game
		if (Priority_Queue.empty() == true)
		{
			cout << " ===> Game didn't have any solution !!!" << endl;
			return;
		}
	}

}


//output : void
//input : queue<Node> &TotalNeighbors(safe tamame matris haye dade baraye anjame amalyat roye an)
//in function ba har bar farakhani meghdar cost baraye tamami eleman haye mojod daer safe vorodi ra yek vahed afzayesh midahd
//va in be in tabir ast ke yek level dar derakht jostejo paein tar rafteheim
void Hitori::Cost(queue<Node> &TotalNeighbors)
{
	queue<Node> tmp_queue(TotalNeighbors);
	queue<Node> tmp2_queue;

	while (tmp_queue.empty() == false)
	{
		Node tmp_node = tmp_queue.front();
		tmp_node.cost++;
		tmp2_queue.push(tmp_node);
		tmp_queue.pop();
	}
	TotalNeighbors = tmp2_queue;

}

//output : void
//input : queue<Node> &TotalNeighbors(safe tamame matris haye dade baraye anjame amalyat roye an)
//in function ba yek bar jostejoye satri va sotoni(kamel) tamai matris haye mojod dar safe vorodi ba residan be har onsore eshtebah
//(onsori ke daraye index yeksan dar satr ya soton ast) yek vahed be "h" an matris mi afzayad ke ba in tabir 
//onsor Goal ma ba nadashtn hich gone onsore eshtebahi "h=0" ast.
void Hitori::Heuristic(queue<Node> &TotalNeighbors)
{
	queue<Node> tmp_queue(TotalNeighbors);
	queue<Node> tmp2_queue;
	
	while (tmp_queue.empty() == false)
	{
		Node tmp_node = tmp_queue.front();
		tmp_node.h = 0;
		{
			for (int i = 1; i < _Size; i++)
			{
				for (int j = 1; j < _Size; j++)
				{
					int second_i = i;
					int second_j = j;
					int index = tmp_node.Matrix[i][j];
					if (index != 0)
					{
						//check horizontal
						if (j < (_Size - 1))
						{
							second_j = j + 1;
							while (second_j < _Size)
							{
								if (tmp_node.Matrix[i][second_j] == index)
								{
									tmp_node.h++;
								}
								second_j++;
							}
						}

						if (j > 1)
						{
							second_j = j - 1;
							while (second_j > 0)
							{
								if (tmp_node.Matrix[i][second_j] == index)
								{
									tmp_node.h++;
								}
								second_j--;
							}

						}
						second_j = j;

						//check vertical
						if (i < (_Size - 1))
						{
							second_i = i + 1;
							while (second_i < _Size)
							{
								if (tmp_node.Matrix[second_i][j] == index)
								{
									tmp_node.h++;
								}
								second_i++;
							}

						}

						if (i > 1)
						{
							second_i = i - 1;
							while (second_i > 0)
							{
								if (tmp_node.Matrix[second_i][j] == index)
								{
									tmp_node.h++;
								}
								second_i--;
							}
						}
						second_i = i;
					}
					
				}
			}
		}
		

		tmp2_queue.push(tmp_node);
		tmp_queue.pop();
	}
	TotalNeighbors = tmp2_queue;
}


//output : void
//input : queue<Node> &TotalNeighbors(safe tamame matris haye dade baraye anjame amalyat roye an)
//in function ba yek bar jostejoye faghat satri tamai matris haye mojod dar safe vorodi ba residan be har onsore eshtebah
//(onsori ke daraye index yeksan dar satr ya soton ast) yek vahed be "h" an matris mi afzayad ke ba in tabir 
//onsor Goal ma ba nadashtn hich gone onsore eshtebahi "h=0" ast.
void Hitori::Heuristic2(queue<Node> &TotalNeighbors)
{
	queue<Node> tmp_queue(TotalNeighbors);
	queue<Node> tmp2_queue;

	while (tmp_queue.empty() == false)
	{
		Node tmp_node = tmp_queue.front();
		tmp_node.h = 0;
		{
			for (int i = 1; i < _Size; i++)
			{
				for (int j = 1; j < _Size; j++)
				{
					int second_i = i;
					int second_j = j;
					int index = tmp_node.Matrix[i][j];
					if (index != 0)
					{
						//check horizontal
						if (j < (_Size - 1))
						{
							second_j = j + 1;
							while (second_j < _Size)
							{
								if (tmp_node.Matrix[i][second_j] == index)
								{
									tmp_node.h++;
								}
								second_j++;
							}
						}

						if (j > 1)
						{
							second_j = j - 1;
							while (second_j > 0)
							{
								if (tmp_node.Matrix[i][second_j] == index)
								{
									tmp_node.h++;
								}
								second_j--;
							}

						}
						second_j = j;

						
					}

				}
			}
		}


		tmp2_queue.push(tmp_node);
		tmp_queue.pop();
	}
	TotalNeighbors = tmp2_queue;

}


//output : queue<Node> (safe tamami hamsaye haye node vorodi)
//input : Node State (yek struct havi matris dade)
//Successor motabegh ba 3 algorithm BFS,DFS,IDS trahi va pyade sazi shode ast
queue<Node> Hitori::Successor(Node State)
{
	//holding the last index of each cell in matrix
	int last_index = 0;

	//out put queue
	queue<Node> TotalStates;


	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			//search each cell to find neighbors, if on node have any neighbors 
			//collect all neighbors in queue and return the queue
			if (State.Matrix[i][j] != 0 && FindNeighbors(State, i, j, TotalStates) == true)
			{
				last_index = State.Matrix[i][j];
				State.Matrix[i][j] = 0;

				//if clearing the cell is valid then we push it to queue
				if (IsValid(State, i, j) == true)
				{
					Node tmp_node(State);
					tmp_node.Matrix[i][j] = 0;
					TotalStates.push(tmp_node);
				}
				State.Matrix[i][j] = last_index;
				return TotalStates;
			}
		}
	}
	return TotalStates;
}


//output : bool (true ==> find some neighbors , false ==>cant find neighbors)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//		, queue<Node> &TotalNeighbor (safe hmsaye haye peyda shode)
//FindNeighbors motabegh ba Successor trahi va pyade sazi shode ast
bool Hitori::FindNeighbors(Node State, int i, int j, queue<Node> &TotalNeighbor)
{
	//seconf i and j to search the matris
	int second_i = i;
	int second_j = j;

	//holding the index of goal cell in function(mother node)
	int index = State.Matrix[i][j];

	//flag to now has same or not ?!
	bool has_same = false;

	//holding the last index of each cell in matrix
	int last_index = 0;
	//check horizontal
	if (j < (_Size - 1))
	{
		second_j = j + 1;
		while (second_j < _Size)
		{
			if (State.Matrix[i][second_j] == index)
			{
				last_index = State.Matrix[i][second_j];
				State.Matrix[i][second_j] = 0;

				//if clearing the cell is valid then we push it to queue
				if (IsValid(State, i, second_j) == true)
				{
					Node tmp_node(State);
					tmp_node.Matrix[i][second_j] = 0;
					TotalNeighbor.push(tmp_node);
				}
				State.Matrix[i][second_j] = last_index;

				has_same = true;
			}
			second_j++;
		}
	}

	if (j > 1)
	{
		second_j = j - 1;
		while (second_j > 0)
		{
			if (State.Matrix[i][second_j] == index)
			{
				last_index = State.Matrix[i][second_j];
				State.Matrix[i][second_j] = 0;

				//if clearing the cell is valid then we push it to queue
				if (IsValid(State, i, second_j) == true)
				{
					Node tmp_node(State);
					tmp_node.Matrix[i][second_j] = 0;
					TotalNeighbor.push(tmp_node);
				}
				State.Matrix[i][second_j] = last_index;
				has_same = true;
			}
			second_j--;
		}

	}
	second_j = j;

	//check vertical
	if (i < (_Size - 1))
	{
		second_i = i + 1;
		while (second_i < _Size)
		{
			if (State.Matrix[second_i][j] == index)
			{
				last_index = State.Matrix[second_i][j];
				State.Matrix[second_i][j] = 0;

				//if clearing the cell is valid then we push it to queue
				if (IsValid(State, second_i, j) == true)
				{
					Node tmp_node(State);
					tmp_node.Matrix[second_i][j] = 0;
					TotalNeighbor.push(tmp_node);
				}
				State.Matrix[second_i][j] = last_index;
				has_same = true;
			}
			second_i++;
		}

	}

	if (i > 1)
	{
		second_i = i - 1;
		while (second_i > 0)
		{
			if (State.Matrix[second_i][j] == index)
			{
				last_index = State.Matrix[second_i][j];
				State.Matrix[second_i][j] = 0;

				//if clearing the cell is valid then we push it to queue
				if (IsValid(State, second_i, j) == true)
				{
					Node tmp_node(State);
					tmp_node.Matrix[second_i][j] = 0;
					TotalNeighbor.push(tmp_node);
				}
				State.Matrix[second_i][j] = last_index;
				has_same = true;

			}
			second_i--;
		}
	}
	second_i = i;

	if (has_same == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//output : bool (true ==> valid to clear cell , false ==> not valid to clear cell)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//IsValid motabegh ba Successor , FindNeighbors trahi va pyade sazi shode ast
bool Hitori::IsValid(Node State, int i, int j)
{
	//check right
	if (j + 1 < _Size && State.Matrix[i][j + 1] == 0)
	{
		return false;
	}

	//check left
	else if (j - 1 > 0 && State.Matrix[i][j - 1] == 0)
	{
		return false;
	}

	//check down
	else if (i + 1 < _Size && State.Matrix[i + 1][j] == 0)
	{
		return false;
	}

	//check up
	else if (i - 1 > 0 && State.Matrix[i - 1][j] == 0)
	{
		return false;
	}

	//check surrounded-up
	else if (CheckSurround(State, i - 1, j) == true)
	{
		return false;
	}

	//check surrounded-down
	else if (CheckSurround(State, i + 1, j) == true)
	{
		return false;
	}

	//check surrounded-right
	else if (CheckSurround(State, i, j + 1) == true)
	{
		return false;
	}

	//check surrounded-left
	else if (CheckSurround(State, i, j - 1) == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//output : bool (true ==> Surround with black cells , false ==> not Surround with black cells)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//CheckSurround motabegh ba IsValid trahi va pyade sazi shode ast
bool Hitori::CheckSurround(Node State, int i, int j)
{
	//left-up corner
	if (i - 1 == 0 && j - 1 == 0 && (State.Matrix[i + 1][j] == 0 && State.Matrix[i][j + 1] == 0))
	{
		return true;
	}
	//up wall corner
	else if (i - 1 == 0 && (j - 1 > 0 && j + 1 < _Size) && (State.Matrix[i][j - 1] == 0 && State.Matrix[i][j + 1] == 0 && State.Matrix[i + 1][j] == 0))
	{
		return true;
	}
	//right-up corner
	else if (i - 1 == 0 && j + 1 == _Size && (State.Matrix[i + 1][j] == 0 && State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//right wall corner
	else if (j + 1 == _Size && (i - 1 > 0 && i + 1 < _Size) && (State.Matrix[i + 1][j] == 0 && State.Matrix[i - 1][j] == 0 && State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//right-down corner
	else if (i + 1 == _Size && j + 1 == _Size && (State.Matrix[i - 1][j] == 0 && State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//down wall corner
	else if (i + 1 == _Size && (j - 1 > 0 && j + 1 < _Size) && (State.Matrix[i][j - 1] == 0 && State.Matrix[i][j + 1] == 0 && State.Matrix[i - 1][j] == 0))
	{
		return true;
	}
	//left-down corner
	else if (i + 1 == _Size && j - 1 == 0 && (State.Matrix[i - 1][j] == 0 && State.Matrix[i][j + 1] == 0))
	{
		return true;
	}
	//left wall corner
	else if (j - 1 == 0 && (i - 1 > 0 && i + 1 < _Size) && (State.Matrix[i + 1][j] == 0 && State.Matrix[i - 1][j] == 0 && State.Matrix[i][j + 1] == 0))
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
bool Hitori::IsGoal(Node State)
{
	int index = 0;
	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			index = State.Matrix[i][j];
			if (index != 0)
			{
				//check vertical
				if (i < (_Size - 1))
				{
					int second_i = i + 1;
					while (second_i < _Size)
					{
						if (State.Matrix[second_i][j] == index)
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
						if (State.Matrix[second_i][j] == index)
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
						if (State.Matrix[i][second_j] == index)
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
						if (State.Matrix[i][second_j] == index)
						{
							return false;
						}
						second_j--;
					}
				}

			}

		}
	}
	return true;

}


int main()
{
	
	Hitori MyHitori;
	{
		using namespace std::chrono_literals;
		auto start = chrono::high_resolution_clock::now();



		//MyHitori.Greedy();
		MyHitori.A_Star();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;

		printf(" ==> time is : %f ms \n", elapsed.count());
	}

	_getch();
	return 0;
}
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

//_Number_Of_Black => tedad selol haey ke mikhahim dar tolid javab random syah konim
#define _Number_Of_Black 20

//e => add neper
#define e    2.7182818284
int node_counter = 0;


//sakhteman dade dar nazar gerefte shode baraye in ghesmate poroje yek 
//struct az noe matris 2 bodeie az jense integer mibashd ke yek 
//constructor mamoli va yek copy constructor niz
//baraye an tarif shode ast
struct Node
{
	int** Matrix;
	int h;
	int cleared_cell_counter;
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
		cleared_cell_counter = tmp.cleared_cell_counter;
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

public:
	//Constructor
	Hitori();

	//Initialiser 
	void Initialization();

	//Functions for printing matrix
	void PrintMatrix(Node _State);
	void PrintResult(Node _State);

	//Function for generating random complete answer
	Node Random_State(Node _State);

	//Simulated Annealing Function
	void Simulated_Annealing();

	//Hill Climb Function
	void HillClimbing();
	
	//Successor Functions
	vector<Node> Successor(Node _State);

	//Heuristic Function 
	int Heuristic(Node _State);
	bool IsValid(Node _State, int i, int j);
	bool CheckSurround(Node _State, int i, int j);

};

//farakhanie tabe Initialization va PrintMatrix baraye khandane etelate 
//sample worodi va hmintor print kardane an
Hitori::Hitori()
{
	Initialization();

	_Data.h = Heuristic(_Data);
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
			File >> _Data.Matrix[i][j];
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
			cout << _State.Matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << " ================= \n";
	cout << " ===> h = " << _State.h << "\n";
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


//output: Node (yek struct havi matris dade)
//input: Node State (yek struct havi matris dade)
//tolide yek node kamele payani ke bazi az selol haye an 
//be sorate random hazf shodeh and
Node Hitori::Random_State(Node _State)
{
	Node tmp_State(_State);
	vector<int> Which_Elements;
	int Random_Element;
	int Number_Of_Black = _Number_Of_Black;
	bool Found_Flag = false;

	int lowest_i = 1;
	int highest_i = pow((_Size - 1), 2);

	

	while (Number_Of_Black != 0)
	{

		Random_Element = (rand() % ((highest_i - lowest_i) + 1)) + lowest_i;

		Found_Flag = false;
		for (int k = 0; k < Which_Elements.size(); k++)
		{
			if (Which_Elements[k] == Random_Element)
			{
				Found_Flag = true;
				break;
			}
		}
		if (Found_Flag == false)
		{
			Which_Elements.push_back(Random_Element);
			Number_Of_Black--;
		}
	}


	int Element = 1;
	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			for (int z = 0; z < Which_Elements.size(); z++)
			{
				if (Which_Elements[z] == Element)
				{
					tmp_State.Matrix[i][j] = 0;
					break;
				}
			}
			Element++;
		}
	}
	tmp_State.cleared_cell_counter = tmp_State.cleared_cell_counter + Which_Elements.size();
	return tmp_State;
}


//output : void
//input : -nothing-
//algorithm HillClimbing tebgh osol mojod dar hosh masnoei tarrahi va pyade sazi shode ast 
void Hitori::HillClimbing()
{
	vector<Node> Neighbor_States;

	Node Current_node(Random_State(_Data));
	Current_node.h = Heuristic(Current_node);

	Node Next_node;
	

	//cout << "\n ===> First State generated:";
	//PrintMatrix(Current_node);
	//_getch();
	


	while (true)
	{
		//Find total neighbor states
		Neighbor_States = Successor(Current_node);
		node_counter = node_counter + Neighbor_States.size();
		
		int Max_Heuristic = -INT_MAX;
		int Selected_Element;
		
		for (int i = 0; i < Neighbor_States.size(); i++)
		{
			if (Neighbor_States[i].h > Max_Heuristic)
			{
				Selected_Element = i;
				Max_Heuristic = Neighbor_States[i].h;
			}
		}
		Next_node = Neighbor_States[Selected_Element];
		Neighbor_States.clear();

		
		
	
		if (Next_node.h <= Current_node.h)
		{
			if (Current_node.h == 0)
			{
				cout << "\n ===> End Game !!!";
				PrintResult(Current_node);
				return;
			}
			else
			{
				cout << "\n ===> Local Maximum !!!";
				PrintResult(Current_node);
				return;
			}
			
		}
		else
		{
			Current_node = Next_node;
			
		}
		
		//cout << "\n ===> Minimum till now:";
		//PrintResult(Current_node);
		//_getch();
	}
		
	
			
}


//output : void
//input : -nothing-
//algorithm Simulated_Annealing tebgh osol mojod dar hosh masnoei tarrahi va pyade sazi shode ast 
void Hitori::Simulated_Annealing()
{
	vector<Node> Neighbor_States;

	int lowest_i = 0;
	int highest_i = (pow((_Size - 1), 2)) - 1;
	int Random_Element;
	int Total_h = 0;
	float T;
	int t = 1;
	float E_current;
	float E_next;
	int Delta_E;

	float randomNumber;
	float Eval;
	Node Current_node(Random_State( _Data));
	Current_node.h = Heuristic(Current_node);

	Node Next_node;

	//cout << "\n ===> First State generated:";
	//PrintMatrix(Current_node);
	//_getch();
	

	T = -abs(t)+50;
	while (T >= 0)
	{		
		T = -abs(t) +50;
		if (T == 0)
		{
			cout << "\n ===> End !!! <T = " << T << ">";
			PrintResult(Current_node);
			return;
		}
		//Find total neighbor states
		Neighbor_States = Successor(Current_node);

		node_counter = node_counter + Neighbor_States.size();
		

		Random_Element = (rand() % ((highest_i - lowest_i) + 1)) + lowest_i;
		
		Next_node = Neighbor_States[Random_Element];
		

		

		E_current = Current_node.h;
		E_next = Next_node.h;
		Delta_E = E_next - E_current;
		if (Delta_E > 0)
		{
			Current_node = Next_node;
		}
		else
		{
			randomNumber = 0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - 0)));
			
			Eval = pow(e, (Delta_E / T));
			/*cout << "\n Delta_E: " << Delta_E << endl;
			cout << " t: " << t << endl;
			cout << " T: " << T << endl;
			cout << " Eval: " << Eval<< endl;
			cout << " randomNumber: " << randomNumber<< endl;*/
			
			if (Eval <= randomNumber)
			{
				//cout << " ================> Selected !!! " << endl;
				Current_node = Next_node;
				
			}
			//_getch();
		}
		//cout << "\n ===> Selected till now:";
		//PrintMatrix(Current_node);
		//_getch();
		t++;
	}
	
}


//output : vector<Node> (list tamami hamsaye haye node vorodi)
//input : Node State (yek struct havi matris dade)
//Successor motabegh ba 2 algorithm HillClimbing,Simulated_Annealing trahi va pyade sazi shode ast
vector<Node> Hitori::Successor(Node _State)
{
	//out put queue
	vector<Node> TotalStates;

	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			Node tmp_node(_State);
			if (_State.Matrix[i][j] == 0)
			{
				//cout << "\n ===> Element " << i << "," << j << " has change from " << _State.Matrix[i][j] << " to "<< _Data.Matrix[i][j]; 
				tmp_node.Matrix[i][j] = _Data.Matrix[i][j];
				tmp_node.cleared_cell_counter--;
			}
			else
			{
				//cout << "\n ===> Element " << i << "," << j << " has change from " << _State.Matrix[i][j] << " to " << 0;
				tmp_node.Matrix[i][j] = 0;
				tmp_node.cleared_cell_counter++;
			}
			tmp_node.h = Heuristic(tmp_node);
			
			TotalStates.push_back(tmp_node);
			//PrintMatrix(tmp_node);
			//_getch();
		}
	}

	return TotalStates;
}


//output : void
//input : Node _State(matris dade baraye anjame amalyat roye an)
//in function ba yek bar jostejoye satri va sotoni(kamel) matris mojod ba residan be har onsore eshtebah
//(onsori ke daraye index yeksan dar satr ya soton ast) yek vahed az "h" an matris kam mikonad hamchenin 
//hamchenin agar onsori megdare an barabar ba sefr bud baraye on az functione IsValid estefade karde va
// dar sorati ke valid nabashad megdare h an matris ra 100 vahed kam mikonad ke ba in tabir 
//onsor Goal ma ba nadashtn hich gone onsore eshtebahi "h=0" ast.
int Hitori::Heuristic(Node _State)
{
	int index = 0;
	int tmp_h = 0;
	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			index = _State.Matrix[i][j];
			if (index != 0)
			{
				//check vertical
				if (i < (_Size - 1))
				{
					int second_i = i + 1;
					while (second_i < _Size)
					{
						if (_State.Matrix[second_i][j] == index)
						{
							tmp_h--;
						}
						second_i++;
					}

				}
				if (i > 1)
				{
					int second_i = i - 1;
					while (second_i > 0)
					{
						if (_State.Matrix[second_i][j] == index)
						{
							tmp_h--;
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
						if (_State.Matrix[i][second_j] == index)
						{
							tmp_h--;
						}
						second_j++;
					}
				}
				if (j > 1)
				{
					int second_j = j - 1;
					while (second_j > 0)
					{
						if (_State.Matrix[i][second_j] == index)
						{
							tmp_h--;
						}
						second_j--;
					}
				}

			}

		}
	}

	//check zero values
	for (int i = 1; i < _Size; i++)
	{
		for (int j = 1; j < _Size; j++)
		{
			if (_State.Matrix[i][j] == 0)
			{
				if (IsValid(_State, i, j) == false)
				{
					tmp_h = tmp_h - 100;
				}
			}
		}
	}
	return tmp_h;
	
}


//output : bool (true ==> valid to clear cell , false ==> not valid to clear cell)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//IsValid motabegh ba Successor , FindNeighbors trahi va pyade sazi shode ast
bool Hitori::IsValid(Node _State, int i, int j)
{
	//check right
	if (j + 1 < _Size && _State.Matrix[i][j + 1] == 0)
	{
		return false;
	}

	//check left
	else if (j - 1 > 0 && _State.Matrix[i][j - 1] == 0)
	{
		return false;
	}

	//check down
	else if (i + 1 < _Size && _State.Matrix[i + 1][j] == 0)
	{
		return false;
	}

	//check up
	else if (i - 1 > 0 && _State.Matrix[i - 1][j] == 0)
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


//output : bool (true ==> Surround with black cells , false ==> not Surround with black cells)
//input : Node State(matris dade asli)
//		, int i, int j(mogheyat haye selole morede nazar)
//CheckSurround motabegh ba IsValid trahi va pyade sazi shode ast
bool Hitori::CheckSurround(Node _State, int i, int j)
{
	//left-up corner
	if (i - 1 == 0 && j - 1 == 0 && (_State.Matrix[i + 1][j] == 0 && _State.Matrix[i][j + 1] == 0))
	{
		return true;
	}
	//up wall corner
	else if (i - 1 == 0 && (j - 1 > 0 && j + 1 < _Size) && (_State.Matrix[i][j - 1] == 0 && _State.Matrix[i][j + 1] == 0 && _State.Matrix[i + 1][j] == 0))
	{
		return true;
	}
	//right-up corner
	else if (i - 1 == 0 && j + 1 == _Size && (_State.Matrix[i + 1][j] == 0 && _State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//right wall corner
	else if (j + 1 == _Size && (i - 1 > 0 && i + 1 < _Size) && (_State.Matrix[i + 1][j] == 0 && _State.Matrix[i - 1][j] == 0 && _State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//right-down corner
	else if (i + 1 == _Size && j + 1 == _Size && (_State.Matrix[i - 1][j] == 0 && _State.Matrix[i][j - 1] == 0))
	{
		return true;
	}
	//down wall corner
	else if (i + 1 == _Size && (j - 1 > 0 && j + 1 < _Size) && (_State.Matrix[i][j - 1] == 0 && _State.Matrix[i][j + 1] == 0 && _State.Matrix[i - 1][j] == 0))
	{
		return true;
	}
	//left-down corner
	else if (i + 1 == _Size && j - 1 == 0 && (_State.Matrix[i - 1][j] == 0 && _State.Matrix[i][j + 1] == 0))
	{
		return true;
	}
	//left wall corner
	else if (j - 1 == 0 && (i - 1 > 0 && i + 1 < _Size) && (_State.Matrix[i + 1][j] == 0 && _State.Matrix[i - 1][j] == 0 && _State.Matrix[i][j + 1] == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	srand(static_cast <unsigned> (time(0)));
	Hitori MyHitori;

	{
		using namespace std::chrono_literals;
		auto start = chrono::high_resolution_clock::now();

		//MyHitori.HillClimbing();
		MyHitori.Simulated_Annealing();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;

		printf(" ==> time is : %f ms \n", elapsed.count());
	}

	

	_getch();
	return 0;
}
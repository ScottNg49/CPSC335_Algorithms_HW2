/* CPSC335-04_Project2_Pitcher's 
/ Team Name   : Scott Ng
/ Class       : CPSC 335-04
/ Contents    : Source.cpp 
/ Team Members: Scott Ng
/ Contact     : scottng49@csu.fullerton.edu
/ Description : Pitcher's Addendum
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isEmpty(int argv)
{
	if (argv == 0)
		return true;
	else
		return false;
};

bool isFull(int argv, int position)
{
	int pitcher_max[] = { 16, 9 ,7 };

	if (argv == pitcher_max[position])
		return true;
	else
		return false;
};

bool check_prior(int temp[], int previous_combination[99][3], int combinations)
{
	int temp_var = 0;
	for (int i = 0; i < combinations; i++)
	{
		temp_var = 0;
		for (int j = 0; j < 3; j++)
		{
			if (temp[j] == previous_combination[i][j])
				temp_var++;

			if (temp_var >= 3)
				return true;
		}
	}
	return false;
};

void save_combination(int temp[], int (&previous_combination)[99][3], int combinations)
{
	for (int i = 0; i < 3; i++)
	{
		previous_combination[combinations][i] = temp[i];
	};
};

void output(int argv[])
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << argv[i] << " ";
	};
	std::cout << endl;
};

void output_previous(int argv[][3], int combinations)
{
	cout << "Previous Combinations : [\n";
	for (int i = 0; i < combinations; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << argv[i][j] << " ";
		}
		cout << '\n';
	}
	cout << "]\n";
};

bool is_equal(int my_array[], int argv[])
{
	for (int i = 0; i < 3; i++)
	{
		if (my_array[i] != argv[i])
			return false;
	}
	return true;
}

int main()
{
	int user_array[] = { 16, 0, 0 },
		pitcher_max[] = { 16, 9 ,7 },
		row = 0,
		previous_combinations[99][3],
		combinations = 1;

	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 3; j++)
			previous_combinations[i][j] = 0;
	}

	previous_combinations[0][0] = 16, previous_combinations[0][1] = 0, previous_combinations[0][2] = 0;


	string InputArray;

	int my_array[3];
	cout << "Enter a combination of integers: ";
	getline(cin, InputArray);

	stringstream ss(InputArray);
	string s;

	//parses string by delimiter whitespace
	int t = 0;
	while (getline(ss, s, ' ')) {
		my_array[t] = stoi(s);
		t++;
	}

	while (row < 50)
	{
		int temp[3];
		int steps = combinations;

		for (int z = 0; z < steps; z++)
		{
			memcpy(user_array, previous_combinations[z], sizeof(user_array));
			for (int i = 0; i < 3; i++)
			{
				memcpy(temp, user_array, sizeof(user_array) * 3);
				for (int j = 0; j < 3; j++)
				{
					memcpy(temp, user_array, sizeof(user_array) * 3);
					if (i != j)
					{
						if (!isEmpty(temp[i]))
						{
							if (!isFull(temp[j], j))
							{
								int pour = pitcher_max[j] - temp[j];

								if (pour > temp[i])
								{
									temp[j] += temp[i];
									temp[i] = 0;
								}

								else if (pour <= temp[i])
								{
									temp[j] += pour;
									temp[i] -= pour;
								}

								if (!check_prior(temp, previous_combinations, combinations))
								{
									// if false then save
									output(temp);
									save_combination(temp, previous_combinations, combinations);
									combinations++;
								}

								if (is_equal(my_array, temp))
								{
									cout << "The combination was found in " << (row + 1) << "steps\n";
									system("pause");
									exit(0);
								}
							}
						}
					}
				}
			}
		}
		
		row++;
	}

	cout << "The combination was not found\n";

	system("pause");
	return 0;
};
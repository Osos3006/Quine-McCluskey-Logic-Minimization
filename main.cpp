#include <iostream>
#include <fstream>
#include "binary_number.h"
#include<string>
#include<vector>

using namespace std;

void create_MinTable(vector<vector<binary_number>>& A,vector<unsigned>&, int size);
//void print_MinTable();
void create_combined();
void print_combined();//***
void print_withDashes();
void create_finalTable();
void print_finalTable();
void print_finalMinterms();
//bool is_printed();
//void init(); //start the table making and printing
//void getinput(); //get input from user
//unsigned count_bits(unsigned n); //min bits to represent a number
vector<vector<binary_number>> Initial_table;   //vector of vectors - each vector inside represents a group according to the number of ones
vector<vector<binary_number>>& mid_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the mid process table
int num_of_var; //number of variables
int main()
{

	
	
	int mint;  //minterm 
	int dont_c;  //don't care
	vector<unsigned> minterms, dontcares, inputs;   //vector of minterms and dont cares
	int num_of_mins = 0, num_of_dc = 0;

	ifstream minterms_file("minterms.txt");

	if (minterms_file.is_open())
	{
		minterms_file >> num_of_var;
		char c;

		minterms_file.get(c);
		minterms_file.get(c);

		while (!minterms_file.eof())  //end of line
		{
			if (!(c == ',' || c == ' ' || c == '\n'))
			{
				mint = int(c) - 48;
				minterms.push_back(mint);
				num_of_mins++;
			}
			else
				if (c == '\n')
				{
					minterms_file.get(c);
					if (!(c == ',' || c == ' '))
					{
						dont_c = int(c) - 48;
						dontcares.push_back(dont_c);
						num_of_dc++;

					}

				}
			minterms_file.get(c);
		}
	}
	minterms_file.close();

	int total_num = num_of_mins + num_of_dc;

	for (int i = 0; i < num_of_mins; i++)
		inputs.push_back(minterms[i]);
	for (int i = 0; i < num_of_dc; i++)
		inputs.push_back(dontcares[i]);


	create_MinTable(Initial_table, inputs, total_num);

	for (int i = 0; i < Initial_table.size(); i++)
		for (int j = 0; j < Initial_table[i].size(); j++)
			cout << Initial_table[i][j].num << endl;
	system("pause");

	return 0;
}

void create_MinTable(vector<vector<binary_number>>& A,  vector<unsigned>& inputs, int size)
{

	binary_number temp;
	int number_of_ones;

	for (int i = 0; i < size; i++)
	{
		number_of_ones = 0;
		binary_number temp(inputs[i]);
		number_of_ones = temp.count_ones(); //****
		if (number_of_ones + 1 > A.size())
			A.resize(number_of_ones + 1);
		A[number_of_ones].push_back(temp);
	}


	
}

void create_combined()
{
	short temp;
	binary_number temp_num;
	for (int i = 0; i < Initial_table.size() - 1; i++)
		for (int j = 0; j < Initial_table[i].size(); j++)
			for (int k = 0; k < Initial_table[i + 1].size(); k++)
			{
				temp_num.num = Initial_table[i][j].num & Initial_table[i + 1][k].num;
				temp_num.dashes = Initial_table[i][j].num ^ Initial_table[i + 1][k].num;
				if (temp_num.count_ones(temp_num.dashes) == 1)
				{
					Initial_table[i][j].is_used = true;
					Initial_table[i + 1][k].is_used = true;


					temp = temp_num.count_ones(temp_num.num);
					if (temp + 1 > mid_table.size)
						mid_table.resize(temp + 1);

					temp_num.is_used = false;
					mid_table[temp].push_back(temp_num);
				}
			}
}



void print_combined()
{
	cout << endl << "MID PROCESS COMPUTATION:" << endl;
	for (int i = 0; i < mid_table.size(); i++) 
	{
		cout << i;
		for (int j = 0; j < mid_table[i].size(); j++) {
			cout << "\t\t";
			//print_p_binary(p_group[i][j].number, p_group[i][j].dashes);
			mid_table[i][j].print_with_dashes(num_of_var);
			cout << endl;
		}
		cout << "\n-------------------------------------" << endl;
	}
}



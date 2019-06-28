#include <iostream>
#include <fstream>
#include "binary_number.h"
#include<string>
#include<vector>

using namespace std;

void create_MinTable(vector<vector<binary_number>>& A,vector<unsigned>&, int size);
void print_MinTable(vector<vector<binary_number>>& A, int Binsize);
void create_combined();
void print_combined();//***
void print_withDashes();
void create_final_table();
void print_final_table();
void print_finalMinterms();
bool is_printed(binary_number);
//void init(); //start the table making and printing
//void getinput(); //get input from user
//unsigned count_bits(unsigned n); //min bits to represent a number
vector<vector<binary_number>> Initial_table;   //vector of vectors - each vector inside represents a group according to the number of ones
vector<vector<binary_number>> mid_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the mid process table
vector<binary_number> printed_numbers; // vector that has printed numbers
vector<vector<binary_number>> final_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the final table for prime implicants

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

				string a = "";



				while (!(c == ',' || c == ' ' || c == '\n'))

				{

					a = a + c;

					minterms_file.get(c);

				}



				mint = atoi(a.c_str());

				minterms.push_back(mint);

				num_of_mins++;

			}



			if (c == '\n')

			{

				string b = "";



				while (!(c == ',' || c == ' ' || c == '\n'))

				{

					b = b + c;

					minterms_file.get(c);

				}



				dont_c = atoi(b.c_str());

				dontcares.push_back(dont_c);

				num_of_dc++;

				minterms_file.get(c);







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
	print_MinTable(Initial_table, num_of_var);
	create_combined();
	print_combined();
	create_final_table();
	print_final_table();

	/*bool flag = false;
	while (!flag)
	{
		create_combined();
		print_combined();
	}*/

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
		number_of_ones = temp.count_ones(inputs[i]); //****
		if (number_of_ones + 1 > A.size())
			A.resize(number_of_ones + 1);
		A[number_of_ones].push_back(temp);
	}


	
}


void print_MinTable(vector<vector<binary_number>>& A, int s)
{

	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
		{
			A[i][j].print_number(s);
			cout << endl;
		}
}

/*like the original table, but the paring of numbers from the original tabledashes
are represented by a 1. for example original A=0011 B=1011, new number
is -011 which is represented as C.number=A&B=0011,C.dashes=A^B=1000*/

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
					if (temp + 1 > mid_table.size())
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
			//print_p_binary(p_group[i][j].number, p_group[i][j].dashes);
			if (!is_printed(mid_table[i][j]))
			{
				cout << "\t\t";
				mid_table[i][j].print_with_dashes(num_of_var);
				printed_numbers.push_back(mid_table[i][j]);
				cout << endl;
			}

			
		}
		cout << "\n-------------------------------------" << endl;
	}
}
bool is_printed(binary_number n) {
	for (int i = 0; i < printed_numbers.size(); i++)
		if (n.num == printed_numbers[i].num && n.dashes ==
			printed_numbers[i].dashes)
			return true;
	return false;
}

/*creates final table. works like p_group(). example; in p_group you have:
A=-001 B=-011 -> C= -0-1 which will be represented as
C.number=A&B=0001&0011=0001, and
C.dashes=A^B^A.dashes=0001^0011^1000=1010.
Computation is done only when A.dashes = b.dashes*/

void create_final_table()
{
	short temp;
	binary_number temp_num;
	unsigned temp_number, temp_dashes;
	for (int i = 0; i < mid_table.size() - 1; i++)
		for (int j = 0; j < mid_table[i].size(); j++)
			for (int k = 0; k < mid_table[i + 1].size(); k++)
			{
				if (mid_table[i][j].dashes == mid_table[i + 1][k].dashes) {
					temp_num.num = mid_table[i][j].num & mid_table[i + 1][k].num;
					temp_num.dashes = mid_table[i][j].num ^ mid_table[i + 1][k].num;
					if (temp_num.count_ones(temp_num.dashes) == 1)
					{
						temp_num.dashes ^= mid_table[i][j].dashes;
						mid_table[i][j].is_used = true;
						mid_table[i + 1][k].is_used = true;
						temp = temp_num.count_ones(temp_num.num);
						if (temp + 1 > final_table.size())
							final_table.resize(temp + 1);
						temp_num.is_used = true;
						final_table[temp].push_back(temp_num);
					}

				}
			}
}


/*print all the values from the final table, except for duplicates.
print all the unused numbers from original table and mid process table*/

void print_final_table()
{
	cout << endl << "FINAL:\n-------------------------------------" << endl;
	int i, j;
	for (i = 0; i < final_table.size(); i++) 
	{
		cout << i; 
		for (j = 0; j < final_table[i].size(); j++) {
			if (!is_printed(final_table[i][j]))
			{
				cout << "\t\t";
				final_table[i][j].print_with_dashes(num_of_var);
				cout << endl;
				printed_numbers.push_back(final_table[i][j]);
			}
		}

		cout << "\n-------------------------------------" << endl;
	}

	cout << " printing unused from mid table" << endl;
	for (i = 0; i < mid_table.size(); i++)
	{

		for (j = 0; j < mid_table[i].size(); j++)
		{
			if (!mid_table[i][j].is_used)
			{
				cout << i;
				cout << "\t\t";
				mid_table[i][j].print_with_dashes(num_of_var);
				cout << endl;
				cout << "\n-------------------------------------" << endl;

			}
		}
	}

	cout << " printing unused from initial table" << endl;

	for (i = 0; i < Initial_table.size(); i++)
	{
		
		for (j = 0; j < Initial_table[i].size(); j++)
			if (!Initial_table[i][j].is_used)
			{
				cout << i;
				cout << "\t\t";
				//print_p_binary(table[i][j].number, table[i][j].dashes);
				Initial_table[i][j].print_with_dashes(num_of_var);
				cout << endl;
				cout << "\n-------------------------------------" << endl;
			}
		
	}
		
	
	//cout << "-------------------------------------" << endl;
}
		


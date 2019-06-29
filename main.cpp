#include <iostream>
#include <fstream>
#include "binary_number.h"
#include<string>
#include<vector>
using namespace std;
void create_MinTable(vector<vector<binary_number>>& A, vector<unsigned>&, int size);
void print_MinTable(vector<vector<binary_number>>& A, int Binsize);
void create_combined(vector<vector<binary_number>>& Initial_table, vector<vector<binary_number>>& mid_table);
void print_combined(vector<vector<binary_number>>& mid_table, vector<binary_number>& printed_numbers);
void print_withDashes();
void create_final_table(vector<vector<binary_number>>& mid_table, vector<vector<binary_number>>& final_table, vector<binary_number>& printed_numbers);
void print_final_table(vector<vector<binary_number>>& Initial_table, vector<vector<binary_number>>& mid_table, vector<vector<binary_number>>& final_table, vector<binary_number>& printed_numbers);
void print_finalMinterms(vector<vector<binary_number>>& mid_table);
bool is_printed(binary_number n, vector<binary_number>& printed_numbers);
bool is_essential(binary_number x, int group, int pos, vector<vector<binary_number>>& primes, vector<unsigned>& minterms);
bool minterm_exists(binary_number t, int x, int group, int pos, vector<vector<binary_number>>& primes, vector<unsigned>& minterms);
bool is_minterm(int x, vector<unsigned>& minterms);
bool in_essentials(binary_number x, vector<binary_number>essentials);
bool covered_by_essential(int x, vector<binary_number> essentials);


//void init(); //start the table making and printing
//void getinput(); //get input from user
//unsigned count_bits(unsigned n); //min bits to represent a number
//vector<vector<binary_number>> Initial_table;   //vector of vectors - each vector inside represents a group according to the number of ones
//vector<vector<binary_number>> mid_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the mid process table
//vector<binary_number> printed_numbers; // vector that has printed numbers
//vector<vector<binary_number>> final_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the final table for prime implicants
//vector<binary_number> cov_minDC;  // vector of type binary that has all the final binary numbers with there covered minterms
int num_of_var; //number of variables
int main()
{
	vector<vector<binary_number>> Initial_table;   //vector of vectors - each vector inside represents a group according to the number of ones
	vector<vector<binary_number>> mid_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the mid process table
	vector<binary_number> printed_numbers; // vector that has printed numbers
	vector<vector<binary_number>> final_table;  // vector of vectors - each vector inside represents a group according to the number of ones and this is the final table for prime implicants


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
				// num_of_mins++;

			}

			if (c == '\n')
			{
				minterms_file.get(c);

				string b = "";
				while (!(c == ',' || c == ' ' || c == '\n'))

				{
					b = b + c;
					minterms_file.get(c);
				}
				if (b != "")
				{
					dont_c = atoi(b.c_str());
					dontcares.push_back(dont_c);
				}
				// num_of_dc++;
				minterms_file.get(c);
			}

			minterms_file.get(c);

		}

	}

	minterms_file.close();

	int total_num = minterms.size() + dontcares.size();

	for (int i = 0; i < minterms.size(); i++)
		inputs.push_back(minterms[i]);
	for (int i = 0; i < dontcares.size(); i++)
		inputs.push_back(dontcares[i]);


	create_MinTable(Initial_table, inputs, total_num);
	print_MinTable(Initial_table, num_of_var);
	//create_combined(Initial_table, mid_table);
	//print_combined(mid_table,printed_numbers);
	// create_final_table(mid_table,final_table, printed_numbers);
	// print_final_table( Initial_table,  mid_table,  final_table, printed_numbers);

	//create initial table 
	// 

	bool final = false;
	binary_number temp_num;

	while (!final)
	{
		create_combined(Initial_table, mid_table);
		// print_combined(Initial_table, printed_numbers);
		if (mid_table.empty())
		{
			for (int i = 0; i < Initial_table.size(); i++)
				for (int j = 0; j < Initial_table[i].size(); j++)
				{
					temp_num = Initial_table[i][j];
					int temp = temp_num.count_ones(temp_num.num);
					if (temp + 1 > final_table.size())
						final_table.resize(temp + 1);
					final_table[temp].push_back(temp_num);

					// final_table[i].push_back(Initial_table[i][j]);

				}
			final = true;
		}
		else
			for (int i = 0; i < Initial_table.size(); i++)
				for (int j = 0; j < Initial_table[i].size(); j++)
				{
					if (!Initial_table[i][j].is_used)
					{
						temp_num = Initial_table[i][j];
						int temp = temp_num.count_ones(temp_num.num);
						if (temp + 1 > final_table.size())
							final_table.resize(temp + 1);
						final_table[temp].push_back(temp_num);
						//final_table[i].push_back(Initial_table[i][j]);
					}
				}

		Initial_table.clear();
		Initial_table = mid_table;
		mid_table.clear();
		//mid_table.resize(0);

	}




	for (int i = 0; i < final_table.size(); i++)
	{
		cout << i;
		for (int j = 0; j < final_table[i].size(); j++) {
			if (!is_printed(final_table[i][j], printed_numbers))
			{
				cout << "\t\t";
				final_table[i][j].print_with_dashes(num_of_var);
				cout << "\t\t" << "covered minterms and Don't cares are: ";
				for (int c = 0; c < final_table[i][j].covered_mins.size(); c++)
					cout << final_table[i][j].covered_mins[c] << ' ';


				cout << endl;
				printed_numbers.push_back(final_table[i][j]);
			}
		}



		cout << "\n-------------------------------------" << endl;
	}

	vector<binary_number> essentials;

	int k = 0;
	bool flag = true;

	for (int i = 0; i < final_table.size(); i++)
		for (int j = 0; j < final_table[i].size(); j++)
		{
			flag = true;
			for (int k = 0; k < final_table[i][j].covered_mins.size() && flag; k++)
				if (is_minterm(final_table[i][j].covered_mins[k], minterms))
				{
					if (!minterm_exists(final_table[i][j], final_table[i][j].covered_mins[k], i, j, final_table, minterms))
					{
						if (!in_essentials(final_table[i][j], essentials))
							essentials.push_back(final_table[i][j]);
						flag = false;
					}
				}

			//if (is_essential(final_table[i][j],i, j,final_table, minterms))
			//	essentials.push_back(final_table[i][j]);
		}

	cout << "Essential Prime Implicants :" << endl;

	for (int i = 0; i < essentials.size(); i++)
	{
		essentials[i].print_with_dashes(num_of_var);
		cout << endl;
	}

	cout << "Minterms that are not covered by essential prime implicants: " << endl;

	for (int i = 0; i < minterms.size(); i++)
		if (!(covered_by_essential(minterms[i], essentials)))
			cout << minterms[i] << "   ";
	cout << endl;


	system("pause");

	return 0;
}

bool covered_by_essential(int x, vector<binary_number> essentials)
{

	for (int i = 0; i < essentials.size(); i++)
	{
		for (int j = 0; j < essentials[i].covered_mins.size(); j++)
			if (essentials[i].covered_mins[j] == x)
				return true;
	}
	return false;
}

bool in_essentials(binary_number x, vector<binary_number>essentials)
{
	for (int i = 0; i < essentials.size(); i++)
	{
		if (x.num == essentials[i].num && x.dashes == essentials[i].dashes)
			return true;
	}
	return false;
}


bool minterm_exists(binary_number t, int x, int group, int pos, vector<vector<binary_number>>& primes, vector<unsigned>& minterms)
{
	for (int i = 0; i<primes.size(); i++)
		for (int j = 0; j < primes[i].size(); j++)
		{
			binary_number r = primes[i][j];
			if ((t.num != primes[i][j].num) && (t.dashes != primes[i][j].dashes))
			{
				for (int k = 0; k < primes[i][j].covered_mins.size(); k++)
					if (is_minterm(primes[i][j].covered_mins[k], minterms))
						if (x == primes[i][j].covered_mins[k])
							return true;
			}


		}

	return false;
}

bool is_minterm(int x, vector<unsigned>& minterms)
{
	//bool flag = false;

	for (int i = 0; i < minterms.size(); i++)
	{
		if (x == minterms[i])
			return true;
	}

	return false;
}


void create_MinTable(vector<vector<binary_number>>& A, vector<unsigned>& inputs, int size)
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

void create_combined(vector<vector<binary_number>>& Initial_table, vector<vector<binary_number>>& mid_table)
{
	short temp;
	//binary_number temp_num;
	for (int i = 0; i < Initial_table.size() - 1; i++) {

		for (int j = 0; j < Initial_table[i].size(); j++) {



			for (int k = 0; k < Initial_table[i + 1].size(); k++)
			{
				binary_number temp_num;

				if (Initial_table[i][j].dashes == Initial_table[i + 1][k].dashes) {
					temp_num.num = Initial_table[i][j].num & Initial_table[i + 1][k].num;
					temp_num.dashes = Initial_table[i][j].num ^ Initial_table[i + 1][k].num;
					if (temp_num.count_ones(temp_num.dashes) == 1)
					{
						temp_num.dashes ^= Initial_table[i][j].dashes; //***

						Initial_table[i][j].is_used = true;
						Initial_table[i + 1][k].is_used = true;

						Initial_table[i][j].covered_mins.push_back(Initial_table[i][j].num);//**
						Initial_table[i + 1][k].covered_mins.push_back(Initial_table[i + 1][k].num);//**

																									/*temp_num.covered_mins.push_back(Initial_table[i][j].num);
																									temp_num.covered_mins.push_back(Initial_table[i+1][k].num);*/


						temp = temp_num.count_ones(temp_num.num);
						if (temp + 1 > mid_table.size())
							mid_table.resize(temp + 1);

						temp_num.is_used = false;

						for (int c = 0; c < Initial_table[i][j].covered_mins.size(); c++)
						{
							//temp_num.covered_mins.resize(temp_num.covered_mins.size() + 1);
							std::vector<int>::iterator it = std::find(temp_num.covered_mins.begin(), temp_num.covered_mins.end(), Initial_table[i][j].covered_mins[c]);
							if (it == temp_num.covered_mins.end())
								temp_num.covered_mins.push_back(Initial_table[i][j].covered_mins[c]);
						}
						for (int c = 0; c < Initial_table[i + 1][k].covered_mins.size(); c++)
						{
							std::vector<int>::iterator it2 = std::find(temp_num.covered_mins.begin(), temp_num.covered_mins.end(), Initial_table[i + 1][k].covered_mins[c]);
							if (it2 == temp_num.covered_mins.end())
								temp_num.covered_mins.push_back(Initial_table[i + 1][k].covered_mins[c]);
							/*cout << Initial_table[i][j].covered_mins[c];
							cout << Initial_table[i + 1][k].covered_mins[c];*/
						}

						//Initial_table[i][j].covered_mins.clear();
						//Initial_table[i + 1][k].covered_mins.clear();
						mid_table[temp].push_back(temp_num);
					}
				}
			}
		}
	}

}



void print_combined(vector<vector<binary_number>>& mid_table, vector<binary_number>& printed_numbers)
{
	cout << endl << "MID PROCESS COMPUTATION:" << endl;
	for (int i = 0; i < mid_table.size(); i++)
	{
		cout << i;
		for (int j = 0; j < mid_table[i].size(); j++) {
			//print_p_binary(p_group[i][j].number, p_group[i][j].dashes);
			if (!is_printed(mid_table[i][j], printed_numbers))
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
bool is_printed(binary_number n, vector<binary_number>& printed_numbers)
{
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


/*
void create_final_table(vector<vector<binary_number>>& mid_table, vector<vector<binary_number>>& final_table, vector<binary_number>& printed_numbers)
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
/*
void print_final_table(vector<vector<binary_number>>& Initial_table,vector<vector<binary_number>>& mid_table, vector<vector<binary_number>>& final_table, vector<binary_number>& printed_numbers)
{
cout << endl << "FINAL:\n-------------------------------------" << endl;
int i, j;
for (i = 0; i < final_table.size(); i++)
{
cout << i;
for (j = 0; j < final_table[i].size(); j++) {
if (!is_printed(final_table[i][j],printed_numbers))
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


*/

#pragma once
#include<vector>
using namespace std;
class binary_number
{


private:

public:
	unsigned num;   //the binary number 
	unsigned dashes;  // represents the locations of the dashes by ones
	bool is_used;    //flag that indicates whether it is used in combinations
	vector<int> covered_mins; //every number has a vector that includes all the minterms it covers 
	binary_number();
	~binary_number();

	unsigned count_ones(unsigned num);
	void print_number(unsigned num);
	int binary_to_decimal();
	void push_decimal();
	
};


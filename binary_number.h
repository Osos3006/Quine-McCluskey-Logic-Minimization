#pragma once
#include<vector>
#include<iostream>
#include<string>
using namespace std;
class binary_number
{


private:

public:
	unsigned num;   //the binary number 
	unsigned dashes;  // represents the locations of the dashes by ones
	bool is_used;    //flag that indicates whether it is used in combinations
	vector<int> covered_mins; //every number has a vector that includes all the minterms it covers 
	binary_number( int dec );
	binary_number();
	~binary_number();

<<<<<<< HEAD
	unsigned count_ones(unsigned num);  // counts the number of ones in the binary number
	void print_number(unsigned num, int Bits_num); // prints the binary number to Bits_num decimal places
	int binary_to_decimal( unsigned bin ); // converts binary to decimal
	unsigned decimal_to_binary(int dec); // converts binary to decimal
	void push_decimal(int dec); // push decimal number to the vector
=======
	unsigned count_ones(unsigned num);
	void print_number(unsigned num);
	int binary_to_decimal();
	void push_decimal();
>>>>>>> 1f6de8cdb82f956857445cd04b3558458c939b4d
	
};


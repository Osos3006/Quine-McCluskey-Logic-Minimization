#pragma once
class binary_number
{


private:

public:
	unsigned num;   //the binary number 
	unsigned dashes;  // represents the locations of the dashes by ones
	bool is_used;    //flag that indicates whether it is used in combinations
	binary_number();
	~binary_number();

	unsigned count_ones(unsigned num);
	void print_number(unsigned num);
	void create_MinToBin();
	void print_MinToBin();
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
};


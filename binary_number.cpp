#include "binary_number.h"
#include<string>

binary_number::binary_number()
{
    num = 0;
    dashes=0;
    is_used=false;
	covered_mins.resize(0);
}

binary_number::binary_number(int dec)
{
	num = decimal_to_binary(dec);
	dashes = 0;
	is_used = false;
	covered_mins.resize(0);
}

int binary_number::count_ones()
{
	short bit = 0;
	int count = 0;
	while (num > 0) 
	{
		bit = num % 2;
		num >>= 1;
		if (bit) {
			count++;
		}
	}
	return count;
}
void binary_number::print_number(int Bits_num)
{
	vector<unsigned> bits = { 0 };
	bits.resize(Bits_num);
	int count = 0; 
	while (num > 0 || count < Bits_num)
	{
		bits[count] = num % 2;
		num >>= 1;
		count++;
	}
	for (int i = count - 1; i >= 0; i--)
		cout << bits[i];
}
int binary_number::binary_to_decimal(unsigned bin)
{
	string bin_st;
	bin_st = bin;
	int dec = stoi(bin_st, nullptr, 2);
	return dec;
}
void binary_number:: push_decimal(int dec)
{
	covered_mins.push_back(dec);
}

unsigned binary_number::decimal_to_binary (int dec)
{
	string bin="";
	while (dec > 0)
	{
		//bin = bin + char(dec % 2)
		string p = to_string(dec % 2);
		//bin.append(p);
		bin = bin + p;
		dec >>= 1;
	}
	unsigned res = atoi(bin.c_str());
	return res;
}

binary_number::~binary_number()
{
}

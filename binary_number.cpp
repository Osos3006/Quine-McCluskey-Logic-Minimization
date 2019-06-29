#include "binary_number.h"
#include<string>

binary_number::binary_number()
{
	num = 0;
	dashes = 0;
	is_used = false;
	covered_mins.resize(0);
}

binary_number::binary_number(int dec)
{
	num = dec;
	dashes = 0;
	is_used = false;
	covered_mins.resize(0);
	covered_mins.push_back(dec);
}

int binary_number::count_ones(int n)
{
	short bit = 0;
	int count = 0;
	while (n > 0)
	{
		bit = n % 2;
		n >>= 1;
		if (bit) {
			count++;
		}
	}
	return count;
}
void binary_number::print_number(int Bits_num)
{
	int n = num;
	vector<unsigned> bits = { 0 };
	bits.resize(Bits_num);
	int count = 0;
	while (n > 0 || count < Bits_num)
	{
		bits[count] = n % 2;
		n >>= 1;
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
void binary_number::push_decimal(int dec)
{
	covered_mins.push_back(dec);
}

/*unsigned binary_number::decimal_to_binary (int dec)
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
}*/
void binary_number::print_with_dashes(int Bits_num)
{
	int n = num;
	int d = dashes;
	vector<unsigned> bits = { 0 };
	bits.resize(Bits_num);
	int count = 0;
	while (n > 0 || count < Bits_num) {
		if (!(d % 2))
			bits[count] = n % 2;
		else
			bits[count] = 2;
		n >>= 1;
		d >>= 1;
		count++;
	}
	for (int i = count - 1; i >= 0; i--) {
		if (bits[i] != 2)
			cout << bits[i];
		else
			cout << "-";
	}
}

binary_number::~binary_number()
{
}

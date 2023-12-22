#include <iostream>
#include <iomanip>
#include <fstream>

int main()
{
	std::ofstream _1("a.out", std::ios::binary | std::ios::in);

	_1.put('a');
	_1.put('b');
	_1.put('c');

	_1.flush();


	std::ofstream _2("a.out", std::ios::binary | std::ios::in);

	_2.seekp(3);

	_2.put('d');
	_2.put('e');
	_2.put('f');

	_2.flush();

	return 0;
}
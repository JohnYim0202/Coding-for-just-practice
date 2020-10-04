#include "Header.h"

int unit = 1;

int main()
{
	char temp_str[100];
	std::cout << "Enter a string: ";
	gets_s(temp_str);

	Code code;
	code.initialize();
	code.setstring(temp_str, unit);
	code.symbolanalyze(unit);
	code.encode(unit);
	code.decode();

	system("pause");
	return 0;
}
#include <cstdio>
#include <iostream>

#include "validate.h"
#include "limit.h"
namespace Validate
{
template <typename T>

bool validate (const T value, const T upper, const T lower)
{
	return ((value <= upper) && (value >= lower));
}
int get_int(std::string message, int lower, int upper)
{
	char str[STRING_LIMIT];
	int x;
	std::cout << message;
	fgets(str, sizeof(str), stdin);
	while (sscanf (str, "%d", &x) != 1 || !validate<int>(x, upper, lower))
	{
		std::cout << "Enter correct value!\n>";
		fgets(str, sizeof(str), stdin);
	}
	return x;
}
}

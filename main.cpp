#define _GLIBCXX_USE_CXX11_ABI 0

#include <any>
#include <iostream>
#include <vector>
#include <variant>
#include <algorithm>

#include "limit.h"
#include "validate.h"
#include "menu_class.h"
#include "time_date_class.h"
#include "flight_class.h"


using namespace std::string_literals;

void addFlights(Node** first, Node** last)
{
	system("cls");
	int number = 0;
	int amount = getsize(*last);
	if (amount == 0)
	{
		number = Validate::get_int("How many flights are there?\n>"s, LOWER_FLIGHTS, UPPER_NO_VALID);
	}
	else
	{
		number = Validate::get_int("How many flights would you like to add?\n>"s, LOWER_FLIGHTS, UPPER_NO_VALID);
	}
	amount += number;
	for(int i = amount - number; i < amount; i++)
	{
		enterFlight(last, i);
	}
}
void printFlights(Node** first, Node** last)
{
	print_header();
	int i = 1;
	printall(*last, i);
	if (getsize(*last) == 1)
	{
		print_empty_table();
	}
	else
	{
		print_line();
	}
	getchar();
}
void deleteFlight(Node** first, Node** last)
{
	int sz = getsize(*last);
	if (!sz)
	{
		std::cout << "Warning! Nothing to delete";
		getchar();
	}
	else
	{
		int toDelete = sz - Validate::get_int("Which flight do you want to delete?\n>", 1, sz) + 1;
		remove(first, last, toDelete);
	}
}
void clearFlights(Node** first, Node** last)
{
	while (getsize(*last))
	{
		remove(first, last, 0);
	}
}
void importFlights(Node** first, Node** last)
{
	int am = 0;
	try
	{
		std::ifstream in("input.txt");
		in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		in >> am;
		for(int i = 0; i < am; i++)
		{
			int dyear, dmonth, dday, dhour, dminute, fhour, fminute;
			std::string ap;
			in >> dday;
			in >> dmonth;
			in >> dyear;
			in >> dhour;
			in >> dminute;
			in >> fhour;
			in >> fminute;
			std::getline(in, ap);
			std::getline(in, ap);
			int result = 1;
			result = Validate::validate(dday, UPPER_DAY, LOWER_DATE) * Validate::validate(dmonth, UPPER_MONTH, LOWER_DATE) * Validate::validate(dyear, UPPER_YEAR, LOWER_DATE);
			result = result * Validate::validate(dhour, UPPER_HOUR, LOWER_TIME) * Validate::validate(dminute, UPPER_MINUTE, LOWER_TIME) * Validate::validate(fhour, UPPER_NO_VALID, LOWER_TIME) * Validate::validate(fminute, UPPER_MINUTE, LOWER_TIME);
			try
			{
				if(result)
				{
					auto ddate = Date(dday, dmonth, dyear);
					auto dtime = Time(dhour, dminute);
					auto ftime = Time(fhour, fminute);
					auto r = Flight(ddate, dtime, ftime, ap);
					add(last, r);
				}
				else
				{
					throw "Error: incorrect data in file string #"s;
				}
			}
			catch(std::string except)
			{
				std::cerr << except << i << std::endl;
				getchar();
			}
		}
		in.close();
	}
	catch (std::ios_base::failure &fail)
	{
		std::cout << fail.what() << std::endl;
	}
}
void exportFlights(Node** first, Node** last)
{
	try
	{
		std::ofstream out("output.txt");
		out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		out << getsize(*last) << std::endl;
		exportall(*last, out);
		out.close();
	}
	catch (std::ios_base::failure &fail)
	{
		std::cout << fail.what() << std::endl;
	}
}
void sortDate(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_date_time(find(*first, j)->m_fl, find(*first, j + 1)->m_fl) == 1)
			{
                swap(first, j);
			}
		}
	}
}
void sortDate_d(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_date_time(find(*first, j)->m_fl, find(*first, j + 1)->m_fl) == -1)
			{
                swap(first, j);
			}
		}
	}
}
void sortFlightTime(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_ftime(find(*first, j)->m_fl, find(*first, j + 1)->m_fl) == 1)
			{
                swap(first, j);
			}
		}
	}
}
void sortFlightTime_d(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_ftime(find(*first, j)->m_fl, find(*first, j + 1)->m_fl) == -1)
			{
                swap(first, j);
			}
		}
	}
}
void sortAirport(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_by_airport(find(*first, j)->m_fl, find(*first, j + 1)->m_fl))
			{
                swap(first, j);
			}
		}
	}
}
void sortAirport_d(Node** first, Node** last)
{
    int size = getsize(*last);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size - i; j++)
		{
			if (compare_by_airport(find(*first, j)->m_fl, find(*first, j + 1)->m_fl) == false)
			{
                swap(first, j);
			}
		}
	}
}
int main()
{

	Menu sort_menu {"How do you want to sort the flights?"s, {{"1. Sort by date and time of departure (ascending)"s, sortDate}, {"2. Sort by date and time of departure (descending)"s, sortDate_d},{"3. Sort by travel time (ascending)"s, sortFlightTime}, {"4. Sort by travel time (descending)"s, sortFlightTime_d}, {"5. Sort by availability of breakfast (ascending)"s, sortFlightTime},{"6. Sort by availability of breakfast (descending)"s, sortFlightTime_d}, {"7. Sort by airport of destination (ascending)"s, sortAirport}, {"8. Sort by airport of destination (descending)"s, sortAirport_d}}};
	Menu print_menu {"How do you want to print the flights?"s, {{"1. Print the flights on screen"s, printFlights}, {"2. Export the flights into output.txt"s, exportFlights}}};
	Menu enter_menu {"How do you want to enter the flights?"s, {{"1. Enter the flights manually"s, addFlights}, {"2. Import the flights from input.txt"s, importFlights}}};
	Menu main_menu {"What do you want to do?"s, {{"1. Enter the flights"s, &enter_menu}, {"2. Delete the flight"s, deleteFlight}, {"3. Sort the flights"s, &sort_menu}, {"4. Print the flights"s, &print_menu}, {"5. Clear all the flights"s, clearFlights}}};
	Flight fst = Flight();
	Node *first = create(fst);
	Node *last = first;
	main_menu.menu(&first, &last);

}



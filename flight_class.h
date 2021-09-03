#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "time_date_class.h"


using namespace std::string_literals;

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

class Flight;

void open();
void print_line();
void print_str_line();
void print_empty_line();
void print_header();
void print_empty_table();
void print_flight(const Flight&, const int, const int);
void export_flight(const Flight&, std::ofstream&);

class Flight
{
private:
	Date m_departureDate;
	Time m_departureTime;
	Time m_flightTime;
	bool m_breakfast;
	std::string m_airport;
public:
	Date getDepartureDate() const
	{
		return m_departureDate;
	}
	void setDepartureDate(const Date& dd)
	{
		m_departureDate = dd;
	}

	Time getDepartureTime() const
	{
		return m_departureTime;
	}
	void setDepartureTime(const Time& dt)
	{
		m_departureTime = dt;
	}

	Time getFlightTime() const
	{
		return m_flightTime;
	}
	void setFlightTime(const Time& ft)
	{
		m_flightTime = ft;
	}

	bool getBreakfast() const
	{
		return m_breakfast;
	}
	void setBreakfast(const bool br)
	{
		m_breakfast = br;
	}

	std::string getAirport() const
	{
		return m_airport;
	}
	void setAirport(const std::string ap)
	{
		m_airport = ap;
	}
	void breakfast_check ()
	{
		m_breakfast = ((m_flightTime.getHour() > 4 || (m_flightTime.getHour() == 4 && m_flightTime.getMinute() >= 1)));
	}
	Flight& operator= (const Flight &flight)
	{
	    m_departureDate = flight.getDepartureDate();
	    m_departureTime = flight.getDepartureTime();
	    m_flightTime = flight.getFlightTime();
	    m_breakfast = flight.getBreakfast();
	    m_airport = flight.getAirport();
	    return *this;
	}
	bool operator== (const Flight &f1)
	{
		return (f1.getAirport() == getAirport() && f1.getFlightTime() == getFlightTime() && f1.getBreakfast() == getBreakfast() && f1.getDepartureDate() == getDepartureDate() && f1.getDepartureTime() == getDepartureTime());
	}
	Flight()
	{
		setDepartureDate(Date());
		setDepartureTime(Time());
		setFlightTime(Time());
		setAirport("Default Airport");
		breakfast_check();
	}
	Flight(const Date& departureDate, const Time& departureTime, const Time& flightTime, const std::string airport)
	{
		setDepartureDate(departureDate);
		setDepartureTime(departureTime);
		setFlightTime(flightTime);
		setAirport(airport);
		breakfast_check();
	}
	Flight(const Flight& flight)
	{
		setDepartureDate(flight.getDepartureDate());
		setDepartureTime(flight.getDepartureTime());
		setFlightTime(flight.getFlightTime());
		setAirport(flight.getAirport());
		breakfast_check();
	}
};

class Node
{
public:
	Flight m_fl;
	Node* prev;
	Node* next;
	Node& operator= (const Node &node)
	{
	    prev = node.prev;
	    next = node.next;
	    return *this;
	}
	Node()
	{
		m_fl = Flight();
		next = nullptr;
		prev = nullptr;
	}
};

Node* create(Flight fl)
{
	Node *tmp = new Node();
	tmp->m_fl = fl;
	tmp->next = nullptr;
	tmp->prev = nullptr;
	return tmp;
}

void add(Node** end, Flight fl)
{
	Node *tmp = new Node();
	tmp->m_fl = fl;
	tmp->next = 0;
	tmp->prev = *end;
	(*end)->next = tmp;
	*end = tmp;
}

Node* find(Node* const first, Flight fl)
{
	Node *tmp = first;
	while (tmp)
	{
		if (tmp->m_fl == fl) break;
		tmp = tmp->next;
	}
	return tmp;
}
Node* find(Node* const first, const int cnt)
{
    int t = cnt;
	Node *tmp = first;
	while (tmp)
	{
		if (!t) break;
		t--;
		tmp = tmp->next;
	}
	return tmp;
}
bool remove(Node **first, Node **end, Flight fl)
{
	if (Node *keyPointer = find(*first, fl))
	{
		if (keyPointer == *first)
		{
			*first = (*first)->next;
			(*first)->prev = 0;
		}
		else
			if (keyPointer == *end)
			{
				*end = (*end)->prev;
				(*end)->next = 0;
			}
			else
			{
				(keyPointer->prev)->next = keyPointer->next; // 1
				(keyPointer->next)->prev = keyPointer->prev; // 2
			}
		delete keyPointer; // 3
		return true;
	}
	return false;
}
bool remove(Node **first, Node **end, int cnt)
{
	if (Node *keyPointer = find(*first, cnt))
	{
		if (keyPointer == *first)
		{
			*first = (*first)->next;
			(*first)->prev = 0;
		}
		else
			if (keyPointer == *end)
			{
				*end = (*end)->prev;
				(*end)->next = 0;
			}
			else
			{
				(keyPointer->prev)->next = keyPointer->next; // 1
				(keyPointer->next)->prev = keyPointer->prev; // 2
			}
		delete keyPointer; // 3
		return true;
	}
	return false;
}
Node* insert(Node *const first, Node **end, Flight keyValue, Flight data)
{
	Node *keyPointer = find(first, keyValue);
	if (keyPointer)
	{
		Node *tmp = new Node();
		tmp->m_fl = data;
		tmp->next = keyPointer->next;
		tmp->prev = keyPointer;
		keyPointer->next = tmp;
		if (keyPointer != *end) (tmp->next)->prev = tmp;

		else *end = tmp;
		return tmp;
	}
	return 0;
}


int getsize(Node* end)
{
	int count = 0;
	Node *temp = end;
	while(temp)
	{
		count++;
		temp = temp->prev;
	}
	return count - 1;
}
int getsize_s(Node* start)
{
	int count = 0;
	Node *temp = start;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	return count - 1;
}

void swap(Node** first, const int i)
{
    Node *ith = find(*first, i);
    Node *next = ith->next;

    Flight tmp = ith->m_fl;
    ith->m_fl = next->m_fl;
    next->m_fl = tmp;

}


void printall(Node* last, int i)
{
	if (last->prev != nullptr)
	{
		print_flight(last->m_fl, i, ON_SCREEN);
		i++;
		printall(last->prev, i);
	}
}
void exportall(Node* last, std::ofstream& out)
{
	if (last->prev == nullptr)
	{

	}
	else
	{
		export_flight(last->m_fl, out);
		exportall(last->prev, out);
	}
}
void clear_stdin()
{
	int ch = getchar();
	while (ch != '\n' && ch != EOF)
	{
		ch = getchar();
	}
}

auto enterTime(const bool val)
{
	int hour, minute;
	if(val)
	{
		hour = Validate::get_int("Enter the hour of departure:\n>"s, LOWER_TIME, UPPER_HOUR) % UPPER_HOUR;
		minute = Validate::get_int("Enter the minute of departure:\n>"s, LOWER_TIME, UPPER_MINUTE) % UPPER_MINUTE;
	}
	else
	{
		hour = Validate::get_int("How many hours the flight will be?\n>"s, LOWER_TIME, UPPER_NO_VALID);
		minute = Validate::get_int("How many minutes the flight will be?\n>"s, LOWER_TIME, UPPER_MINUTE);
	}
	return Time(hour, minute);
}
auto enterDate()
{
	int day, month, year;
	day = Validate::get_int("Enter the day of the flight:\n>"s, LOWER_DATE, UPPER_DAY);
	month = Validate::get_int("Enter the month of the flight:\n>"s, LOWER_DATE, UPPER_MONTH);
	year = Validate::get_int("Enter the year of the flight:\n>"s, LOWER_DATE, UPPER_YEAR);
	return Date(day, month, year);
}
std::string enterAirport()
{
	std::cout << "What's the airport of destination?\n>";
	std::string ap;
	std::cin >> ap;
	clear_stdin();
	return ap;
}
void enterFlight(Node** end, const int n)
{
	print_str_line();
	std::cout << "Flight #" << n + 1 << std::endl;
	add(end, Flight(enterDate(), enterTime(true), enterTime(false), enterAirport()));
}


void print_line()
{
	std::cout << "+----+------------+--------+-------------+-----------+---------------+\n";
}
void print_str_line()
{
	std::cout <<  "----------------------------\n";
}
void print_empty_line()
{
	std::cout <<  "+--------------------------------------------------------------------+\n";
}
void print_header()
{
	print_line();
	std::cout << "| No |    Date    |  Time  | Travel time | Breakfast |    Airport    |\n";
}
void print_empty_table()
{
	print_empty_line();
	std::cout << "|                     There's no flights yet...                      |\n";
	print_empty_line();
}
void print_flight(const Flight& fl, const int i, const int mode)
{
	std::string b = (fl.getBreakfast() ? "+" : "-");
	print_line();
	//choose_stream(mode, str) << "| %2i | %02d.%02d.%04d | %02d:%02d  |    %02d:%02d    |     %s     | %13s |\n", i, fl.getDepartureDate().getDay(), fl.getDepartureDate().getMonth(), fl.getDepartureDate().getYear(), fl.getDepartureTime().getHour(), fl.getDepartureTime().getMinute(), fl.getFlightTime().getHour(), fl.getFlightTime().getMinute(), b, fl.getAirport());
	std::cout << "| "           << std::right << std::setw(02) << i
			  << " | "          << std::setw(02) << std::setfill('0') << fl.getDepartureDate().getDay()
			  << "."            << std::setw(02) << std::setfill('0') << fl.getDepartureDate().getMonth()
			  << "."            << std::setw(04) << std::setfill('0') << fl.getDepartureDate().getYear()
			  << " | "          << std::setw(02) << std::setfill('0') << fl.getDepartureTime().getHour()
			  << ":"            << std::setw(02) << std::setfill('0') << fl.getDepartureTime().getMinute()
			  << "  |    "      << std::setw(02) << std::setfill('0') << fl.getFlightTime().getHour()
			  << ":"            << std::setw(02) << std::setfill('0') << fl.getFlightTime().getMinute()
			  << "    |     "   << b
			  << "     | "      << std::setw(14) << std::left << std::setfill(' ') << fl.getAirport()
			  << "|\n";
}
void export_flight(const Flight& f, std::ofstream& out)
{
	out << std::setw(02) << std::setfill('0') << f.getDepartureDate().getDay() << " "
		<< std::setw(02) << std::setfill('0') << f.getDepartureDate().getMonth() << " "
		<< std::setw(04) << std::setfill('0') << f.getDepartureDate().getYear() << " "
		<< std::setw(02) << std::setfill('0') << f.getDepartureTime().getHour() << " "
		<< std::setw(02) << std::setfill('0') << f.getDepartureTime().getMinute() << " "
		<< std::setw(02) << std::setfill('0') << f.getFlightTime().getHour() << " "
		<< std::setw(02) << std::setfill('0') << f.getFlightTime().getMinute() << std::endl
		<< f.getAirport() << std::endl;
}
int signum(const int x)
{
	return (!x) ? 0 : (x / abs(x));
}
int compare_time (const Flight& first, const Flight& second)
{
	int result = 0;
	int arr[2];
	arr[0] = signum(first.getDepartureTime().getHour() - second.getDepartureTime().getHour());
	arr[1] = signum(first.getDepartureTime().getMinute() - second.getDepartureTime().getMinute());
	result = signum(10 * arr[0] + arr[1]);
	return result;
}

int compare_date_time (const Flight& first, const Flight& second)
{
	int result = 0;
	int arr[4];
	arr[0] = signum(first.getDepartureDate().getYear() - second.getDepartureDate().getYear());
	arr[1] = signum(first.getDepartureDate().getMonth() - second.getDepartureDate().getMonth());
	arr[2] = signum(first.getDepartureDate().getDay() - second.getDepartureDate().getYear());
	arr[3] = compare_time(first, second);
	result = signum(1000 * arr[0] + 100 * arr[1] + 10 * arr[2] + arr[3]);
    return result;

}

int compare_ftime (const Flight& first, const Flight& second)
{
	int result = 0;
	int arr[2];
	arr[0] = signum(first.getFlightTime().getHour() - second.getFlightTime().getHour());
	arr[1] = signum(first.getFlightTime().getMinute() - second.getFlightTime().getMinute());
	result = signum(10 * arr[0] + arr[1]);
    return result;
}
bool compare_by_airport (const Flight& first, const Flight& second)
{
	return ((first.getAirport().compare(second.getAirport()) < 0) ?  true : false);
}

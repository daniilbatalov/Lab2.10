#define _GLIBCXX_USE_CXX11_ABI 0

#define STRING_LIMIT 256


#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <cstdio>

#include "flight_class.h"

#pragma once

using namespace std::string_literals;

class Object
{
public:
	std::string m_name;

	std::string getName() const
	{
		return m_name;
	}
    void printName() const
	{
		std::cout << getName() << std::endl;
	}

	void setName(std::string& name)
	{
		m_name = name;
	}

	Object() {};
	Object(const std::string& name) : m_name(name) {};
};


class Menu : public Object
{
private:
	using func_type = void(*)(Node** first, Node** last);

	class MenuItem: public Object
	{
	public:
		std::variant<func_type, Menu*> m_next;
	};
	using vmi = std::vector<MenuItem>;

	vmi m_list;

public:

	auto getSize()
	{
		return m_list.size();
	}

	void appendItem(const MenuItem& toAppend)
	{
		m_list.emplace_back(toAppend);
	}

	bool deleteItem(const size_t index)
	{
		if (Validate::validate(index, static_cast<size_t>(0), static_cast<size_t>(getSize())))
		{
			m_list.erase(m_list.begin() + index);
			return true;
		}
		return false;
	}

	bool insertItem (size_t index, const MenuItem& toInsert)
	{
		if (Validate::validate(index, static_cast<size_t>(0), static_cast<size_t>(getSize())))
		{
			m_list.insert(m_list.begin() + index, toInsert);
			return true;
		}
		return false;
	}
    auto getItem (size_t index) const
    {
        return m_list.at(index);
    }
	void menu(Node** first, Node** last)
	{
		menu(*this, first, last);
	}

	Menu(){}
	Menu(const std::string& t, const vmi& vm) : Object(t), m_list(vm){}


private:

	void menu(const Menu& m, Node** first, Node** last)
	{
		const auto printMenu = [this, m_size = m.m_list.size()](const Menu& mu)
		{
		    system("cls");
			mu.printName();
			for (MenuItem item : mu.m_list)
			{
				item.printName();
			}
			std::cout << "0. Exit" << std::endl;
			return Validate::get_int(">"s, 0, m_size);
		};
		for (size_t opt = 0U; (opt = printMenu(m)) > 0;)
			if (const auto& mi = m.m_list[opt - 1]; std::holds_alternative<Menu::func_type>(mi.m_next))
				std::get<Menu::func_type>(mi.m_next)(first,last);
			else
				menu(*std::get<Menu*>(mi.m_next), first, last);
	}
};


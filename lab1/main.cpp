/*#include <iostream>
#include <string>

int main()
{
	setlocale(LC_ALL, "Rus");
	std::string string;
	std::cout << "Введите строку" << std::endl;
	std::cin >> string;
	if ((string[0] == ')') || (string[0] == '}') || (string[0] == ']') || (string.size() / sizeof(char) == 1))
	{
		std::cout << "Строка не существует" << std::endl;
		return 0;
	}

	int i = 0;

	while ((string.size() / sizeof(string[0]) > 0) || (i>string.size() / sizeof(string[0])))
	{
		if ((string[0] == ')') || (string[0] == '}') || (string[0] == ']'))
		{
			std::cout << "Строка не существует" << std::endl;
			return 0;
		}

		switch (string[i])
		{
		case ')':
			if (string[i - 1] == '(')
			{
				string.erase(i - 1, 2);
				i -= 3;
				if (i<0) { i = -1; }
			}
			else
			{
				std::cout << "Строка не существует" << std::endl;
				return 0;
			}
			break;
		case '}':
			if (string[i - 1] == '{')
			{
				string.erase(i - 1, 2);
				i -= 3;
				if (i<0) { i = -1; }
			}
			else
			{
				std::cout << "Строка не существует" << std::endl;
				return 0;
			}
			break;
		case ']':
			if (string[i - 1] == '[')
			{
				string.erase(i - 1, 2);
				i -= 3;
				if (i<0) { i = -1; }
			}
			else
			{
				std::cout << "Строка не существует" << std::endl;
				return 0;
			}
			break;
		default:
			break;
		}
		i++;
		//std::cout << i << std::endl;
		//std::cout << string << std::endl;
	}
	if (string == "")
		std::cout << "Строка существует" << std::endl;
	else
		std::cout << "Строка не существует" << std::endl;
	return 0;
}
*/

#include <iostream>
#include <vector>
#include <string>

int main()
{
	setlocale(LC_ALL, "RUS");
	std::vector <char> mas;
	std::cout << "Введите последовательнось скобок: ";

	std::string string;
	std::cin >> string;
	for (int i = 0; i < string.size(); i++)
	{
		if ((i != 0) && (mas.size() > 0))
		{
			if (((mas.back() == '{') && (string[i] == '}')) || ((mas.back() == '(') && (string[i] == ')')) || ((mas.back() == '[') && (string[i] == ']')))
			{
				mas.pop_back();
			}
			else
			{
				mas.push_back(string[i]);
			}
		}
		else
		{
			mas.push_back(string[i]);
		}
	}
	if (mas.size() > 0)
	{
		std::cout << "\nСтрока не существует" << std::endl;
	}
	else
	{
		std::cout << "\nСтрока существует" << std::endl;
	}
	std::cin;
	return 0;
}
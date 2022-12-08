#include <iostream>
#include <vector>

void count(std::string &str)	//функция cчитывания строки 
{
	std::vector<char> stack;
	std::vector<int> priority;
	std::string outStr;

	if (str[str.size() - 1] != '=')	//проверка на правильность выражения
	{
		std::cout << "Ошибка: нужно = в конце выражения!" << std::endl;
		return;
	}

	for (int i = 0; i < str.size(); i++)
	{
		if ((str[i] >= '0') && (str[i] <= '9'))	//если входящий символ - число, помещаем его в стек
		{
			outStr.push_back(str[i]);
			continue;
		}

		int pr = 0;
		switch(str[i])
		{
		case '+':
		case '-':
			pr = 2;
			break;
		case '/':
		case '*':
			pr = 3;
			break;
		case '(':
			pr = 1;
			break;
		case ')':
		{
			int k = priority.size() - 1;
			
			if (k > 0)
			{
				do {
					outStr.push_back(' ');
					outStr.push_back(stack[k]);
					priority.pop_back();
					stack.pop_back();
					k--;
				} while((priority[k] != 1));
				priority.pop_back();
				stack.pop_back();
				continue;
			}
			else
			{
				std::cout << "Ошибка: неверная расстановка скобок: больше закрывающих!"  << std::endl;
				return;
			}
			break;
		}	
		default:
			break;
		}
		if (pr != 0)
		{
			if (stack.size() > 1)
			{
				while (priority.back() >= pr)	//пока приоритет последнего в стеке >= приоритета текущего:
				{
					if(str[i] == '(') { break; }
					outStr.push_back(stack.back());
					outStr.push_back(' ');
					priority.pop_back();
					stack.pop_back();
				}
			}
			if(str[i]!='(') outStr.push_back(' ');
			stack.push_back(str[i]);	//когда либо не осталось элементов в стеке, либо не удовл. предыдущему условию:
			priority.push_back(pr);		//пушим в стек текущий элемент и его приоритет
		}
	}
	while (stack.size() > 0)
	{
		if (stack.back() == '(')
		{
			std::cout << "Ошибка: неверная расстановка скобок: больше открывающих!" << std::endl;
			return;
		}
		outStr.push_back(' ');
		outStr.push_back(stack.back());
		priority.pop_back();
		stack.pop_back();
	}

	std::vector<float> operands;
	for (int i = 0; i < outStr.length(); i++)
	{
		float num = 0;
		if ((outStr[i] >= '0') && (outStr[i] <= '9'))	//если входящий символ - число, помещаем его в стек
		{
			while ((outStr[i] >= '0') && (outStr[i] <= '9'))
			{
				num *= 10;
				num += (float)(outStr[i]-'0');
				i++;
			}
			operands.push_back(num);
		}
		else if(outStr[i]!= ' ')
		{
			float a=0, b=0;
			int c = operands.back();
			b = operands.back();
			operands.pop_back();
			a = operands.back();
			operands.pop_back();

			switch (outStr[i])
			{
			case '+':
				operands.push_back(a+b);
				break;
			case '-':
				operands.push_back(a-b);
				break;
			case '*':
				operands.push_back(a*b);
				break;
			case '/':
				if (b == 0)
				{
					std::cout << "Ошибка: попытка деления на нуль!" << std::endl;
					return;
				}
				else
				{
					operands.push_back(a/b);
				}
				break;
			default:
				break;
			}
		}
	}

	if(operands.size()>0)
		std::cout << operands[0] << std::endl;

}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::string str;
	std::cout << "Введите строку без пробелов, заканчивающуюся оператором = " << std::endl;
	std::cin >> str;
	
	count(str);

	return 0;
}

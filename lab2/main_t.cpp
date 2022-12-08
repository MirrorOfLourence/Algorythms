#include <iostream>
#include <algorithm>

void read(const std::string& string, int length)		//ф-и€ чтени€ введЄнной строки
{
	int firstOperand, secondOperand;
	bool isSet = false;			//флаг, было ли уже задано значение операнда
	bool wasSign = false;		//флаг, были ли спец символы, делающие переход на второй операнд
	char signType = NULL;		//тип оператора
	for (int i = 0; i < length; i++)
	{
		if ((string[i] >= '0') && (string[i] <= '9'))
		{
			if (!wasSign)		//если не было раздел€ющего символа, ищем значение первого операнда
			{
				if (!isSet)		//если операнд не был задан, ему присваиваетс€ значение первой считанной цифры
				{
					firstOperand = string[i] - '0';
					isSet = true;
				}
				else			//если операнд был задан, к его значению прибавл€етс€ новый дес€ток с цифрой
				{
					firstOperand = firstOperand*10 + (string[i] - '0');
				}
			}
			else				//если был раздел€ющий символ, ищем значение второго операнда
			{

			}
			
			
		}
		else
			switch (string[i])
			{
			case '+':
			case '-':
			case '*':
			case '/':
			default:
				break;
			}
		
	}
}

int calculate()		//ф-и€ вычислени€ выражени€ с двум€ операндами
{
	

	return 0;
}

int calcBracket()		//ф-и€ вычислени€ выражени€ в скобках
{
	int result=0;

	return result;
}

void checkBrackets(const std::string& string, int length)
{
	int numOfBreackets = std::count(string[0], string[length-1], '(') + 
}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::string string;
	std::cout << "¬ведите строку" << std::endl;
	std::cin >> string;

	int length = string.size()/sizeof(string[0]);

	read(string, length);

	return 0;
}
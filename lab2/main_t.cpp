#include <iostream>
#include <algorithm>

void read(const std::string& string, int length)		//�-�� ������ �������� ������
{
	int firstOperand, secondOperand;
	bool isSet = false;			//����, ���� �� ��� ������ �������� ��������
	bool wasSign = false;		//����, ���� �� ���� �������, �������� ������� �� ������ �������
	char signType = NULL;		//��� ���������
	for (int i = 0; i < length; i++)
	{
		if ((string[i] >= '0') && (string[i] <= '9'))
		{
			if (!wasSign)		//���� �� ���� ������������ �������, ���� �������� ������� ��������
			{
				if (!isSet)		//���� ������� �� ��� �����, ��� ������������� �������� ������ ��������� �����
				{
					firstOperand = string[i] - '0';
					isSet = true;
				}
				else			//���� ������� ��� �����, � ��� �������� ������������ ����� ������� � ������
				{
					firstOperand = firstOperand*10 + (string[i] - '0');
				}
			}
			else				//���� ��� ����������� ������, ���� �������� ������� ��������
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

int calculate()		//�-�� ���������� ��������� � ����� ����������
{
	

	return 0;
}

int calcBracket()		//�-�� ���������� ��������� � �������
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
	std::cout << "������� ������" << std::endl;
	std::cin >> string;

	int length = string.size()/sizeof(string[0]);

	read(string, length);

	return 0;
}
#include <iostream>
#include <vector>

void sort(std::vector<int>& mas, int length)	//������� ���������� ���������
{
	int tmp, depth, numNow = length;
	while (length > 1)
	{
		numNow /= 1.247f;		//��������� �������� ����������� ��� ������������
		if(numNow < 1) {numNow = 1;}
		depth = 0;
		for (int i = 0; (i + numNow) < length; ++i)
		{
			if (mas[i] > mas[i + numNow])		//���� ������������ �������� ����� �����������, ������
			{
				tmp = mas[i];
				mas[i] = mas[i + numNow];
				mas[i + numNow] = tmp;
				depth = i;
			}
		}
		if (numNow == 1)		//���� ��� ����� 1, �� ��������� ������� ������������;
		{
			length = depth+1;
		}
	}
}

int main()
{
	std::vector<int> mas;
	int length = 0;
	for (int i = 0; i < 10; i++)	//��������� ������ ���������� �������
	{
		mas.push_back(rand()%100);
		std::cout  << mas[i] << std::endl;
	}
	std::cout  << std::endl << std::endl;

	length = mas.size();
	sort(mas, length);
	for (int i = 0; i < length; i++)	//������� ������
	{
		std::cout  << mas[i] << std::endl;
	}
	return 0;
}
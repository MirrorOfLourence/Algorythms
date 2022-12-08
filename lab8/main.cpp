#include <iostream>
#include <vector>
	
int getDigit(int num, int iter)		//функция, возвращает iter-тый разряд числа с конца
{
	int res = num;
	for (int i= 0; i < iter; i++)
	{
		res = res / 10;
	}

	return (res%10);
}
void sort(std::vector<int>& mas, int length)	//функция поразрядной сортировки
{
	std::vector<std::vector<int>> mainMas(10,std::vector<int>());
	std::vector<std::vector<int>> currentMas(10,std::vector<int>());
	int iter = 0;
	for (int i = 0; i < length; i++)
	{
		currentMas[getDigit(mas[i], iter)].push_back(mas[i]);
	}
	mainMas = currentMas;
	iter++;
	
	while (mainMas[0].size() < length)
	{
		for (int i = 0; i < 10; i++)
		{
			int replaced = 0;
			for (int j = 0; j < mainMas[i].size(); j++)
			{
				int pos = getDigit(mainMas[i][j], iter);
				if (i != pos)
				{
					currentMas[pos].push_back(mainMas[i][j]);
					std::cout <<"i="<< i << std::endl;
					std::cout << "currentMas.size()-" << currentMas.size() << std::endl;
					std::cout << "currentMas[i].size()=" << currentMas[i].size() << std::endl;
					std::cout << "j=" << j << std::endl;
					std::cout << "replaced=" << replaced << std::endl;
					std::cout << "=" << *currentMas[i].begin() << std::endl;
					//std::cout << "==" << (currentMas[i].begin() == (currentMas[i].begin() + j - replaced)) << std::endl;

					currentMas[i].erase(currentMas[i].begin() + (j-replaced));
					replaced++;
				}	
			}
		}
		for (int i = 0; i < 10; i++)
		{
			mainMas[i].clear();
		}
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < currentMas[i].size(); j++)
			{
				mainMas[i].push_back(currentMas[i][j]);
			}
		}
		iter++;
	}
	for (int i = 0; i < length; i++)
	{
		mas[i] = mainMas[0][i];
	}

}

int main()
{
	std::vector<int> mas;
	int length = 0;
	for (int i = 0; i < 10; i++)	//заполняем массив случайными числами
	{
		mas.push_back(rand()%100);
		std::cout  << mas[i] << std::endl;
	}
	std::cout  << std::endl << std::endl;

	length = mas.size();
	sort(mas, length);
	for (int i = 0; i < length; i++)	//выводим массив
	{
		std::cout  << mas[i] << std::endl;
	}
	return 0;
}
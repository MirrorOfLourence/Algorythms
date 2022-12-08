#include <iostream>
#include <vector>

void sort(std::vector<int>& mas, int length)	//функция сортировки Шелла
{	
	for (int  step = length/2; step > 0; step /= 2)
	{
		for (int i = 0; i < length - step; i++)
		{
			int j = i;
			while (j >= 0 && (mas[j] > mas[j + step]))
			{
				int tmp = mas[j];
				mas[j] = mas[j+step];
				mas[j+step] = tmp;
				j--;
			}
		}
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
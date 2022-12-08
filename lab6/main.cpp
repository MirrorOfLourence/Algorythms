#include <iostream>
#include <vector>

void sort(std::vector<int>& mas, int length)	//функция сортировки посредством выбора(по возрастанию)
{
	int temp, iter = 0;
	while(length - iter > 0)
	{
		int iterMin=0, min = INT_MAX;
		for (int i = iter; i < length; i++)			//определяем позицию наименьшего элемента в массиве
		{
			if (mas[i] < min)
			{
				min = mas[i];
				iterMin = i;
			}
		}

		if (iterMin != 0)
		{
			temp = mas[iter];			//меняем местами первый и наименьший элемент массива
			mas[iter] = min;
			mas[iterMin] = temp;
		}
		iter++;
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
#include <iostream>
#include <vector>

void sort(std::vector<int>& mas, int length)	//функция сортировки вставками
{
	int adress, numSorted=1, numUnsorted=length-1, i = 0;
	std::vector<int> tmpMas = {mas[0]};
	std::vector <int>::iterator it;		//итератор для указания вставки в вектор
	while (numUnsorted > 0)
	{
		for (int i = 0; i < numSorted; ++i)
		{
			if ((mas[numSorted] > tmpMas[i]) || (mas[numSorted] == tmpMas[i]))	//если неотсортированное число >= последнему из отсортированных 
			{
				adress = i+1;
			}
			else
			{
				adress = (i==0 ? 0 : i); 
				it = tmpMas.begin() + adress;
				tmpMas.insert(it, mas[numSorted]);
				numSorted++;
				numUnsorted--;
				break;
			}
			if (i == numSorted - 1)
			{
				it = tmpMas.begin() + adress;
				tmpMas.insert(it, mas[numSorted]);
				numSorted++;
				numUnsorted--;
				break;
			}
		}
	}

	for (int i = 0; i < length; i++)
	{
		mas[i] = tmpMas[i];
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
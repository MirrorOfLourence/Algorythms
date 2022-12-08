#include <iostream>
#include <vector>
	
void sort(std::vector<int>& mas, int start, int end)	//функция сортировки слиянием(двухпутевой)
{
    int length = end - start;
    if (length < 2)    //если в массиве 0 или 1 элемент
        return;
    if (length == 2)   //если в массиве 2 элемента
    {
        if(mas[start]>mas[start+1])
            std::swap(mas[start], mas[start+1]);
        return;
    }

    sort(mas, start, start + length/2); //сортируем первую половину 
    sort(mas, start + length/2, end); //сортируем вторую половину 

    std::vector<int> current;
    int s1 = start;                 //начало первой половины
    int e1 = start+ length/2;  //конец первой половины и
    int s2 = e1;                    //начало второй половины
    while (current.size() < length)    //пока текущий массив меньше исходного, сливаем половинки
    {
        if (s1 >= e1 || ((s2 < end) && (mas[s2] <= mas[s1])))
        {
            current.push_back(mas[s2]);
            s2++;
        }
        else
        {
            current.push_back(mas[s1]);
            s1++;
        }
    }

    for (int i = start; i < end; i++)   //перемещаем в исходный массив элементы отсортированного подмассива
    {
        mas[i] = current[i-start];
    }
}

int main()
{
    std::vector<int> mas;
    int length = 0;
    for (int i = 0; i < 11; i++)	//заполняем массив случайными числами
    {
        mas.push_back(rand()%100);
        std::cout << mas[i] << std::endl;
    }
    std::cout <<  std::endl;

    length = mas.size();
    sort(mas, 0, length);
    for (int i = 0; i < length; i++)	//выводим массив
    {
        std::cout << mas[i] << std::endl;
    }
	return 0;
}
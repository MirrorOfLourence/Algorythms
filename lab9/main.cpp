#include <iostream>
#include <vector>
	
void sort(std::vector<int>& mas, int length)	//функция пирамидальной сортировки
{
    int i = length/2 - 1;	//итератор просеиваемого элемента

    int depth = 1;
    for (int k = length, modif = 1; k > 0; )
    {
        depth++;
        modif*=2;
        k -= modif;
    }

    for (; i >= 0 ; i--)
    {
        int j = 1;
        for (int k = i, modif = 1; k > 0; ) //находим слой нахождения элемента
        {
            j++;
            modif*=2;
            k -= modif;
        }

        int pos = i;
        while (j < depth)	//пока элемент не ушёл на нижний слой
        {
            if (2*pos+1 > length-1)
            {
                break;
            }
            if ((mas[pos] > mas[2*pos+1])&&(mas[pos] > mas[2*pos + 2]))	//если левый лист меньше, поднимаем его
            {
                if (mas[2 * pos + 1] <= mas[2 * pos + 2])	//поднимаем наименьший из листьев
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    std::swap(mas[pos], mas[2*pos+2]);
                    j++;
                    pos = 2*pos+2;
                    continue;
                }
              
            }
            else
            {
                if (mas[pos] > mas[2*pos + 1])	//если правый лист меньше, поднимаем его
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    if (mas[pos] > mas[2*pos + 2])	//если правый лист меньше, поднимаем его
                    {
                        std::swap(mas[pos], mas[2*pos+2]);
                        j++;
                        pos = 2*pos+2;
                        continue;
                    }
                }
            }
            
            j++;
        }
    }

    i = length-1;
    for (; i > 0 ; i--)
    {
        
        std::swap(mas[0], mas[i]);   //меняем местами очередной элемент с корневым

        int j = 1;
        int pos = 0;
        while (j < depth)	//пока элемент не ушёл на нижний слой
        {
            if (2*pos+1 > length-1)
            {
                break;
            }

            if ((mas[pos] > mas[2*pos+1])&&(mas[pos] > mas[2*pos + 2])&&(2*pos+1 < i)&&(2*pos+2 < i))	//если левый лист меньше, поднимаем его
            {
                if (mas[2 * pos + 1] <= mas[2 * pos + 2])	//поднимаем наименьший из листьев
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    std::swap(mas[pos], mas[2*pos+2]);
                    j++;
                    pos = 2*pos+2;
                    continue;
                }

            }
            else
            {
                if ((mas[pos] > mas[2*pos + 1])&&(2*pos+1 < i))	//если правый лист меньше, поднимаем его
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    if ((mas[pos] > mas[2*pos + 2])&&(2*pos+2 < i))	//если правый лист меньше, поднимаем его
                    {
                        std::swap(mas[pos], mas[2*pos+2]);
                        j++;
                        pos = 2*pos+2;
                        continue;
                    }
                }
            }
            j++;
        }
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
    sort(mas, length);
    for (int i = 0; i < length; i++)	//выводим массив
    {
        std::cout << mas[i] << std::endl;
    }
	return 0;
}
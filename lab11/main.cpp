#include <iostream>
#include <vector>
	

void quicksort(int *start, int *end)	//������� ���������� 
{
    if(end - start <= 1) {return;}

    int *p_pivot = (start + (end - start)/2);
    int pivot = *p_pivot;
    int *l = start, *r = end;
    
    while(l<=r)
    {
        while(*l < pivot) {l++;}
        while(*r > pivot) {r--;}
        if (l <= r)
        {
            std::swap(*l, *r);
            l++;
            r--;
        }
    }

    if(start < r) { quicksort(start, r+1); }
    if(l < end) { quicksort(l, end); }
}

int main()
{
    std::vector<int> mas;
    int length = 0;
    for (int i = 0; i < 11; i++)	//��������� ������ ���������� �������
    {
        mas.push_back(rand()%100);
        std::cout << mas[i] << std::endl;
    }
    std::cout <<  std::endl;

    length = mas.size();
    quicksort(&mas[0], &mas[length-1]);
    for (int i = 0; i < length; i++)	//������� ������
    {
        std::cout << mas[i] << std::endl;
    }
	return 0;
}
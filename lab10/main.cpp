#include <iostream>
#include <vector>
	
void sort(std::vector<int>& mas, int start, int end)	//������� ���������� ��������(�����������)
{
    int length = end - start;
    if (length < 2)    //���� � ������� 0 ��� 1 �������
        return;
    if (length == 2)   //���� � ������� 2 ��������
    {
        if(mas[start]>mas[start+1])
            std::swap(mas[start], mas[start+1]);
        return;
    }

    sort(mas, start, start + length/2); //��������� ������ �������� 
    sort(mas, start + length/2, end); //��������� ������ �������� 

    std::vector<int> current;
    int s1 = start;                 //������ ������ ��������
    int e1 = start+ length/2;  //����� ������ �������� �
    int s2 = e1;                    //������ ������ ��������
    while (current.size() < length)    //���� ������� ������ ������ ���������, ������� ���������
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

    for (int i = start; i < end; i++)   //���������� � �������� ������ �������� ���������������� ����������
    {
        mas[i] = current[i-start];
    }
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
    sort(mas, 0, length);
    for (int i = 0; i < length; i++)	//������� ������
    {
        std::cout << mas[i] << std::endl;
    }
	return 0;
}
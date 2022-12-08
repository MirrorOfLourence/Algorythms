#include <iostream>
#include <vector>
	
void sort(std::vector<int>& mas, int length)	//������� ������������� ����������
{
    int i = length/2 - 1;	//�������� ������������� ��������

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
        for (int k = i, modif = 1; k > 0; ) //������� ���� ���������� ��������
        {
            j++;
            modif*=2;
            k -= modif;
        }

        int pos = i;
        while (j < depth)	//���� ������� �� ���� �� ������ ����
        {
            if (2*pos+1 > length-1)
            {
                break;
            }
            if ((mas[pos] > mas[2*pos+1])&&(mas[pos] > mas[2*pos + 2]))	//���� ����� ���� ������, ��������� ���
            {
                if (mas[2 * pos + 1] <= mas[2 * pos + 2])	//��������� ���������� �� �������
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
                if (mas[pos] > mas[2*pos + 1])	//���� ������ ���� ������, ��������� ���
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    if (mas[pos] > mas[2*pos + 2])	//���� ������ ���� ������, ��������� ���
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
        
        std::swap(mas[0], mas[i]);   //������ ������� ��������� ������� � ��������

        int j = 1;
        int pos = 0;
        while (j < depth)	//���� ������� �� ���� �� ������ ����
        {
            if (2*pos+1 > length-1)
            {
                break;
            }

            if ((mas[pos] > mas[2*pos+1])&&(mas[pos] > mas[2*pos + 2])&&(2*pos+1 < i)&&(2*pos+2 < i))	//���� ����� ���� ������, ��������� ���
            {
                if (mas[2 * pos + 1] <= mas[2 * pos + 2])	//��������� ���������� �� �������
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
                if ((mas[pos] > mas[2*pos + 1])&&(2*pos+1 < i))	//���� ������ ���� ������, ��������� ���
                {
                    std::swap(mas[pos], mas[2*pos+1]);
                    j++;
                    pos = 2*pos+1;
                    continue;
                }
                else
                {
                    if ((mas[pos] > mas[2*pos + 2])&&(2*pos+2 < i))	//���� ������ ���� ������, ��������� ���
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
    for (int i = 0; i < 11; i++)	//��������� ������ ���������� �������
    {
        mas.push_back(rand()%100);
        std::cout << mas[i] << std::endl;
    }
    std::cout <<  std::endl;

    length = mas.size();
    sort(mas, length);
    for (int i = 0; i < length; i++)	//������� ������
    {
        std::cout << mas[i] << std::endl;
    }
	return 0;
}
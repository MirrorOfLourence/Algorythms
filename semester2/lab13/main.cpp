#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

std::string text;   //входной текст
std::string sample; //образец поиска
std::unordered_map<char, int> tableBad;
std::vector<int> tableGood;
std::vector<int> answer;
int sampleSize=0;

void operatingTableB()   //создаём таблицу сдвигов для плохих символов, для тех, которых нет и последнего - длина шаблона,
{   //для остальных индекс последнего вхождения с конца шаблона
    for (int i = 0; i < sampleSize-1; i++)
    {
        tableBad[sample[i]] = sampleSize - 1 - i;
    }
}
bool isPrefix(int p)    //ф-ия для проверки, является ли подстрока, с индекса p, префиксом sample
{
    int j = 0;
    for (int i = p; i < sampleSize; i++)
    {
        if(sample[i] != text[j])
            return false;
        j++;
    }
    return true;
}
int suffixLength(int p) //ф-ия возвращает для позиции p длину максимального суффикса шаблона. 
{
    int len = 0;
    int i = p;
    int j = sampleSize-1;
    while ((i >= 0) && (text[i] == sample[j]))
    {
        len++; i--; p--;
    }
    return len;
}
void operatingTableG()
{
    int lastPrefPos = sampleSize;
    for (int i = sampleSize - 1; i >= 0; i--)
    {
        // Если подстрока является префиксом, то запомним её начало
        if(isPrefix(i+1))
            lastPrefPos = i+1;
        tableGood[sampleSize - i - 1] = lastPrefPos - i + sampleSize - 1;
    }
    //Вычислении функции
    for (int i = 0; i < sampleSize - 2; i++)
    {
        int slen = suffixLength(i);
        tableGood[slen] = lastPrefPos - 1 - i + slen;
    }
}

void BM()   //Ф-ия по алгоритму Боейра-Мура
{
    if (sampleSize == 0)
    {
        std::cout << "Искомая подстрока не найдена!" << std::endl;   //пустой шаблон
        return;
    }
    operatingTableB();
    operatingTableG();
    for (int i = sampleSize - 1; i < text.size(); i++)
    {
        int j = sampleSize-1;
        while ( j >= 0 &&(sample[j] == text[i]))
        {
            if(j==0)
            {
                answer.push_back(i);    //найдена подстрока в позиции i
                break;
            }
            j--; i--;
        } 
        i += (tableGood[sampleSize - j - 1] > tableBad[text[i]]) ? tableGood[sampleSize - j - 1] : tableBad[text[i]];
    }
    if (answer.empty())
        std::cout << "Искомая подстрока не найдена!" << std::endl;
}
int main()
{
    setlocale(LC_ALL, "Rus");

    std::cout << "Введите образец для поиска: ";
    std::cin >> sample;
    std::cout << std::endl;
    sampleSize = sample.size();

    std::ifstream in;   //поток на вход
    in.open("input.txt");   //загружаем в поток файл ввода
    if (in.is_open())   //если файл открылся, то
    {
        std::getline(in, text);
        for (char c : text) //добавляем алфавит
        {
            tableBad.insert({c, sample.size()});
        }
        tableGood.resize(sample.size(), 0);
        BM();
    }
    for (int iter : answer)
    {
        std::cout << "\t" << iter;
    }
    std::cout << std::endl;

    return 0;
}
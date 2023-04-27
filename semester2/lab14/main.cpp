#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

std::string text;   //входной текст
std::string sample; //образец 
std::vector<int> answer;
int alphabetSize=26;
int q = INT_MAX;

void rabinKarp()
{
    int sampleSize = sample.size();
    int strSize = text.size();
    int i = 0, j = 0;
    int hashSample = 0, hashText = 0, h = 1;

    for (i = 0; i < sampleSize - 1; i++)    //h = (alpabetSize ^ sampleSize) % q
    {
        h = (h*alphabetSize) % q;
    }

    for (i = 0; i < sampleSize; i++)    //рассчитываем хеш шаблона и первого кусочка текста
    {
        hashSample = (alphabetSize * hashSample + sample[i]) % q;
        hashText = (alphabetSize * hashText + text[i]) % q;
    }

    for (i = 0; i <= text.size() - sampleSize; i++)
    {
        if (hashSample == hashText) //если хеши совпали, проверяем посимвольно шаблон и кусочек текста
        {
            for (j = 0; j < sampleSize; j++)
            {
                if(text[i+j] != sample[j])  //если нашли несовпадение, прекращаем проверку
                    break;
            }
            if (j == sampleSize)    //Если в предыдущем цикле дошли до конца, то добавляем индекс очередного совпадения
                answer.push_back(i);
        }
        if (i < text.size() - sampleSize)   //пересчитываем хеш для следующего кусочка текста
        {   
            hashText = (alphabetSize * (hashText -  text[i] * h) + text[i + sampleSize])%q;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    std::cout << "Введите образец для поиска: ";
    std::cin >> sample;
    std::cout << std::endl;

    std::ifstream in;   //поток на вход
    in.open("input.txt");   //загружаем в поток файл ввода
    if (in.is_open())   //если файл открылся, то
    {
        std::getline(in, text);
        rabinKarp();
    }
    for (int iter : answer)
    {
        std::cout << "Совпадние обнаружено по итератору: " << iter << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
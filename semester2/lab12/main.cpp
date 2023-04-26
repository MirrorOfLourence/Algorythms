#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::string text;   //входной текст
std::string sample; //образец поиска
std::vector<int> prefix;    //префикс-функция

std::vector<int> prefixFunction ()  //построение префикс-функции
{
    int n = (int) text.length();    //длина текста
    std::vector<int> pi (n);    //вектор для указания совпадения символов с образцом
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];    //число совпадений равно числу совпадений предыдущего символа
        while (j > 0 && text[i] != text[j]) //пока есть хотя бы одно совпадение и символы строки и образца не совпадают
            j = pi[j-1];    //откатываем число совпадений до значения для прошлого символа
        if (text[i] == text[j])  ++j;   //если символы строки и образца совпали, увеличиваем текущее значений совпадений
        pi[i] = j;  //записываем число совпадений для текущего символа
    }
    return pi;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    std::cout << "Введите образец дл¤ поиска: ";
    std::cin >> sample;
    std::cout << std::endl;

    std::ifstream in;   //поток на вход
    in.open("input.txt");   //загружаем в поток файл ввода
    if (in.is_open())   //если файл открылс¤, то
    {
        std::getline(in, text);
    }
    text = "" + sample + "#" + text;
    prefix = prefixFunction();
    for (int i = 0; i < prefix.size(); i++)
    {
        if(prefix[i] == sample.size()) 
            std::cout << "Вхождение подстроки по индексу:\t" << i - sample.size()*2<< std::endl;
    }
    return 0;
}
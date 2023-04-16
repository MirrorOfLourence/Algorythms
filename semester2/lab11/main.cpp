#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

std::unordered_map<char, std::vector<int>> automata;
std::string text;
std::string sample;
std::string alphabet;

std::string getSuf(const std::string& str)
{
    int matched = 0;
    std::string result = "";
    for (int i = 1; i <= str.size(); i++)
    {
        std::string pref = sample.substr(0, i);
        std::string suf = str.substr(str.size() - i);
        if (pref == suf)
        {
            result = suf;
            matched = suf.size();
        }
        else
            matched = 0;
    }
    return result;
}

void buildAutomata()
{
    int numOfChars = alphabet.size();
    int lengthOfSample = sample.size();
    for (int i = 0; i < lengthOfSample; i++)
    {
        std::string substr = sample.substr(0, i); //создаЄм подстроку
        for (int j = 0; j < numOfChars; j++)
        {
            substr.push_back(alphabet[j]);
            int matched = 0;
            std::string suf = getSuf(substr);
            matched = suf.size();
            
            automata[alphabet[j]][i] = matched;
            substr.pop_back();
        }

    }
}

void workAutomata()
{
    int state = 0;
    int countOfMatches = 0;
    for (int i = 0; i < text.size(); i++)
    {
        if (state == sample.size())
        {
            std::cout << "¬хождение є" << ++countOfMatches << ":\t" << i - sample.size() << std::endl;
            state = 0;
            continue;
        }
        state = automata[text[i]][state];

    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    
    std::cout << "¬ведите образец дл€ поиска: ";
    std::cin >> sample;
    std::cout << std::endl;

    std::ifstream in;   //поток на вход
    in.open("input.txt");   //загружаем в поток файл ввода
    if (in.is_open())   //если файл открылс€, то
    {
        std::getline(in, text);
        for (char c : text) //добавл€ем алфавит
        {
            automata.insert({c,std::vector<int>(sample.size(), 0)});
        }
        for (auto v : automata)
        {
            alphabet.push_back(v.first);
        }
        buildAutomata();
        workAutomata();
    }
    return 0;
}
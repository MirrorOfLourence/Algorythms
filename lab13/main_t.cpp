//Открытая адресация, линейное зондирование.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class HashNode  //Класс элемента-ячейки таблицы
{
public:
    HashNode(int key, std::string name) //Конструктор класса
        :m_key(key), m_name(name)
    {}
    std::string name()  //функция, возвращающая имя в ячейке
    {
        return m_name;
    }
    int key()
    {
        return m_key; //функция, возвращающая ключ ячейки
    }
private:
    int m_key;
    std::string m_name;
};

class HashTable //Класс хеш-таблицы
{
public:
    HashTable() //по умолчанию создаём таблицу на first_size ключей
    {
        for (int i = 0; i < first_size; i++)
        {
            hash_table.push_back(HashNode(i,""));
        }
    };

    int getFS() //ф-ия, возвращает first_size
    {
       return first_size;
    }

    int hashFunction(const std::string& str);   //хеш-функция

    void insert(const std::string& node);   //ф-ия вставки элемента

    std::string get(const std::string& str);    //ф-ия получения имени элемента таблицы

    int size();

    HashNode operator[] (int key)   //перегрузим оператор для класса hash_table
    {
        return hash_table[key];
    }

private:
    std::vector<HashNode> hash_table;
    int first_size = 12;
};

int HashTable::hashFunction(const std::string& str) //хеш-функция, для получения ключа
{
    int hash=0;
    for (auto i = 0; i < str.size(); i++)
    {
        hash+=(str[i]-'0');
    }
    return (hash%37);   //вычисляем через остаток от деления суммы ASCII-значений символов строки
}

void HashTable::insert(const std::string& node) //ф-ия вставки элемента в таблицу
{
    int key = hashFunction(node);   //получаем ключ текущего элемента
    if (key >= hash_table.size())   //если ключ не входит в изначальную таблицу, делаем Push_back в таблицу, т.е. добавляем новую ячейку
    {
        hash_table.push_back(HashNode(key, node));
    }
    else    //в противном случае:
    {
        int i = key;
        bool flag = false;
        while(hash_table[i].name() != "")   //пока элемент ячейки с нужным нам ключом не пустой, смотрим следующий элемент
        { 
            i++;
        }
        if (hash_table.size() < i)  //если не нашли свободных ячеек в таблице, добавляем новую
        {
            hash_table.push_back(HashNode(key,node));
        }
        else    //иначе записываем в первую, считая с целевой, пустую ячейку по ключу
        {
            hash_table[i] = HashNode(key, node);
            return;
        } 
    }
    return;
}

std::string HashTable::get(const std::string& str)  //ф-ия, возвращающая имя по ключу
{
    int key = hashFunction(str);
    if(hash_table.size()-1 < key)   //если ключ выходит за границы таблицы, придаём ему значение последнего из возможных элементов изначальной таблицы
        key = getFS();
    for (int i = key; i < hash_table.size(); i++)   //циклом проверяем совпадения имён
    {
        if (hash_table[i].name() == str)
        {
            return hash_table[i].name();
        }
    }
    return "ERROR: Line is not found!"; //если не нашли, выводим сообщение от ошибке поиска
}
        
int HashTable::size()      //ф-ия, возвращает текущий размер хеш-таблицы
{
    return hash_table.size();
};


int main()
{

    HashTable ht;
    std::string line;
    int a = 1;

    std::ifstream in("input.txt");
    std::ofstream out;
    if (in.is_open())   //циклом выводим в консоль считанные из файла строки, вставляя их в хеш-таблицу по ключу
    {
        while (getline(in, line))
        {
            ht.insert(line);
            std::cout << a << ") "<< ht.get(line) << std::endl;
            a++;
        }
    }
    in.close();

    out.open("output.txt", std::ios::out | std::ios::trunc);
    out << "key\t|\tline\n";
    int i = 0;
    for (; i < ht.size() - 1; i++)      //записываем в файл вывода элементы хеш-таблицы, как они там лежат
    {
        out << ht[i].key() << "\t|\t" << ht[i].name() << "\n";
    }
    out << ht[i].key() << "\t|\t" << ht[i].name();
    out.close();

    return 0;
}

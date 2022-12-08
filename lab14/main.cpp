//Метод цепочек

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>


class Identifier
{
public:
    Identifier(const std::string& name):
        m_name(name)
    {
    }

public:
    std::string name() const
    {
        return m_name;
    }

private:
    std::string m_name;
};

bool operator==(const Identifier& left, const Identifier& right)
{
    return left.name() == right.name();
}

class IDNotFound : std::exception
{
public:
    IDNotFound(const std::string id_name):
        m_what(std::string("Identifier \'") + id_name + "\' not found!")
    {
    }

public:
    const char *what() const throw()
    {
        return m_what.c_str();
    }

private:
    std::string m_what;
};


size_t hash(const Identifier& id)
{
    if (id.name().length() == 1)
        return 2 * size_t(id.name()[0]);

    return size_t(id.name()[0]) + size_t(id.name()[1]);
}

class HashTable
{
public:
    static const size_t min_hash_value = int('A') + int('0');
    static const size_t max_hash_value = int('z') + int('z');
    static const size_t hash_table_size = max_hash_value - min_hash_value;

public:
    void add(const Identifier& id)
    {
        m_hash_table[hash(id) - min_hash_value].push_back(id);
    }

    Identifier& get(const std::string& id_name)
    {
        std::list<Identifier>& line = m_hash_table[hash(id_name) - min_hash_value];

        std::list<Identifier>::iterator it =
            std::find(line.begin(), line.end(), id_name);

        if (it == line.end())
            throw IDNotFound(id_name);

        return *it;
    }

private:
    std::list<Identifier> m_hash_table[hash_table_size];
};

int main()
{

    setlocale(LC_ALL, "Russian");


    HashTable ht;
    std::string line;
    int a = 1;

    std::ifstream in("input.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            ht.add(Identifier(line));
            std::cout << a << ") "<< ht.get(line).name() << std::endl;
            a++;
        }
    }
    in.close();
    

    try//пример, когда значение не найдено в таблице
    {
        std::cout << ht.get("hello").name() << std::endl;
    }
    catch (const IDNotFound &ex)
    {
        std::cerr << ex.what() << std::endl;
    }


}
//ќткрыта¤ адресаци¤, линейное зондирование

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class HashNode
{
public:
    HashNode(int key, std::string name)
        :m_key(key), m_name(name)
    {}
    std::string name()
    {
        return m_name;
    }
    int key()
    {
        return m_key;
    }
private:
    int m_key;
    std::string m_name;
};

class HashTable
{
public:
    HashTable()
    {
        for (int i = 0; i < first_size; i++)
        {
            hash_table.push_back(HashNode(i,""));
        }
    };

    int getFS()
    {
       return first_size;
    }

    int hashFunction(const std::string& str);

    void insert(const std::string& node);

    std::string get(const std::string& str);

    int size();

    HashNode operator[] (int key)
    {
        return hash_table[key];
    }

private:
    std::vector<HashNode> hash_table;
    int first_size = 12;
};

int HashTable::hashFunction(const std::string& str)
{
    int hash=0;
    for (auto i = 0; i < str.size(); i++)
    {
        hash+=(str[i]-'0');
    }
    return (hash/37);
}

void HashTable::insert(const std::string& node)
{
    int key = hashFunction(node);
    if (key >= hash_table.size())
    {
        hash_table.push_back(HashNode(key, node));
    }
    else
    {
        int i = key;
        bool flag = false;
        while(hash_table[i].name() != "")
        { 
            i++;
        }
        if (hash_table.size() < i)
        {
            hash_table.push_back(HashNode(key,node));
        }
        else
        {
            hash_table[i] = HashNode(key, node);
            return;
        } 
    }
    return;
}

std::string HashTable::get(const std::string& str)
{
    int key = hashFunction(str);
    if(hash_table.size()-1 < key)
        key = getFS();
    for (int i = key; i < hash_table.size(); i++)
    {
        if (hash_table[i].name() == str)
        {
            return hash_table[i].name();
        }
    }
    return "ERROR: Line is not found!";
}

int HashTable::size()
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
    if (in.is_open())
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
    for (; i < ht.size() - 1; i++)
    {
        out << ht[i].key() << "\t|\t" << ht[i].name() << "\n";
    }
    out << ht[i].key() << "\t|\t" << ht[i].name();
    out.close();

    return 0;
}

//Открытая адресация, линейное зондирование

#include <iostream>
#include <string>
#include <vector>
#include <stack>

struct tNode //Класс элемента бинарного дерева
{ 
    int data;
    int level;
    tNode* left;
    tNode* right;
    tNode* parent;
};

tNode* MAKE(int data, tNode* p)  //Ф-ия создания узла
{
    tNode* q = new tNode;
    q->data = data;
    q->level = (p==nullptr ? 0 : p->level+1);
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void ADD(int data, tNode*& root)    //Ф-ия добавления элемента по правилам БДП
{
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    tNode* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    tNode* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}

void ADD_FICTIVE(int data, tNode*& root, bool is_left)  //Функция добавления элемента на основе скобочной записи
{
    tNode* v = root;
    tNode* u = MAKE(data, v);
    if(is_left)
        v->left = u;
    else
        v->right = u;
}

void FILL(std::string& str, int& i, tNode*& root)   //Функция заполнения бинарного дерева на основе скобочной записи
{
    int value=0;
    /*while ((str[i] >= '0') && (str[i] <= '9'))  //Если в строке число, пишем его в значение узла
    {
        value += value*10 + str[i] - '0';
        i++;
    }
    ADD(value, root);*/

    while (str[i] != '\0')
    {
        switch (str[i])
        {
        case '(':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))  
            {
                value = value*10 + str[i] - '0';
                i++;
            }

            if (value!=0)
            {
                ADD_FICTIVE(value, root, true);
                if(str[i] == '(')
                    FILL(str, i, root->left);
            }
            value = 0;
            break;
        }    
        case ',':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))  
            {
                value = value*10 + str[i] - '0';
                i++;
            }

            if (value!=0)
            {
                ADD_FICTIVE(value, root, false);
                if(str[i] == '(')
                    FILL(str, i, root->right);
            }
            value = 0;
            break;
        }
            
        case ')':
            i++;
            return;
        default:
            break;
        }
    }
}

void PASS(tNode* v)
{
    if (v == nullptr)
        return;

    PASS(v->left);
     
    std::cout << v->data << std::endl;

    PASS(v->right); 
}

tNode* SEARCH(int data, tNode* v)   
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}

void DELETE(int data, tNode*& root)
{ 
    tNode* u = SEARCH(data, root);
    if (u == nullptr)
        return;

    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }
  
    if (u->left == nullptr && u->right != nullptr && u == root) // u==root
    {
        tNode* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
  
    if (u->left != nullptr && u->right == nullptr && u == root) // u==root
    {
        tNode* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }
    
    if (u->left != nullptr && u->right != nullptr)
    {
        tNode* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    tNode* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}


void CLEAR(tNode*& v)
{
    if (v == nullptr)
        return; 

    CLEAR(v->left); 

    CLEAR(v->right);

    delete v;
    v = nullptr;
}

void PRINT(tNode* root)
{
    if (root == nullptr)
    {
        std::cout << std::endl;
        return;
    }
        

    PRINT(root->right);

    for (int i = root->level; i > 0; i--)
    {
        std::cout << '\t';
    }
    std::cout << root->data << std::endl;

    PRINT(root->left); 
}

void work(tNode* root)
{
    std::cout << "\t\t\t\tMENU\t\t\t\t" <<std::endl;

    int oper;
    bool flag=false;
    while (!flag)
    {
        std::cout << "Enter a number for operation:" << std::endl;
        std::cout << "add(0)\tdelete(1)\tsearch(2)\texit(3)" << std::endl;
        std::cin >> oper;
        switch (oper)
        {
        case 0:
        {
            int val;
            std::cout << "Enter the value to add: ";
            std::cin >> val;
            ADD(val, root);
            break;
        }
        case 1:
        {
            int val;
            std::cout << "Enter the value to delete: ";
            std::cin >> val;
            DELETE(val, root);
            break;
        }   
        case 2:
        {
            int val;
            std::cout << "Enter the value to search: ";
            std::cin >> val;

            tNode* e = nullptr;
            e = SEARCH(val, root);
            std::cout << "Element " << (e==nullptr ? "not found!" : "found!") << std::endl;
            break;
        }  
        case 3:
            flag = true;
            break;
        default:
            break;
        }
    }
    PRINT(root);
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::string str;
    std::cout << "Введите выражение в скобочном виде!" << std::endl;
    std::cin >> str;

    tNode* root = nullptr;

    int value=0, i=0;
    while ((str[i] >= '0') && (str[i] <= '9'))  //Если в строке число, пишем его в значение узла
    {
        value += value*10 + str[i] - '0';
        i++;
    }
    ADD(value, root);
    FILL(str,i, root);

    //PASS(root);
    
    //1(2(,4(7,8)),3(5(,9(11,)),6(10,)))
    //8(3(1,6(4,7)),10(,14(13,)))
    
    work(root);

    CLEAR(root);

    return 0;
}

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

tNode* MAKE(int data, tNode* p)  //ф-ия, создающая очередной элемент бинарного дерева
{
    tNode* q = new tNode;   //создаём структуру
    q->data = data; //записываем данные
    q->level = (p==nullptr ? 0 : p->level+1);   //уровень элемента в дереве, необходим для вывода дерева в удобном виде
    q->left = nullptr;  //левый потомок - изначально nullptr
    q->right = nullptr; //правый потомок - тоже
    q->parent = p;  //адрес родительского элемента
    return q;
}

void ADD(int data, tNode*& root)   //ф-ия добавления элементов по правилам Бинарного Дерева Поиска(далее БДП)
{
    if (root == nullptr) {   //если родительский элемент - нулевой, имеет дело с корнем
        root = MAKE(data, nullptr);
        return;
    }
    tNode* v = root;    //иначе создаём временную переменную v
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))    //пока выполняются условия существования бинарного дерева
        if (data < v->data) //если значение нового элемента меньше родительского, переходим на левого потомка
            v = v->left;
        else    //иначе на правого потомка
            v = v->right;
    if (data == v->data)    //если данные повторяются, выходим из функции, т.к. в БДП данные уникальны
        return;
    tNode* u = MAKE(data, v);   //создаём элемент-потомка в зависимости от значения нового элемента, и полученного указателя в v
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}

void ADD_FICTIVE(int data, tNode*& root, bool is_left)  //Фиктивная функция добавления элемента, для создания бинарного дерева по скобочной записи
{   //упрощённая версия ф-ии ADD
    tNode* v = root;
    tNode* u = MAKE(data, v);
    if(is_left)
        v->left = u;
    else
        v->right = u;
}

void FILL(std::string& str, int& i, tNode*& root)   //Ф-ия заполнения бинарного дерева из скобочной записи
{
    int value=0;

    while (str[i] != '\0')  //пока не дочитали до конца строки, посимвольно обрабатываем:
    {
        switch (str[i])
        {
        case '(':   //если считали скобку, считаем следующее за ней число
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))  
            {
                value = value*10 + str[i] - '0';
                i++;
            }

            if (value!=0)   //если число отлично от 0, то добавляем его в дерево через ADD_FICTIVE
            {
                ADD_FICTIVE(value, root, true);
                if(str[i] == '(')
                    FILL(str, i, root->left);   //и переходим рекурсивно на левого потомка предыдущего элемента
            }
            value = 0;
            break;
        }    
        case ',':   //если встречаем запятую, также считываем число за ней
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))  
            {
                value = value*10 + str[i] - '0';
                i++;
            }

            if (value!=0)   //если число отлично от нуля, то добавляем его в дерево через ADD_FICTIVE
            {
                ADD_FICTIVE(value, root, false);
                if(str[i] == '(')
                    FILL(str, i, root->right);  //и переходим рекурсивно на правого потомка предыдущего элемента
            }
            value = 0;
            break;
        }
            
        case ')':   //если встречаем закрывающую скобку, переходим на следующий элемент и выходим из текущей итерации ф-ии считывания
            i++;
            return;
        default:
            break;
        }
    }
}

void PASS(tNode* v) //ф-ия вывода бинарного дерева(в порядке, как они расположены в дереве, где корень будет в центре)
{
    if (v == nullptr)
        return;

    PASS(v->left);
     
    std::cout << v->data << std::endl;

    PASS(v->right); 
}

tNode* SEARCH(int data, tNode* v)   //ф-ия поиска элемента дерева
{
    if (v == nullptr)    //если искомый узел - nullptr, выходим из ф-ии
        return v;
    if (v->data == data)    //если данные совпадают, то возвращаем искомый элемент
        return v;
    if (data < v->data) //иначе рекурсивно ищем у левого потомка, если данные меньше, чем в рассматриваемом элементе
        return SEARCH(data, v->left);
    else    //или у правого, если больше
        return SEARCH(data, v->right);
}

void DELETE(int data, tNode*& root) //ф-ия удаления элемента дерева
{ 
    tNode* u = SEARCH(data, root);
    if (u == nullptr)    //если искомый элемент уже пустой, выходим из ф-ии
        return;

    if (u->left == nullptr && u->right == nullptr && u == root) //если все потомки нулевые, а искомый элемент - текущий, то:
    {
        delete root;    //удаляем искомый элемент,
        root = nullptr;     //заменяем указатель на него на nullptr
        return;     //выходим из ф-ии
    }
  
    if (u->left == nullptr && u->right != nullptr && u == root) // если правый потомок не нулевой, то 
    {
        tNode* t = u->right;    //создаём временную переменную с правым потомком искомого элемента
        while (t->left != nullptr)  //пока его левый потомок отличен от нуля, сдвигаемся на него
            t = t->left;
        u->data = t->data;  //передаём искомому элементу значения найденного левого потомка
        u = t;  //переназначаем указатели
    }
  
    if (u->left != nullptr && u->right == nullptr && u == root) //аналогично прошлому шагу, для левого потомка
    {
        tNode* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }
    
    if (u->left != nullptr && u->right != nullptr)   //если оба потомка отличны от нуля, делаем то же, что и для правого 
    {
        tNode* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    tNode* t;
    if (u->left == nullptr) //если левый потомок полученной u нулевой, то записываем во вновь созданную переменную t значение правого потомка u
        t = u->right;
    else    //иначе - левого
        t = u->left;
    if (u->parent->left == u) //если левый потомок родителя u == u -> переназначаем левого потомка родителя u на временную переменную t
        u->parent->left = t;
    else    //иначе - правого потомка
        u->parent->right = t;
    if (t != nullptr)   //если t - не nullptr, 
        t->parent = u->parent;  //то перезаписываем родительский элемент t на родительский элемент u
    delete u;   //наконец, удаляем u
}


void CLEAR(tNode*& v)   //ф-ия удаления бинарного дерева, освобождения выделенной памяти
{
    if (v == nullptr)   //если подан нулевой элемент, выходим из функции, дерево и так удалено
        return; 

    CLEAR(v->left);     //иначе рекурсивно вызываем ф-ию очистки для левого

    CLEAR(v->right);    //и правого потомков текущего

    delete v;   //удаляем текущий элемент
    v = nullptr;    //заменяем на nullptr;
}

void PRINT(tNode* root) //ф-ия вывода функции в консоль с помощью меню
{
    if (root == nullptr)    //если указанные элемент - нулевой, выходим из функции
    {
        std::cout << std::endl;
        return;
    }
        

    PRINT(root->right); //рекурсивно переходим к правому потомку текущего узла

    for (int i = root->level; i > 0; i--)   //печатаем количество табов, равное уровню узла в дереве
    {
        std::cout << '\t';
    }
    std::cout << root->data << std::endl;   //печатаем значение узла

    PRINT(root->left); //рекурсивно переходим к левому потомку текущего узла
}

void work(tNode* root)  //ф-ия, реализующая меню для работы с деревом
{
    std::cout << "\t\t\t\tMENU\t\t\t\t" <<std::endl;

    int oper;
    bool flag=false;
    while (!flag)   //пока не дана команда на выход из меню, оно работает
    {
        std::cout << "Enter a number for operation:" << std::endl;  //предложение выбрать операцию
        std::cout << "add(0)\tdelete(1)\tsearch(2)\texit(3)" << std::endl;  //список доступных операций
        std::cin >> oper;
        switch (oper)   //обработка введённого значения
        {
        case 0: //в случае 0
        {
            int val;
            std::cout << "Enter the value to add: ";    //запрашиваем значение элемента, который нужно добавить
            std::cin >> val;
            ADD(val, root); //добавляем элемент
            break;
        }
        case 1: //в случае 1
        {
            int val;
            std::cout << "Enter the value to delete: "; //запрашиваем значение элемента, который надо удалить
            std::cin >> val;
            DELETE(val, root);  //удаляем элемент
            break;
        }       
        case 2: //в случае 2
        {
            int val;
            std::cout << "Enter the value to search: "; //запрашиваем значение элемента, которое нужно найти
            std::cin >> val;

            tNode* e = nullptr;
            e = SEARCH(val, root);  //ищем элемент
            std::cout << "Element " << (e==nullptr ? "not found!" : "found!") << std::endl; //если найден/не найдён, соответствующе сигнализируем об этом
            break;
        }  
        case 3: //в случае 3
            flag = true;    //выставляем флаг на выход из while
            break;  
        default:
            break;
        }
    }
    PRINT(root);    //после завершения работы с деревом печатаем его
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
        value = value*10 + str[i] - '0';
        i++;
    }
    ADD(value, root);
    FILL(str,i, root);

    //PASS(root);
    
    //8(3(1,6(4,7)),10(,14(13,)))   //ТЕСТИРОВАЛ НА ЭТИХ ОТЛАДОЧНЫХ ЗНАЧЕНИЯХ, НЕОБХОДИМО ВВОДИТЬ ПРАВИЛЬНОЕ БИНАРНОЕ ДЕРЕВО ПОИСКА ДЛЯ КОРРЕКТНОЙ РАБОТЫ
    
    work(root);

    CLEAR(root);

    return 0;
}

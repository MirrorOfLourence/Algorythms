#include <iostream>
#include <string>
#include <vector>
#include <stack>

struct tNode //Класс элемента бинарного дерева
{ 
    int data;
    tNode* left;
    tNode* right;
    tNode* parent;
};

tNode* MAKE(int data, tNode* p)  //ф-ия, создающая очередной элемент бинарного дерева
{
    tNode* q = new tNode;      //создаём структуру
    q->data = data; //записываем данные
    q->left = nullptr;  //левый потомок - изначально nullptr
    q->right = nullptr; //правый потомок - тоже
    q->parent = p;  //адрес родительского элемента
    return q;
}

void ADD(int data, tNode*& root)    //ф-ия добавления элементов по правилам Бинарного Дерева Поиска(далее БДП)
{
    if (root == nullptr) {  //если родительский элемент - нулевой, имеет дело с корнем
        root = MAKE(data, nullptr);
        return;
    }
    tNode* v = root;    //иначе создаём временную переменную v
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))   //пока выполняются условия существования бинарного дерева
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
    if (v == nullptr)   //если искомый узел - nullptr, выходим из ф-ии
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
    if (u == nullptr)   //если искомый элемент уже пустой, выходим из ф-ии
        return;

    if (u->left == nullptr && u->right == nullptr && u == root) //если все потомки нулевые, а искомый элемент - текущий, то:
    {
        delete root;    //удаляем искомый элемент,
        root = nullptr; //заменяем указатель на него на nullptr
        return; //выходим из ф-ии
    }

    if (u->left == nullptr && u->right != nullptr && u == root) // если правый потомок не нулевой, то 
    {
        tNode* t = u->right;    //создаём временную переменную с правым потомком искомого элемента
        while (t->left != nullptr)  //пока его левый потомок отличен от нуля, сдвигаемся на него
            t = t->left;
        u->data = t->data;  //передаём искомому элементу значения найденного левого потомка
        u = t;  //переназначаем указатели
    }
    
    if (u->left != nullptr && u->right == nullptr && u == root) // u==root  //аналогично прошлому шагу, для левого потомка
    {
        tNode* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right != nullptr)  //если оба потомка отличны от нуля, делаем то же, что и для правого 
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
    if (u->parent->left == u)   //если левый потомок родителя u == u -> переназначаем левого потомка родителя u на временную переменную t
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

void preorder(tNode* root)  //ф-ия прямого обхода
{
    if(root == nullptr) //если текущий элемент - нулевой, то
        return; //выходим из функции
    std::cout << root->data << std::endl;   //сначала выводим значение текущего узла
    
    preorder(root->left);   //затем рекурсивно вызываем ф-ию для его левого потомка
    preorder(root->right);  //затем для правого
}

void inorder(tNode* root)   //ф-ия прямого обхода
{
    if(root == nullptr) //если текущий элемент - нулевой, то
        return; //выходим из функции
    inorder(root->left);    //сначала рекурсивно вызываем ф-ию для левого потомка текущего узла
    std::cout << root->data << std::endl;   //затем - выводим значение текущего узла
    inorder(root->right);   //затем - рекурсивно вызываем ф-ию для правого потомка текущего узла
}

void postorder(tNode* root) //ф-ия прямого обхода
{
    if(root == nullptr) //если текущий элемент - нулевой, то
        return; //выходим из функции
    postorder(root->left);  //сначала рекурсивно вызываем ф-ию для левого потомка текущего узла
    postorder(root->right); //затем - рекурсивно вызываем ф-ию для правого потомка текущего узла
    std::cout << root->data << std::endl;   //затем - выводим значение текущего узла
    
}

void leveled_order(tNode* root) //ф-ия не рекурсивного прямого обхода
{
    std::stack<tNode*> stack;   //создаём стек(из стандартной библиотеки)
    stack.push(root);      //кладём в него корень дерева

    while (!stack.empty()) //пока стек не опустеет, выполняем:
    {
        tNode* node = stack.top();  //берём элемент с верхушки стека
        stack.pop();    //удаляем взятый элемент из стека
        std::cout << node->data << std::endl;   //выводим значение текущего элемента

        if (node->left != nullptr)  //если левый потомок текущего узла - не пустой, то
        {
            stack.push(node->left); //кладём его(левый потомок) в стек
        }
        if (node->right != nullptr) //аналогично для правого потомка
        {
            stack.push(node->right);
        }
    }
}


int main()
{
    setlocale(LC_ALL, "rus");

    std::string str;
    std::cout << "Введите выражение в скобочном виде!" << std::endl;
    std::cin >> str;

    tNode* root = nullptr;

    int value=0, i=0;   //Рассчитываем корневой элемент дерева
    while ((str[i] >= '0') && (str[i] <= '9'))  //Если в строке число, пишем его значение в значение узла
    {
        value = value*10 + str[i] - '0';
        i++;
    }
    ADD(value, root);   //Добавляем корневой элемент дерева
    FILL(str,i, root);  //Заполняем дерево из скобочной записи

    //PASS(root);

    std::cout << "\nПрямой обход:\n_______________________________\n";
    preorder(root);
    std::cout << "\nЦентральный обход:\n_______________________________\n";
    inorder(root);
    std::cout << "\nКонцевой обход\n_______________________________\n";
    postorder(root);
    std::cout << "\nНе рекурсивный прямой обход\n_______________________________\n";
    leveled_order(root);
    std::cout << "\n_______________________________\n";
    //1(2(,4(7,8)),3(5(,9(11,)),6(10,)))    //ТЕСТИРОВАЛ НА ЭТИХ ОТЛАДОЧНЫХ ЗНАЧЕНИЯХ

    CLEAR(root);    //очищаем динамическую память

    return 0;
}

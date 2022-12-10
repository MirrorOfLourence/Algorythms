//Îòêðûòàÿ àäðåñàöèÿ, ëèíåéíîå çîíäèðîâàíèå

#include <iostream>
#include <string>
#include <vector>
#include <stack>

struct tNode //Êëàññ ýëåìåíòà áèíàðíîãî äåðåâà
{ 
    int data;
    int level;
    tNode* left;
    tNode* right;
    tNode* parent;
};

tNode* MAKE(int data, tNode* p)  //Ô-èÿ ñîçäàíèÿ óçëà
{
    tNode* q = new tNode;
    q->data = data;
    q->level = (p==nullptr ? 0 : p->level+1);
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void ADD(int data, tNode*& root)    //Ô-èÿ äîáàâëåíèÿ ýëåìåíòà ïî ïðàâèëàì ÁÄÏ
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

void ADD_FICTIVE(int data, tNode*& root, bool is_left)  //Ôóíêöèÿ äîáàâëåíèÿ ýëåìåíòà íà îñíîâå ñêîáî÷íîé çàïèñè
{
    tNode* v = root;
    tNode* u = MAKE(data, v);
    if(is_left)
        v->left = u;
    else
        v->right = u;
}

void FILL(std::string& str, int& i, tNode*& root)   //Ôóíêöèÿ çàïîëíåíèÿ áèíàðíîãî äåðåâà íà îñíîâå ñêîáî÷íîé çàïèñè
{
    int value=0;
    /*while ((str[i] >= '0') && (str[i] <= '9'))  //Åñëè â ñòðîêå ÷èñëî, ïèøåì åãî â çíà÷åíèå óçëà
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

void preorder(tNode* root)
{
    if(root == nullptr)
        return;
    std::cout << root->data << std::endl;
    
    preorder(root->left);
    preorder(root->right);
}

void inorder(tNode* root)
{
    if(root == nullptr)
        return;
    inorder(root->left);
    std::cout << root->data << std::endl;
    inorder(root->right);
}

void postorder(tNode* root)
{
    if(root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << std::endl;
    
}

void leveled_order(tNode* root)
{
    std::stack<tNode*> stack;
    stack.push(root);

    while (!stack.empty())
    {
        tNode* node = stack.top();
        stack.pop();
        std::cout << node->data << std::endl;

        if (node->left != nullptr)
        {
            stack.push(node->left);
        }
        if (node->right != nullptr)
        {
            stack.push(node->right);
        }
    }
}


int main()
{
    setlocale(LC_ALL, "rus");

    std::string str;
    std::cout << "Ââåäèòå âûðàæåíèå â ñêîáî÷íîì âèäå!" << std::endl;
    std::cin >> str;

    tNode* root = nullptr;

    int value=0, i=0;
    while ((str[i] >= '0') && (str[i] <= '9'))  //Åñëè â ñòðîêå ÷èñëî, ïèøåì åãî â çíà÷åíèå óçëà
    {
        value += value*10 + str[i] - '0';
        i++;
    }
    ADD(value, root);
    FILL(str,i, root);

    PASS(root);

    std::cout << "\n\n_______________________________\n";

    preorder(root);
    std::cout << "\n_______________________________\n";
    inorder(root);
    std::cout << "\n_______________________________\n";
    postorder(root);
    std::cout << "\n_______________________________\n";
    leveled_order(root);
    std::cout << "\n_______________________________\n";
    //1(2(,4(7,8)),3(5(,9(11,)),6(10,)))
    //8(3(1,6(4,7)),10(,14(13,)))


    CLEAR(root);

    return 0;
}

// Copied from gitlab, missed the school lesson not my names of vars
//Binary tree

#include <iostream>
using namespace std;

class Item
{
public:
    int key = 0;

    Item* left = nullptr;
    Item* right = nullptr;
};

Item* find (Item* p, int value)
{
    if (p == nullptr) 
    { 
        // nenasel
    }
    else if (p->key == value) 
    {
        // nasel
    }
    else if (value < p->key) 
    {
        p = find (p->left, value);
    }
    else 
    {
        p = find (p->right, value);
    }
    return p;
}

Item* search (Item* top, int value)
{
    Item* p = top;

    while (p != nullptr && p->key != value)
    {
        if (value < p->key)
            p = p->left;
        else
            p = p->right;
    }

    return p;
}

void insert (Item * & p, int value)
{
    if (p == nullptr)
    {
        // nasel jsem vhodne misto
        p = new Item;
        p->key = value;
        p->left = nullptr;
        p->right = nullptr;
    }
    else if (p->key == value)
    {
        // hodnota jiz je ve stromu
    }
    else if (value < p->key)
    {
        insert (p->left, value);
    }
    else
    {
        insert (p->right, value);
    }
}

void print (Item*p, int level = 1) {
    if (p != nullptr) {

        for (int i = 2; i <= level; i++)
        {
            cout << "---- ";
        }
        cout << p->key << endl;

        print(p->left, level + 1);
        print(p->right, level + 1);
    }
}


Item* unlink(Item* & e) // najdi nejvetsi, odpoj
{
    if (e->right != nullptr)
    {
        return unlink(e->right);
    }
    else
    {
        Item* t = e;
        e = e->left;
        return t;

    }
}

void remove (Item * & p, int value)
{
    if (p == nullptr)
    {
        // nenasel jsem hodnotu ve stromu
    }
    else if (value < p->key)
    {
        remove (p->left, value);
    }
    else if (value > p->key)
    {
        remove (p->right, value);
    }
    else // if (p->key == value)
    {
        // nasel jsem hodnotu k vymazani
        Item* t = p;
        if (p->left == nullptr)
        {
            p = p->right;
        }
        else if (p->right == nullptr)
        {
            p = p->left;
        }
        else
        {
            // dva podstromy
            Item* u = unlink (p->left); // nahradnik, najdi nejvetsi, odpoj
            u->left = p->left;
            u->right = p->right;
            p = u; // ukotveni
        }
        delete t;
    }
}

Item* root = nullptr;

int main()
{
    insert(root, 7);
    insert(root, 4);
    insert(root, 8);
    insert(root, 20);
    insert(root, 1);
    insert(root, 5);

    // for (int i = 30; i <= 40; i++)
    //    insert(root, i);

    remove(root, 7);

    Item* myRes = search (root, 20);
    cout << (myRes ? "Nasel jsem" : "Nenasel jsem") << endl;

    print (root);
    cout << "O.K." << endl;
}

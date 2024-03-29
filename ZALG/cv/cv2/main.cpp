#include <iostream>
#include <cassert> //could be assert.h

using namespace std;

enum {OK};

class myList; // has to have forward declaration of myList or myItem, depends whats written first

class myItem
{
    // public:
    //     myItem* getFirst() {return first;};
    //     myItem* getLast() {return last; };
    public: //private: 
        myList* link;
        string name;
        int red;
        int blue;
        int green;
        myItem* next;
        myItem* prev;
        //myItem () : name(""), red(0), blue(0), green(0),next(nullptr), prev(nullptr){}
        myItem( string name0="", int r0=0, int g0=0, int b0=0) 
        : link (nullptr), name(name0), red(r0), blue(b0), green(g0),next(nullptr), prev(nullptr){ name = name0; } 

        void insertBefore(myItem* fresh);
        void insertAfter(myItem* fresh);
        void remove();
};

class myList
{
    public:
        myItem* first = nullptr;
        myItem* last = nullptr;

    private:
        void insert (myItem* before, myItem* fresh, myItem* after);

    public:
        void insertFirst(myItem* fresh);
        void insertLast(myItem* fresh);
        void print();

        myItem* find (string name0);

        myList () { }
        ~ myList (); 

        friend class myItem;

};

myList::~myList()
{
    myItem *tmp = first; // could be written like this
    while (tmp)
    {
        myItem* t = tmp->next;
        // t->remove();
        delete tmp;
        tmp = t;
    }
    first = nullptr;
    last = nullptr; 
}

void myList::insert (myItem* before, myItem* fresh, myItem* after)
{
    // assert (first == nullptr && last == nullptr || first != nullptr && last != nullptr)
    assert (fresh);
    assert(fresh->link == nullptr);
    fresh->link = this; //my List

    fresh->prev = before;
    fresh->next = after;

    if (before){
        before->next = fresh;
    }else{
        first = fresh;
    }

    if (after){
        after->prev = fresh;
    }else{
        last = fresh;
    }
}

void myList::insertFirst(myItem *fresh) // puts us inside the class
{
    insert(nullptr, fresh, first); // we don't have to write myList::insert, we are inside the class 
}

void myList::insertLast(myItem* fresh)
{
    insert(last, fresh, nullptr);
}

void myList::print()
{
    //this; //pointer before us

    for (myItem* tmp = first; tmp; tmp = tmp->next){
        cout << "Name: " << tmp->name << " | red: " << tmp->red;
        cout << " blue: " << tmp->blue << " green: " << tmp->green << endl;
    }

    // myItem *tmp = first; // could be written like this
    // while (tmp)
    // {
    //     cout << "Name: " << tmp->name << " | red: " << tmp->red;
    //     cout << " blue: " << tmp->blue << " green: " << tmp->green << endl;
    //     tmp = tmp->next;
    // }
}

void myItem::insertAfter(myItem* fresh)
{
    this->link->insert( this, fresh, this->next);
}

void myItem::insertBefore(myItem *fresh)
{
    link->insert(prev, fresh, this);
}

myItem* myList::find (string name0)
{
    for (myItem *tmp = first; tmp ; tmp = tmp->next){
        if (tmp->name == name0){
            return tmp;
        }
    }
    return nullptr;
}

void myItem::remove()
{
    if (link){ //link != nullptr

        // myItem *before = prev;
        // myItem *after = next;

        if (prev){
            prev->next = next;
        }else{
            link->first = next;
        }
        if (next){
            next->prev = prev;
        }else{
            link->last = prev;
        }

        next = nullptr;
        prev = nullptr;
        link = nullptr;
    }
}


int main()
{
    cout << "---------------------------------" << endl;
    myList l;
    l.insertFirst(new myItem ("red", 255,0,0) );
    l.insertFirst(new myItem ("blue", 0,255,0) );
    l.insertFirst(new myItem ("green", 0,0,255) );
    l.insertFirst(new myItem ("rainbow", 255,255,255) );
    l.first->insertAfter (new myItem ("white", 0,0,0));
    l.print();
    cout << "---------------------------------" << endl;
    myList s;
    s.insertLast(new myItem ("red", 255,0,0) );
    s.insertLast(new myItem ("blue", 0,255,0) );
    s.insertLast(new myItem ("green", 0,0,255) );
    s.insertLast(new myItem ("rainbow", 255,255,255) );
    s.print();
    cout << "---------------------------------" << endl;
    myItem* a = s.find("green");


    if (a){
        cout << a->red << endl;
        a->remove();
        s.insertFirst(a);
        
    }else{
        cout << "Doens't exist" << endl;
    }
    cout << "---------------------------------" << endl;
    s.print();
    cout << "---------------------------------" << endl;

    myList b;
    while (s.first){
        myItem *t = s.first;
        t->remove();
        b.insertFirst(t);
    }
    cout << "Printing list s: " << endl;
    s.print();
    cout << "---------------------------------" << endl;
    b.print();
    cout << "---------------------------------" << endl;
    return OK;
}
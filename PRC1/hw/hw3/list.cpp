#include "list.h"
#include <iostream>


List::List()
        : first(new Element()),
          last(new Element()),
          counter(0)
{
    initList();
}

List::~List(){
    clear();
    delete first;
    delete last;
}

//copy elements from source list into this list
void List::copyDataFrom(List &source){
    Element *iter = source.first->next;
    while(iter!=source.last){
        this->pushBack(iter->getData());
        iter = iter->next;
    }
}

List::List(List &other)
        : first(new Element), last(new Element),
          counter(0)
{
    initList();
    copyDataFrom(other);
}

void List::clear(){
    while(!isEmpty()){
        popFront();
    }
}

void List::initList(){
    first->next = last;
    last->prev = first;
}

void List::pushBack(Data d){
    last->next = new Element;
    last->setData(d);
    last->next->prev = last;
    last = last->next;
    counter++;
}

/*
 * last <-> first
 * next <-> prev
*/
void List::pushFront(Data d){
    first->prev = new Element;
    first->setData(d);
    first->prev->next = first;
    first = first->prev;
    counter++;
}

void List::popFront(){
    if(!isEmpty()){
        first = first->next;
        delete first->prev;
        first->prev = nullptr;
        counter--;
    }
}

void List::popBack(){
    if(!isEmpty()){
        last = last->prev;
        delete last->next;
        last->next = nullptr;
        counter--;
    }
}

void List::print() const{
    for(Element *iter = first->next;
        iter!=last;
        iter = iter->next){
        iter->printLn();
    }
}


Element* List::find(Data d){
    last->setData(d);
    Element *iter = first->next;
    while(iter->getData()!=d){
        iter = iter->next;
    }
    return iter == last ? nullptr : iter;
}

bool List::remove(Data d){
    Element *del = find(d);
    if(!del){
        return del;
    }
    del->prev->next = del->next;
    del->next->prev = del->prev;
    delete del;
    counter--;
    return true;
}

/*
My implementation of 3 given functions
 */

void List::sort()
{
    Element *tmp = first->next;
    Element *min = new Element;
    while (tmp->next != last)
    {
        min = findMin(tmp);
        if (min->getData() >= tmp->getData()){
            tmp = tmp->next;
            continue;
        }else{
            swap(tmp, min);
            tmp = min->next;
        }
    }
}

Element* List::findMin(Element* from)
{
    Element* min = from;
    while (from != last)
    {
        if (from->getData() < min->getData()){
            min = from;
        }
        from = from->next;
    }
    return min;
}

void List::swap(Element *a,Element *b)
{
    /*
    These will be used later, could have been done with less variables but I feel like this
    makes the code more readable
     */
    auto *aNext = a->next;
    auto *bNext = b->next;
    auto *aPrev = a->prev;
    auto *bPrev = b->prev;

    // this code executes is a and be are neighbors
    if (a->next == b)
    {
        //we make a.prev point to b and b.prev to a.prev
        aPrev->next = b;
        b->prev = aPrev;

        // now we change a and b
        b->next = a;
        a->prev = b;

        //at last we change pointers of a.next to b.next and b.next.prev to a;
        a->next =bNext;
        bNext->prev = a;
    }else {
        //firstly we swap pointers before a and b i.e. a.prev points to b and be points to it back  same with
        //b.prev points to a and a points to it back
        aPrev->next = b;
        b->prev = aPrev;
        bPrev->next = a;
        a->prev = bPrev;

        //here we do the same thing but with a.next and b.next
        a->next = bNext;
        bNext->prev = a;
        b->next = aNext;
        aNext->prev = b;
    }


    /*
    This can be only used if we carry only small amount of data, e.g. only some number like
    in this example we have only 1 int in element. So we do not need to swap the whole blocks with pointers
    only the data.

//    Data tmp = a->getData();
//    a->setData(b->getData());
//    b->setData(tmp);
     */
}
/******************************************************************************
* CONVETION: ALl templated types should be defined in header.
******************************************************************************/

#pragma once
#include <initializer_list>
#include <iostream>
#include <stdlib.h>     // For size_t
#include <utility>      // For Move

using namespace std;

template<class T>
class my_list
{
public:
  using element_type = T;
  my_list();
  my_list(initializer_list<T>);
  my_list(const my_list&); // Copy constructor
  my_list(my_list&&); // Move constructor
  ~my_list();

  // assignments operators
  my_list& operator=(my_list& l);
  my_list& operator=(my_list&& l);

  // joining operators
  my_list operator+(const my_list& s)const&;
  my_list operator+(my_list&& s)const&;

  // insertion
  void push_front(T&);
  void push_front(T&&);
  void push_back(T&);
  void push_back(T&&);

  // deletion
  void remove_first();
  void clear();

  // states
  size_t size() {return num_of_elements; }
  bool is_empty() {return head == sentinel; }

  // helper
  void print() const;

  // utilities
  void swap(my_list& l);
  void swap(my_list&& l);

private:
  struct element;
  element* head = nullptr;
  element* sentinel = nullptr;
  size_t num_of_elements = 0;

  void copy(const my_list& l);
};

// templated element
template<class T>
struct my_list<T>::element
{
  T data;
  element* next;
  // element(T data, element* next): data(data), next(next) {}
  element(T _data, element* _next): data(_data), next(_next) {}

  // allocates only for specific element (not other types of data - more at std::alllocator)
  // void* operator new(size_t v);
};

// Also does not matter if I use class or typename (there is small diff)
// I can name the parameter how ever I want
template<typename TT>
my_list<TT>::my_list()
{
  head = sentinel = new element{TT{}, nullptr};
}

template<typename T>
//my_list<T>::my_list(initializer_list<T> list): my_list() ???
my_list<T>::my_list(initializer_list<T> list)
{
  head = sentinel = new element{T{}, nullptr};
  for (auto i : list)
  {
    push_back(i);
  }
}

template<class T>
inline my_list<T>::my_list(const my_list& l): my_list()
{
  copy(l);
}

template<class T>
my_list<T>::my_list(my_list&& l)
{
  swap(l);
}

template<typename T>
my_list<T>::~my_list()
{
  clear();
  delete sentinel;
}

// "copy-assignment operator"
template<class T>
my_list<T>& my_list<T>::operator=(my_list& l)
{
  clear();
  copy(l);
  return *this;
}

// move operator
template<class T>
my_list<T>& my_list<T>::operator=(my_list&& l)
{
  swap(l);
  return *this;
}

// right operand is r-value
template<class T>
my_list<T> my_list<T>::operator+(const my_list<T>& l)const&
{
  my_list<T> res(*this);
  res.copy(l);
  return res;
}

// right operand is r-value
template<class T>
my_list<T> my_list<T>::operator+(my_list<T>&& l)const&
{
  my_list<T> res(*this);
  res.copy(l);
  return res;
}

// l-value -> variables e.g. push_back(i)
// r-value -> random numbers e.g. push_back(20)

// This is what r-value (I have &&). Basically MOVE
template<typename T>
void my_list<T>::push_back(T&& what)
{
  sentinel->data = move(what);
  sentinel->next = new element{ T{}, nullptr};
  sentinel = sentinel->next;
  ++num_of_elements;
}


// l-value. Basically COPY
template<typename T>
void my_list<T>::push_back(T& what)
{

  sentinel->data = what;
  sentinel->next = new element{ T{}, nullptr};
  sentinel = sentinel->next;
  ++num_of_elements;
}

template<typename T>
void my_list<T>::push_front(T& what)
{
  head = new element{ what, head };
  ++num_of_elements;
}

template<typename T>
void my_list<T>::push_front(T&& what)
{
  head = new element{ move(what), head };
  ++num_of_elements;
}

template<typename T>
void my_list<T>::remove_first()
{
  if (!is_empty())
  {
    auto tmp = head;
    head = head->next;
    delete tmp;
    --num_of_elements;
  }
}

template<typename T>
void my_list<T>::clear()
{
  while(!is_empty())
  {
    remove_first();
  }
}

template<class T>
void my_list<T>::print() const
{
  auto tmp = head;
  cout << "( ";
  while (tmp != sentinel)
  {
    cout << tmp->data << ", ";
    tmp = tmp->next;
  }
  cout << ")" << endl;;
}

template<class T>
void my_list<T>::swap(my_list& l)
{
  std::swap(head, l.head);
  std::swap(sentinel, l.sentinel);
  std::swap(num_of_elements, l.num_of_elements);
}

template<class T>
void my_list<T>::swap(my_list&& l)
{

  std::swap(head, l.head);
  std::swap(sentinel, l.sentinel);
  std::swap(num_of_elements, l.num_of_elements);
}

template<class T>
void my_list<T>::copy(const my_list& l)
{
  for (auto tmp = l.head; tmp != l.sentinel; tmp = tmp->next)
  {
    push_back(tmp->data);
  }
}


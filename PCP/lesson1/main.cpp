#include <utility>      // For Move
#include "my_list_templated.h"

using namespace std;

int main()
{
  my_list<int> l1 {1,2,3};
  my_list<int> l;
  l.push_back(20);
  l.push_back(30);

  l.print();
  l1.print();
  int i = 20;
  l.push_front(i);

  my_list<int> l2 = l1;

  l2.print();

  // Using move -> creates r-value
  l2 = std::move(l);

  l2.print();

  my_list<int> l3;

  l3 = l1 + l2;
  l3.print();

  return 0;
}

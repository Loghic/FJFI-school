#include <iostream>
using namespace std;
// Forwarded reference or universal reference. It can return L-value or R-value
auto&& f()
{
  return 1;
}
/*****************************************************************************/
class Showcase
{
  int i;
public:
  Showcase(int i ) : i(i){}
  int get_value() {return i;}
  int value(this Showcase self)
  {
    self.i++;
    return self.i;
  }
};

int main()
{
  Showcase u{5};
  u.value();
  cout << "u.value(class): " <<  u.value() << "\nu.get_value(): " << u.get_value() << endl;
}

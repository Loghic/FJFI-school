#include <ios>
#include <iostream>
#include <type_traits>
#include <utility>

using namespace std;

template<class T, class = std::void_t<>>
struct has_preincrement : std::false_type
{};

template<class T>
struct has_preincrement<T, std::void_t<decltype(++std::declval<T&>())> > : std::true_type
{};

class Numero1
{
  int i;
public:
  Numero1(int i) : i(i) {}
  Numero1& operator++() { ++i; return *this; }
};

class Numero2
{
  int i;
public:
  Numero2(int i) : i(i) {}
  Numero2 operator++(int) { ++i; return *this; }
};



template<class T>
constexpr bool has_preincrement_in = has_preincrement<T>::value;

int main(int argc, char* argv[])
{
  std::cout << std::boolalpha;
  std::cout << has_preincrement_in<Numero1> << std::endl;
  std::cout << has_preincrement_in<Numero2> << std::endl;
  cout << "Hello sablono\n";
  return 0;
}


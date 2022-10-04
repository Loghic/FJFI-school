#include "napis.hpp"
#include "napis.cpp"

int main()
{
    Napis napis("Nazdar, lidi"s); // "s" za stringem, aby vedel, ze je to string
    // napis.text = "ahoj"; Nefunguje 'text' je private
    napis.vypis();
    return 0;
}
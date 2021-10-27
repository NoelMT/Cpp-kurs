#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void write_date ( string text, int d = 31, int m = 12, int y = 2021 );

int main()
{
  cout << "Test av en datumfunktion: " << endl;

  write_date ( "Julafton i år", 24  );             // anrop av funktionen write_date
  return 0;
}

void write_date ( string &text, int d, int m, int y )
{
string test;

test = text;

cout << test << endl;
}

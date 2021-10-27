#include <iostream>
#include <string>
using namespace std;

void frekvenser(const string &rad, int & bokstaever, int & siffror, int & ovriga);


// Anm. Värdeanrop för "rad", dvs.
// void frekvenser(string rad, osv. ) också möjligt.

int main()
{
  string rad;
  cout<<"Mata in en rad text: ";
  getline(cin,rad);

  int b,s,o;  // b =bokstäver, s=siffror, o = övriga tecken.

  frekvenser(rad,b,s,o);
  cout << "Antal bokstäver = " << b<< endl;
  cout << "Antal siffror = " << s<< endl;
  cout << "Antal övriga tecken = " << o << endl;

  return 0;
}

void frekvenser(const string &rad, int & bokstaever, int & siffror, int & ovriga)
{
  bokstaever=siffror=ovriga=0;
  for (int i=0; i< (int) rad.length(); i++)
    {
      if (isalpha(rad.at(i))) bokstaever++;
      else if (isdigit(rad.at(i))) siffror++;
      else ovriga++;
    }
}

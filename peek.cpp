#include <cctype>
#include <iostream>
#include <string>



using namespace std;
 int main()
 {

   return 0;
 }

 void enFunktion( string s ){
  char tmp;
  for ( int i = 0; i < s.length(); i++ ){
    tmp = s.at(i);
    if ( isupper(tmp) ){
      cout << tmp;
    }
  }
  cout << endl;
}

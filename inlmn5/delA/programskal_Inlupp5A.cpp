//
// Programskal till obluppg5A
//
// Hanterar fallet med 26 bokstäver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska.TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså ej skickas
// som parameter till den funktion som behöver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Här kommer klassdeklarationen
class Text
{
private:
    string texten;
    int abs[ANTAL_BOKSTAVER];
    int antbok;
public:
    Text();
    void setText( const string &nyText );
    bool beraknaHistogramAbs();
    void skrivHistogramAbs();


};
// -------------------------------------------------------

// Huvudprogram:

int main()
{
 // Deklarera variabler
  string text;
  int antal;
  Text minText;// Ett objekt av typen Text skapas

  // Läs in en rad med text från tangentbordet
  cout <<"Ge en rad med text:" << endl;
  getline(cin,text);

  // Skicka strängen text till objektet minText
  minText.setText( text );

  // Beräkna och skriv ut histogrammet
  antal = minText.beraknaHistogramAbs( );
  minText.skrivHistogramAbs( );

  return 0;
}

// -------------------------------------------------------
// Här skriver du klassimplementationen
    Text::Text(){
    texten = "";
    for (int i = 0; i< ANTAL_BOKSTAVER;i++)
        abs[i] = 0;
    antbok = 0;
    }

//--------------------------------------------------------
// Funktionsdefinitioner:
void Text::setText( const string &nyText ){

    texten = nyText;
}
bool Text::beraknaHistogramAbs(){
    int antal = 0;
    int pos = 0;
for ( int i=0; i< (int) texten.length(); i++)
    {
      if (texten.at(i)>='a' && texten.at(i)<='z'){
      antal++;
      pos = texten.at(i) - 'a';
      abs[pos]++;
        }
        else if (texten.at(i)>='A' && texten.at(i)<='Z'){ //r‰knar alla stora bokst‰ver
        antal++;
        pos = texten.at(i) - 'A';
      abs[pos]++;
            }
    }
    antbok = antal;
    if (antal > 0){
        return true;
    }
    else {
        return false;
    }
}
void Text::skrivHistogramAbs(){
    cout << "\n" << "Resultat fˆr bokst‰verna A-Z" << endl << endl;
    cout << "Totalt antal bokst‰ver: " << antbok << endl;
    cout << "Bokstavsfˆrdelning:" << endl << endl;
for (int i=0; i<ANTAL_BOKSTAVER; i++)
    {
      // bˆrjar med ett A sen ˆkar med 1 varje loop sÂ att n‰sta ascii v‰rde blir n‰sta bokstav
      char bokstav = char (i+'A');
       cout << bokstav << ":" << "  " << abs[i] <<endl;
    }
}



// -------------------------------------------------------
// Rapport om uppgiften

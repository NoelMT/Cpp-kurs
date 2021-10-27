//
// Programskal till inlämningsuppgift 4 - deluppgift B
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
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
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
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string & rad, int arr[] );

// Funktionen abs_till_rel
void abs_till_rel(double frekv[],int arr[], int &num);
// Funktionen plotta_histogram_rel
void plotta_histogram(double frekv[]);
// Funktionen tolkning
void tolka(double frekv[], int &num);
// Funktionen namn_pa_fil
string namn_pa_fil();
// Funktionen inlasning
string inlasning(string &namn);
//--------------------------------------------------------
// Huvudprogram:

int main()
{
// varibeldeklaration
    string rad,fil,text;
    int arr[ANTAL_BOKSTAVER];
    double frekv[ANTAL_BOKSTAVER];
    //nollställer array
    for (int i=0; i < ANTAL_BOKSTAVER; i++){
    frekv[i] = 0.0;
    arr[i] = 0;
    }
    //anropar namnpåfil och inläsning som hämtar text från en fil som anges i programet, om filen inte hittas fråga loppen igen efter nytt filnamn
    do{
    fil = namn_pa_fil();
    cout << "\n";
    text = inlasning(fil);
    }
    while(text == "FILSAKNAS"  );

    //rad = "hej test";

    int num = berakna_histogram_abs(text,arr); //funktions anropp

    abs_till_rel(frekv,arr,num);

    plotta_histogram(frekv);

    tolka(frekv,num);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:

int berakna_histogram_abs(string & rad, int arr[] ){ //funktion som tar emot en sträng och en array sedan returneras antalet bokstäver
int antal = 0;
for ( int i=0; i< (int) rad.length(); i++)
    {
      int pos;
      if (rad.at(i)>='a' && rad.at(i)<='z'){    //räknar alla små bokstäver
      pos = rad.at(i) - 'a'; //använder skillnaden för att ta reda på vilken bokstav i arrayen som ska ökas
      arr[pos]++;
      antal++;
        }
        else if (rad.at(i)>='A' && rad.at(i)<='Z'){ //räknar alla stora bokstäver
        pos = rad.at(i) - 'A';
        arr[pos]++;
        antal++;
            }
    }



    return antal; //array är alltid referens parametrar därför behövs den inte returneras
}

void abs_till_rel(double frekv[],int arr[], int &num){ //funktion som ej returnerar något men gör om från antalet gången varje bokstav har använts till procent
for(int i = 0; i < ANTAL_BOKSTAVER; i++){
    frekv[i] = ((double)arr[i] /(double)num)*100;
}
}

void plotta_histogram(double frekv[]){  //skriver ut Bokstavsfordelning med * och varje * är 0.5%
 cout << "Bokstavsfordelning:" << "\n" << "\n";

  for(int i=0; i<ANTAL_BOKSTAVER; i++)
    {
        char bokstav = char (i+'A');
        cout << bokstav << ": ";

        for(int j=0; j<frekv[i]*2; j++){
            cout << "*";
            }
        cout << "\n";
    }
}

void tolka(double frekv[], int &num){ //funktion som räknar ut kvadrat summan sedan hittar vilket språk texten liknar mest med hjälp av 2dim TOLK_HJALP arrayen
string namn[4] = {"Engelska", "Franska", "Svenska", "Tyska"};
double tot[4] = {0,0,0,0};
double delta;
double min;
int pos = 0;

for(int i = 0; i < 4;i++){
    for(int j = 0; j < ANTAL_BOKSTAVER; j++){
        delta = TOLK_HJALP[i][j] - frekv[j];
        tot[i] += (delta*delta);
    }
}
min = tot[0];

cout << "\nTotala antalet bokstäver: "  << num << endl;
for(int i = 0; i < 4 ;i++){
    cout << namn[i] << " Kvadratsumman ar: " << tot[i] << endl;
    if(min > tot[i]){
        min = tot[i];
        pos = i;
    }
}

cout << namn[pos] << " ar det mest troliga spraket." << endl << endl;
}

string namn_pa_fil(){ //funktion som läser in en rad text och sedan kollar om ".txt" finns i strängen finns med om det inte finns läggs det till

string namn;

cout << "Ange fil namn: ";
    getline(cin, namn);

size_t chek = namn.rfind(".txt");

if(chek == string::npos){
    namn = namn + ".txt";
    }

    return namn;
}

string inlasning(string &namn){ //funktionen tar emot ett filnamn och om filen finns så läser den in texten till en sträng som returneras

string text;

    ifstream in(namn.c_str());

    if(!in.good())
    {
        cout << namn << " kan ej hittas." << endl;
        return "FILSAKNAS";
    }

    while(in.good())
    {
        char tecken = in.get();
        if(in.good())
            text = text + tecken;
    }

    in.close();

    return text;
}
// -------------------------------------------------------
// Rapport om uppgiften

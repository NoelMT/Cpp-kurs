//
// Programskal till inlŠmningsuppgift 4 - deluppgift A
//
// Hanterar fallet med 26 bokstäver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

int berakna_histogram_abs(string & rad, int arr[]);

void skriv_histogram_abs(int arr[]);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
  // Deklarera variabler
    string rad;
    int arr[ANTAL_BOKSTAVER];
    //nollställer array
    for (int i=0; i < ANTAL_BOKSTAVER; i++)
    arr[i] = 0;


  // Läs in en rad med text från tangentbordet
    cout<<"skriv in en rad text: ";
    getline(cin,rad);

  // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
  // och antalet bokstäver.
    berakna_histogram_abs(rad,arr);


  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
    skriv_histogram_abs(arr);

  return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string & rad, int arr[] ){ //funktion som tar emot en sträng och en array sedan returneras antalet bokstäver som har använts
for ( int i=0; i< (int) rad.length(); i++)
    {
      int pos;
      if (rad.at(i)>='a' && rad.at(i)<='z'){    //räknar alla små bokstäver
      pos = rad.at(i) - 'a'; //använder skillnaden för att ta reda på vilken bokstav i arrayen som ska ökas
      arr[pos]++;
        }
        else if (rad.at(i)>='A' && rad.at(i)<='Z'){ //räknar alla stora bokstäver
        pos = rad.at(i) - 'A';
        arr[pos]++;
            }
    }
    int antal = 0;

    for (int i = 0; i < ANTAL_BOKSTAVER;i++){ //räknar antalet bokstäver som används i raden
        if(arr[i] > 0){
            antal++;
            }
        }
    return antal; //array är alltid referens parametrar därför behövs den inte returneras
}

void skriv_histogram_abs(int arr[]){
 for (int i=0; i<ANTAL_BOKSTAVER; i++)
    {
      // börjar med ett A sen ökar med 1 varje loop så att nästa ascii värde blir nästa bokstav
      char bokstav = char (i+'A');
       cout << bokstav << ":" << "  " << arr[i] <<endl;
    }

}



// Redovisning av uppgiften i ord.

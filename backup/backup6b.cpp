//
// Programskal till obluppg5A
//
// Hanterar fallet med 26 bokstŠver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int MAX_KOMPISAR = 10;
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;




//--------------------------------------------------------
//klassdeklarationen
class Transaktion
 {
 private:
   string datum;
   string typ;
   string namn;
   double belopp;
   int    antal_kompisar;
   //string kompisar[MAX_PERSONER];
   string *kompisar;


 public:
   Transaktion();
   ~Transaktion();
   Transaktion& operator=( const Transaktion& t);
   string hamtaNamn() const;
   string hamtaNamn();
   double hamtaBelopp();
   int    hamtaAntalKompisar();
   bool   finnsKompis(const string &namnet);
   bool   lasIn(istream &is);
   void   skrivUt(ostream &os);
   void   skrivTitel(ostream &os);
   double rakna_skuld(string namn);
 };

 class Person
 {
 private:
   string namn;
   double betalat_andras; // ligger ute med totalt
   double skyldig;        // skyldig totalt

 public:
   Person();
   Person(const string &namn, double betlt, double skyld);
   double hamtaBetalat();
   double hamtaSkyldig();
   string hamtanamn();
   void   skrivUt(ostream &os);

};

class PersonLista
 {
 private:
   int    antal_personer;
   Person personer[MAX_PERSONER];

 public:
   PersonLista();
   ~PersonLista();
   void   laggTill(Person ny_person);
   void   skrivUtOchFixa(ostream &os);
   double summaSkyldig();
   double summaBetalat();
   bool   finnsPerson(const string& namn);
 };

 class TransaktionsLista
 {
 private:
   int         antal_transaktioner;
   //Transaktion transaktioner[MAX_TRANSAKTIONER];
   Transaktion *transaktioner;


 public:
   TransaktionsLista();
   ~TransaktionsLista();
   void   lasIn(istream & is);
   void   skrivUt(ostream & os);
   void   laggTill(Transaktion & t);
   double totalKostnad();
   double liggerUteMed(const string &namnet);
   double arSkyldig(const string &namnet);
   PersonLista FixaPersoner();
   int hamta_transaktioner();
 };
// -------------------------------------------------------
// Funktionen namn_pa_fil
string namn_pa_fil();
// Funktionen inlasning
string inlasning(string &namn);
// Huvudprogram:

int main()
{
  cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  std::ifstream     is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            { Transaktion transaktion;
            cout << "Antal trans = " <<transaktioner.hamta_transaktioner() << endl;
              transaktion.skrivTitel(cout);
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivTitel(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
             // if(){}
              double ar_skyldig = transaktioner.arSkyldig(namn);

              if (ar_skyldig == 0.)
                cout << "Personen finns inte med i listan :(" << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;

              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

// -------------------------------------------------------
// HŠr skriver du klassimplementationen
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    antal_kompisar = 0;
}
Transaktion::~Transaktion()
{


}
string Transaktion::hamtaNamn(){
    return namn;
}
double Transaktion::hamtaBelopp(){
return belopp;
}
int Transaktion::hamtaAntalKompisar(){
return antal_kompisar;
}
bool Transaktion::finnsKompis(const string &namnet){

    bool check = false;

    for (int i = 0; i < MAX_PERSONER; i++){
    if (kompisar[i].compare(namnet) == 0)
        check = true;
    }
    return check;
}
bool  Transaktion::lasIn(istream &is){

    is >> datum >> typ >> namn >> belopp >> antal_kompisar;

    kompisar = new string[antal_kompisar];
    for(int i = 0; i <antal_kompisar; i++){
        is >> kompisar[i];
        }
    return !is.eof();
   }
void Transaktion::skrivUt (ostream &os){
 os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
    for(int i = 0; i < antal_kompisar; i++){
        os << kompisar[i] << "\t";
}
    os << "\n";
   }


void Transaktion::skrivTitel(ostream &os){
    os << "Datum" << "\t" << "typ" << "\t" << "namn" << "\t" << "belopp" << "\t" << "Antal och lista av kompisar" << "\n";
   }
TransaktionsLista::TransaktionsLista()
{
    antal_transaktioner = 0;
    transaktioner = 0;

}
TransaktionsLista::~TransaktionsLista()
{

    delete[] transaktioner;
    transaktioner = 0;
}
 void   TransaktionsLista::lasIn(istream & is){
  Transaktion ny;

  while (ny.lasIn(is)){

  laggTill(ny);

  }
 }
void   TransaktionsLista::skrivUt(ostream & os){
    for (int i = 0; i < antal_transaktioner; i++ ){
       transaktioner[i].skrivUt(os);
    }

   }
void   TransaktionsLista::laggTill(Transaktion & t){
// transaktioner[antal_transaktioner++] = t;

Transaktion *nyTrans = 0;
    nyTrans = new Transaktion[antal_transaktioner+1]; // Skapa array med antal+1 elem.

    for ( int i = 0; i < antal_transaktioner; i++ )  //Kopiera in de gamla
	{
	  nyTrans[i] = transaktioner[i];
	}

      nyTrans[antal_transaktioner] = t;     // lägg in transaktion sist i arrayen
      antal_transaktioner++;          // öka antalet transaktioner i arrayen

      delete [] transaktioner; // Avallokera minne.

      transaktioner = nyTrans;       // Sätt array till nya arrayen.

   }
  double TransaktionsLista::totalKostnad(){
      double sum = 0;
    for(int i = 0; i < antal_transaktioner; i++){
  sum += transaktioner[i].hamtaBelopp();
    }
    return sum;
  }
double TransaktionsLista::liggerUteMed(const string &namnet){
string namn;
double sum = 0;
for (int i = 0; i < antal_transaktioner; i++){
    namn = transaktioner[i].hamtaNamn();
    if(namn.compare(namnet) == 0){
    sum += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));

        }
    }
    return sum;
}
double TransaktionsLista::arSkyldig(const string &namnet){
    bool check;
    double sum = 0;
    for(int i = 0; i < antal_transaktioner;i++){
      //  check = transaktioner[i].finnsKompis(namnet);
        if(transaktioner[i].finnsKompis(namnet)){
            sum += transaktioner[i].rakna_skuld(namnet);
        }
    }
    return sum;
}
PersonLista TransaktionsLista::FixaPersoner(){
PersonLista nylist;
string nam;
double betala = 0;
double skuld = 0;
bool check;
    for(int i = 0; i < antal_transaktioner; i++){
        nam = transaktioner[i].hamtaNamn();
        check = nylist.finnsPerson(nam);
        if(check == 0){
            Person nya(nam, liggerUteMed(nam),arSkyldig(nam));
            nylist.laggTill(nya);
        }
    }
    return nylist;
}
Person::Person()
{
    namn = "";
    betalat_andras = 0.0;
    skyldig = 0.0;
}
Person::Person(const string &nam, double betlt, double skyld)
{
    namn = nam;
    betalat_andras = betlt;
    skyldig = skyld;
}
double Person::hamtaBetalat()
{
    return betalat_andras;
}
double Person::hamtaSkyldig()
{
    return skyldig;
}
string Person::hamtanamn()
{
    return namn;
}
void Person::skrivUt(ostream &os)
{
    os << namn << " ligger ute med: " << hamtaBetalat() <<" och är skyldig: " << hamtaSkyldig() << " " ;
    if(hamtaSkyldig() < hamtaBetalat())
    {
        os << hamtanamn() << " Skall ha " << hamtaBetalat() - hamtaSkyldig() << " från potten!" << endl;
    }
    else
    {
        os << hamtanamn() << " Skall lägga " << hamtaSkyldig() - hamtaBetalat() << " till potten!" << endl;
    }
}
PersonLista::PersonLista()
{
    antal_personer = 0;
}
PersonLista::~PersonLista()
{
}
void PersonLista::laggTill(Person ny_person)
{
    personer[antal_personer++] = ny_person;
}
void   PersonLista::skrivUtOchFixa(ostream &os){
os << "-----------------------------------------------------------" <<endl;
    for(int i = 0; i < antal_personer; i++)
    {
        personer[i].skrivUt(os);
    }
    if (summaSkyldig() == summaBetalat())
        os << "\nDe belopp personer lägger till potten är lika me de som andra ta från potten!";
}
double PersonLista::summaSkyldig()
{
    double s = 0;
    for(int i = 0; i < antal_personer; i++)
    {
        s += personer[i].hamtaSkyldig();
    }
    return s;
}
double PersonLista::summaBetalat()
{
    double b = 0;
    for(int i = 0; i < antal_personer; i++)
    {
        b += personer[i].hamtaBetalat();
    }
    return b;
}
 bool PersonLista::finnsPerson(const string& namn){  //oklart om maxpersoner borde användas istället
 bool check = false;

    for(int i = 0; i < antal_personer; i++){
        if(personer[i].hamtanamn() == namn){
            check = true;
        }
    }
    return check;
 }
 int TransaktionsLista::hamta_transaktioner(){
 return antal_transaktioner;
 }
 double Transaktion::rakna_skuld(string namn){
double skuld = 0.0;

    for(int i = 0; i < antal_kompisar; i++)
    {
        if(kompisar[i] == namn)
        {
            skuld = belopp / (antal_kompisar + 1);
        }
    }
    return skuld;
 }
Transaktion& Transaktion::operator=( const Transaktion& t)
{
  if (this != &t)
    {
      delete[] kompisar;
      datum          = t.datum;
      typ            = t.typ;
      namn           = t.namn;
      belopp         = t.belopp;
      antal_kompisar = t.antal_kompisar;
      kompisar       = new string[antal_kompisar];
      for (int i=0; i < antal_kompisar; i++)
	kompisar[i] = t.kompisar[i];
    }
  return *this;
}
//--------------------------------------------------------

// Funktionsdefinitioner:


// -------------------------------------------------------
// Rapport om uppgiften

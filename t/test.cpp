/*
================================================================================
Datorer och programmering, DoP, 10 hsp, termin/�r: VT/2013
Inl�mningsuppgift nr: 6A
Namn: Thomas Nordenmark
Personummer: 810427-8257
Fyll i (alt. stryk det som INTE �r relevant) av nedanst�ende:
Den fil som jag l�mnar in g�r att kompilera och
programmet fungerar f�r alla de testdata som finns f�r uppgiften: Ja
     Om Nej, beskriv vilka testdata som ger problem: -
Jag har anv�nt kompilator/editor: GCC 4.8.1 / LLVM-GCC 4.2.1
                                  GVim 7.4 / MacVim 7.4
Jag har anv�nt f�ljande dator: PC / MacBook 3.1
      med operativsystemet: Arch Linux x64 / OS X Lion 10.7.5
Jag har arbetat ungef�r 15 timmar med denna uppgift
================================================================================
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//---Globala konstanter---
const int MAX_KOMPISAR = 10;
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

//---Deklaration av externa funktioner---
void visaMeny();
int menyVal();

//---Deklaration av programmets klasser---
// Lagrar en persons sammanlagda transaktionsdata
class Person
{
private:
    string namn;
    double betalat_andras;   // ligger ute med totalt
    double skyldig;          // skyldig totalt

public:
    Person();
    Person(string n, double b, double s);
    double haemta_betalat();
    double haemta_skyldig();
    string haemta_namn();
    void skrivUt();
};

// H�ller ordning p� personer som deltar i sammanhanget
class PersonLista
{
private:
    int antal_pers;
    Person pers[MAX_PERSONER];

public:
    PersonLista();
    ~PersonLista();
    void laggTillEn(Person pny);
    void skrivUtOchFixa();
    double summaSkyldig();
    double summaBetalat();
    bool finnsNamn(string namnet);
};

// Lagrar data om en viss transaktion
class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int ant_kompisar;
    string kompisar[MAX_KOMPISAR];

public:
    Transaktion();
    ~Transaktion();
    string haemta_namn();
    double haemta_belopp();
    int haemta_ant_kompisar();
    double haemta_skyldig(string namnet);
    bool finnsKompis(string namnet);
    bool laesEnTrans(istream &is);
    void skrivEnTrans(ostream &os);
};

// Lagrar data om samtliga transaktioner
class TransaktionsLista
{
private:
    Transaktion trans[MAX_TRANSAKTIONER];
    int antalTrans;

public:
    TransaktionsLista();
    ~TransaktionsLista();
    void laesin(istream &is);
    void skrivut(ostream &os);
    void laggTill(Transaktion &t);
    double totalkostnad();
    double liggerUteMed(string namnet);
    double aerSkyldig(string namnet);
    PersonLista FixaPersoner();
};

//---Huvudprogram---
int main()
{
    // Deklaration av variabler
    int menyval = -1; // Menyvalet f�r huvudmenyn
    int antal = 0; // Antal nya transaktioner f�r denna session
    string namnet; // Namnet p� person f�r att ta reda p� skuld, utl�gg m.m

    // Skapa objekt
    Transaktion t;
    TransaktionsLista tlista;
    PersonLista perslista;
    Transaktion nya_trans[MAX_TRANSAKTIONER]; // Array f�r tillagda transaktioner

    // Skapa och �ppna infilsobjekt
    ifstream infil("resa.txt");
    // Skapa och �ppna utfilsobjekt
    ofstream utfil("resa.txt", ios_base::app);
    // B�rja med att l�sa in alla data fr�n infil
    tlista.laesin(infil);
    // St�ng infil
    infil.close();

    // S� l�nge menyvalet inte �r 0
    while(menyval != 0)
    {
        // Visa huvudmenyn
        visaMeny();
        // H�mta menyvalet
        menyval = menyVal();

        // Switch f�r huvudmenyns olika aktiviteter
        switch(menyval)
        {
            case 0: // Avsluta och skriv nya transaktioner p� fil
                cout << "\nProgrammet avslutas. Nya transaktioner skrivs till fil."
                     << endl;

                for(int i = 0; i < antal; i++)
                {
                    nya_trans[i].skrivEnTrans(utfil);
                }

                // St�ng utfilen, beh�vs egentligen inte
                utfil.close();
                break;
            case 1: // L�s transaktion fr�n tangentbord
                t.laesEnTrans(cin);
                tlista.laggTill(t);
                nya_trans[antal] = t;
                antal++;
                break;
            case 2: // Skriv info om samtliga transaktioner
                cout << "\nSkriver info om samtliga transaktioner:" << endl;
                tlista.skrivut(cout);
                cout << endl;
                break;
            case 3: // Skriv ut aktivitetens totalkostnad
                cout << "\nAktivitetens totalkostnad: " << tlista.totalkostnad()
                     << " kr." << endl << endl;
                break;
            case 4: // Kontrollera en given persons skuld
                cout << "Ange namn: "; cin >> namnet;
                cout << namnet << " �r skyldig: " << tlista.aerSkyldig(namnet)
                     << " kr." << endl << endl;
                break;
            case 5: // Kontrollera en given persons utl�gg
                cout << "Ange namn: "; cin >> namnet;
                cout << namnet << " ligger ute med: "
                     << tlista.liggerUteMed(namnet) << " kr." << endl << endl;
                break;
            case 6: // Skriv ut alla deltagare och ber�kna slutresultat
                perslista = tlista.FixaPersoner();
                cout << endl;
                perslista.skrivUtOchFixa();
                cout << endl;
                break;
        }
    }

    return 0;
}

//---Definition av externa funktioner---
// Funktion f�r att skriva ut huvudmenyn
void visaMeny()
{
    cout << "*************V�lj i menyn nedan*************" << endl << endl;
    cout << "0. Avsluta. Alla transaktioner sparas p� fil." << endl;
    cout << "1. L�s in en transaktion fr�n tangentbordet." << endl;
    cout << "2. Skriv ut information om alla transaktioner." << endl;
    cout << "3. Ber�kna totala kostnaden." << endl;
    cout << "4. Hur mycket �r en viss person skyldig?" << endl;
    cout << "5. Hur mycket ligger en viss person ute med?" << endl;
    cout << "6. Lista alla personer mm och FIXA!" << endl << endl;
}

// Funktion f�r att hantera valet i huvudmenyn
int menyVal()
{
    int menyval;

    cout << "Menyval: ";
    cin >> menyval;

    return menyval;
}

//---Definition av metoder i klasser---
//---Metoder i klassen Person---
// Konstruktor
Person::Person()
{
    namn = "";
    betalat_andras = 0.0;
    skyldig = 0.0;
}

// �verlagrad konstruktor
Person::Person(string n, double b, double s)
{
    namn = n;
    betalat_andras = b;
    skyldig = s;
}

// Selektorer
double Person::haemta_betalat()
{
    return betalat_andras;
}

double Person::haemta_skyldig()
{
    return skyldig;
}

string Person::haemta_namn()
{
    return namn;
}

// Skriver information om en given persons betalningar och skulder
void Person::skrivUt()
{
    if(betalat_andras > skyldig)
    {
        cout << namn << " ligger ute med " << setiosflags(ios::fixed)
             << setprecision(0) << betalat_andras << ", �r skyldig "
             << setiosflags(ios::fixed) << setprecision(0) << skyldig
             << " och ska ha " << setiosflags(ios::fixed) << setprecision(0)
             << betalat_andras - skyldig << " fr�n potten." << endl;
    }
    else
    {
        cout << namn << " ligger ute med " << setiosflags(ios::fixed)
             << setprecision(0) << betalat_andras << ", �r skyldig "
             << setiosflags(ios::fixed) << setprecision(0) << skyldig
             << " och ska betala " << setiosflags(ios::fixed) << setprecision(0)
             << skyldig - betalat_andras << " till potten." << endl;
    }
}

//---Metoder i klassen PersonLista---
// Konstruktor
PersonLista::PersonLista()
{
    antal_pers = 0;
}

// Destruktor
PersonLista::~PersonLista()
{
}

// L�gger till en ny person till arrayen pers[]
void PersonLista::laggTillEn(Person pny)
{
    pers[antal_pers] = pny;
    antal_pers++;
}

// Skriver ut information om varje personobjekt i arrayen pers[]
void PersonLista::skrivUtOchFixa()
{
    for(int i = 0; i < antal_pers; i++)
    {
        pers[i].skrivUt();
    }
}

// Summan av alla skulder f�r en given person
double PersonLista::summaSkyldig()
{
    double skyldig = 0.0;

    for(int i = 0; i < antal_pers; i++)
    {
        skyldig += pers[i].haemta_skyldig();
    }

    return skyldig;
}

// Summan av alla utl�gg f�r en given person
double PersonLista::summaBetalat()
{
    double betalat = 0.0;

    for(int i = 0; i < antal_pers; i++)
    {
        betalat += pers[i].haemta_betalat();
    }

    return betalat;
}

// Finns det givna namnet i personarrayen?
bool PersonLista::finnsNamn(string namnet)
{
    for(int i = 0; i < MAX_PERSONER; i++)
    {
        if(pers[i].haemta_namn() == namnet)
        {
            return true;
	}
    }

    return false;
}

//---Metoder i klassen Transaktion---
// Konstruktor
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    ant_kompisar = 0;

    for(int i = 0; i < MAX_KOMPISAR; i++)
    {
        kompisar[i] = "";
    }
}

// Destruktor
Transaktion::~Transaktion()
{
}

// Selektorer
string Transaktion::haemta_namn()
{
    return namn;
}

double Transaktion::haemta_belopp()
{
    return belopp;
}

int Transaktion::haemta_ant_kompisar()
{
    return ant_kompisar;
}

double Transaktion::haemta_skyldig(string namnet)
{
    double skuld = 0.0;

    for(int i = 0; i < ant_kompisar; i++)
    {
        if(kompisar[i] == namnet)
        {
            skuld = belopp / (ant_kompisar + 1);
        }
    }

    return skuld;
}

// Returnerar true om namnet finns i arrayen kompisar
bool Transaktion::finnsKompis(string namnet)
{
    for(int i = 0; i < MAX_KOMPISAR; i++)
    {
        if(kompisar[i].find(namnet, 0) != std::string::npos)
            return true;
    }
}

// L�ser en transaktion
bool Transaktion::laesEnTrans(istream &is)
{
    is >> datum >> typ >> namn >> belopp >> ant_kompisar;
    for(int i = 0; i < ant_kompisar; i++)
        is >> kompisar[i];

    return !is.eof();
}

// Skriver info om ett transaktionsobjekt
void Transaktion::skrivEnTrans(ostream &os)
{
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << ant_kompisar
        << "\t";
    for(int i = 0; i < ant_kompisar; i++)
        os << kompisar[i] << "\t";

    os << endl;
}

//---Metoder i klassen TransaktionsLista---
// Konstruktor
TransaktionsLista::TransaktionsLista()
{
    antalTrans = 0;
}

// Destruktor
TransaktionsLista::~TransaktionsLista()
{
}

// Anv�nder Transaktion::laesEnTrans och TransaktionsLista::laggTill f�r att l�sa
// in data till arrayen trans[]
void TransaktionsLista::laesin(istream &is)
{
    Transaktion t;

    // S� l�nge det finns rader kvar att l�sa i infil
    while(t.laesEnTrans(is))
    {
        laggTill(t);
    }
}

// Anv�nder Transaktion::skrivEnTrans f�r att skriva ut info om samtliga
// transaktionsobjekt i arrayen trans[]
void TransaktionsLista::skrivut(ostream &os)
{
    for(int i = 0; i < antalTrans; i++)
    {
        trans[i].skrivEnTrans(os);
    }
}

// L�gger till aktuellt objekt sist i arrayen trans[]
void TransaktionsLista::laggTill(Transaktion &t)
{
    trans[antalTrans] = t;
    antalTrans++;
}

// Summerar aktivitetens totala kostnader
double TransaktionsLista::totalkostnad()
{
    double totalkostnad = 0;

    for(int i = 0; i < antalTrans; i++)
    {
        totalkostnad += trans[i].haemta_belopp();
    }

    return totalkostnad;
}

// Ber�knar hur mycket pengar en given person ligger ute med
double TransaktionsLista::liggerUteMed(string namnet)
{
    double betalat = 0.0;

    for(int i = 0; i < antalTrans; i++)
    {
        if(trans[i].haemta_namn() == namnet)
            betalat += (trans[i].haemta_belopp() - (trans[i].haemta_belopp() /
                       (trans[i].haemta_ant_kompisar() + 1)));
    }

    return betalat;
}

// Ber�knar hur mycket en given person �r skyldig
double TransaktionsLista::aerSkyldig(string namnet)
{
    double skyldig = 0.0;

    for(int i = 0; i < antalTrans; i++)
    {
        if (trans[i].finnsKompis(namnet))
            skyldig += trans[i].haemta_skyldig(namnet);
    }

    return skyldig ;
}

// Skapar ett PersonListe-objekt med data om en persons transaktioner
PersonLista TransaktionsLista::FixaPersoner()
{
    PersonLista perslista;
    string persnamn;
    double persskuld;
    double persbetalat;

    for(int i = 0; i < antalTrans; i++)
    {
        if(!perslista.finnsNamn(trans[i].haemta_namn()))
        {
            persnamn = trans[i].haemta_namn();
            persskuld =+ aerSkyldig(persnamn);
            persbetalat =+ liggerUteMed(persnamn);

            Person nypers = Person(persnamn, persbetalat, persskuld);
            perslista.laggTillEn(nypers);
        }
    }

    return perslista;
}

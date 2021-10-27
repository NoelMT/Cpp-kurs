#include <iostream>
using namespace std;

// Deklarationer av funktionerna
void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int &tal1, int &tal2);
int berakna(int undre, int ovre, char c);
void skrivResultat(int &svar);

int main(){

  //deklaration av variabler
    int tal1,tal2,svar;
    char op;

    skrivInfo(); // funktion som skriver info om programmet

    tal1 = lasEttTal(); //läser in första talet

    tal2 = lasEttTal(); //läser in andra talet

    op = lasOp();       //läser in vilken operation

    ordna(tal1,tal2); //funktion som byter plats så att första talet är minst

    svar = berakna(tal1, tal2, op); //fanropar funktion som utför beräkning och plaserar svaret i varibeln svar

    skrivResultat(svar); // anropar funnktion som skriver ut svaret av beräkningen

    return 0;
}
// Definitioner av funktionerna
void skrivInfo(){                   //skriver ut start info
    cout << "Skriv in 2 heltal och ett rekne sett " << endl;
}

int lasEttTal(){ //läser in ett tal och returnerar de heltalet
    cout<< "Skriv ett heltal: ";
    int tal;
    cin >> tal;
return tal;
}
char lasOp(){ //läser in en char och returnerar de värdet, endast a,m och k går att läsa in
    int t = 1;
    char c;
   do{
    cout << "val av operation,\n 'a' addition \n 'm' muliplikation \n 'k' produktsumma"  << endl;
    cin >> c;
    switch(c)
    {
        case 'a':
        {
           t = 0;
            break;
        }
        case 'm':
        {
          t = 0;
            break;
        }
        case 'k':
        {
           t = 0;
            break;
        }
        default:
            t = 1;
            break;
    }
   }
   while(t);
}

void ordna(int &tal1,int &tal2){ //funktion som inte returnerar något men byter plats på talen med hjälp a referensparametrar
    int byte;
    if(tal1 > tal2) {
        byte = tal1;
        tal1 = tal2;
        tal2 = byte;
    }
}

int berakna(int undre, int ovre, char c){ // alla berekningar beroende på operationene som bestämts i värdeparametern c
    int svar;
 switch(c)
    {
        case 'a':
        {
            svar = 0;
            for (int i = undre; i <= ovre;i++){
                svar += i;
        }
            return svar;
            break;
        }
        case 'm':
            {
            svar = 1;
            for (int i = undre; i <= ovre;i++){
                svar *= i;
            }
            return svar;
            break;
        }
        case 'k':
        {
            svar = 0;
            for (int i = undre; i <= ovre;i++){
                svar += i*i;
            }
            cout << svar;  //bara för test
            return svar;
            break;
        }
        default:

            break;
    }
}

void skrivResultat(int &svar){ //skriver ut svaret
cout << "Svaret blir: " << svar << endl;
}


/*
 * Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

име (динамички алоцирана низа од знаци)
пол (bool)
возраст (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

Дополнително за оваа класа да се преоптоварат:

оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
Да се дефинира класа Maraton за кој се чуваат:

локација (низа од максимум 100 знаци)
низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
број на учесници (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:

оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

 Input:
 5
Skopje
Elena 0 23
Mitko 1 41
Iskra 0 31
Jovan 1 28
Zoran 1 40

 Output:
Elena
zhenski
23
Iskra
zhenski
31
Jovan
mashki
28
32.6
 */

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

class Ucesnik {
    char ime[100];
    bool pol;
    int vozrast;
public:
    Ucesnik(){};
    Ucesnik(char *ime, bool pol, int vozrast){
        strcpy(this -> ime, ime);
        this -> pol = pol;
        this -> vozrast = vozrast;
    }
    Ucesnik(const Ucesnik &u){
        strcpy(this -> ime, u.ime);
        this -> pol = u.pol;
        this -> vozrast = u.vozrast;
    }
    char *getIme(){
        return ime;
    }
    bool getPol (){
        return pol;
    };
    int getVozrast(){
        return vozrast;
    }

    bool operator> (const Ucesnik &u) const {
        return vozrast > u.vozrast;
    }

    friend ostream &operator<<(ostream &os, const Ucesnik &u){
        os << u.ime << endl;
        if (u.pol){
            os << "mashki" << endl;
        }
        else {
            os << "zhenski" << endl;
        }
        os << u.vozrast << endl;
        return os;
    }


    ~Ucesnik(){}
};

class Maraton {
    char lokacija[100];
    Ucesnik ucesnici[100];
    int brojUcesnici;
public:
    Maraton(){
        brojUcesnici = 0;
    }
    Maraton(char lokacija[]){
        brojUcesnici = 0;
        strcpy(this -> lokacija,lokacija);
    }
    Maraton(const Maraton &m){
        strcpy(this -> lokacija,m.lokacija);
        this -> brojUcesnici = m.brojUcesnici;
        for (int i = 0; i < m.brojUcesnici; ++i) {
            this -> ucesnici[i] = m.ucesnici[i];
        }
    }
    char *getLokacija(){
        return lokacija;
    }


    Maraton &operator+= (const Ucesnik &u){
        if (brojUcesnici < 100){
            ucesnici[brojUcesnici] = u;
            brojUcesnici++;
        }
        return *this;
    }

    double prosecnoVozrast(){
        int sum = 0;
        for (int i = 0; i < brojUcesnici; ++i) {
            sum+=ucesnici[i].getVozrast();
        }
        return (1.0*sum)/(1.0*brojUcesnici);
    }

    void pecatiPomladi(Ucesnik &u){
        for (int i = 0; i < brojUcesnici; ++i) {
            if (ucesnici[i].getVozrast()< u.getVozrast()){
                cout << ucesnici[i];
            }
        }
    }



    ~Maraton(){}
};




int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}

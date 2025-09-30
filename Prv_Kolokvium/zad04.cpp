/*
 * Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци), динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед.
 Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот.
 На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

 Input:
 Amsterdam
0
5
Ana
1
1
Kate
2
0
Ace
2
0
Borce
2
1
Mimi
2
0

 Output:
 Amsterdam
Kate
2
0

Ace
2
0

Mimi
2
0

Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0
Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0

 */

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Patnik{

private:
    char name[100];
    int wagon;
    bool bike;

    void copy_p(const Patnik &other) {
        strcpy(this->name,other.name);
        this->wagon = other.wagon;
        this->bike = other.bike;
    }
public:
    Patnik() {
        strcpy(this->name,"name");
        this->wagon = 0;
        this->bike = false;
    }
    Patnik(char *name, int wagon, bool bike) {
        strcpy(this->name,name);
        this->wagon = wagon;
        this->bike = bike;
    }
    Patnik(const Patnik &other) {
        copy_p(other);
    }
    Patnik &operator=(const Patnik &other) {
        if (this != &other) {
            copy_p(other);
        }
        return *this;
    }
    bool isBike() const {
        return bike;
    }
    int getWagon() const {
        return wagon;
    }
    friend ostream &operator<<(ostream &output, Patnik &p) {
        output << p.name << endl;
        output << p.wagon << endl;
        output << p.bike << endl;
        return output;
    }
    ~Patnik() {}
};

class Voz{

private:
    char destination[100];
    Patnik *passengers;
    int n;
    int maxb;
    void copy_v(const Voz &other) {
        strcpy(this->destination,other.destination);
        this->n = other.n;
        this->passengers = new Patnik[other.n];
        for (int i = 0; i < other.n; i++) {
            passengers[i] = other.passengers[i];
        }
    }

public:
    Voz() {
        strcpy(this->destination,"destination");
        passengers = nullptr;
        n = 0;
        this->maxb = 0;
    }
    Voz(char *destination, int maxb) {
        strcpy(this->destination,destination);
        this->maxb = maxb;
        passengers = nullptr;
        n = 0;
    }
    Voz(const Voz &other) {
        copy_v(other);
    }
    Voz &operator=(const Voz &other) {
        if (this != &other) {
            delete [] passengers;
            copy_v(other);
        }
        return *this;
    }
    Voz &operator+=(Patnik &p) {
        if (p.isBike() && maxb == 0) {
            return *this;
        }
        Patnik *temp = new Patnik[n+1];
        for (int i = 0; i < n; i++) {
            temp[i] = passengers[i];
        }
        temp[n] = p;
        n++;
        delete [] passengers;
        passengers = temp;
        return *this;
    }
    friend ostream &operator<<(ostream &output, Voz &v) {
        output << v.destination << endl;;
        for (int i = 0; i < v.n; i++) {
            output << v.passengers[i] << endl;
        }
        return output;
    }
    void patniciNemaMesto() {
        int count_bikes = 0, no_room1 = 0, no_room2 = 0;
        for (int i = 0; i < n; i++) {
            if (passengers[i].isBike() && passengers[i].getWagon()==1) {
                count_bikes++;
            }
            if ((passengers[i].isBike() && passengers[i].getWagon()==1) && (count_bikes > maxb)) {
                no_room1++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (passengers[i].isBike() && passengers[i].getWagon()==2) {
                count_bikes++;
            }
            if ((passengers[i].isBike() && passengers[i].getWagon()==2) && (count_bikes > maxb)) {
                no_room2++;
            }
        }
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << no_room1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << no_room2 << endl;
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}

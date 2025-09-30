/*
 * Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број,
 како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

 Input:
5
1
Hamilton 30 95 0 55000
Vetel 26 88 1 800
Barrichello 38 198 0 810
Rossi 32 130 1 800
Lorenzo 24 45 0 900
VozacX 38 198 1 800

 Output:
 === DANOK ===
Hamilton
30
95
1650
Vetel
26
88
VETERAN
4000
Barrichello
38
198
3240
Rossi
32
130
VETERAN
4000
Lorenzo
24
45
3600
=== VOZAC X ===
VozacX
38
198
VETERAN
=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===
2
 */

#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;


class Vozac{
protected:
    char ime[101];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(){}
    Vozac(char *ime="", int vozrast=0, int trki=0,bool veteran = false){
        strcpy(this -> ime, ime);
        this -> vozrast = vozrast;
        this -> trki = trki;
        this -> veteran = veteran;
    }
    Vozac(const Vozac & other){
        strcpy(this -> ime, other.ime);
        this -> vozrast = other.vozrast;
        this -> trki = other.trki;
        this -> veteran = other.veteran;
    }
    void setIme(char *ime){
        strcpy(this -> ime, ime);
    }
    void setVozrast(int vozrast){
        this -> vozrast = vozrast;
    }
    void setTrki(int trki){
        this -> trki = trki;
    }
    void setVeteran(bool veteran){
        this -> veteran = veteran;
    }
    char *getIme(){
        return ime;
    }
    int getVozrast(){
        return vozrast;
    }
    int getTrki(){
        return trki;
    }
    bool getVeteran(){
        return veteran;
    }
    friend ostream &operator<< (ostream &os, Vozac &v){
        os << v.ime << '\n' << v.vozrast << '\n' << v.trki << endl;
        if (v.veteran){
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual double zarabotuvacka() = 0;
    virtual double danok() = 0;


    bool operator==(Vozac &v1){
        return this -> zarabotuvacka() == v1.zarabotuvacka();
    }

    ~Vozac()= default;
};

class Avtomobilist : public Vozac{
    double cenaAvtomobil;
public:
    using Vozac::Vozac;
    Avtomobilist(char *ime,int vozrast, int trki, bool veteran, double cenaAvtomobil=0)
            : Vozac(ime,vozrast,trki,veteran){
        this -> cenaAvtomobil = cenaAvtomobil;
    }


    double zarabotuvacka() override {
        return  cenaAvtomobil / 5.0;
    }

    double danok() override {
        if (trki > 10){
            return  zarabotuvacka()*(15.0/100.0);
        }
        else {
            return  zarabotuvacka()*(10.0/100.0);
        }
    }


};

class Motociklist : public  Vozac{
    int mokjnostMotor;
public:
    using Vozac::Vozac;
    Motociklist(char *ime, int vozrast, int trki, bool veteran, int mokjnostMotor)
            : Vozac(ime,vozrast,trki,veteran){
        this -> mokjnostMotor = mokjnostMotor;
    }

    double zarabotuvacka() override {
        return  mokjnostMotor * 20;
    }

    double danok() override {
        if (veteran){
            return zarabotuvacka()*(25.0/100.0);
        }
        else {
            return zarabotuvacka()*(20.0/100.0);
        }
    }

    ~Motociklist(){}

};

int soIstaZarabotuvachka(Vozac **vp, int n, Vozac *v){
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (vp[i]->zarabotuvacka() == v->zarabotuvacka()){
            count ++;
        }
    }
    return count;
}



int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}

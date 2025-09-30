/*
 За потребите на електронскиот огласник ФИНКИ-Огласи треба да се развие класа Oglas со информации за наслов (текстуална низа од максимум 50 знаци), категорија (текстуална низа од максимум 30 знаци), опис (текстуална низа од максимум 100 знаци) и цена изразена во евра (реален број). (5 поени)

За оваа класа да се обезбедат:

Оператор > за споредба на двa огласи според цената (5 поени)
Оператор << за печатење на податоците за огласот во форма: (5 поени)
[наслов]

[опис]

[цена] evra

Да се развие класа Oglasnik во која се чуваат податоци за име на огласникот (текстуална низа од максимум 20 знаци), низа од огласи (динамички резервирана низа од објекти од класата Oglas) и број на огласи во низата (цел број) (5 поени)

За оваа класа да се обезбедат:

Оператор += за додавање нов оглас во низата од огласи. (5 поени) Ако цената на огласот што се внесува е негативна, треба да се генерира исклучок NegativnaVrednost (објект од класата NegativnaVrednost што посебно треба да се дефинира). Во ваков случај се печати порака “Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!“ и не се додава во низата. (5 поени)
Оператор << за печатење на огласите во огласникот. (5 поени) Печатењето треба да биде во следниот формат:
[Име на огласникот]

[наслов1] [опис1] [цена1]

[наслов2] [опис2] [цена2]

...

Функција void oglasOdKategorija(const char *k) со која се печатат сите огласи од категоријата k што е проследена како влезен аргумент на методот. (5 поени)

Функција void najniskaCena() со која се печати огласот што има најниска цена. Ако има повеќе огласи со иста најниска цена, да се испечатат податоците за првиот од нив. (5 поени)

Сите променливи во класите се приватни.

Да се обезбедат сите потребни методи за правилно функционирање на програмата. (5 поени)

 Input:
2
BMW 520 FULL OPREMA
Avtomobili
Godina: 2011 Kilometraza: 140 000 - 149 999
13000
VW PASSAT 2.0 TDI 140 KS BLUEMOTION
Avtomobili
Godina: 2011 Kilometraza: 140 000 - 149 999
12000

 Output:
 -----Test Oglas & operator > -----
Prviot oglas e poskap.
 */

#include<iostream>
#include<cstring>

using namespace std;

class NegativnaVrednost{
public:
    static void isklucok(){
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas{
protected:
    char naslov[51];
    char kategorija[51];
    char opis[101];
    double cena;
public:
    Oglas(char *naslov="", char* kategorija="", char *opis="", double cena=0){
        strcpy(this -> naslov, naslov);
        strcpy(this -> kategorija, kategorija);
        strcpy(this -> opis,opis);
        this -> cena = cena;
    }
    Oglas(const Oglas &other){
        strcpy(this -> naslov, other.naslov);
        strcpy(this -> kategorija, other.kategorija);
        strcpy(this -> opis, other.opis);
        this -> cena = other.cena;
    }
    double getCena(){
        return cena;
    }
    char *getNaslov(){
        return naslov;
    }
    char *getOpis(){
        return opis;
    }
    char *getKategorija(){
        return kategorija;
    }

    bool operator>(const Oglas &other) {
        return this -> cena > other.cena;
    }

    friend ostream &operator<< (ostream &os, Oglas &o){
        os << o.naslov << endl;
        os << o.opis << endl;
        os << o.cena << " evra " <<endl;
        cout << endl;
        return os;
    }


    ~ Oglas(){}

};

class Oglasnik : public Oglas {
    char ime [21];
    Oglas *oglasi;
    int brojOglasi;
public:
    Oglasnik(char *naslov="", char* kategorija="", char *opis="", double cena=0, char *ime ="FINKI-Oglasnik",Oglas *oglasi = nullptr, int brojOglasi = 0)
            : Oglas(naslov,kategorija,opis,cena){
        this -> brojOglasi = brojOglasi;
        strcpy(this -> ime, ime);
        this -> oglasi = new Oglas [brojOglasi];
    }

    Oglasnik(const Oglasnik &other) : Oglas(other){
        this -> brojOglasi = other.brojOglasi;
        strcpy(this -> ime, other.ime);
        this -> oglasi = new Oglas [brojOglasi];
        for (int i = 0; i < brojOglasi; ++i) {
            oglasi[i] = other.oglasi[i];
        }
    }


    Oglasnik &operator+=(Oglas &o){
        if (o.getCena() < 0){
            NegativnaVrednost::isklucok();
            return *this;
        }
        Oglas *temp = new Oglas [brojOglasi+1];
        for (int i = 0; i < brojOglasi; ++i) {
            temp[i] = oglasi[i];
        }
        temp[brojOglasi] = o;
        delete [] oglasi;
        oglasi = temp;
        brojOglasi++;
        return *this;
    }

    friend ostream &operator<< (ostream &os, Oglasnik &o){
        os << o.ime << endl;
        for (int i = 0; i < o.brojOglasi; ++i) {
//           os << o.oglasi[i].getNaslov() << " " << o.oglasi[i].getOpis() << " " << o.oglasi[i].getCena() << " evra " << endl;
            cout << o.oglasi[i] ;
        }
        return os;
    }

    void oglasiOdKategorija( const char *k){
        for (int i = 0; i < brojOglasi; ++i) {
            if ( strcmp (oglasi[i].getKategorija(),k) == 0){
                cout << oglasi[i];
            }
        }
    }

    void najniskaCena(){
        Oglas najniska = oglasi[0];
        for (int i = 1; i <brojOglasi ; ++i) {
            if (oglasi[i].getCena() < najniska.getCena()){
                najniska = oglasi[i];
            }
        }
        cout << najniska;
    }

    ~Oglasnik(){
        delete [] oglasi;
    }
};



int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
/*
 * Да се дефинира класа Пица за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

 Input:
 FINKI-Pica
4
Margarita
200
Domaten sos, kaskaval, maslinovo maslo
0
Napolitana
210
Domaten sos, kaskaval, svezi sampinjoni, maslinovo maslo
0
Kapricioza
210
Domaten sos, kaskaval, sunka, svezi sampinjoni
30
Vegetarijana
230
Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka
20
Pica-FINKI
Vegetarijana
230
Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka
20

 Output:
FINKI-Pica
Pici na promocija:
Kapricioza  - Domaten sos, kaskaval, sunka, svezi sampinjoni, 210 147
Vegetarijana - Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka, 230 184
Pica-FINKI
Pici na promocija:
Kapricioza  - Domaten sos, kaskaval, sunka, svezi sampinjoni, 210 147
Vegetarijana - Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka, 230 184

 */

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

class Pica{
    char ime[15];
    int cena;
    char sostojki[300];
    int popust;
public:
    Pica(){
        popust = 0;
    }
    Pica(char *ime, int cena, char*sostojki, int popust){
        strcpy(this -> ime, ime);
        this -> cena = cena;
        strcpy(this -> sostojki, sostojki);
        this -> popust = popust;
    }
    Pica(const Pica &p){
        strcpy(this -> ime, p.ime);
        this -> cena = p.cena;
        strcpy(this -> sostojki, p.sostojki);
        this -> popust = p.popust;
    }
    char *getIme(){
        return ime;
    };
    int getCena(){
        return cena;
    }
    char *getSostojki(){
        return sostojki;
    }
    int getPopust(){
        return popust;
    }

    void pecati (){
        cout << ime << " - " << sostojki <<", " << cena << " ";
    }

    bool istiSe(Pica p){
        if (strcmp(this->sostojki,p.sostojki) == 0){
            return true;
        }
        return false;
    }


    ~Pica(){}
};


class Picerija {
    char ime[15];
    Pica pici[100];
    int brojPici;
public:
    Picerija(){
        brojPici = 0;
    }
    Picerija(char*ime){
        brojPici = 0;
        strcpy(this -> ime,ime);
    }
    Picerija(const Picerija &p){
        strcpy(this -> ime, p.ime);
        this -> brojPici = p.brojPici;
        for (int i = 0; i < brojPici; ++i) {
            pici[i] = p.pici[i];
        }
    }

    void setIme(char *ime){
        strcpy(this -> ime,ime);
    }

    void dodadi(Pica P){
        if (brojPici<100){
            for (int i = 0; i < brojPici; ++i) {
                if (pici[i].istiSe(P)){
                    return;
                }
            }
            pici[brojPici] = P;
            brojPici++;
        }
    }

    Picerija &operator+= (Pica &P){
        if (brojPici<100){
            for (int i = 0; i < brojPici; ++i) {
                if (pici[i].istiSe(P)){
                    return *this;
                }
            }
            pici[brojPici] = P;
            brojPici++;
        }
        return  *this;
    }

    char *getIme(){
        return ime;
    }


    void piciNaPromocija(){
        for (int i = 0; i < brojPici; ++i) {
            double promo = 0;
            if (pici[i].getPopust()>0){
                promo = pici[i].getCena() * (1-pici[i].getPopust()/100.0) ;
                pici[i].pecati();
                cout << promo << endl;
            }
        }
    }


};



int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}

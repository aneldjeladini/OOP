/*
 * Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

 Input:
FINKICloud
2
Ubuntu
17.04
1
2.25
Ubuntu
16.04
1
1.25
Ubuntu
14.04
1
1.25

 Output:
 Repozitorium: FINKICloud
Ime: Ubuntu Verzija: 17.04 Tip: 1 Golemina:2.25GB
Ime: Ubuntu Verzija: 16.04 Tip: 1 Golemina:1.25GB
=====Brishenje na operativen sistem=====
Repozitorium: FINKICloud
Ime: Ubuntu Verzija: 17.04 Tip: 1 Golemina:2.25GB
Ime: Ubuntu Verzija: 16.04 Tip: 1 Golemina:1.25GB

 */

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

enum Tip {LINUX, UNIX,WINDOWS};
class OperativenSistem{
    char ime[100];
    float verzija;
    Tip tip;
    float goleminaGB;
public:
    OperativenSistem(){
    }
    OperativenSistem(char *ime, float verzija, Tip tip, float goleminaGB){
        strcpy(this -> ime, ime);
        this -> verzija = verzija;
        this -> tip = tip;
        this -> goleminaGB = goleminaGB;
    }
    OperativenSistem(const OperativenSistem &o){
        strcpy(this -> ime, o.ime);
        this -> verzija = o.verzija;
        this -> tip = o.tip;
        this -> goleminaGB = o.goleminaGB;
    }
    char *getIme(){
        return ime;
    }
    float getVerzija(){
        return verzija;
    }
    Tip getTip(){
        return tip;
    }
    float getGolemina(){
        return goleminaGB;
    }

    OperativenSistem &operator=(const OperativenSistem &other){
        strcpy(this -> ime, other.ime);
        this -> verzija = other.verzija;
        this -> tip = other.tip;
        this -> goleminaGB = other.goleminaGB;
    }

    void pecati (){
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << tip << " Golemina:" << goleminaGB << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os){
        if (strcmp(this -> ime, os.ime) == 0 &&
            this -> verzija == os.verzija &&
            this -> tip == os.tip &&
            this -> goleminaGB == os.goleminaGB){
            return true;
        }
        return false;
    }

    int sporediVerzija(const OperativenSistem &os){
        if (this -> verzija == os.verzija){
            return 0;
        }
        else if (this -> verzija < os.verzija){
            return -1;
        }
        else {
            return 1;
        }
    }

    bool istaFamilija (const OperativenSistem &sporedba){
        if (strcmp(this -> ime, sporedba.ime) == 0 && this -> tip == sporedba.tip){
            return true;
        }
        return false;
    }

    ~OperativenSistem(){}
};


class Repozitorium {
    char ime[20];
    OperativenSistem operativni_sistemi[100];
    int broj_operativni;
public:
    Repozitorium(){
        broj_operativni = 0;
    }
    Repozitorium(const char *ime){
        strcpy(this -> ime,ime);
        broj_operativni = 0;
    }
    Repozitorium(const Repozitorium &r){
        strcpy(this -> ime , r.ime);
        this -> broj_operativni = broj_operativni;
        for (int i = 0; i < broj_operativni; ++i) {
            this -> operativni_sistemi[i] = operativni_sistemi[i];
        }
    }

    void pecatiOperativniSistemi(){
        cout << "Repozitorium: " << ime << endl;
        for (int i = 0; i < broj_operativni; ++i) {
            operativni_sistemi[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem){
        for (int i = 0; i < broj_operativni; ++i) {
            if (operativni_sistemi[i].ednakviSe(operativenSistem)){
                for (int j = i; j < broj_operativni-1 ; ++j) {
                    operativni_sistemi[j] = operativni_sistemi[j+1];
                }
                --broj_operativni;
                return;
            }
        }
    }

    void dodadi(const OperativenSistem &nov){
        for (int i = 0; i < broj_operativni; ++i) {
            if (operativni_sistemi[i].istaFamilija(nov)){
                if (operativni_sistemi[i].sporediVerzija(nov) == -1){
                    operativni_sistemi[i] = nov;
                    return;
                }
            }
        }
        operativni_sistemi[broj_operativni] = nov;
        broj_operativni++;
    }



    ~Repozitorium(){}
};


int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
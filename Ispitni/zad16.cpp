/*
 Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)

 Input:
3
1 Belgrad 3200 900 1
1 Bitola 2500 400 0
2 Sofija 5000 1040 2

 Output:
 Bitola 400 2500
Belgrad 900 3840
Sofija 1040 4600
 */

#include <iostream>
#include <cstring>
using namespace std;


class Transport {
protected:
    char *destinacija;
    int cena;
    int rastojanie;
public:
    Transport(char *destinacija = nullptr, int cena = 0, int rastojanie = 0){
        this -> destinacija = new char [strlen(destinacija)+1];
        strcpy(this -> destinacija, destinacija);
        this -> cena = cena;
        this -> rastojanie = rastojanie;
    }
    Transport(const Transport &other){
        this -> destinacija = new char [strlen(other.destinacija)+1];
        strcpy(this -> destinacija, other.destinacija);
        this -> cena = other.cena;
        this -> rastojanie = other.rastojanie;
    }
    Transport &operator=(const Transport &other){
        if (this != &other){
            delete []destinacija;
            this -> destinacija = new char [strlen(other.destinacija)+1];
            strcpy(this -> destinacija, other.destinacija);
            this -> cena = other.cena;
            this -> rastojanie = other.rastojanie;
        }
        return *this;
    }

    virtual int cenaTransport(){
        return cena;
    }

    bool operator<(Transport &other)const{
        return this->rastojanie < other.rastojanie;
    }

    int getRastojanie(){
        return rastojanie;
    }
    char *getDestinacija(){
        return destinacija;
    }

    ~Transport(){
        delete [] destinacija;
    }
};

class AvtomobilTransport : public Transport{
    bool imaSofer;
public:
    AvtomobilTransport(char *destinacija = nullptr, int cena = 0, int rastojanie = 0,bool imaSofer=false)
            : Transport(destinacija,cena,rastojanie){
        this -> imaSofer = imaSofer;
    }
    AvtomobilTransport(const AvtomobilTransport &other) : Transport(other){
        this -> imaSofer = other.imaSofer;
    }
    AvtomobilTransport &operator= (const AvtomobilTransport &other){
        if (this != &other){
            delete [] destinacija;
            this -> destinacija = new char [strlen(other.destinacija)+1];
            strcpy(this -> destinacija, other.destinacija);
            this -> cena = other.cena;
            this -> rastojanie = other.rastojanie;
            this -> imaSofer = other.imaSofer;
        }
        return *this;
    }

    void setImaSofer(bool imaSofer){
        this -> imaSofer = imaSofer;
    }

    bool getImaSofer(){
        return imaSofer;
    }

    int cenaTransport() override {
        if (imaSofer){
            return cena * 1.2;
        }
        return cena;
    }


    ~AvtomobilTransport(){}
};


class KombeTransport : public Transport{
    int brojPatnici;
public:
    KombeTransport(char *destinacija = nullptr, int cena = 0, int rastojanie = 0, int brojPatnici=0)
            : Transport(destinacija,cena,rastojanie) {
        this -> brojPatnici = brojPatnici;
    }
    KombeTransport &operator=(const KombeTransport &other){
        if (this != &other){
            delete [] destinacija;
            this -> destinacija = new char [strlen(other.destinacija)+1];
            strcpy(this -> destinacija, other.destinacija);
            this -> cena = other.cena;
            this -> rastojanie = other.rastojanie;
            this -> brojPatnici = other.brojPatnici;
        }
        return *this;
    }
    void setKapacitet(int brojPatnici){
        this -> brojPatnici = brojPatnici;
    }
    int getKapacitet(){
        return brojPatnici;
    }

    int cenaTransport() override {
        return cena - (brojPatnici * 200);
    }

    ~KombeTransport(){}
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t){
    Transport *temp[n];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (ponudi[i]->cenaTransport() > t.cenaTransport()){
            temp[j] = ponudi[i];
            j++;
        }
    }
    for (int i = 0; i <j; ++i) {
        for (int k = 0; k < j-i-1; ++k) {
            if (temp[k]->getRastojanie() > temp[k+1]->getRastojanie()){
                swap(temp[k],temp[k+1]);
            }
        }
    }
    for (int i = 0; i < j; ++i) {
        cout << temp[i]->getDestinacija() << " " << temp[i]->getRastojanie() << " " << temp[i]->cenaTransport() << endl;
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}

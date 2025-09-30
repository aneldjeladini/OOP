/*
 Дадена е дел од дефиницијата на класата Karticka. За секоја картичка се чуваат информации за трансакциска сметка (низа од 15 знаци) , пин код (цел број) и дали има повеќе пин кодови (булова променлива).

За секој картичка може да се пресмета тежината за пробивање на картичката. Тежината на пробивање е бројот на цифрите на пин кодот.

Специјалните картички покрај еден задолжителен имаат уште неколку пин кодови . За овие корисници да се моделира соодветна класа SpecijalnaKaricka во која покрај дополнителните пин кодови (динамичко алоцирана низа од цели броеви) се чува и бројот на пин кодовите (цел број). Со дополнителните пин кодови се менува и тежината на пробивање на картичката и таа се зголемува за бројот на дополнителни пин кодови.

Максималниот број на дополнителни пин кодови кој може да има било која картичка е P. P има фиксна вредност 4 за сите картички и оваа вредност не може да се промени.

Во класите Karticka и SpecijalnaKarticka треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за картичката во формат: smetka: tezina (5 поени)
tezinaProbivanje() – ја пресметува тежината за пробивање на картичката (5 поени)
Во класата SpecijalnaKarticka дефинирај ја функцијата:

преоптоварен оператор += за додавање на нов пин код (5 поени)
Ако се направи обид да се внесат повеќе од дозволениот број на пин кодови во безбедносниот код да се фрли исклучок (објект од класата OutOfBoundException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Brojot na pin kodovi ne moze da go nadmine dozvolenoto) и справете се со исклучокот така да додадениот пин код не се зема предвид (10 поени)

Дадена е дел од дефиницијата на класата Banka во која се чуваат информаци за името на банката (низа од 30 знаци) и за картичките издадени од банката (низа од 20 покажувачи кон класата Karticka) како и бројот на такви картички.

Велиме дека картичката издадена од банката може да се пробие ако тежината за пробивање е најмногуLIMIT. Вредноста LIMIT е членка на класата Banka, има почетна вредност 7 и истата може да се промени со функцијата setLimit(). За сите банки оваа вредност е иста. (5 поени)

Во класата Banka имплементирај ги функциите:

функција pecatiKarticki() во која се печатат сите картички кои можат да се пробијат, секој во посебен ред. Претходно во првиот ред се печати: Vo bankata XXXXX moze da se probijat kartickite: (5 поени).

функција dodadiDopolnitelenPin(char * smetka, int novPin) во која на картичката со дадена трансакциона сметка се додава нов дополнителен пин код. Ако тоа не е можно функцијата не прави ништо (15 поени).

 Input:
2
ab1232432 345 0
bh4555432 876 1
4
ab1232432 2
ab1112432 100
ab1232432 56
ab1211111 88

 Output:
 Vo bankata Komercijalna moze da se probijat kartickite:
ab1232432: 3
bh4555432: 3
 */

#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    Karticka(const Karticka &other){
        strcpy(this -> smetka,other.smetka);
        this -> pin = other.pin;
        this ->povekjePin = other.povekjePin;
    }

    Karticka &operator=(const Karticka &other){
        if (this!=&other){
            strcpy(this -> smetka,other.smetka);
            this -> pin = other.pin;
            this ->povekjePin = other.povekjePin;
        }
        return *this;
    }

    char *getSmetka(){
        return smetka;
    }
    void setSmetka(char *smetka){
        strcpy(this -> smetka,smetka);
    }
    int getPin(){
        return pin;
    }
    void setPin(int pin){
        this -> pin = pin;
    }
    virtual int tezinaProbivanje(){
        int temp = pin;
        int count=0;
        while (temp > 0){
            temp/=10;
            count++;
        }
        return count;
    }
    virtual void print (){
        cout << smetka << ": " << tezinaProbivanje() << endl;
    }
    virtual bool getDopolnitelenPin(){
        return povekjePin;
    }
    // дополниете ја класата
};

//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka : public Karticka {
    int *dopolnitelniKodovi;
    int brojKodovi;
    static const int P = 4;
public:
    SpecijalnaKarticka(char* smetka="",int pin=0,int *dopolnitelniKodovi= nullptr, int brojKodovi=0)
            : Karticka(smetka,pin){
        povekjePin = true;
        this -> brojKodovi = brojKodovi;
        this -> dopolnitelniKodovi = new int [brojKodovi];
        for (int i = 0; i < brojKodovi; ++i) {
            this -> dopolnitelniKodovi[i] = dopolnitelniKodovi[i];
        }
    }
    SpecijalnaKarticka (const SpecijalnaKarticka &other) : Karticka(other){
        this -> brojKodovi = other.brojKodovi;
        this -> dopolnitelniKodovi = new int [other.brojKodovi];
        for (int i = 0; i < brojKodovi; ++i) {
            this -> dopolnitelniKodovi[i] = other.dopolnitelniKodovi[i];
        }
        this -> povekjePin = true;
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &other){
        if(this!= &other){
            Karticka::operator=(other);
            delete [] dopolnitelniKodovi;
            this -> brojKodovi = other.brojKodovi;
            this -> dopolnitelniKodovi = new int [brojKodovi];
            for (int i = 0; i < brojKodovi; ++i) {
                this -> dopolnitelniKodovi[i] = other.dopolnitelniKodovi[i];
            }
            this -> povekjePin = true;
        }
        return *this;
    }

    SpecijalnaKarticka &operator+=(int pin){
        if (brojKodovi < P){
            int *temp = new int [brojKodovi+1];
            for (int i = 0; i < brojKodovi; ++i) {
                temp[i] = dopolnitelniKodovi[i];
            }
            temp[brojKodovi] = pin;
            brojKodovi++;
            delete[]dopolnitelniKodovi;
            dopolnitelniKodovi = temp;
        }
        return *this;
    }

    int tezinaProbivanje () override{
        return Karticka::tezinaProbivanje() + brojKodovi;
    }

    void print () override {
        cout << smetka << ": " << tezinaProbivanje() << endl;
    }

    bool getDopolnitelenPin() override {
        return povekjePin;
    }


    ~SpecijalnaKarticka(){

        delete [] dopolnitelniKodovi;
    }
};



class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }

    static void setLIMIT(int x){
        LIMIT = x;
    }

    void pecatiKarticki(){
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite: " << endl;
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT){
                karticki[i]->print();
            }
        }
    }

    void  dodadiDopolnitelenPin(char * smetka, int novPin){
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->getDopolnitelenPin()){
                SpecijalnaKarticka *s = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if (strcmp(karticki[i]->getSmetka(),smetka) == 0){
                    *s+=novPin;
                }
            }
        }
    }





    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата

};

int Banka::LIMIT = 7;



int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}

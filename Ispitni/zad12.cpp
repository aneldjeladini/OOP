/*
 Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот. Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)

 Input:
3
TelService
6
iPhone
0
2020
Samsung
0
1999
Huawei
0
1990
Toshiba
1
2016
OnePlus
0
2009
Fujitsu
1
2010

 Output:
 ===== Testiranje na isklucoci ======
Невалидна година на производство
Невалидна година на производство
Невалидна година на производство
Ime: TelService
Toshiba
Laptop 5
OnePlus
Mobilen 1
Fujitsu
Laptop 3
 */

#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
using namespace std;

enum tip {smartfon=0,kompjuter};

class Device {
    char model[101];
    tip tipUred;
    double casoviProverka;
    static double pocetniCasovi;
    int godinaProizvodstvo;
public:
    Device(char *model="", tip tipUred=smartfon,int godinaProizvodstvo=2010){
        strcpy(this -> model,model);
        this -> tipUred = tipUred;
        this -> godinaProizvodstvo = godinaProizvodstvo;
        casoviProverka = pocetniCasovi;

    }
    Device(const Device &other){
        strcpy(this -> model,other.model);
        this -> tipUred = other.tipUred;
        this -> godinaProizvodstvo = other.godinaProizvodstvo;
        this -> casoviProverka = other.casoviProverka;
    }

    static void setPocetniCasovi(double x){
        pocetniCasovi = x;
    }
    void setCasoviProverka(){
        casoviProverka = pocetniCasovi;
    }

    friend ostream &operator<<(ostream &os, Device &d){
        os << d.model << endl;
        d.setCasoviProverka();
        if (d.godinaProizvodstvo > 2015){
            d.casoviProverka +=2;
        }
        if (d.tipUred == kompjuter){
            d.casoviProverka+=2;
        }
        if (d.tipUred == smartfon){
            os << "Mobilen ";

        }
        else {
            os << "Laptop ";
        }
        os << d.casoviProverka << endl;
    }

    int getGodinaProizvodstvo(){
        return godinaProizvodstvo;
    }
    double getCasoviProverka(){
        return casoviProverka;
    }

    ~Device(){}
};
double Device::pocetniCasovi=1;

class MobileServis{
    char adresa[101];
    Device *devices;
    int numDevices;
public:
    MobileServis(char *adresa="" , Device *devices= nullptr, int numDevices=0){
        strcpy(this -> adresa,adresa);
        this -> numDevices = numDevices;
        this -> devices = new Device [numDevices];
        for (int i = 0; i < numDevices; ++i) {
            this -> devices[i] = devices[i];
        }
    }
    MobileServis(const MobileServis &other){
        strcpy(this -> adresa,other.adresa);
        this -> numDevices = other.numDevices;
        this -> devices = new Device [other.numDevices];
        for (int i = 0; i < numDevices; ++i) {
            this -> devices[i] = other.devices[i];
        }
    }
    MobileServis &operator+=(Device &d){
        if (d.getGodinaProizvodstvo() > 2019 || d.getGodinaProizvodstvo()<2000){
            cout << "Невалидна година на производство" << endl;
        }
        else {
            Device *temp = new Device [numDevices+1];
            for (int i = 0; i < numDevices; ++i) {
                temp[i] = devices[i];
            }
            temp[numDevices] = d;
            numDevices++;
            delete [] devices;
            devices = temp;
        }
        return *this;
    }

    void pecatiCasovi(){
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < numDevices; ++i) {
            cout << devices[i];
        }
    }



    ~MobileServis(){
        delete [] devices;
    }
};






#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}


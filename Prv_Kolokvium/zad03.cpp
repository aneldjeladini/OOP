/*
 * За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
Име на компанијата која ја издала акцијата (низа од 50 знаци)
Цена според која се купени акциите (реален број)
Моментална цена на акцијата (реален број)
Број на акции кои се купени (цел број)
За класата да се дефинираат потребните конструктори и set метода за моменталната цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се имплементираат методи double value() и double profit(). Првата треба да ја пресметува вредноста на акциите, а втората треба да го пресметува моменталниот профит од акциите. Пресметката се врши на следниот начин (5 поени):

Вредност = број на акции * моментална цена
Профит = број на акции * (моментална цена - цена по која се купени)
Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени): Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит

Да се креира класа Client која содржи:

Име и презиме на клиентот (низа од 60 знаци)
ID на сметка (цел број)
Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
Број на објекти во низата (цел број)
За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:

+= за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)

<< за печатење на информации за портфолиото на клиентот така што во првиот ред ќе бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)

Комплетна функционанлост (5 поени)

 input:
3
Aleksandar
240992
3
CH0038863350
Nestle
100
90
100
DE000BAY0017
Bayer
60
70
500
DE0007164600
SAP
110
115
200

 Output:
 =====TEST NA KLASATA Client=====
Konstruktor OK
Operator += OK
240992 67000
Nestle 100 100 90 -1000
Bayer 500 60 70 5000
SAP 200 110 115 1000
Operator << OK
 */
#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord {
    char ID[12];
    char companyName[50];
    double buyPrice;
    double currentPrice;
    int numStocks;
public:
    StockRecord(){}
    StockRecord(char *ID, char *companyName, int buyPrice, int numStocks){
        strcpy(this -> ID, ID);
        strcpy(this -> companyName , companyName);
        this -> buyPrice = buyPrice;
        this -> numStocks = numStocks;
        this -> currentPrice = buyPrice;
    }
    StockRecord(char *ID, char *companyName, double buyPrice, double currentPrice, int numStocks){
        strcpy(this -> ID, ID);
        strcpy(this -> companyName , companyName);
        this -> buyPrice = buyPrice;
        this -> currentPrice = currentPrice;
        this -> numStocks = numStocks;

    }
    StockRecord(const StockRecord &sr){
        strcpy(this -> ID, sr.ID);
        strcpy(this -> companyName , sr.companyName);
        this -> buyPrice = sr.buyPrice;
        this -> currentPrice = sr.currentPrice;
        this -> numStocks = sr.numStocks;
    }

    void setNewPrice(double c){
        currentPrice = c;
    }

    double getCurrentPrice(){
        return currentPrice;
    }

    char *getName() {
        return companyName;
    }

    double value() const{
        return numStocks * currentPrice;
    }
    double profit() const{
        return numStocks * (currentPrice - buyPrice);
    }


    friend ostream &operator<< (ostream& os, const StockRecord &s){
        os << s.companyName << " " << s.numStocks << " " << s.buyPrice << " " << s.currentPrice << " " << s.profit() << endl;
        return os;
    }

    ~StockRecord(){}

};

class Client {
    char nameAndSurname [60];
    int ID;
    StockRecord companies[100];
    int numberOfCompanies;
public:
    Client(){}
    Client(char *nameAndSurname, int ID, StockRecord *companies, int numberOfCompanies){
        strcpy(this -> nameAndSurname,nameAndSurname);
        this -> ID = ID;
        this -> numberOfCompanies = numberOfCompanies;
        for (int i = 0; i < numberOfCompanies; ++i) {
            this -> companies[i] = companies[i];
        }
    }
    Client(char *nameAndSurname, int ID){
        strcpy(this -> nameAndSurname,nameAndSurname);
        this -> ID = ID;
        this -> numberOfCompanies = 0;
    }
    Client(const Client &c){
        strcpy(this -> nameAndSurname,c.nameAndSurname);
        this -> ID = c.ID;
        this -> numberOfCompanies = c.numberOfCompanies;
        for (int i = 0; i < this->numberOfCompanies; ++i) {
            this -> companies[i] = c.companies[i];
        }
    }

    double totalValue() const{
        double total = 0.0;
        for (int i = 0; i < numberOfCompanies; ++i) {
            total += companies[i].value();
        }
        return total;
    }

    Client &operator+=(const StockRecord &other){
        if (numberOfCompanies < 100){
            companies[numberOfCompanies] = other;
            numberOfCompanies++;
        }
        return *this;
    }

    friend ostream &operator<< (ostream& os,  const Client &c){
        os << c.ID << " " << c.totalValue() << endl;

        for (int i = 0; i < c.numberOfCompanies; ++i) {
            os << c.companies[i];
        }
        return os;
    }

    ~Client(){}

};




// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}

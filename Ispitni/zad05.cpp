/*
 *Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата. Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

 Input:
6
5
Albert Einstein
einstein@finki.mk
1
2
Isaac Newton
newton@finki.mk
2
10
Galileo Galilei
galilei@finki.mk
1
12
Stephen Hawking
hawking@finki.mk
0
17
Nikola Tesla
tesla@finki.mk
0
7

 Output:
 ===== Test Case - update method  ======

Update:
Albert Einstein
einstein@finki.mk
2
loyal 10
Isaac Newton
newton@finki.mk
10
vip 30
Galileo Galilei
galilei@finki.mk
12
vip 30
Stephen Hawking
hawking@finki.mk
17
loyal 10
Nikola Tesla
tesla@finki.mk
7
loyal 10
 */

#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;
const int MAX = 500;
enum typeC {STANDARD, LOYAL, VIP};
class Customer {
    char name[51];
    char eMail[51];
    typeC type;
    int baseDsicount; //%
    int additionalDiscount; // %
    int productsBought;
public:
    Customer(const char *name="",const char *eMail="", typeC type = STANDARD,  int productsBought=0){
        strcpy(this -> name,name);
        strcpy(this -> eMail,eMail);
        this -> type = type;
        this -> productsBought = productsBought;
        if (type == STANDARD){
            baseDsicount = 0;
            additionalDiscount = 0;
        }else if (type == LOYAL){
            baseDsicount = 10;
            additionalDiscount = 0;
        }else if (type == VIP){
            baseDsicount = 10;
            additionalDiscount = 20;
        }
    }

    Customer(const Customer &c){
        strcpy(this -> name,c.name);
        strcpy(this -> eMail,c.eMail);
        this -> type = c.type;
        this -> productsBought = c.productsBought;
        this -> baseDsicount = c.baseDsicount;
        this -> additionalDiscount = c.additionalDiscount;
    }

    void setDiscount1(int x){
        this -> baseDsicount = x;
    }
    void setType(typeC type){
        this -> type = type;
    }

    void setAdditionalDiscount(int additionalDiscount){
        this -> additionalDiscount = additionalDiscount;
    }

    typeC getType(){
        return type;
    }

    int getProductsBought(){
        return productsBought;
    }

    char *getEmail(){
        return eMail;
    }

    friend ostream &operator<< (ostream &os, Customer &c){
        os << c.name << endl;
        os << c.eMail << endl;
        os << c.productsBought << endl;
        if (c.type == STANDARD){
            os << "standard " << c.baseDsicount + c.additionalDiscount << endl;
        }
        else if (c.type == LOYAL){
            os << "loyal " << c.baseDsicount + c.additionalDiscount << endl;
        }
        else if (c.type == VIP){
            os << "vip " << c.baseDsicount + c.additionalDiscount << endl;
        }

        return os;
    }

    ~Customer(){}

};

class FINKI_bookstore{
    Customer *customers;
    int numCustomers;
public:
    FINKI_bookstore(Customer *customers = nullptr, int numCustomers = 0){
        this -> numCustomers = numCustomers;
        this -> customers = new Customer [numCustomers];
        for (int i = 0; i < numCustomers; ++i) {
            this -> customers[i] = customers[i];
        }
    }




    FINKI_bookstore &operator+=(Customer &c){
        for (int i = 0; i < numCustomers; ++i) {
            if (strcmp(customers[i].getEmail(),c.getEmail()) == 0){
                cout <<  "The user already exists in the list!" << endl;
                return *this;
            }
        }
        Customer *tmp = new Customer [numCustomers+1];
        for (int i = 0; i < numCustomers; ++i) {
            tmp[i] = customers[i];
        }
        tmp[numCustomers] = c;
        delete [] customers;
        customers = tmp;
        numCustomers++;
        return *this;
    }

    void update(){
        for (int i = 0; i < numCustomers; ++i) {
            if (customers[i].getType()== STANDARD && customers[i].getProductsBought() > 5){
                customers[i].setType(LOYAL);
                customers[i].setDiscount1(10);
            }
            else if (customers[i].getType() == LOYAL && customers[i].getProductsBought() > 10){
                customers[i].setType(VIP);
                customers[i].setAdditionalDiscount(20);
            }
        }
    }

    friend ostream &operator<< (ostream &os, FINKI_bookstore &fi){
        for (int i = 0; i < fi.numCustomers; ++i) {
            os << fi.customers[i];
        }
        return os;
    }

    void setCustomers (Customer * customers, int n){
        delete [] this -> customers;
        this -> numCustomers = n;
        this -> customers = new Customer [n];
        for (int i = 0; i < n; ++i) {
            this -> customers[i] = customers[i];
        }
    }

    ~FINKI_bookstore(){
        delete [] customers;
    }

};



int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}

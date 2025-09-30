/*
 * Да се дефинира класа IceCream во која се чуваат податоци за:

име (динамичка низа од знаци),
состав (низа од знаци, најмногу 100)
цена (децимален број),
попуст (цел број, изразен во проценти) иницијална вредност 0.
За потребите на класата да се имплементираат:

соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
оператор << за печатење на податоците за сладоледот во следниов формат:
име: состав цена [цена на попуст]

делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)

оператор ++ во префикс нотација за зголемување на попустот за 5
оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
метод void setName(char* name) со кој се менува името на сладоледот.
Да се креира класа IceCreamShop во која се чува:

име на продавницата (низа од знаци, најмногу 50)
динамички резервирано поле од објекти од класата IceCream
број на сладоледи во полето (цел број).
За оваа класа да се обезбедат:

соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
оператор += за додавање нов објект од класата IceCream во полето
оператор << за печатење на листа од сите сладоледи во продавницата. Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.

 Input:
 3
FINKI Ice Cream
3
Strawberry Ice Cream in Lemon Bowls
Strawberry ice cream, Lemons
100
Caramel Apple Delight
Caramel Delight ice cream, Apples
120
Dreyer’s Ice Cream Blueberry Pie
French Vanilla ice cream, Graham cracker pie crust, blueberries
60

 Output:
====== TESTING IceCreamShop ======
CONSTRUCTOR
OPERATOR +=
FINKI Ice Cream
Strawberry Ice Cream in Lemon Bowls: Strawberry ice cream, Lemons 100
Caramel Apple Delight: Caramel Delight ice cream, Apples 120
Dreyer’s Ice Cream Blueberry Pie: French Vanilla ice cream, Graham cracker pie crust, blueberries 60

 */

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;


class IceCream{
    char name[200];
    char ingr[100];
    float price;
    int discount;
public:
    IceCream(){
        discount = 0;
    }
    IceCream(char *name,char *ingr, float price, int discount){
        strcpy(this -> name , name);
        strcpy(this -> ingr , ingr);
        this -> price = price;
        this -> discount = discount;
    }
    IceCream(char *name,char *ingr, float price){
        strcpy(this -> name , name);
        strcpy(this -> ingr , ingr);
        this -> price = price;
        discount = 0;
    }
    IceCream(const IceCream &i){
        strcpy(this -> name , i.name);
        strcpy(this -> ingr , i.ingr);
        this -> price = i.price;
        this -> discount = i.discount;
    }

    void setDiscount(int discount){
        if (discount >= 0 && discount <= 100) {
            this->discount = discount;
        }
    }
    void setName(char *name){
        strcpy(this -> name, name);
    }

    char *getName(){
        return name;
    };
    char *getIngr(){
        return ingr;
    }
    float getPrice(){
        return price;
    }
    int getDiscount(){
        return discount;
    }

    friend ostream &operator<<(ostream &os, const IceCream &iceCream){
        os << iceCream.name << ": " << iceCream.ingr << " " << iceCream.price << " ";
        if (iceCream.discount > 0){
            os << "("<<iceCream.price - (iceCream.price * (iceCream.discount / 100.0)) <<")";
        }

        return os;
    }

    IceCream &operator++(){
        discount += 5;
        return *this;
    }

    IceCream operator+ ( const IceCream &other) const  {
        IceCream temp(*this);
        strcat(temp.name,"+");
        strcat(temp.name,other.name);

        strcat(temp.ingr, ", ");
        strcat(temp.ingr,other.ingr);

        temp.price += (other.price + 10);
        temp.discount = other.discount;

        return temp;

    }

    IceCream operator+(const char* extraIngredient) const {
        IceCream temp(*this);

        strcat(temp.name, " + ");
        strcat(temp.name, extraIngredient);

        temp.price += 10;

        return temp;
    }


    ~IceCream(){}

};

class IceCreamShop{
    char name[50];
    IceCream iceCreams[200];
    int number_icecreams;
public:
    IceCreamShop(){
        number_icecreams = 0;
    }
    IceCreamShop(char *name){
        strcpy(this -> name,name);
        number_icecreams = 0;
    }
    IceCreamShop(const IceCreamShop &shop){
        strcpy(this -> name, shop.name);
        this -> number_icecreams = shop.number_icecreams;
        for (int i = 0; i < number_icecreams; ++i) {
            this -> iceCreams[i] = shop.iceCreams[i];
        }
    }

    IceCreamShop &operator+= (const IceCream &iceCream){
        iceCreams[number_icecreams] = iceCream;
        number_icecreams++;

        return *this;
    }

    friend ostream &operator<< (ostream &os,IceCreamShop &shop){
        os << shop.name << endl;
        for (int i = 0; i < shop.number_icecreams; ++i) {
            cout << shop.iceCreams[i] << endl;
        }
        return os;
    }

    ~IceCreamShop(){}
};



int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
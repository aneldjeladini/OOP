/*
 Да се дефинира класа Product во која ќе се чуваат информации за производ во една продавница и тоа име (стринг), категорија (стринг) и цена (цел број) и достапна количина (цел број).

За класата да се дефинираат потребните конструктори, оператор за печатење << и метод int totalPrice() - методот ја враќа вкупната вредност на производот пресметана како производ на цената и достапната количина. (10 п.)

Да се дефинира класа Store во која ќе се чуваат листа на производи (динамички алоцирана низа од објекти од класата Product и цел број кој ја означува големината на листата).

За класата да се имплементираат:

Потребните конструктори
Оператор += за додавање на производ (Product) во продавницата (5 п.)
Оператор за печатење << (5 п.)
Метод Store fromCategory (string & category) - кој прима како аргумент категорија (стринг), а враќа нов објект од класата Store во кој во листата на производи се сместени само производи од категоријата category. (5 п.)
Доколку нема ниту еден таков продукт да се фрли исклучок од класата NoProductFoundException. (5 п.) Справувањето со исклучокот треба да испечати порака “No products from category {category} were found in the store”. (5 п.)
Дополнете ја main функцијата со следните барања:

Од датотеката input.txt прочитајте ги информациите за сите производи:
За секој производ во 4 реда се дадени информациите за името, категоријата, цената и количината.
По читањето на информациите за секој производ, секој производ се додава во објектот store.
Во датотеката output1.txt да се испечатат информациите за продавницата.
Во датотеката output2.txt да се испечати резултатот од методот fromCategory за категоријата category вчитана во почетниот код. (15 п.)

 Input:
 Coca-cola zero 1.75L
drinks
80
100
Sandwich with ham and cheese
food
60
150
----
drinks

 Output:
 All products:
Coca-cola zero 1.75L (drinks) 100 x 80 = 8000
Sandwich with ham and cheese (food) 150 x 60 = 9000
Products from category drinks:
Coca-cola zero 1.75L (drinks) 100 x 80 = 8000
 */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;



void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


class NoProductFoundException{
    string category;
public:
    NoProductFoundException(string category=""){
        this -> category = category;
    }

    void message(){
        cout << "No products from category " << category << " were found in the store" << endl;
    }
};

class Product {
    string name;
    string category;
    int price;
    int availableQuantity;
public:
    Product(const string &name="", const string &category="", int price=0,int availableQuantity=0){
        this -> name = name;
        this -> category = category;
        this -> price = price;
        this -> availableQuantity = availableQuantity;
    }
    Product(const Product &other){
        this -> name = other.name;
        this -> category = other.category;
        this -> price = other.price;
        this -> availableQuantity = other.availableQuantity;
    }

    Product &operator=(const Product &other){
        if (this != &other){
            this -> name = other.name;
            this -> category = other.category;
            this -> price = other.price;
            this -> availableQuantity = other.availableQuantity;
        }
        return *this;
    }

    string getCategory(){
        return category;
    }
    string getName(){
        return name;
    }
    int getPrice(){
        return price;
    }
    int getAvailableQuantity(){
        return availableQuantity;
    }

    int totalPrice(){
        return price * availableQuantity;
    }

    friend ostream &operator<<(ostream &os,Product &p){
        os << p.name << " (" << p.category << ") " << p.availableQuantity << " x " << p.price << " = " << p.totalPrice() << endl;
        return os;
    }

    ~Product(){}
};

class Store{
    Product *products;
    int numProducts;
public:
    Store(Product *products= nullptr, int numProducts = 0){
        this -> numProducts = numProducts;
        this -> products = new Product [numProducts];
        for (int i = 0; i < numProducts; ++i) {
            this -> products[i] = products[i];
        }
    }
    Store(const Store &other){
        this -> numProducts = other.numProducts;
        this -> products = new Product [other.numProducts];
        for (int i = 0; i < numProducts; ++i) {
            this -> products[i] = other.products[i];
        }
    }
    Store &operator+=(Product &p){
        Product *temp = new Product[numProducts+1];
        for (int i = 0; i < numProducts; ++i) {
            temp[i] = products[i];
        }
        temp[numProducts] = p;
        numProducts++;
        delete [] products;
        products = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, Store &s){
        for (int i = 0; i < s.numProducts; ++i) {
            os << s.products[i];
        }
        return os;
    }
    Store fromCategory(string &category){
        Product *filtered = new Product[numProducts];
        int count=0;
        for (int i = 0; i < numProducts; ++i) {
            if (products[i].getCategory() == category){
                filtered[count] = products[i];
                count++;
            }
        }
        if (count == 0){
            delete [] filtered;
            throw NoProductFoundException(category);
        }
        Store result (filtered, count);
        delete [] filtered;
        return result;
    }

    ~Store(){
        delete [] products;
    }
};


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    ifstream fin("input.txt");
    string name,categoryInput;
    int price, quantity;

    while (getline(fin,name)){
        getline(fin,categoryInput);
        fin >> price >> quantity;
        fin.ignore();
        Product p(name,categoryInput,price,quantity);
        s+=p;
    }
    fin.close();

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream fout1("output1.txt");
    fout1 << s;
    fout1.close();

    ofstream fout2("output2.txt");
    try {
        Store filtered = s.fromCategory(category);
        fout2 << filtered;
    } catch (NoProductFoundException &e){
        e.message();
    }
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}
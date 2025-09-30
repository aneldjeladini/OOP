/*
 * Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

 Input:
 4
3
1
0-312-31677-1
The Moscow Vector
Robert Ludlum
7
www.finki-education/olinebooks/book1.pdf
1
2
007-6092006565
Thinking in C++
Bruce Eckel
52
1.2
1
1
978-0672326974
C++ Primer Plus
Stephen Prata
20
www.finki-education/olinebooks/book2.pdf
30

 Output:
====== Testing method mostExpensiveBook() ======
FINKI-Education
Total number of online books: 2
Total number of print books: 1
The most expensive book is:
007-6092006565: Thinking in C++, Bruce Eckel 59.8

 */

#include<iostream>
#include<cstring>

using namespace std;


class Book {
protected:
    char ISBN[21];
    char title[51];
    char author[31];
    double basePrice;
public:
    Book(char *ISBN="", char *title ="", char *author="", double basePrice=0){
        strcpy(this -> ISBN,ISBN);
        strcpy(this -> title,title);
        strcpy(this -> author,author);
        this -> basePrice = basePrice;
    }
    Book(const Book &other){
        strcpy(this -> ISBN,other.ISBN);
        strcpy(this -> title,other.title);
        strcpy(this -> author,other.author);
        this -> basePrice = other.basePrice;
    }
    Book &operator=(const Book &other){
        if (this != &other) {
            strcpy(this->ISBN, other.ISBN);
            strcpy(this->title, other.title);
            strcpy(this->author, other.author);
            this->basePrice = other.basePrice;
        }
        return *this;
    }

    virtual double bookPrice() = 0;

    bool operator> ( Book &other){
        return this -> bookPrice() > other.bookPrice();
    }
    friend ostream &operator<< (ostream &os, Book &b){
        os << b.ISBN << ": " << b.title << ", " << b.author << " " << b.basePrice << endl;
    }

    void setISBN(char *ISBN){
        strcpy(this -> ISBN,ISBN);
    }



    virtual ~Book() = default;
};

class OnlineBook:public Book {
    char *url;
    int sizeMB;
public:
    OnlineBook(char *ISBN="", char *title ="", char *author="", double basePrice=0, char *url = nullptr, int sizeMB = 0)
            : Book(ISBN,title,author,basePrice){
        this -> url = new char [strlen(url)+1];
        strcpy(this -> url,url);
        this -> sizeMB = sizeMB;
        if (sizeMB > 20){
            this -> basePrice = basePrice + basePrice * (20.0/100.0);
        }
    }
    OnlineBook(const OnlineBook &other) : Book(other){
        this -> url = new char [strlen(other.url)+1];
        strcpy(this -> url, other.url);
        this -> sizeMB = other.sizeMB;
    }
    OnlineBook &operator=(const OnlineBook &other) {
        if (this!=&other){
            strcpy(this -> ISBN,other.ISBN);
            strcpy(this -> title,other.title);
            strcpy(this -> author,other.author);
            this -> basePrice = other.basePrice;
            delete [] url;
            this -> url = new char [strlen(other.url)+1];
            strcpy(this -> url, other.url);
            this -> sizeMB = other.sizeMB;
        }
        return *this;
    }



    double bookPrice() override{
        if (sizeMB > 20){
            return basePrice + basePrice * (20.0/100.0);
        }
        return basePrice;
    }



    ~OnlineBook(){
        delete [] url;
    }
};

class PrintBook : public Book {
    double weightKG;
    bool available;
public:
    PrintBook(char *ISBN="", char *title ="", char *author="", double basePrice=0, double weightKG = 0, bool available = false)
            : Book(ISBN,title,author,basePrice){
        this -> weightKG = weightKG;
        this -> available = available;
        if (weightKG > 0.7){
            this -> basePrice = basePrice + basePrice * (15.0/100.0);
        }
    }
    PrintBook(const PrintBook &other) : Book(other){
        this -> weightKG = other.weightKG;
        this -> available = other.available;
    }
    PrintBook &operator= (const PrintBook &other){
        if (this != &other){
            strcpy(this->ISBN, other.ISBN);
            strcpy(this->title, other.title);
            strcpy(this->author, other.author);
            this->basePrice = other.basePrice;
            this -> weightKG = other.weightKG;
            this -> available = other.available;
        }
        return *this;
    }

    double bookPrice() override{
        if (weightKG > 0.7){
            return basePrice + basePrice * (15.0/100.0);
        }
        return basePrice;
    }


};

void mostExpensiveBook (Book** books, int n){
    cout << "FINKI-Education" << endl;
    int countOnline = 0;
    int countPrint = 0;
    Book *mostexpensive = books[0];
    for (int i = 0; i < n; ++i) {
        if (dynamic_cast<OnlineBook *> (books[i])){
            countOnline++;
        }
        else {
            countPrint ++;
        }
        if (books[i]->bookPrice() > mostexpensive->bookPrice()){
            mostexpensive = books[i];
        }
    }
    cout << "Total number of online books: " << countOnline << endl;
    cout << "Total number of print books: " << countPrint << endl;
    cout << "The most expensive book is: " << endl;
    cout << *mostexpensive;
}


int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}

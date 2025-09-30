/*
Дефинирајте апстрактна класа Library со следниве спецификации (5 поени):

Име на библиотеката (низа од максимум 50 знаци/стринг)
Град во кој се наоѓа (низа од максимум 50 знаци/стринг)
Основна цена на месечна членарина (реален број)
Информација дали работи за викенд (Boolean променлива)
Дополнително, класата треба да содржи двe чисто виртуелни функции-членови на класта:

void printDetail() - функција која ги печати информациите за објектот
double calculateMembershipCardCost() - функција која враќа цена на чинење на членарина во библиотеката
Да се дефинираат две класи, AcademicLibrary и NationalLibrary, кои наследуваат од класата Library (5 поени).

За класата AcademicLibrary дополнително се чува информација за отворени можности за истражување (Boolean променлива), како и информација за број на специјализирани колекции од списанија во рамки на библиотеката (целобројна променлива).

Цената на членарина (функција double calculateMembershipCardCost()) за AcademicLibrary се пресметува на следниот начин:

Ако библиотеката нуди отворени можности за истражување, тогаш цената се зголемува за 24%.
Дополнително, секоја специјализирани колекции од списанија ја зголемува цената за $6.

Функцијата void printDetail() ги печати карактеристиките за библиотеката во следниот формат:

[Ime na biblioteka] - (Academic) [Grad] [Broj na spec. kolekcii] [Cena na clenarina] (10 поени)

За класата NationalLibrary дополнително се чува информација за тоа дали библиотеката нуди едукативни програми за културното наследство (Boolean променлива), како и информација за бројот на сочувани оригинални ракописи од национално значење (цел број).

Цената на членарина (функција double calculateMembershipCardCost()) за NationalLibrary се пресметува на следниот начин:

Ако библиотеката нуди едукативни програми, тогаш цената се намалува за 7%.
Дополнително, секој сочуван оригинален ракопис ја зголемува цената за $15.

Функцијата void printDetail() ги печати карактеристиките за библиотеката во следниот формат:

[Ime na biblioteka] - (National) [Grad] [Broj na rakopisi] [Cena na clenarina] (10 поени)

Да се дефинира следната глобална функција:

int findMostExpensiveNationalLibrary(Library **l, int n) која како аргумент прима низа од покажувачи кон библиотеки и големина на низата, а како резултат го враќа индексот во низата на националната библиотека (NationalLibrary) која има најскапата членарина.
 Доколку не постои таков објект во низата, функцијата враќа -1. Ако повеќе национални библиотеки имаат иста цена на членарина, се избира таа која работи за викенд (последниот најден). (20 поени)

 Input:
 4
2
1
Harvard Library
Cambridge
25.0
1
1
38
1
Stanford Library
Stanford
20.0
1
0
120

 Output:
 National Library not found in the array!
findMostExpensiveNationalLibrary method OK
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Library{
protected:
    string name;
    string city;
    double subscriptionPrice;
    bool openOnWeekends;
public:

    Library(const string &name="",const string &city="", double subscriptionPrice=0,  bool openOnWeekends = false){
        this -> name = name;
        this -> city = city;
        this -> subscriptionPrice = subscriptionPrice;
        this -> openOnWeekends = openOnWeekends;
    }

    Library(const Library &other){
        this -> name = other.name;
        this -> city = other.city;
        this -> subscriptionPrice = other.subscriptionPrice;
        this -> openOnWeekends = other.openOnWeekends;
    }

    Library &operator= (const Library &other){
        if (this != &other){
            this -> name = other.name;
            this -> city = other.city;
            this -> subscriptionPrice = other.subscriptionPrice;
            this -> openOnWeekends = other.openOnWeekends;
        }
        return *this;
    }

    bool getOpenWeekends(){
        return openOnWeekends;
    }

    virtual void printDetail() =0;
    virtual double calculateMembershipCardCost() =0;

    virtual ~Library() = default;

};

class AcademicLibrary : public Library{
    bool researchOpportunity;
    int numberColections;
public:
    AcademicLibrary(const string &name="",const string &city="", double subscriptionPrice=0,  bool openOnWeekends = false,bool researchOpportunity=false,int numberColections = 0 )
            : Library(name,city,subscriptionPrice,openOnWeekends){
        this -> researchOpportunity = researchOpportunity;
        this -> numberColections = numberColections;
    }
    AcademicLibrary(const AcademicLibrary &other) : Library(other){
        this -> researchOpportunity = other.researchOpportunity;
        this -> numberColections = other.numberColections;
    }
    AcademicLibrary &operator=(const AcademicLibrary &other){
        if (this != &other){
            this -> name = other.name;
            this -> city = other.city;
            this -> subscriptionPrice = other.subscriptionPrice;
            this -> openOnWeekends = other.openOnWeekends;
            this -> researchOpportunity = other.researchOpportunity;
            this -> numberColections = other.numberColections;
        }
        return *this;
    }


    double calculateMembershipCardCost() override {
        double cost = subscriptionPrice;
        if (researchOpportunity){
            cost *= 1.24;
        }
        cost += (numberColections * 6);
        return cost;
    }

    void printDetail() override{
        cout << name << " - (Academic) " << city << " " << numberColections << " " << calculateMembershipCardCost() << endl;
    }




    ~AcademicLibrary(){}
};


class NationalLibrary : public Library{
    bool offersEducationPrograms;
    int numOriginalHandwritings;
public:
    NationalLibrary(const string &name="",const string &city="", double subscriptionPrice=0,  bool openOnWeekends = false, bool offersEducationPrograms=false,  int numOriginalHandwritings=0 )
            : Library(name,city,subscriptionPrice,openOnWeekends) {
        this -> offersEducationPrograms = offersEducationPrograms;
        this -> numOriginalHandwritings = numOriginalHandwritings;
    }
    NationalLibrary(const NationalLibrary &other) : Library(other){
        this -> offersEducationPrograms = other.offersEducationPrograms;
        this -> numOriginalHandwritings = other.numOriginalHandwritings;
    }
    NationalLibrary &operator= (const NationalLibrary &other){
        if (this != &other){
            this -> name = other.name;
            this -> city = other.city;
            this -> subscriptionPrice = other.subscriptionPrice;
            this -> openOnWeekends = other.openOnWeekends;
            this -> offersEducationPrograms = other.offersEducationPrograms;
            this -> numOriginalHandwritings = other.numOriginalHandwritings;
        }
        return *this;
    }

    double calculateMembershipCardCost() override {
        double cost = subscriptionPrice;
        if (offersEducationPrograms){
            cost *= 0.93;
        }
        cost += (numOriginalHandwritings * 15);

        return cost;
    }

    void printDetail() override{
        cout << name << " - (National) " << city << " " << numOriginalHandwritings << " " << calculateMembershipCardCost() << endl;
    }


    ~NationalLibrary(){}
};

int findMostExpensiveNationalLibrary(Library **l, int n){
    int index = -1;
    for (int i = 0; i < n; ++i) {
        if (dynamic_cast<NationalLibrary *>(l[i])){
            index = i;
        }
    }
    if (index == -1){
        return index;
    }
    Library *max = l[index];
    for (int i = 0; i < n; ++i) {
        if (dynamic_cast<NationalLibrary *>(l[i])){
            if (l[i]->calculateMembershipCardCost() > max->calculateMembershipCardCost()){
                max = l[i];
                index = i;
            }
            else if (l[i]->calculateMembershipCardCost() == max->calculateMembershipCardCost()){
                if (l[i]->getOpenWeekends()){
                    max = l[i];
                    index = i;
                }
            }
        }
    }
    return index;
}




int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}

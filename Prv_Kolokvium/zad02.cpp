/*Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот

 Input:
 2
1
1
2
0 1
0
 Output:
 List number: 1 List info: 1: 1 sum: 1 average: 1
Sum: 1 Average: 1
Successful attempts: 1 Failed attempts: 1*/

#include <iostream>
#include <cctype>

using namespace std;

class List {
    int broj_broevi;
    int broevi[100];
public:
    List(){}
    List(int broevi[],int broj_broevi){
        this -> broj_broevi = broj_broevi;
        for (int i = 0; i < broj_broevi; ++i) {
            this -> broevi[i] = broevi[i];
        }
    }
    List(const List &li){
        this -> broj_broevi = li.broj_broevi;
        for (int i = 0; i < broj_broevi; ++i) {
            this -> broevi[i] = li.broevi[i];
        }
    }

    List& operator=(const List &other) {
        if (this != &other) {
            this->broj_broevi = other.broj_broevi;
            for (int i = 0; i < broj_broevi; ++i) {
                this->broevi[i] = other.broevi[i];
            }
        }
        return *this;
    }
    int getBrojBroevi(){
        return broj_broevi;
    }
    int sum(){
        int Sum = 0;
        for (int i = 0; i < broj_broevi; ++i) {
            Sum += broevi[i];
        }
        return Sum;
    }

    float average(){
        return (1.0 * sum()) / (1.0*broj_broevi);
    }

    void print(){
        cout << "List info: " << broj_broevi <<": ";
        for (int i = 0; i < broj_broevi; ++i) {
            cout << broevi[i] << " ";
        }
        cout << "sum: " << sum() << " " << "average: " << average() << endl;
    }
    ~List(){}
};

class ListContainer {
    List listi[100];
    int broj_listi;
    int broj_obidi;
public:

    ListContainer(){
        broj_obidi = 0;
        broj_listi = 0;
    }
    ListContainer(List listi[] , int brojo_listi){
        this -> broj_listi = brojo_listi;
        for (int i = 0; i < brojo_listi; ++i) {
            this -> listi[i] = listi[i];
        }
    }
    int suc = 0;
    int fail = 0;

    ListContainer& operator=(const ListContainer &other){
        this -> broj_listi = other.broj_listi;
        for (int i = 0; i < broj_listi; ++i) {
            this -> listi[i] = other.listi[i];
            this -> suc = other.suc;
            this -> fail = other.fail;
        }
        return *this;
    }



    void addNewList(List l){
        broj_obidi++;
        for (int i = 0; i < broj_listi; ++i) {
            if (listi[i].sum() == l.sum()){
                fail++;
                return;
            }
        }

        if (broj_listi < 100){
            listi[broj_listi] = l;
            suc ++;
            broj_listi ++;
        }

    }


    int sum(){
        int Sum = 0;
        for (int i = 0; i <broj_listi; ++i) {
            Sum += listi[i].sum();
        }
        return Sum;
    }

    double average(){
        int totalSum = 0;
        int totalElements = 0;
        for (int i = 0; i < broj_listi; ++i) {
            totalSum += listi[i].sum();
            totalElements += listi[i].getBrojBroevi();
        }
        return (1.0*totalSum)/totalElements;
    }

    void print(){
        if (broj_listi == 0){
            cout << "The list is empty" << endl;
            return;
        }
        for (int i = 0; i < broj_listi; ++i) {
            cout << "List number: " << i+1 <<" " ;
            listi[i].print();
        }
        cout << "Sum: " << sum() << " Average: " << average() << endl;
        cout << "Successful attempts: " << suc << " Failed attempts: " << fail << endl;
    }







};





int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}




/*
 Да се дефинира класа Student во која ќе се чуваат информации за студент кој полагал испит по некој предмет и тоа индекс (стринг), име (стринг), презиме (стринг) и поени освоени на испитот (цел број).

За класата да се дефинираат потребните конструктори , оператор за печатење <<  и метод int grade() (методот ја враќа оценката по предметот по скалата 0-49 (5), 50-59 (6), 60-69 (7), 70-79 (8), 80-89 (9), 90-100 (10)). (10 п.)

Да се дефинира класа Results во која ќе се чуваат листа на студенти кои го положиле испитот по предметот (динамички алоцирана низа од објекти од класата Student и цел број кој ја означува големината на листата).

За класата да се имплементираат:

Потребните конструктори
Оператор += за додавање на студент (Student) во резултатите (5 п.)
Доколку студентот кој се додава има помалку од 50 поени, односно не го положил испитот, да се фрли исклучок од класата StudentFailedException. (5 п.) Справувањето со исклучокот треба да испечати порака “Student with id {ID} failed the course”. (5 п.)
Оператор за печатење << (5 п.)

Метод Results withGrade(int grade) - кој прима како аргумент оценка (цел број), а враќа нов објект од класата Results во кој во листата на студенти кои го полагале предметот се содржат само студентите со оценка grade. (5 п.)

Дополнете ја main функцијата со следните барања:

Од датотеката input.txt прочитајте ги информациите за сите студенти кои го полагале испитот и тоа во следниот формат:
Информациите за секој студент се дадени во еден ред и тоа во редослед индекс, име, презиме и поени, одделени со празно место.
По читањето на информациите за секој студент, секој студент се додава во објектот results.
Во датотеката output1.txt да се испечатат резултатите за сите студенти.

Во датотеката output2.txt да се испечатат резултатите за сите студенти со оценка grade вчитана во почетниот код. (15 п.)

 Input:
151020 Stefan Andonov 89
151021 Vlatko Spasev 55
----
9

 Output:
 All students:
151020 Stefan Andonov 89 Grade: 9
151021 Vlatko Spasev 55 Grade: 6
Grade report for grade 9:
151020 Stefan Andonov 89 Grade: 9
 */

#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
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

class StudentFailedException {
    string id;
public:
    StudentFailedException(const string &id=""){
        this -> id = id;
    }
    void message(){
        cout << "Student with id " << id << " failed the course" << endl;
    }
};


class Student{
    string indeks;
    string ime;
    string prezime;
    int poeni;
public:
    Student(const string &indeks="",const string &ime="", const string &prezime="", int poeni=0){
        this -> indeks = indeks;
        this -> ime = ime;
        this -> prezime = prezime;
        this -> poeni = poeni;
    }
    Student (const Student &other){
        this -> indeks = other.indeks;
        this -> ime = other.ime;
        this -> prezime = other.prezime;
        this -> poeni = other.poeni;
    }
    Student &operator=( const Student &other){
        if (this != &other){
            this -> indeks = other.indeks;
            this -> ime = other.ime;
            this -> prezime = other.prezime;
            this -> poeni = other.poeni;
        }
        return *this;
    }
    int grade() const{
        int ocenka = 0;
        if (poeni < 50){
            ocenka = 5;
        }
        else if (poeni == 100){
            ocenka = 10;
        }
        else if (poeni > 49 && poeni < 100){
            ocenka = poeni/10 + 1;
        }
        return ocenka;
    }

    friend ostream &operator<< (ostream &os, const Student &s){
        os << s.indeks << " " << s.ime << " " << s.prezime << " " << s.poeni << " Grade: " << s.grade() << endl;
        return os;
    }

    string getIndeks(){
        return indeks;
    }

    ~Student(){}
};

class Results {
    Student *studenti;
    int numStudents;
public:
    Results(Student *studenti = nullptr, int numStudents=0){
        this -> numStudents = numStudents;
        this -> studenti = new Student [numStudents];
        for (int i = 0; i < numStudents; ++i) {
            this -> studenti[i] = studenti[i];
        }
    }
    Results(const Results &other){
        this -> numStudents = other.numStudents;
        this -> studenti = new Student [other.numStudents];
        for (int i = 0; i < numStudents; ++i) {
            this -> studenti[i] = other.studenti[i];
        }
    }

    Results &operator=(const Results &other){
        if (this!= &other){
            this -> numStudents = other.numStudents;
            delete [] studenti;
            this -> studenti = new Student [other.numStudents];
            for (int i = 0; i < numStudents; ++i) {
                this -> studenti[i] = other.studenti[i];
            }
        }
        return *this;
    }

    Results &operator+=(Student &s){
        if (s.grade() == 5){
            throw StudentFailedException(s.getIndeks());
        }
        Student *temp = new Student [numStudents+1];
        for (int i = 0; i < numStudents; ++i) {
            temp[i] = studenti[i];
        }
        temp[numStudents] = s;
        numStudents++;
        delete [] studenti;
        studenti = temp;

        return *this;
    }

    friend ostream &operator<< (ostream &os, Results &r){
        for (int i = 0; i < r.numStudents; ++i) {
            os << r.studenti[i];
        }
        return os;
    }

    Results withGrade(int grade){
        Student *filtered = new Student [numStudents];
        int count = 0;
        for (int i = 0; i < numStudents; ++i) {
            if (studenti[i].grade() == grade){
                filtered[count++] = studenti[i];
            }
        }
        Results newResult (filtered,count);
        return newResult;
    }

    int getNumStudents(){
        return numStudents;
    }


    ~Results(){
        delete [] studenti;
    }

};




int main() {

    wtf();

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`
    ifstream fin("input.txt");
    string indeks, ime, prezime;
    int poeni;
    while (fin >> indeks){
        fin >> ime;
        fin >> prezime;
        fin >> poeni;
        Student s (indeks,ime,prezime,poeni);
        try {
            results += s;
        }catch (StudentFailedException &e){
            e.message();
        }
    }
    fin.close();



    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream fout1 ("output1.txt");
    fout1 << results;
    fout1.close();

    ofstream fout2 ("output2.txt");
    Results newR = results.withGrade(grade);
    if (newR.getNumStudents() == 0) {
        fout2 << "None" << endl;
    } else {
        fout2 << newR;
    }
    fout2.close();



    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}
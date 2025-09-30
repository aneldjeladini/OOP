/*
 * Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.

Во класата File треба да се чуваат следниве податоци:

Име на датотеката (динамички алоцирана низа од знаци)
Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:

Конструктор без параметри
Конструктор со параметри
Конструктор за копирање
Деструктор
Преоптоварување на операторот =
Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:

Име на директориумот (динамички алоцирана низа од знаци)
Број на датотеки во него (на почеток директориумот е празен)
Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:

Конструктор со потпис Folder(const char* name)
Деструктор
Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
 */

#include<iostream>
#include<cstring>

using namespace std;

enum Extension {pdf,txt,exe};
class File {
    char ime[100];
    Extension tip;
    char sopstvenik[100];
    int goleminaMB;
public:
    File(){}
    File(char *ime, char *sopstvenik, int goleminaMB, Extension tip){
        strcpy(this -> ime, ime);
        this -> tip = tip;
        strcpy(this -> sopstvenik , sopstvenik);
        this -> goleminaMB = goleminaMB;
    }
    File(const File &f){
        strcpy(this -> ime, f.ime);
        this -> tip = f.tip;
        strcpy(this -> sopstvenik , f.sopstvenik);
        this -> goleminaMB = f.goleminaMB;
    }
    char *getIme(){
        return ime;
    }
    Extension getTip(){
        return tip;
    }
    char *getSopstvenik(){
        return sopstvenik;
    }
    int getGolemina(){
        return goleminaMB;
    }

    File &operator=(const File &other){
        if (this != &other){
            strcpy(this -> ime , other.ime);
            this -> tip = other.tip;
            strcpy(this -> sopstvenik , other.sopstvenik);
            this -> goleminaMB = other.goleminaMB;
        }
        return *this;
    }

    void print() {
        cout << "File name: " << ime;
        if (tip == txt){
            cout << ".txt" << endl;
        } else if(tip == pdf){
            cout << ".pdf" << endl;
        }else if (tip == exe){
            cout << ".exe" << endl;
        }
        cout << "File owner: " << sopstvenik << endl;
        cout << "File size: " << goleminaMB << endl;
    }

    bool equals (const File &that){
        if (strcmp(this -> sopstvenik,that.sopstvenik) == 0 &&
            strcmp(this -> ime,that.ime) == 0 &&
            this -> tip == that.tip){
            return true;
        }
        return false;
    }

    bool equalsType (const File &that){
        if (this -> tip == that.tip){
            return true;
        }
        return false;
    }


    ~File(){}
};

class Folder{
    char ime[100];
    int brojFajlovi;
    File fajlovi[100];
public:
    Folder(){
        brojFajlovi = 0;
    }
    Folder(const char *name){
        strcpy(ime,name);
    }
    Folder(char *ime, int brojFajlovi, File *fajlovi){
        strcpy(this -> ime,ime);
        this -> brojFajlovi = brojFajlovi;
        for (int i = 0; i < brojFajlovi; ++i) {
            this -> fajlovi[i] = fajlovi[i];
        }
    }
    Folder(const Folder &f) {
        strcpy(this->ime, f.ime);
        this->brojFajlovi = f.brojFajlovi;
        for (int i = 0; i < brojFajlovi; ++i) {
            this->fajlovi[i] = f.fajlovi[i];
        }
    }

    void print(){
        cout << "Folder name: " << ime << endl;
        for (int i = 0; i < brojFajlovi; ++i) {
            fajlovi[i].print();
        }
    }

    void remove(const File &file){
        for (int i = 0; i < brojFajlovi; ++i) {
            if (fajlovi[i].equals(file)){
                for (int j = i; j < brojFajlovi-1 ; ++j) {
                    fajlovi[j] = fajlovi[j+1];
                }
                --brojFajlovi;
                return;
            }
        }
    }

    void add(const File &file){
        if (brojFajlovi < 100){
            fajlovi[brojFajlovi] = file;
            brojFajlovi++;
        }
    }


    ~Folder(){};
};


int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
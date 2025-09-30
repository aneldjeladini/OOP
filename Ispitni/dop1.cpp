/*
 Да се дефинира класа Song во која ќе се чуваат информации за некоја песна, и тоа: наслов на песната (стринг), име и презиме на авторот на песната (стринг), изведувач на песната (стринг), времетраење на песната (во секунди, цел број).

За класата да се дефинираат потребните конструктори, set() и get() методи, оператор за читање >>, како и метод void print(ofstream& out), за печатење на информациите за песната во датотека што се предава како аргумент на методот (преку ofstream објектот). (10 п.)

Да се дефинира класа Festival во која ќе се чуваат информации за некој музички фестивал, и тоа: име на фестивалот (стринг), град во којшто се одржува фестивалот (стринг), датум на одржување (стринг; формат: ден/месец/година), како и листа на песни пријавени за фестивалот (динамички алоцирана низа од објекти од класата Song, како и цел број n кој ја означува големината на листата).

За класата Festival да се имплементираат:

Потребните конструктори и деструктор (5 п.)
Оператор -= за бришење на песна (објект од класата Song) од листата. Од листата се бришат сите песни со идентични податоци (исти: наслов, автор, изведувач и времетраење) како песната што е предадена како аргумент на операторот. Пред да се изведе бришење, да се провери дали листата е празна (да се спречи обидот за бришење на објект од празна листа, со печатење на соодветна порака: „Trying to delete from an empty list!“). (10 п.)
Метод void print(ofstream& out), за печатење на информациите за фестивалот во датотека што се предава како аргумент на методот (преку ofstream објектот). Овој метод задолжително треба да го повика методот print од класата Song, за печатење на информациите за листата од песни. (5 п.)

Оператор за читање >> (5 п.)

Метод Festival notFromAuthor(string author) - кој како аргумент прима име и презиме на автор (еден стринг - author), а враќа нов објект од класата Festival кој во листата од песни ги содржи само оние песни чиј автор НЕ е author. (5 п.)

Дополнете ја main функцијата со следните барања:

Од датотеката vlezna.txt прочитајте ги информациите за фестивалот. Секој податок се наоѓа во засебен ред (прво се зададени информациите за самиот фестивал, па бројот на пријавени песни, па на крајот и информациите за секоја песна што е пријавена за фестивалот). Информациите се вчитуваат директно во објектот festival.
Во датотеката izlezna1.txt се печатат сите информации за фестивалот и сите песни.

Во датотеката izlezna2.txt се печатат информациите само за оние песни чиј автор НЕ е авторот author, вчитан во почетниот код. (10 п.)

 Input:
 Ohridski Trubaduri
Ohrid
30/08/2024
2
Usni na usni
Grigor Koprov
Toshe Proeski
215
Tvoeto pismo moja Biblija
Damir Imeri
Andrijana Janevska
198
----
Grigor Koprov

 Output:
 All the data for the festival:
Festival: Ohridski Trubaduri - Ohrid, 30/08/2024
Song title: Usni na usni, Author: Grigor Koprov, Interpreted by: Toshe Proeski, 215 sek.
Song title: Tvoeto pismo moja Biblija, Author: Damir Imeri, Interpreted by: Andrijana Janevska, 198 sek.
Songs NOT from the author Grigor Koprov:
Festival: Ohridski Trubaduri - Ohrid, 30/08/2024
Song title: Tvoeto pismo moja Biblija, Author: Damir Imeri, Interpreted by: Andrijana Janevska, 198 sek.

 */

#include <iostream>
#include <cstring>
#include<string>
#include <fstream>


using namespace std;

class EmptyFestival{
    string message;
public:
    EmptyFestival(const string &message=""){
        this -> message = message;
    }
    void print(){
        cout << message << endl;
    }
};

void wtf() {
    ofstream fout("vlezna.txt");
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

class Song {
    string naslov;
    string avtor;
    string izveduvac;
    int vremetraenje;
public:
    Song(const string &naslov="", const string &avtor="", const string &izveduvac="", int vremetraenje=0){
        this -> naslov = naslov;
        this -> avtor = avtor;
        this -> izveduvac = izveduvac;
        this -> vremetraenje = vremetraenje;
    }
    Song(const Song &other){
        this -> naslov = other.naslov;
        this -> avtor = other.avtor;
        this -> izveduvac = other.izveduvac;
        this -> vremetraenje = other.vremetraenje;
    }
    Song &operator=(const Song &other){
        if (this != &other){
            this -> naslov = other.naslov;
            this -> avtor = other.avtor;
            this -> izveduvac = other.izveduvac;
            this -> vremetraenje = other.vremetraenje;
        }
        return *this;
    }
    void setNaslov(const string &Naslov){
        this -> naslov = Naslov;
    }
    void setAvtor(const string &Avtor){
        this -> avtor = Avtor;
    }
    void setIzveduvac(const string &Izveduvac){
        this -> izveduvac = Izveduvac;
    }
    void setVremetraenje(int Vremetraenje){
        this -> vremetraenje = Vremetraenje;
    }
    string getNaslov(){
        return naslov;
    }
    string getAvtor(){
        return avtor;
    }
    string getIzveduvac(){
        return izveduvac;
    }
    int getVremetraenje()const{
        return vremetraenje;
    }

    friend istream &operator>>(istream &is,Song &s){
        getline(is,s.naslov);
        getline(is,s.avtor);
        getline(is,s.izveduvac);
        is >> s.vremetraenje;
        is.ignore();
        return is;
    }

    void print(ofstream& out) const{
        out << "Song title: " << naslov << ", Author: " << avtor << ", Interpreted by: " << izveduvac << ", " << vremetraenje << " sek." << endl;
    }

    bool operator==(Song &other){
        if (this -> naslov == other.naslov &&
            this -> avtor == other.avtor &&
            this -> izveduvac == other.izveduvac &&
            this -> vremetraenje == other.vremetraenje){
            return true;
        }
        return false;
    }

    ~Song(){}
};

class Festival{
    string name;
    string city;
    string date;
    Song *songs;
    int numSongs;
public:
    Festival(const string &name="", const string &city="", const string &date="", Song *songs= nullptr,int numSongs=0){
        this -> name = name;
        this -> city = city;
        this -> date = date;
        this -> numSongs = numSongs;
        if (songs!= nullptr) {
            this->songs = new Song[numSongs];
            for (int i = 0; i < numSongs; ++i) {
                this->songs[i] = songs[i];
            }
        }
    }
    Festival(const Festival &other){
        this -> name = other.name;
        this -> city = other.city;
        this -> date = other.date;
        this -> numSongs = other.numSongs;
        if (songs!= nullptr) {
            this->songs = new Song[other.numSongs];
            for (int i = 0; i < numSongs; ++i) {
                this->songs[i] = other.songs[i];
            }
        }
    }

    Festival &operator=(const Festival &other){
        if (this != &other){
            this -> name = other.name;
            this -> city = other.city;
            this -> date = other.date;
            this -> numSongs = other.numSongs;
            if (songs!= nullptr) {
                delete [] songs;
                this->songs = new Song[other.numSongs];
                for (int i = 0; i < numSongs; ++i) {
                    this->songs[i] = other.songs[i];
                }
            }
        }
        return *this;
    }

    Festival &operator-=(Song &s){
        if (numSongs == 0){
            EmptyFestival e("Trying to delete from an empty list!");
            e.print();
            return *this;
        }
        for (int i = 0; i < numSongs; ++i) {
            if (songs[i] == s){
                for (int j = i; j < numSongs-1; ++j) {
                    songs[j] = songs[j+1];
                }
                --numSongs;
                --i;
            }
        }
        return *this;
    }

    void print(ofstream &out) const{
        out << "Festival: " << name << " - " << city << ", " << date << endl;
        for (int i = 0; i < numSongs; ++i) {
            songs[i].print(out);
        }
    }

    friend istream &operator>> (istream &is, Festival &f){
        getline(is,f.name);
        getline(is,f.city);
        getline(is,f.date);
        is >> f.numSongs;
        is.ignore();
        f.songs = new Song[f.numSongs];
        for (int i = 0; i < f.numSongs; ++i) {
            is >> f.songs[i];
        }
        return is;
    }

    Festival notFromAuthor(string author){
        Song *temp = new Song [numSongs];
        int count = 0;
        for (int i = 0; i < numSongs; ++i) {
            if (songs[i].getAvtor() != author){
                temp[count++] = songs[i];
            }
        }
        Festival _festival(this->name, this->city, this->date, temp, count);

        if (count == 0) {
            Song dummy;
            _festival -= dummy;
        }

        return _festival;

    }

    ~Festival(){
        delete [] songs;
    }

};


int main() {

    wtf();

    Festival festival;
    //TODO your code here
    //TODO Read the data from the file and store them in `festival`
    ifstream fin("vlezna.txt");
    fin >> festival;
    fin.close();

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    string author;
    getline(cin, author);
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files izlezna1.txt and izlezna2.txt after this line
    ofstream fout1("izlezna1.txt");
    festival.print(fout1);
    fout1.close();

    ofstream fout2("izlezna2.txt");
    festival.notFromAuthor(author).print(fout2);
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}
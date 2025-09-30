/*
 * Да се креира класата Zichara во која ќе се чуваат информации за:

место (динамичко алоцирано поле од знаци)
цена на дневна карта (цел број)
Да се креира класа PlaninarskiDom во која се чуваат информации за:

име (статичко поле од најмногу 15 знаци)
цени по сезони (поле од 2 цели броеви кои ја претставуваат цената за спиење за еден ден во планинарскиот дом во двете различни сезони. Секој планинарски дом има две сезони: летна и зимска. Летната сезона почнува на 1ви април и завршува до 1ви сепмтември. На пример цената за престој на 24ти Јули ќе биде сместена во полето со индекс 0 - каде е сместена цената за летната сезона)
класа на планинарскиот дом (еден знак кој може да има вредност од A до F, каде A е најдобра класа)
дали има жичара (bool-тип)
жичарата на планинарскиот дом (покажувач кон објект од класата Zichara)
За дадените класи дефинирајте ги потребните: конструктори, деструктори, set и get методи. Оптоварете го соодветно операторот =. (20 поени)

Да се оптоварат:

операторот -- (префискен) за намалување на класата на планинарскиот дом (во класата PlaninarskiDom). Да се запази дека за планинарскиот дом најмала класа е F. (5 поени)
операторот << за печатење на објект одPlaninarskiDom. (5 поени)
операторот <= за одредување дали планинарскиот дом има класа помала или еднаква со дадениот знак (споредба на планинарски дом со знак). (5 поени)
Формат на печатење на информации за еден планинарски дом:

Pelister klasa:A so zichara //ако има жичара
Korab klasa:B //ако нема жичара
Во класата PlaninarskiDom да се имплементира функција со име presmetajDnevenPrestoj со која се пресметува цената за дневен престој во планинарскиот дом за даден ден и месец во годината. Ако планинарскиот дом има жичара во цената за дневен престој влегува и дневната карта за жичарата. Функцијата враќа void (не враќа ништо). Првиот аргумент на функцијата е денот (1-31), а вториот е месецот (1-12) за кои се пресметува цената. Третиот аргумент е цената за дневен престој која ќе се пресмета во функцијата. Доколку денот или месецот се невалидни да се фрли соодветен исклучок со кој се справуваме во main-функцијата. Да се земе дека секој месец има 31 ден. (15 поени)

Дадена е main-функција во која се користат класите Zichara и PlaninarskiDom. Без таа да се менува креирајте ги опишаните класи.

 Input:
 Pelister 21 31 E
1
Molika 20
3 3

 Output:
Informacii za PlaninarskiDomot:
Pelister klasa:F so Zichara
Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D
Cenata za 3.3 e 51
 */

#include<iostream>
#include<string.h>
using namespace std;

//ова е место за вашиот код

class Zichara {
    char mesto[100];
    int cena_dnevna;
public:
    Zichara(){}
    Zichara(char *mesto, int cena_dnevna){
        strcpy(this -> mesto,mesto);
        this -> cena_dnevna = cena_dnevna;
    }
    Zichara(const Zichara &z){
        strcpy(this -> mesto,z.mesto);
        this -> cena_dnevna = z.cena_dnevna;
    }
    char *getMesto(){
        return mesto;
    }
    int getCena(){
        return cena_dnevna;
    }
    ~Zichara(){}
};

class PlaninarskiDom{
    char ime[15];
    int ceni_sezona[2];
    char klasa;
    bool ImaZicara;
    Zichara *zicara;
public:
    PlaninarskiDom(){}
    PlaninarskiDom(char *ime, int ceni_sezona[],char klasa, bool ImaZicara, Zichara *zicara){
        strcpy(this -> ime, ime);
        for (int i = 0; i < 2; ++i) {
            this -> ceni_sezona[i] = ceni_sezona[i];
        }
        this -> klasa = klasa;
        this -> ImaZicara = ImaZicara;
        this -> zicara = zicara;
    }
    PlaninarskiDom(const PlaninarskiDom &p){
        strcpy(this -> ime, p.ime);
        for (int i = 0; i < 2; ++i) {
            this -> ceni_sezona[i] = p.ceni_sezona[i];
        }
        this -> klasa = p.klasa;
        this -> ImaZicara = p.ImaZicara;
        this -> zicara = p.zicara;
    }
    PlaninarskiDom(char *ime, int *ceni_sezona, char klasa){
        strcpy(this -> ime, ime);
        for (int i = 0; i < 2; ++i) {
            this -> ceni_sezona[i] = ceni_sezona[i];
        }
        this -> klasa = klasa;
    }

    void setZichara(Zichara &z){
        this -> zicara = &z;
    }

    PlaninarskiDom &operator--(){
        if (klasa < 'F'){
            ++klasa;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, PlaninarskiDom &p){
        os << p.ime << " klasa:" << p.klasa << " ";
        if (p.ImaZicara){
            os << "so Zichara" << endl;
        }
        else {
            os << endl;
        }
        return os;
    }

    bool operator<= (char c) const{
        return this->klasa > c;
    }

    void presmetajDnevenPrestoj(int den,int mesec, int &cena_dneven){
        if (mesec < 1 || mesec > 12 || den < 1 || den > 31){
            throw -1;
        }
        if ( (mesec >= 4 && mesec < 9) || (den==1 && mesec == 9)){
            cena_dneven = ceni_sezona[0];
        }
        else {
            cena_dneven = ceni_sezona[1];
        }
        if (!ImaZicara && zicara != nullptr){
            cena_dneven += zicara->getCena();
        }
    }


};




int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}

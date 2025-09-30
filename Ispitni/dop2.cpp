/*
 Да се дефинира апстрактна класа Doctor, во која се чуваат информации за:
- името на докторот (стринг)
- презимето на докторот (стринг)
- плата (децимален број)
- код (стринг)
Во рамките на оваа класа да се дефинираат два чисто виртуелни методи:
-float calculateSalary() - за пресметка на платата на еден доктор.
-void print() - за печатење на информациите за еден доктор. (5 поени)

Кодот на секој доктор е стринг со должина 8, кој мора да ја има таа должина и не смее да содржи запирка. Доколку кодот на еден доктор не ги исполнува овие услови да се фрли исклучок од класата InvalidCodeFormatException. Со исклучокот треба да се справите во главната програма, при секој обид за креирање објект. При справувањето со исклучокот да се испечати соодветна порака. (15 поени)

Од класата Doctor да се изведат две класи: GeneralDoctor и Specialist, кои претставуваат матичен доктор и специјалист, соодветно. За секој матичен доктор, дополнително се чува бројот на пациенти (цел број), а за секој специјалист дополнително се чува неговата специјалност (стринг), бројот на неговите интервенции (цел број) и години искуство (цел број). (5 поени)

Во изведените класи соодветно да се препокријат виртуелните методи. Форматот за печатење да се види од тест-примерите, а пресметката на плата се прави на следниот начин:
- За GeneralDoctor - основна плата е 45000 денари. Дополнително, за секои 10 пациенти докторот добива по 3000 денари. Да се врати платата со пресметан персонален данок од 7%.
- За Specialist - основна плата е 55000 денари. За секоја интервенција, специјалистите добиваат по 85 денари плус на основната плата. Дополнително, за секоја година работно искуство, специјалистите добиваат по 5% бонус од основната плата. Да се врати платата со пресметан персонален данок од 7%. (10 поени)

Да се дефинира глобална функција со потпис: void findDoctorsPercentage(Doctor **doctors, int n), која како аргументи прима низа од покажувачи кон доктори и нејзината големина. Функцијата треба да го испечати процентот на специјалисти и процентот на матични доктори. Форматот да се види од тест примерите. (15 поени)

 Input:
 6
7
1 John Smith 236XY@2B 120
2 Alice Johnson ABCD123@ Pediatrician 35 8
1 Michael Brown 345X!Y2B 150
2 Sarah Davis 785#Qy2B Cardiologist 42 6
1 Emily Wilson 96Tr$$33 200
2 William Parker 7896YZ$s Neurologist 38 10
1 Jessica Lee 1234ABCD 130

 Output:
 INTEGRATION TEST AND TESTING GLOBAL FUNCTION!
LIST OF ALL DOCTORS:
General Doctor: John Smith CODE:236XY@2B Salary: 75330
Specialist: Alice Johnson CODE:ABCD123@ Pediatrician Salary: 74376.8
General Doctor: Michael Brown CODE:345X!Y2B Salary: 83700
Specialist: Sarah Davis CODE:785#Qy2B Cardiologist Salary: 69815.1
General Doctor: Emily Wilson CODE:96Tr$$33 Salary: 97650
Specialist: William Parker CODE:7896YZ$s Neurologist Salary: 79728.9
General Doctor: Jessica Lee CODE:1234ABCD Salary: 78120
42.8571% of the doctors are specialists and 57.1429% are general doctors.
 */

#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class Doctor{
protected:
    string name;
    string surname;
    string code;
    float salary;
public:
    Doctor(const string &name="", const string &surname="", const string &code="", float salary=0){
        this -> name = name;
        this -> surname = surname;
        this -> code = code;
        this -> salary = salary;
    }
    Doctor(const Doctor &other){
        this -> name = other.name;
        this -> surname = other.surname;
        this -> code = other.code;
        this -> salary = other.salary;
    }
    Doctor &operator=(const Doctor &other){
        if (this != &other){
            this -> name = other.name;
            this -> surname = other.surname;
            this -> code = other.code;
            this -> salary = other.salary;
        }
        return *this;
    }

    virtual float calculateSalary()=0;
    virtual void print() = 0;

    bool validCode(){
        if (code.length() != 8){
            return false;
        }
        for (int i = 0; i <code.length() ; ++i) {
            if (code[i] == ','){
                return false;
            }
        }
        return true;
    }




    virtual ~Doctor() = default;
};

class InvalidCodeFormatException{
    string code;
public:
    InvalidCodeFormatException(const string &code=""){
        this -> code = code;
    }
    void message(){
        cout << "The code " << code << " is invalid doctor code format. THE CODE MUST BE 8 CHARACTERS LONG AND CANNOT CONTAIN COMMA." << endl;
    }
};

class GeneralDoctor: public Doctor{
    int numPatients;
    bool valid = true;
public:

    GeneralDoctor(const string &name="", const string &surname="", const string &code="", int numPatients=0)
            : Doctor(name,surname,code) {
        if (!validCode()) {
            InvalidCodeFormatException(code).message();
            valid = false;
        }
        this->salary = 45000;
        this->numPatients = numPatients;
    }
    GeneralDoctor(const GeneralDoctor &other) : Doctor(other){
        this -> numPatients = other.numPatients;
    }
    GeneralDoctor &operator=(const GeneralDoctor &other){
        if (this != &other){
            this -> name = other.name;
            this -> surname = other.surname;
            this -> code = other.code;
            this -> salary = other.salary;
            this -> numPatients = other.numPatients;
        }
        return *this;
    }

    float calculateSalary() override {
        float base = 45000;
        base += (numPatients/10)*3000;
        base *= 0.93;
        return base;
    }

    void print() override{
        if (!valid)return;
        cout << "General Doctor: " << name << " " << surname << " CODE:" << code << " Salary: " << calculateSalary() << endl;
    }

    ~GeneralDoctor(){}
};

class Specialist: public Doctor{
    string speciality;
    int numInterventions;
    int yearsExperience;
    bool valid=true;
public:

    Specialist(const string &name="", const string &surname="", const string &code="", const string &speciality="",int numInterventions=0, int yearsExperience=0 )
            : Doctor(name,surname,code) {
        if (!validCode()) {
            InvalidCodeFormatException(code).message();
            valid = false;
        }
        this->speciality = speciality;
        this->numInterventions = numInterventions;
        this->yearsExperience = yearsExperience;
        this->salary = 55000;
    }

    Specialist(const Specialist &other) : Doctor(other){
        this -> speciality = other.speciality;
        this -> numInterventions = other.numInterventions;
        this -> yearsExperience = other.yearsExperience;
    }
    Specialist &operator=(const Specialist &other){
        if (this != &other){
            this -> name = other.name;
            this -> surname = other.surname;
            this -> code = other.code;
            this -> salary = other.salary;
            this -> speciality = other.speciality;
            this -> numInterventions = other.numInterventions;
            this -> yearsExperience = other.yearsExperience;
        }
        return *this;
    }
    float calculateSalary() override{
        float base = 55000;
        base = base+ base*((1.0*yearsExperience * 5.0)/100);
        base += (numInterventions * 85);
        base *= 0.93;
        return base;
    }
    void print() override{
        if (!valid)return;
        cout << "Specialist: " << name << " " << surname << " CODE:" << code << " " << speciality << " Salary: " << calculateSalary() << endl;
    }
};

void findDoctorsPercentage(Doctor **doctors, int n){
    float generalCount = 0;
    float specCount = 0;
    float temp = n;
    for (int i = 0; i < n; ++i) {
        if (doctors[i]->validCode() == false){
            --temp;
            continue;
        }else if (dynamic_cast <GeneralDoctor *>(doctors[i])){
            generalCount++;
        } else {
            specCount++;
        }
    }
    cout << (specCount/temp)*100 << "% of the doctors are specialists and " << (generalCount/temp)*100 << "% are general doctors." << endl;
}

int main()
{
    int testCase, n;
    string name, surname, specialty, code;
    int numberOfPatients, yearsOfExperience, numberOfInterventions;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "TESTING GENERAL DOCTOR CLASS" << endl;
        Doctor *d = new GeneralDoctor("John", "Smith", "236XY@2B", 120);
        Doctor *d1 = new GeneralDoctor("Marco", "Brown", "345X!Y2B", 120);
        Doctor *d2 = new GeneralDoctor("Emily", "Johnson", "ABCD123@", 230);
        d->print();
        d1->print();
        d2->print();

        cout << "GENERAL DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 2)
    {
        cout << "TESTING SPECIALIST DOCTOR CLASS" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "96Tr$$33", "Cardiologist", 45, 5);
        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        Doctor *d2 = new Specialist("Micheal", "Rosen", "7896YZ$s", "Radiologist", 41, 10);
        d->print();
        d1->print();
        d2->print();
        cout << "SPECIALIST DOCTOR CLASS OK!" << endl;
    }
    else if (testCase == 3)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        Doctor *d = new GeneralDoctor("John", "Smith", "23Y@2B", 120);
        d->print();

        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 4)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
        d->print();
        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else if (testCase == 5)
    {
        cout << "TESTING EXCEPTION HANDLING" << endl;
        Doctor *d = new Specialist("Beth", "Davis", "9,R$$334", "Cardiologist", 45, 5);
        d->print();

        Doctor *d1 = new Specialist("William", "Wilson", "785#Qy2B", "Pulmonologist", 50, 7);
        d1->print();

        Doctor *d2 = new Specialist("Beth", "Davis", "96Tr,", "Cardiologist", 45, 5);
        d2->print();

        cout << "EXCEPTION HANDLING OK!" << endl;
    }
    else
    {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION!" << endl;
        cin >> n;
        Doctor **doctors = new Doctor *[n];
        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            cin >> name >> surname;
            cin >> code;
            if (t == 1) // General doctor
            {
                cin >> numberOfPatients;

                doctors[i] = new GeneralDoctor(name, surname, code, numberOfPatients);

            }
            else // Specialist
            {
                cin >> specialty;
                cin >> numberOfInterventions >> yearsOfExperience;

                doctors[i] = new Specialist(name, surname, code, specialty, numberOfInterventions, yearsOfExperience);

            }
        }
        cout << "LIST OF ALL DOCTORS: " << endl;
        for (int i = 0; i < n; i++)
        {
            doctors[i]->print();
        }
        findDoctorsPercentage(doctors, n);
        for (int i = 0; i < n; i++)
        {
            delete doctors[i];
        }
        delete[] doctors;
    }
    return 0;
}

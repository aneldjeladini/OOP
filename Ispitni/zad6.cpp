/*
 * Потребно е да се имплементира класа за компјутерска игра (Game), што содржи информации за:

име на играта (низа од макс. 100 знаци)
цена на играта (децимален број)
дали е играта купена на распродажба (bool променлива).
Од класата Game да се изведе класа SubscriptionGame, што дополнително ќе чува:

месечен надоместок за играње (децимален број).
датум кога играта е купена (месец и година како позитивни цели броеви)
За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>). Да се дефинира и операторот == кој ќе споредува игри според нивното име.

Да се дефинира класа за корисник (User) во која се чуваат:

кориснично име на корисникот (низа од макс. 100 знаци)
колекција од игри кои се купени од корисникот (динамички алоцирана низа).
Да се преоптовари операторот += кој ќе овозможи додавање на нова игра во колекцијата на игри. Притоа ако корисникот ја има веќе купено играта, потребно е да се креира исклучок од типот ExistingGame. Класата за имплементација на исклучоци потребно е има соодветен конструктор и метода message за печатење на порака на екран.

Да се креира и метода total_spent() во класата User која ќе пресметува колку пари корисникот потрошил за својата колекција од игри. Доколку играта е купена на распродажба, цената на играта е 30% од стандарната цена. Доколку играта е од типот SubscriptionGame, потребно е да се вкалкулира и сумата потрошена за месечниот надоместок (број_на_изминати_месеци x цена_на_месечен_надоместок) без да се земе во предвид моменталниот месец (мај 2018).

Да се преоптовари и оператоторот за печатење на корисникот, која печати информации во сл. формат (види тест примери 7 до 12):

User: username
- Game: PUBG, regular price: $70, bought on sale
- Game: Half Life 2, regular price: $70 - Game: Warcraft 4, regular price: $40, monthly fee: $10, purchased: 1-2017

Листа на дел од методите со нивни прототипови кои се користат во main:

ЕxistingGame::message()
Game::operator==(Game&)
User::operator+=(Game&)
User::get_game(int)
User::total_spent(int)
User::get_name()
User::get_games_number()

 Input:
 4
World of Warcraft
40
0
10
1
2017

 Output:
 Testing operator>> for SubscriptionGame
Game: World of Warcraft, regular price: $40, monthly fee: $10, purchased: 1-2017
 */

#include<iostream>
#include<cstring>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

class ExistingGame{
public:
    static void message(){
        cout << "The game is already in the collection" << endl;
    }
};

class Game {
protected:
    char name[101];
    double price;
    bool forSale;
public:
    Game(const char *name="", double price=0.0, bool forSale=true){
        strcpy(this -> name, name);
        this -> price = price;
        this -> forSale = forSale;
    }
    Game(const Game &g){
        strcpy(this -> name, g.name);
        this -> price = g.price;
        this -> forSale = g.forSale;
    }

    void setName(char *name){
        strcpy(this -> name, name);
    }
    void setPrice(double price){
        this -> price = price;
    }
    void setForSale(bool forSale){
        this -> forSale = forSale;
    }

    char *getName(){
        return name;
    }

    double getPrice(){
        return price;
    }

    bool getForSale(){
        return forSale;
    }

    virtual int getType(){
        return 0;
    }


    friend ostream &operator<< (ostream &os, Game &g) {
        os << "Game: " << g.name << ", " << "regular price: $" << g.price;
        if (g.forSale){
            os << ", bought on sale";
        }
        return os;
    }

    friend istream &operator>> (istream &is, Game&g){
        cin.ignore();
        cin.getline(g.name,101);
        is >> g.price;
        is >> g.forSale;
        cin.ignore();
        return is;
    }

    bool operator==(Game &other){
        return !strcmp(this -> name,other.name);
    }




    ~Game(){}

};


class SubscriptionGame : public Game {
    double monthlySubscription;
    unsigned int month , year;
public:
    SubscriptionGame(const char *name="", double price=0.0, bool forSale=true,double monthlySubscription = 0, unsigned int month = 1, unsigned int year = 2025)
            : Game(name,price,forSale){
        this -> monthlySubscription = monthlySubscription;
        this -> month = month;
        this -> year = year;
    }
    SubscriptionGame(const SubscriptionGame &other) : Game(other) {
        this -> monthlySubscription = other.monthlySubscription;
        this -> month = other.month;
        this -> year = other.year;
    }

    double getMonthlySubscription(){
        return monthlySubscription;
    }

    unsigned int getMonth(){
        return month;
    }

    unsigned int getYear(){
        return year;
    }

    friend ostream &operator<< (ostream  &os, SubscriptionGame &sg){
        os << "Game: " << sg.name << ", " << "regular price: $" << sg.price;
        if (sg.forSale){
            os << ", bought on sale";
        }
        os << ", monthly fee: $" << sg.monthlySubscription << ", purchased: " << sg.month << "-" << sg.year << endl;
        return os;
    }

    friend istream &operator>> (istream &is, SubscriptionGame &sg){
        cin.ignore();
        cin.getline(sg.name,101);
        is >> sg.price;
        is >> sg.forSale;
        is >> sg.monthlySubscription;
        is >> sg.month ;
        is >> sg.year;
        return is;
    }
    int getType() override{
        return 1;
    }

    ~SubscriptionGame(){}
};


class User{
    char username[101];
    Game *games;
    int numGames;
public:
    User( const char *username = "", Game *games = nullptr, int numGames = 0){
        strcpy(this -> username, username);
        this -> numGames = numGames;
        this -> games = new Game [numGames];
        for (int i = 0; i < numGames; ++i) {
            this -> games[i] = games[i];
        }
    }

    User(const User &other){
        strcpy(this -> username, other.username);
        this -> numGames = other.numGames;
        this -> games = new Game [other.numGames];
        for (int i = 0; i < other.numGames; ++i) {
            this -> games[i] = other.games[i];
        }
    }

    User &operator+=(Game &game){
        for (int i = 0; i < numGames; ++i) {
            if (games[i] == game){
                ExistingGame ::message();
                return *this;
            }
        }
        Game *temp = new Game [numGames+1];
        for (int i = 0; i < numGames; ++i) {
            temp[i] = games[i];
        }
        temp[numGames] = game;
        delete [] games;
        games = temp;
        numGames++;
        return *this;
    }

    double total_spent(){
        double total = 0;
        for (int i = 0; i < numGames; ++i) {
            if (games[i].getForSale()){
                total += games[i].getPrice() * (1 - 0.30);
            }
            else {
                total += games[i].getPrice();
            }

            if (games[i].getType() == 1){
                SubscriptionGame *sub = dynamic_cast<SubscriptionGame*> (&games[i]);
                if (sub){
                    int currentMonth = 5;
                    int currentYear = 2015;
                    int monthsPassed = (currentYear - sub->getYear()) * 12 + (currentMonth - sub ->getMonth());
                    total += sub->getMonthlySubscription()*monthsPassed;
                }
            }
        }
        return total;
    }

    friend ostream &operator<< (ostream &os, User &u){
        os << "User: " << u.username << endl;
        for (int i = 0; i < u.numGames; ++i) {
            if (u.games[i].getType() == 1) {
                SubscriptionGame *sg = dynamic_cast< SubscriptionGame *>(&u.games[i]);
                if (sg){
                    os << "- " << *sg << endl;
                }
                else {
                    os << "- " << u.games[i] << endl;
                }
            }
        }
        return os;
    }


    ~User(){
        delete [] games;
    }
};



int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}

#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int, int, int);
    vector<int> getStat();
};

class Unit{
    string name;
    string type;        
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on; 
    Equipment *equipment; 
public:            
    Unit(string,string); 
    void showStatus();
    void newTurn();
    int attack(Unit &);
    int ultimateAttack(Unit &); 
    int beAttacked(int);
    int heal();    
    void guard();
    void dodge();  
    bool isDead();
    void equip(Equipment *);  
};

// สร้าง Constructor ของ Equipment
Equipment::Equipment(int h, int a, int d){
    hpmax = h;
    atk = a;
    def = d;
}

// ฟังก์ชัน getStat() ของ Equipment
vector<int> Equipment::getStat(){
    return {hpmax, atk, def};
}

// ฟังก์ชัน equip() ของ Unit
void Unit::equip(Equipment *newEquip){
    if(equipment != nullptr){
        vector<int> oldStats = equipment->getStat();
        hpmax -= oldStats[0];
        atk -= oldStats[1];
        def -= oldStats[2];
    }

    vector<int> newStats = newEquip->getStat();
    hpmax += newStats[0];
    atk += newStats[1];
    def += newStats[2];

    equipment = newEquip;

    if(hp > hpmax){
        hp = hpmax;
    }
}

// ✅ เพิ่มฟังก์ชัน Constructor ของ Unit
Unit::Unit(string t, string n){
    type = t;
    name = n;
    if(type == "Hero"){
        hpmax = rand()%20 + 120;
        atk = rand()%5 + 14;
        def = rand()%3 + 9;
    } else if(type == "Monster"){
        hpmax = rand()%20 + 250;
        atk = rand()%5 + 25;
        def = rand()%3 + 5;
    }
    hp = hpmax;
    guard_on = false;
    dodge_on = false;
    equipment = nullptr;
}

// ✅ เพิ่มฟังก์ชัน showStatus()
void Unit::showStatus(){
    if(type == "Hero"){
        cout << "---------------------------------------\n"; 
        cout << name << "\n"; 
        cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;        
        cout << "\n---------------------------------------\n";
    } else if(type == "Monster"){
        cout << "\t\t\t\t---------------------------------------\n"; 
        cout << "\t\t\t\t" << name << "\n"; 
        cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
        cout << "\n\t\t\t\t---------------------------------------\n";
    }
}

// ส่วนอื่น ๆ คงเดิม
void Unit::newTurn(){
    guard_on = false; 
    dodge_on = false; 
}

int Unit::beAttacked(int oppatk){
    int dmg;
    if(dodge_on){
        if(rand() % 2 == 0){ 
            return 0;
        } else { 
            dmg = (oppatk > def) ? (oppatk - def) * 2 : 0;
        }
    } else {
        dmg = (oppatk > def) ? oppatk - def : 0;
        if(guard_on) dmg = dmg / 3;
    }    
    hp -= dmg;
    if(hp <= 0) hp = 0;
    return dmg;
}

int Unit::attack(Unit &opp){
    return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &opp){
    return opp.beAttacked(atk * 2);
}

int Unit::heal(){
    int h = rand()%21 + 10;
    if(hp + h > hpmax) h = hpmax - hp;
    hp = hp + h;
    return h;
}

void Unit::guard(){
    guard_on = true;
}    

void Unit::dodge(){
    dodge_on = true;
}

bool Unit::isDead(){
    return hp <= 0;
}

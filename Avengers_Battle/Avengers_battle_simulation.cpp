// This Project includes 
// Function Overloading
// Operator Overloading

#include<bits/stdc++.h>
using namespace std;

class QNS{
    private:
    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;

    public:
    QNS(int P, int D, int E, int H){
        powerLevel=min(P,5000);
        durability=D;
        energyStorage=E;
        heatLevel=max(H,0);
    }

    // copy suit
    QNS(const QNS& qns){  
        powerLevel=qns.powerLevel;
        durability=qns.durability;
        energyStorage=qns.energyStorage;
        heatLevel=qns.heatLevel;
    }

    // default suit 
    QNS(){
        powerLevel=1000;
        durability=500;
        energyStorage=300;
        heatLevel=0;
    }

    QNS& operator + (QNS& Q){
        powerLevel+=Q.getEnergyStorage();
        powerLevel=min(5000,powerLevel);
        durability+=Q.getDurability();
        energyStorage+=Q.getPowerLevel();
        return *this;
    }

    QNS& operator - (int X){
        durability-=X;
        if(durability<=0){
            // suit destroyed
        }
        energyStorage+=X;
        heatLevel+=X;
        return *this;
    }

    QNS& operator * (int X){
        powerLevel+=(powerLevel*X)/100;
        powerLevel=min(5000,powerLevel);
        energyStorage+=5*X;
        heatLevel+=X;
        if(heatLevel>500){
            //suit overheats
        }
        return *this;
    }

    QNS& operator / (int X){
        // if(X>heatLevel)X=heatLevel;
        durability+=X;
        heatLevel-=X;
        heatLevel=max(0,heatLevel);
        return *this;
    }

    void boostPower(int factor){
        (*this) * factor;
    }

    void boostPower(QNS otherSuit){
        *this + otherSuit;
    }

    bool operator == (QNS& Q){
        if(powerLevel+durability==Q.getPowerLevel()+Q.getDurability()){
            return true;
        }
        else return false;
    }

    bool operator < (QNS& Q){
        if(powerLevel+durability<Q.getPowerLevel()+Q.getDurability()) return true;
        else return false;
    }

    //getters
    int getPowerLevel(){
        return powerLevel;
    }
    int getDurability(){
        return durability;
    }
    int getEnergyStorage(){
        return energyStorage;
    }
    int getHeatLevel(){
        return heatLevel;
    }

};

class Avenger{
    private:
    string name;
    QNS suit;
    int attackStrength;

    public:
    Avenger(){}
    // constructor
    Avenger(string avName, QNS avSuit, int strength){
        name=avName;
        suit=avSuit;
        attackStrength=strength;
    }

    void attack(Avenger& enemy){
        enemy.getSuit() - attackStrength; 
    }

    void upgradeSuit(queue<QNS> &suits){
        suit + suits.front();
        suits.pop();
    }

    void repair(int x){
        suit / x;
    }

    void printStatus(){
        cout<<name<<" "<<suit.getPowerLevel()<<" "<<suit.getDurability()<<" "<<suit.getEnergyStorage()<<" "<<suit.getHeatLevel()<<endl;;
    }

    QNS& getSuit(){
        return suit;
    }

    string getName(){
        return name;
    }

    int getStrength(){
        return attackStrength;
    }

    string checkSuit(){
        string update;
        if(suit.getHeatLevel()>500){
            update=name+" suit overheated";
        }
        if(suit.getDurability()<=0){
            update=name+" suit destroyed";
        }
        // else update="";
        return update;
    }
};

class Battle{
    private:
    vector<Avenger> heroes;
    vector<Avenger> enemies;
    vector<string> battleLog;

    public:
    void startBattle(){
        int k,n,m;
        cin>>k>>n>>m;
        queue<QNS> suits;
        for(int i=0;i<k;i++){
            int p,d,e,h;
            cin>>p>>d>>e>>h;
            suits.push(QNS(p,d,e,h));
        }
        for(int i = 0; i < n; i++){  
            string name;
            cin>>name;
            int strength;
            cin>>strength;
            if(suits.size()<=0){
                cout<<name<<" is out of fight";
            }
            else{
                heroes.push_back(Avenger(name,suits.front(),strength));
                suits.pop();
            }
        }
        for(int i = 0; i < m; i++){  
            string name;
            cin>>name;
            int strength;
            cin>>strength;
            if(suits.size()<=0){
                cout<<name<<" is out of fight"<<endl;;
            }
            else{
                enemies.push_back(Avenger(name,suits.front(),strength));
                suits.pop();
            }
        }
        string command;
        cin>>command;
        while(command == "BattleBegin"){
            string choice;
            cin>>choice;
            if(choice=="End"){
                break;
            }
            if(choice=="Attack"){
                string name1, name2;
                cin>>name1>>name2;
                Avenger* avenger1 = nullptr;
                Avenger* avenger2 = nullptr;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==name1){
                        avenger1= &heroes[i];
                    }
                    if(heroes[i].getName()==name2){
                        avenger2= &heroes[i];
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==name1){
                        avenger1=&enemies[i];
                    }
                    if(enemies[i].getName()==name2){
                        avenger2=&enemies[i];
                    }
                }
                avenger2->getSuit()-avenger1->getStrength();
                string update=avenger1->getName()+" attacks "+avenger2->getName();
                battleLog.push_back(update);
                if(avenger2->checkSuit()!="")
                battleLog.push_back(avenger2->checkSuit());
            }
            if(choice=="Repair"){
                string name;
                cin>>name;
                int value;
                cin>>value;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==name){
                        heroes[i].repair(value);
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==name){
                        enemies[i].repair(value);
                    }
                }
                string update=name+" repaired";
                battleLog.push_back(update);
            }
            if(choice=="BoostPowerByFactor"){
                string name;
                cin>>name;
                int value;
                cin>>value;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==name){
                        heroes[i].getSuit().boostPower(value);
                        string update=name+" boosted";
                        battleLog.push_back(update);
                        if(heroes[i].checkSuit()!="")
                        battleLog.push_back(heroes[i].checkSuit());
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==name){
                        enemies[i].getSuit().boostPower(value);
                        string update=name+" boosted";
                        battleLog.push_back(update);
                        if(enemies[i].checkSuit()!="")
                        battleLog.push_back(enemies[i].checkSuit());
                    }
                }
            }
            if(choice=="BoostPower"){
                string name;
                cin>>name;
                int p,d,e,h;
                cin>>p>>d>>e>>h;
                QNS suit;
                suit=QNS(p,d,e,h);
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==name){
                        heroes[i].getSuit()+suit;
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==name){
                        enemies[i].getSuit()+suit;
                    }
                }
                string update=name+" boosted";
                battleLog.push_back(update);
            }
            if(choice=="AvengerStatus"){
                string name;
                cin>>name;
                for(int i=0;i<heroes.size();i++){
                    if(heroes[i].getName()==name){
                        heroes[i].printStatus();
                    }
                }
                for(int i=0;i<enemies.size();i++){
                    if(enemies[i].getName()==name){
                        enemies[i].printStatus();
                    }
                }
            }
            if(choice=="Upgrade"){
                string name;
                cin>>name;
                if(suits.size()!=0){
                    for(int i=0;i<heroes.size();i++){
                        if(heroes[i].getName()==name){
                            heroes[i].getSuit()+suits.front();
                            suits.pop();
                        }
                    }
                    for(int i=0;i<enemies.size();i++){
                        if(enemies[i].getName()==name){
                            enemies[i].getSuit()+suits.front();
                            suits.pop();
                        }
                    }
                    string update=name+" upgraded";
                    battleLog.push_back(update);
                }
                else{
                    string update=name+" upgrade Fail";
                    battleLog.push_back(update);
                }
            }
            if(choice=="PrintBattleLog"){
                printBattleLog();
            }
            if(choice=="BattleStatus"){
                Result();
            }
        }
    }
    void printBattleLog(){
        for(int i=0;i<battleLog.size();i++){
            cout<<battleLog[i]<<endl;
        }
    }
    int Result(){
        int herototal=0;
        int enemytotal=0;
        for(int i=0;i<heroes.size();i++){
            if(heroes[i].getSuit().getDurability()>0)
            herototal+=heroes[i].getSuit().getPowerLevel()+heroes[i].getSuit().getDurability();
        }
        for(int i=0;i<enemies.size();i++){
            if(enemies[i].getSuit().getDurability()>0)
            enemytotal+=enemies[i].getSuit().getPowerLevel()+enemies[i].getSuit().getDurability();
        }
        if(herototal>enemytotal){
            cout<<"heroes are winning"<<endl;
            return 1;
        }
        else if(herototal<enemytotal){
            cout<<"enemies are winning"<<endl;
            return -1;
        }
        else{
            cout<<"tie"<<endl;
            return 0;
        } 
    }
};

int main(){
    Battle battle;
    battle.startBattle();
}

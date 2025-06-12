// This Project includes 
// Dynamic programing
// min-vertex covering

#include<bits/stdc++.h>
using namespace std;
#define int long long 

// to track count of sentinels
int senapatis = 0;
int dandanayakas = 0;
int chaturanginis = 0;

// base class
class Sentinel{
    protected:
    int ID;
    string name;
    string rank;

    public:
    Sentinel(){}
    Sentinel(int id, string n, string r){  // constructor
        ID = id;
        name = n;
        rank = r;
    }
    virtual int countHigherRanked()=0;  // pure virtual
    int getID(){
        return ID;
    }
    string getName(){
        return name;
    }
    string getRank(){
        return rank;
    }
};


// derived classes
class Senapati: public Sentinel{
    public:
    Senapati():Sentinel(){}
    Senapati(int id, string n, string r):Sentinel(){  // constructor
        ID = id;
        name = n;
        rank = r;
    }
    int countHigherRanked(){      // sentinels more ranked than Senapati
        return 0;
    }
    int getID(){
        return ID;
    }
    string getName(){
        return name;
    }
    string getRank(){
        return rank;
    }
};

class Dandanayaka: public Sentinel{
    public:
    Dandanayaka():Sentinel(){}
    Dandanayaka(int id, string n, string r):Sentinel(){  // constructor
        ID = id;
        name = n;
        rank = r;
    }
    int countHigherRanked(){     // sentinels more ranked than Dandanayaka
        return senapatis;
    }
    int getID(){
        return ID;
    }
    string getName(){
        return name;
    }
    string getRank(){
        return rank;
    }
};

class Chaturangini: public Sentinel{
    public:
    Chaturangini():Sentinel(){}
    Chaturangini(int id, string n, string r):Sentinel(){  // constructor
        ID = id;
        name = n;
        rank = r;
    }
    int countHigherRanked(){    // sentinels more ranked than Chaturangini
        return senapatis + dandanayakas;
    }
    int getID(){
        return ID;
    }
    string getName(){
        return name;
    }
    string getRank(){
        return rank;
    }
};

class Comparator{        // comparator to compare ranks of sentinels 
    public:
    bool operator()(Sentinel* a , Sentinel* b){
        if((a->getRank() == "SENAPATI" && b->getRank() == "DANDANAYAKA")||(a->getRank() == "DANDANAYAKA" && b->getRank() == "CHATURANGINI")||(a->getRank() == "SENAPATI" && b->getRank() == "CHATURANGINI"))
            return true;
        else if((a->getRank() == "DANDANAYAKA" && b->getRank() == "SENAPATI")||(a->getRank() == "CHATURANGINI" && b->getRank() == "DANDANAYAKA")||(a->getRank() == "CHATURANGINI" && b->getRank() == "SENAPATI"))
            return false;
        else{
            return a->getID() < b->getID();
        }
    }
};

// Tree of kingdom
template<typename T>
class Kingdom{
    private:
    vector<vector<int>> roadsList;  // adjlist of the kingdom graph
    vector<T> sentinels;   // sentinels list
    int n;

    public:
    Kingdom(vector<vector<int>> roads, vector<T> sentis){
        roadsList = roads;
        sentinels = sentis;
        n = sentinels.size();
    }

    void dfs(vector<vector<int>> &roads, vector<int> &visited, int root, int parent, vector<pair<int,int>> &dp){
        visited[root]=1;
        dp[root].first = 0;
        dp[root].second = 1;
        for(int i=0;i<(int)roads[root].size();i++){
            int child = roads[root][i];
            if(visited[child]==0){
                dfs(roads, visited, child, root, dp);
                dp[root].first += dp [child].second;
                dp[root].second += min(dp[child].first, dp[child].second);
            }
        }
    }

    int Active_Sentinels(){   //  count no of active sentinels
        vector<int> visited(n,0);
        int parent = -1;
        vector<pair<int,int>> dp(n);
        dfs(roadsList, visited, 0, parent, dp);
        return min(dp[0].first, dp[0].second);
    }

    vector<int> Sentinel_Ranks(){   // sort sentinals according to there ranks
        vector<T> s=sentinels;
        sort(s.begin(), s.end(), Comparator());
        vector<int> IDs(s.size());
        for(int i=0;i<(int)s.size();i++){
            IDs[i] = s[i]->getID();
        }
        return IDs;
    }

    int Higher_Ranked_Sentinels(int n){    // return no of sentinels ranked above them
        return sentinels[n]->countHigherRanked();
    }

};

int32_t main(){
    int n;  // no of outposts
    cin>>n;
    vector<vector<int>> roadsList(n,vector<int>());
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        roadsList[a].push_back(b);
        roadsList[b].push_back(a);
    }
    vector<Sentinel*> sentinels(n);
    for(int i=0;i<n;i++){
        string name,rank;
        cin>> name>> rank;
        if(rank == "SENAPATI"){
            Sentinel *s = new Senapati(i,name,rank);
            sentinels[i] = s;
            senapatis++;
        }
        else if(rank == "DANDANAYAKA"){
            Sentinel *s = new Dandanayaka(i,name,rank);
            sentinels[i] = s;
            dandanayakas++;
        }
        else{
            Sentinel *s = new Chaturangini(i,name,rank);
            sentinels[i] = s;
            chaturanginis++;
        }
    }
    Kingdom<Sentinel*> Empire(roadsList, sentinels);
    int queries;
    cin>>queries;
    for(int i=0;i<queries;i++){
        int query;
        cin>>query;
        if(query==1){
            cout<<Empire.Active_Sentinels()<<endl;
        }
        else if(query == 2){
            vector<int> sentinelRank = Empire.Sentinel_Ranks();
            for( auto rank: sentinelRank){
                cout<<rank<<" ";
            }
            cout<<endl;
        }
        else{
            int node;
            cin>>node;
            cout<<Empire.Higher_Ranked_Sentinels(node)<<endl;
        }
    }
}
// This Project includes 
// Dynamic programing
// Bit-masking

#include <bits/stdc++.h>
using namespace std;
#define int long long

class Island
{

protected:
    string islandID;
    int x; // x coord of circle formed cause of rotation
    int y; // y coord of circle formed cause of rotation
    long double r; // radius of circle

public:
    Island() {}
    virtual void findReq() = 0; // pure virtual fxn
    virtual void take() = 0;
    string getID()
    {
        return islandID;
    }
    int getX()
    { // get x_coord of center
        return x;
    }
    int getY()
    { // get y_coord of center
        return y;
    }
    long double getRadius()
    { // get radius
        return r;
    }
    friend istream &operator>>(istream &cin, Island *A);
    friend ostream &operator<<(ostream &cout, Island *A);
};

long double find_distance(int x1, int y1, int x2, int y2){ // find distance
    // return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return sqrtl((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

istream &operator>>(istream &cin, Island *A){
    A->take();
    return cin;
}

ostream &operator<<(ostream &cout, Island *A){
    cout << A->getID();
    return cout;
}

class RECTANGLE : public Island
{

public:
    RECTANGLE() {}
    RECTANGLE(string ID, int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, int x4_, int y4_) : Island(){
        islandID = ID;
        // coordinates of island edges
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        x3 = x3_;
        y3 = y3_;
        x4 = x4_;
        y4 = y4_;
    }
    // finding center and redius
    void findReq() override{
        x = (x1 + x2 + x3 + x4) / 4;
        y = (y1 + y2 + y3 + y4) / 4;
        r = find_distance(x, y, x1, y1);
    }

    void take(){
        string id;
        cin >>  id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        islandID = id;
    }

private:
    int x1, y1, x2, y2, x3, y3, x4, y4;
};

class TRIANGLE : public Island
{

public:
    TRIANGLE() {}
    TRIANGLE(string ID, int x1_, int y1_, int x2_, int y2_, int x3_, int y3_) : Island(){
        islandID = ID;
        // coordinates of island edges
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        x3 = x3_;
        y3 = y3_;
    }

    // finding centroid and longest radius
    void findReq() override{
        x = (x1 + x2 + x3) / 3;
        y = (y1 + y2 + y3) / 3;
        vector<int> x_arr = {x1, x2, x3};
        vector<int> y_arr = {y1, y2, y3};
        r = 0;
        for (int i = 0; i < 3; i++){
            r = max(r, find_distance(x, y, x_arr[i], y_arr[i]));
        }
    }

    void take(){
        string id;
        cin>> id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        islandID = id;
    }

private:
    int x1, y1, x2, y2, x3, y3;
};

class CIRCLE : public Island
{

public:
    CIRCLE() {}
    CIRCLE(string ID, int x1_, int y1_, long double r_) : Island(){
        islandID = ID;
        x1 = x1_;
        y1 = y1_;
        rad = r_;
    }

    // finding center and redius
    void findReq() override{
        x = x1;
        y = y1;
        r = rad;
    }

    void take(){
        string id;
        cin >>  id >> x1 >> y1 >> rad;
        islandID = id;
    }

private:
    int x1, y1;
    long double rad;
};

class Create_Map
{

private:
    vector<Island *> Islands;
    vector<vector<int>> map;
    vector<vector<int>> dp;
    vector<vector<int>> parent;
    int n;
    void setDP(){
        for (int mask = 1; mask < (1 << n); mask++){
            for (int u = 0; u < n; u++){
                if (dp[mask][u]){
                    for (int v : map[u]){
                        if (!(mask & (1 << v))){
                            int new_mask = mask | (1 << v);
                            if (!dp[new_mask][v]){
                                dp[new_mask][v] = 1;
                                parent[new_mask][v] = u;
                            }
                        }
                    }
                }
            }
        }
    }

    vector<Island *> backtrack(int endNode, int mask){
        vector<Island *> result;
        while (endNode != -1){
            result.push_back(Islands[endNode]);
            int prevMask = mask ^ (1 << endNode);
            int prntNode = parent[mask][endNode];
            mask = prevMask;
            endNode = prntNode;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    int noOf1s(int mask){
        int count = 0;
        while (mask){
            count = count + (mask & 1);
            mask >>= 1;
        }
        return count;
    }

public:
    bool add_edge(Island *A, Island *B){
        return (A->getRadius() + B->getRadius()) >= find_distance(A->getX(), A->getY(), B->getX(), B->getY());
    }

    Create_Map(vector<Island *> ISLAND){
        Islands = ISLAND;
        n = Islands.size();

        map.resize(n);
        dp.assign(1 << n, vector<int>(n, 0));
        parent.assign(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++){
            Islands[i]->findReq();
        }

        // creating a graph
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                if (add_edge(Islands[i], Islands[j])){
                    map[i].push_back(j);
                    map[j].push_back(i);
                }
            }
        }
    }

    vector<Island *> Track(){ // tracks the longest path
        // since we can rotate island rotating the island gives circle
        // finding the connectivity and checking it has hamiltonian path or not
        // track the path

        for (int i = 0; i < n; i++){
            dp[1 << i][i] = 1;
            parent[1 << i][i] = -1;
        }
        setDP();
        int maxLen = 0, endNode = -1, bestMask = 0;
        for (int i = 1; i < (1 << n); i++){
            for (int u = 0; u < n; u++){
                if (noOf1s(i) > maxLen && dp[i][u]){
                    maxLen = noOf1s(i);
                    bestMask = i;
                    endNode = u;
                }
            }
        }
        vector<Island *> path = backtrack(endNode, bestMask);
        reverse(path.begin(), path.end());

        if (path.size() == n){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
            cout << path.size() << endl;
        }
        return path;
    }
};

int32_t main()
{
    int n;
    cin >> n; // no of islands
    vector<Island *> Islands(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "RECTANGLE")
        {
            RECTANGLE *R = new RECTANGLE();
            cin >> R;
            Island *RI = R;
            Islands[i] = RI;
        }
        else if (s == "TRIANGLE")
        {
            TRIANGLE *T = new TRIANGLE();
            cin >> T;
            Island *TI = T;
            Islands[i] = TI;
        }
        else
        { // s == "CIRCLE"
            CIRCLE *C = new CIRCLE();
            cin >> C;
            Island *CI = C;
            Islands[i] = CI;
        }
    }
    Create_Map path(Islands);
    vector<Island *> ans = path.Track(); // track the path
    for (auto I : ans)
    {
        cout << I << " ";
    }
    cout<<endl;
}



#include <bits/stdc++.h>
using namespace std;
#define int long long

class Island
{

protected:
    string islandID;
    int x; // x coord of circle formed cause of rotation
    int y; // y coord of circle formed cause of rotation
    long double r; // radius of circle

public:
    Island() {}
    virtual void findReq() = 0; // pure virtual fxn
    virtual void take() = 0;
    string getID()
    {
        return islandID;
    }
    int getX()
    { // get x_coord of center
        return x;
    }
    int getY()
    { // get y_coord of center
        return y;
    }
    long double getRadius()
    { // get radius
        return r;
    }
    friend istream &operator>>(istream &cin, Island *A);
    friend ostream &operator<<(ostream &cout, Island *A);
};

long double find_distance(int x1, int y1, int x2, int y2)
{ // find distance
    // return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return sqrtl((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

istream &operator>>(istream &cin, Island *A)
{
    A->take();
    return cin;
}

ostream &operator<<(ostream &cout, Island *A)
{
    cout << A->getID();
    return cout;
}

class RECTANGLE : public Island
{

public:
    RECTANGLE() {}
    RECTANGLE(string ID, int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, int x4_, int y4_) : Island()
    {
        islandID = ID;
        // coordinates of island edges
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        x3 = x3_;
        y3 = y3_;
        x4 = x4_;
        y4 = y4_;
    }
    // finding center and redius
    void findReq() override
    {
        x = (x1 + x2 + x3 + x4) / 4;
        y = (y1 + y2 + y3 + y4) / 4;
        r = find_distance(x, y, x1, y1);
    }

    void take()
    {
        string id;
        cin >>  id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        islandID = id;
    }

private:
    int x1, y1, x2, y2, x3, y3, x4, y4;
};

class TRIANGLE : public Island
{

public:
    TRIANGLE() {}
    TRIANGLE(string ID, int x1_, int y1_, int x2_, int y2_, int x3_, int y3_) : Island()
    {
        islandID = ID;
        // coordinates of island edges
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        x3 = x3_;
        y3 = y3_;
    }

    // finding centroid and longest radius
    void findReq() override
    {
        x = (x1 + x2 + x3) / 3;
        y = (y1 + y2 + y3) / 3;
        vector<int> x_arr = {x1, x2, x3};
        vector<int> y_arr = {y1, y2, y3};
        r = 0;
        for (int i = 0; i < 3; i++)
        {
            r = max(r, find_distance(x, y, x_arr[i], y_arr[i]));
        }
    }

    void take()
    {
        string id;
        cin>> id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        islandID = id;
    }

private:
    int x1, y1, x2, y2, x3, y3;
};

class CIRCLE : public Island
{

public:
    CIRCLE() {}
    CIRCLE(string ID, int x1_, int y1_, long double r_) : Island()
    {
        islandID = ID;
        x1 = x1_;
        y1 = y1_;
        rad = r_;
    }

    // finding center and redius
    void findReq() override
    {
        x = x1;
        y = y1;
        r = rad;
    }

    void take()
    {
        string id;
        cin >>  id >> x1 >> y1 >> rad;
        islandID = id;
    }

private:
    int x1, y1;
    long double rad;
};

class Create_Map
{

private:
    vector<Island *> Islands;
    vector<vector<int>> map;
    vector<vector<int>> dp;
    vector<vector<int>> parent;
    int n;
    void setDP()
    {
        for (int mask = 1; mask < (1 << n); mask++)
        {
            for (int u = 0; u < n; u++)
            {
                if (dp[mask][u])
                {
                    for (int v : map[u])
                    {
                        if (!(mask & (1 << v)))
                        {
                            int new_mask = mask | (1 << v);
                            if (!dp[new_mask][v])
                            {
                                dp[new_mask][v] = 1;
                                parent[new_mask][v] = u;
                            }
                        }
                    }
                }
            }
        }
    }

    vector<Island *> backtrack(int endNode, int mask)
    {
        vector<Island *> result;
        while (endNode != -1)
        {
            result.push_back(Islands[endNode]);
            int prevMask = mask ^ (1 << endNode);
            int prntNode = parent[mask][endNode];
            mask = prevMask;
            endNode = prntNode;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    int noOf1s(int mask)
    {
        int count = 0;
        while (mask)
        {
            count = count + (mask & 1);
            mask >>= 1;
        }
        return count;
    }

public:
    bool add_edge(Island *A, Island *B)
    {
        return (A->getRadius() + B->getRadius()) >= find_distance(A->getX(), A->getY(), B->getX(), B->getY());
    }

    Create_Map(vector<Island *> ISLAND)
    {
        Islands = ISLAND;
        n = Islands.size();

        map.resize(n);
        dp.assign(1 << n, vector<int>(n, 0));
        parent.assign(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
        {
            Islands[i]->findReq();
        }

        // creating a graph
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (add_edge(Islands[i], Islands[j]))
                {
                    map[i].push_back(j);
                    map[j].push_back(i);
                }
            }
        }
    }

    vector<Island *> Track()
    { // tracks the longest path
        // since we can rotate island rotating the island gives circle
        // finding the connectivity and checking it has hamiltonian path or not
        // track the path

        for (int i = 0; i < n; i++)
        {
            dp[1 << i][i] = 1;
            parent[1 << i][i] = -1;
        }
        // cout<<"ij"<<endl;
        setDP();
        int maxLen = 0, endNode = -1, bestMask = 0;
        for (int i = 1; i < (1 << n); i++)
        {
            for (int u = 0; u < n; u++)
            {
                if (noOf1s(i) > maxLen && dp[i][u])
                {
                    maxLen = noOf1s(i);
                    bestMask = i;
                    endNode = u;
                }
            }
        }
        // cout<<"ij"<<endl;
        // cout<<"ij"<<endl;
        vector<Island *> path = backtrack(endNode, bestMask);

        if (path.size() == n)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
            cout << path.size() << endl;
        }
        return path;
    }
};

int32_t main()
{
    int n;
    cin >> n; // no of islands
    vector<Island *> Islands(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "RECTANGLE")
        {
            RECTANGLE *R = new RECTANGLE();
            cin >> R;
            Island *RI = R;
            Islands[i] = RI;
        }
        else if (s == "TRIANGLE")
        {
            TRIANGLE *T = new TRIANGLE();
            cin >> T;
            Island *TI = T;
            Islands[i] = TI;
        }
        else
        { // s == "CIRCLE"
            CIRCLE *C = new CIRCLE();
            cin >> C;
            Island *CI = C;
            Islands[i] = CI;
        }
        // cout<<Islands[i]<<endl;
    }
    Create_Map path(Islands);
    vector<Island *> ans = path.Track(); // track the path
    // cout<<"ij"<<endl;
    for (auto I : ans)
    {
        cout << I << " ";
    }
    cout << endl;
}
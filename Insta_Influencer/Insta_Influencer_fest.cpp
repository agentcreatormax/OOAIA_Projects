// This Project includes
/* * Strongly connected components
   * Toposort in a DAG
   * Cycle existence in a DAG
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

int isCyclic = 0; // useful at topological sort for outputing "no"

// comparator
class Comparator
{
public:
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

void dfsVisit(vector<vector<int>> &adjList, int n, int source, vector<int> &visited, vector<int> &pathVisited)
{
    // dfs through every source
    if (visited[source - 1] == 0){
        visited[source - 1] = 1;
        pathVisited[source - 1] = 1;
        for (int i = 0; i < adjList[source - 1].size(); i++){
            if (visited[adjList[source - 1][i] - 1] == 0){
                dfsVisit(adjList, n, adjList[source - 1][i], visited, pathVisited);
            }
            else{
                if (pathVisited[adjList[source - 1][i] - 1] == 1)
                isCyclic = 1;
            }
        }
        pathVisited[source - 1] = 0;
    }
}
int t = 1;
vector<int> dfs_finish_times(vector<vector<int>> &adjList, int n, int source, vector<int> &visited, vector<int> &finish_times)
{
    if (visited[source - 1] == 0)
    {
        visited[source - 1] = 1;
        for (int i = 0; i < adjList[source - 1].size(); i++)
        {
            if (visited[adjList[source - 1][i] - 1] == 0)
            {
                dfs_finish_times(adjList, n, adjList[source - 1][i], visited, finish_times);
                t++;
                finish_times[source - 1] = t;
            }
        }
    }
    finish_times[source - 1] = t;
    return finish_times;
}

// dfs algo that helps wheather the cycle is present or not
void dfs(vector<vector<int>> &adjList, int n)
{
    vector<int> visited(n, 0);
    vector<int> pathVisited(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {

            dfsVisit(adjList, n, i + 1, visited, pathVisited);
        }
    }
}
int total_length = 0;
// to find max length of cycle(scc)
int max_scc(vector<vector<int>> &adjList, int n, int source, vector<int> &visited, int &l)
{
    // dfs through every source
    total_length = max(total_length, l);
    if (visited[source - 1] == 0){
        visited[source - 1] = 1;
        for (int i = 0; i < adjList[source - 1].size(); i++){
            if (visited[adjList[source - 1][i] - 1] == 0){
                l++;
                max_scc(adjList, n, adjList[source - 1][i], visited, l);
                total_length = max(total_length, l);
            }
        }
    }
    return total_length;
}

int max_scc(vector<vector<int>> &adjList, int n, int source, vector<int> &visited, int &l, int &count, vector<int> &components)
{
    // dfs through every source
    total_length = max(total_length, l);
    components[source - 1] = count - 1;
    
    visited[source - 1] = 1;
    for (int i = 0; i < adjList[source - 1].size(); i++){
        if (visited[adjList[source - 1][i] - 1] == 0){
            l++;
            max_scc(adjList, n, adjList[source - 1][i], visited, l,count, components);
            total_length = max(total_length, l);
        }
    }
    
    return total_length;
}

// khans algo using bfs
vector<int> lexicoToposort(vector<vector<int>> &adjList, int n)
{
    vector<int> toposort;
    vector<int> inDegree(n);
    for (int i = 0; i < n; i++)
    {
        for (int j : adjList[i])
        {
            inDegree[j - 1]++;
        }
    }
    priority_queue<int, vector<int>, greater<int>> pq; // min heap pq
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            pq.push(i + 1);
        }
    }
    while (!pq.empty())
    {
        int u = pq.top();
        toposort.push_back(u);
        pq.pop();
        for (int i = 0; i < adjList[u - 1].size(); i++)
        {
            inDegree[adjList[u - 1][i] - 1]--;
            if (inDegree[adjList[u - 1][i] - 1] == 0)
                pq.push(adjList[u - 1][i]);
        }
    }
    return toposort;
}

class GraphAlgorithm
{
public:
    GraphAlgorithm() {}                                     // default constructor
    GraphAlgorithm(vector<vector<int>> &v) { adjList = v; } // constructor
    virtual void Query() = 0;                               // pure virtual fxn

protected:
    vector<vector<int>> adjList; // to make this accessable to every child we keep is in protected
};

class isCycle : public GraphAlgorithm
{
public:
    isCycle(vector<vector<int>> &v) : GraphAlgorithm(v) {} // default constructor
    void Query()
    {
        int n = adjList.size();
        dfs(adjList, n);
        if (isCyclic == 1)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
};

class indepComponent : public GraphAlgorithm
{
public:
    indepComponent(vector<vector<int>> &v) : GraphAlgorithm(v) {} // constructor
    void Query()
    {
        if (isCyclic == 0)
        {
            cout << adjList.size() << " " << 1 << endl;
            return;
        }
        int n = adjList.size();
        // print number of SCCs and max length of cycle
        // create compliment adjList
        vector<int> finish_times(n, 0);
        vector<int> visited(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                finish_times = dfs_finish_times(adjList, n, i + 1, visited, finish_times);
            }
        }
        vector<vector<int>> compAdjList(n, vector<int>());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                compAdjList[adjList[i][j] - 1].push_back(i + 1);
            }
        }
        // perform DFS on compliment graph starting from high finish time
        vector<pair<int, int>> finishTimes_of_points(n);
        for (int i = 0; i < n; i++)
        {
            finishTimes_of_points.push_back({finish_times[i], i});
        }
        sort(finishTimes_of_points.rbegin(), finishTimes_of_points.rend());

        vector<int> inverse_finish_times(n);
        for (int i = 0; i < n; i++)
        {
            inverse_finish_times[i] = finishTimes_of_points[i].second + 1;
        }
        vector<int> scc_comps(n);
        vector<int> visited_comp(n, 0);
        int length;
        int max_length = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (visited_comp[inverse_finish_times[i] - 1] == 0)
            {
                cnt++;
                int l = 1;
                length = max_scc(compAdjList, n, inverse_finish_times[i], visited_comp, l);
                max_length = max(length, max_length);
            }
        }
        cout << cnt << " " << max_length << endl;
    }
};

class validOrder : public GraphAlgorithm
{
public:
    validOrder(vector<vector<int>> &v) : GraphAlgorithm(v) {} // constructor
    void Query()
    {
        if (isCyclic == 1)
        {
            cout << "NO" << endl;
            return;
        }
        int n = adjList.size();
        vector<int> topoSort = lexicoToposort(adjList, n);

        for (int node : topoSort)
        {
            cout << node << " ";
        }
        cout << endl;
    }
};

class maxHype : public GraphAlgorithm
{
private:
    vector<int> HypeScore;

public:
    maxHype(vector<vector<int>> &v, vector<int> &hypeScore) : GraphAlgorithm(v) { HypeScore = hypeScore; } // constructor
    void Query()
    {
        // max sum of hype in every path in DAG

        int n = adjList.size();
        // print number of SCCs and max length of cycle
        // create compliment adjList
        vector<int> finish_times(n, 0);
        vector<int> visited(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                finish_times = dfs_finish_times(adjList, n, i + 1, visited, finish_times);
            }
        }
        vector<vector<int>> compAdjList(n, vector<int>());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adjList[i].size(); j++)
            {
                compAdjList[adjList[i][j] - 1].push_back(i + 1);
            }
        }
        // perform DFS on compliment graph starting from high finish time
        vector<pair<int, int>> finishTimes_of_points(n);
        for (int i = 0; i < n; i++)
        {
            finishTimes_of_points.push_back({finish_times[i], i});
        }
        sort(finishTimes_of_points.rbegin(), finishTimes_of_points.rend());

        vector<int> inverse_finish_times(n);
        for (int i = 0; i < n; i++)
        {
            inverse_finish_times[i] = finishTimes_of_points[i].second + 1;
        }
        vector<int> visited_comp(n, 0);
        int length;
        int cnt = 0;
        vector<int> components(n);
        for (int i = 0; i < n; i++){
            if (visited_comp[inverse_finish_times[i] - 1] == 0){
                components[inverse_finish_times[i] - 1] = cnt;
                cnt++;
                int l = 1;
                length = max_scc(compAdjList, n, inverse_finish_times[i], visited_comp, l, cnt, components);
            }
        }

        vector<vector<int>> SCC_adjList;
        int m = cnt;
        SCC_adjList.resize(m);
        vector<int> combined_hype(m, 0);
        for (int i = 0; i < n; i++)
        {

            combined_hype[components[i]] += HypeScore[i];
            for (int j = 0; j < adjList[i].size(); j++)
            {
                if (components[i] != components[adjList[i][j] - 1])
                {
                    SCC_adjList[components[i]].push_back(components[adjList[i][j] - 1] + 1);
                }
            }
        }

        for (int i = 0; i < m; i++){
            sort(SCC_adjList[i].begin(), SCC_adjList[i].end());
            SCC_adjList[i].erase(unique(SCC_adjList[i].begin(), SCC_adjList[i].end()), SCC_adjList[i].end());
        }

        vector<int> max_hype(m, 0);
        vector<int> SCC_topoSort = lexicoToposort(SCC_adjList, m);
        for (int i : SCC_topoSort){
            if (max_hype[i-1]== 0){
                max_hype[i-1]=combined_hype[i-1];
            }
            for (int j : SCC_adjList[i-1]){
                max_hype[j-1] = max(max_hype[j-1], combined_hype[j-1] + max_hype[i-1]);
            }
        }
        cout << *max_element(max_hype.begin(), max_hype.end()) << endl;
    }
};

int32_t main()
{
    // input vertices(events), edges(dependencies)
    // input node score(hype)
    // contruct adj list(predecence)
    // no. of queries and queries
    int v, e;
    cin >> v >> e;
    vector<int> hypeScore(v);
    vector<vector<int>> adjList(v, vector<int>());
    for (int i = 0; i < v; i++)
    {
        cin >> hypeScore[i];
    }

    for (int i = 0; i < e; i++)
    {
        int x, y;
        cin >> x >> y;
        adjList[x - 1].push_back(y);
    }
    GraphAlgorithm *G;

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            G = new isCycle(adjList);
        }
        if (choice == 2)
        {
            G = new indepComponent(adjList);
        }
        if (choice == 3)
        {
            G = new validOrder(adjList);
        }
        if (choice == 4)
        {
            G = new maxHype(adjList, hypeScore);
        }
        G->Query();
        delete G;
    }
}
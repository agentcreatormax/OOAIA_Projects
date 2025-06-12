// This Project includes
/* * implementing Priority queue
   * Dijkstras algorithm
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

class Node{
    private:
    string RoomID;
    int value;  // shortest distance from source
    int index;  // to contruct int based graph
    int parity;  // to check even path or odd path

    public:
    Node(){}

    Node(string ID,int i){  // contructor
        RoomID = ID;
        value = INT_MAX;
        index = i;
        parity = 0;

    }

    void changeParity(){    
        if(parity == 0){
            parity = 1;
        }
        else{
            parity = 0;
        }
    }
    
    int getParity(){   // to get parity of node
        return parity;
    }

    int getValue(){   // to get shortest distance from source
        return value;
    }

    void setValue(int d){  // to update the value
        value = d;
    }

    int getIndex(){
        return index; // return index
    }
};

template <typename T>
class min_pq{
    private:
    int cursize;
    vector<T> Nodes;

    void percolateup(int hole){
        while(hole>1&&Nodes[hole/2].getValue()>Nodes[hole].getValue()){
            swap(Nodes[hole],Nodes[hole/2]);
            hole=hole/2;
        }
    }

    void percolatedown(int hole){
        while((2*hole) <= cursize){ 
            int child1 = 2*hole;
            int child2 = 2*hole+1;
            int cmx=child1;
            if(child2 <= cursize && Nodes[child2].getValue() < Nodes[child1].getValue()){
                cmx=child2;
            }
            if(Nodes[cmx].getValue() < Nodes[hole].getValue()){
                swap(Nodes[cmx],Nodes[hole]);
                hole=cmx;
            }
            else{
                break;
            }
        }
        return;
    }

    public:
    min_pq(){  // contructor
        cursize = 0;
        Nodes.resize(1);
    }

    bool isFull(){return cursize+1==Nodes.size();}

    const size_t size(){  // returns size of pq when needed
        return cursize;
    }

    void push(const T& A){  // inserts a node
        if(isFull()){
            Nodes.resize(2*Nodes.size()+1);
        }
        Nodes[cursize+1]=A;
        cursize++;
        percolateup(cursize);
    }

    void pop(){   // remove the top node(least valued node)
        if (empty()) return;
        Nodes[1]=Nodes[cursize];
        // Nodes.pop_back();
        cursize--;
        percolatedown(1);
    }

    const T& top(){  // returns top node
        if(!empty())
        return Nodes[1];
        return T();
    }

    const bool empty(){  // checks wheather the pq is empty or not
        return cursize==0;
    }

};

class Dijkstra{    // to implement Dijkstra algo
    private:
    vector<vector<int>> adjList;    // stores graph as adjacency list
    map<pair<int,int>,int> weights;   // stores weights weight[indices of 2 nodes]=weight of edge btw them
    vector<Node> Nodes;    // stores nodes of the graph
    vector<bool> visited;    // stores visited nodes
    
    public:
    Dijkstra(vector<vector<int>> adjlist, map<pair<int,int>,int> w, vector<Node> rooms){
        adjList = adjlist;
        weights = w;
        Nodes = rooms;
    }

    int Shortest_path(int A, int B){  // implement Dijkstra
        Node source_Node = Nodes[A];
        Node destination_Node = Nodes[B];
        vector<vector<int>> visited(adjList.size(), {0,0});  // visited
        for(int i=0; i <(int) Nodes.size(); i++){  // initialize all nodes as unvisited
            Nodes[i].setValue(INT_MAX);
        }
        min_pq<Node> pq;  // priority queue to store nodes to be visited 
        source_Node.setValue(0);  
        pq.push(source_Node); 
        while(!pq.empty()){
            Node n = pq.top();
            pq.pop();
            if(n.getIndex() == B && n.getParity()==0){
                return n.getValue();
            }
            visited[n.getIndex()][n.getParity()] = 1;
            for(int i=0; i<(int)adjList[n.getIndex()].size(); i++){
                int v = adjList[n.getIndex()][i];
                if(!visited[v][1-n.getParity()]){
                    int w = weights[{n.getIndex(),v}];
                    if(n.getParity()==Nodes[v].getParity()){
                        Nodes[v].changeParity();
                        Nodes[v].setValue(n.getValue()+w);
                        pq.push(Nodes[v]);
                    }   
                    else{
                        Nodes[v].setValue(n.getValue()+w);
                        pq.push(Nodes[v]); 
                    }
                }
            }
        }
        return -1;  // if no path exists
    }
};

int32_t main(){
    int v,e;
    cin>>v>>e;
    vector<Node> Rooms;
    unordered_map<string, int> roomIndex;
    vector<vector<int>> adjList(v,vector<int>());
    map<pair<int,int>,int> weights;
    for(int i=0;i<v;i++){
        string s;
        cin>>s;
        roomIndex[s] = i;
        Rooms.push_back(Node(s,i));
    }
    for(int i=0;i<e;i++){
        string a,b;
        cin>>a>>b;
        int d;
        cin>>d;
        int u = roomIndex[a];
        int v = roomIndex[b];
        weights[{u,v}] = d;
        weights[{v,u}] = d;
        adjList[u].emplace_back(v);
        adjList[v].emplace_back(u);
    }
    string source;
    string destination;
    cin>>source>>destination;
    int startIdx = roomIndex[source];
    int endIdx = roomIndex[destination];
    cout<<Dijkstra(adjList,weights,Rooms).Shortest_path(startIdx, endIdx)<<endl;
}
// This project includes
/* * Polymorphism
   * operator Overloading
*/

#include<bits/stdc++.h>
using namespace std;

class Graph{

    private:
    vector<vector<int>> AdjMatrix;

    public:
    Graph(){ }

    void operator+ (Graph& graph){  //union

        //resizing the matrix to higher vertex
        int maxGridLength= max((int)graph.getAdjMatrix().size(),(int)AdjMatrix.size());
        for(int i=0;i<maxGridLength;i++){
            if(i<(int)graph.getAdjMatrix().size()){
                for(int j=graph.getAdjMatrix().size();j<maxGridLength;j++) graph.getAdjMatrix()[i].push_back(0);
            }
            else {
                vector<int>temp(maxGridLength,0);
                graph.getAdjMatrix().push_back(temp);
            }
        }

        for(int i=0;i<maxGridLength;i++){
            if(i<(int)AdjMatrix.size()){
                for(int j=AdjMatrix.size();j<maxGridLength;j++) AdjMatrix[i].push_back(0);
            }
            else {
                vector<int>temp(maxGridLength,0);
                AdjMatrix.push_back(temp);
            }
        }
        for(int i=0;i<maxGridLength;i++){
            for(int j=0;j<maxGridLength;j++){
                AdjMatrix[i][j]=max(AdjMatrix[i][j],graph.getAdjMatrix()[i][j]);
            }
        }  
    }

    void operator- (Graph& graph){  //intersection

        int maxGridLength= max((int)graph.getAdjMatrix().size(),(int)AdjMatrix.size());
        for(int i=0;i<maxGridLength;i++){
            if(i<(int)graph.getAdjMatrix().size()){
                for(int j=graph.getAdjMatrix().size();j<maxGridLength;j++) graph.getAdjMatrix()[i].push_back(0);
            }
            else {
                vector<int>temp(maxGridLength,0);
                graph.getAdjMatrix().push_back(temp);
            }
        }

        for(int i=0;i<maxGridLength;i++){
            if(i<(int)AdjMatrix.size()){
                for(int j=AdjMatrix.size();j<maxGridLength;j++) AdjMatrix[i].push_back(0);
            }
            else {
                vector<int>temp(maxGridLength,0);
                AdjMatrix.push_back(temp);
            }
        }

        for(int i=0;i<maxGridLength;i++){
            for(int j=0;j<maxGridLength;j++){
                AdjMatrix[i][j]=min(AdjMatrix[i][j],graph.getAdjMatrix()[i][j]);
            }
        }
    }

    void operator! (){    //complement 
        for(int i=0;i<(int)AdjMatrix.size();i++){
            for(int j=0;j<(int)AdjMatrix.size();j++){
                if(i!=j)
                AdjMatrix[i][j]=1-AdjMatrix[i][j];
                else
                AdjMatrix[i][j] = 0;
            }
        }
    }

    vector<vector<int>>& getAdjMatrix(){
        return AdjMatrix;
    }

    void addEdge(int v1,int v2){
        int n= AdjMatrix.size();
        if(v1>=n||v2>=n){
            return;
        }
        AdjMatrix[v1][v2]=1;
        AdjMatrix[v2][v1]=1;
    }

    void removeEdge(int v1,int v2){
        int n= AdjMatrix.size();
        if(v1>=n||v2>=n){
            return;
        }
        AdjMatrix[v1][v2]=0;
        AdjMatrix[v2][v1]=0;
    }

    bool dfs(int root,int target,vector<vector<int>> &dup){
    for(int i=0;i<(int)dup.size();i++){
        if(dup[root][i]==1){
            if(i==target) return true;
            dup[root][i]=0;
            dup[i][root]=0;
            if(dfs(i,target,dup)) return true;
        }
    }
    return false;
}

    
    void isReachable(int root,int target){
        int n= AdjMatrix.size();
        if(root>=n||target>=n){
            return;
        }
        if(root==target) {cout<<"Yes"<<'\n';return;}
        vector<vector<int>> dup=AdjMatrix;
        if(dfs(root,target,dup)){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }

};

istream& operator>> (istream& cin, Graph& graph){   //input
   
        int v,e;
        cin>>v>>e;
        graph.getAdjMatrix().assign(v, vector<int>(v ,0));
        for(int i=0;i<e;i++){
            int a,b;
            cin>>a>>b;
            graph.addEdge(a,b);
        }
    return cin;
}

ostream& operator<<(ostream& cout, Graph& graph){    // output
    for(int i=0;i<(int)graph.getAdjMatrix().size();i++){
        cout<<"Vertex "<<i<<": ";
        for(int j=0;j<(int)graph.getAdjMatrix().size();j++){
            if(graph.getAdjMatrix()[i][j]==1){
                cout<<j<<" ";
            }
        }
        cout<<endl;
    }
    return cout;
}

int main(){
    Graph g;
    while(1){
        string choice;
        cin>>choice;
        if(choice=="end"){
            break;
        }
        if(choice=="Graph"){
            cin >> g;
        }
        if(choice=="printGraph"){
            cout << g;
        }
        if(choice=="isReachable"){
            int v1,v2;
            cin>>v1>>v2;
            g.isReachable(v1,v2);
        }
        if(choice=="complement"){
            !g;
        }
        if(choice=="add_edge"){
            int v1,v2;
            cin>>v1>>v2;
            g.addEdge(v1,v2);
        }
        if(choice=="remove_edge"){
            int v1,v2;
            cin>>v1>>v2;
            g.removeEdge(v1,v2);
        }
        if(choice=="union"){
            string t; cin>>t;
            Graph g1;
            cin >> g1;
            g+g1;
        }
        if(choice=="intersection"){
            string t; cin>>t;
            Graph g1;
            cin >> g1;
            g-g1;
        }
    }

}
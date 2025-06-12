// This Project includes
// Usage of Comparator class
// Divide and Conquer techniques like
/* * Counting Inversions
   * Finding Closest Pair
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
int cnt=0;

class Point{  // to keep track of index
    public:
    int x,y;
    int index;
};

class Comparator{       // managing type of sort (ascending or descending)
    public:
    bool operator()(string s, int a,int b){
        if(s=="ascending"){return a<b;}
        else{return a>b;}
    }
};

class Chess{
    private:
    int  n;
    vector<vector<int>> board;

    public:
    Chess(){}

    void board_size(int k){    // initialising length of board
        n=k;
        board.resize(n, vector<int>(n, 0));
    }

    void set_board(vector<vector<int>> arr){      // entering values 
        board = arr;
    }

    void print(){             // printing board
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    void sort_rows(string type){          // sort rows ascending or descending using comparator
        for(int i=0;i<n;i++){
            merge_sort(board[i],0,n-1,type);
        }
    }

    void merge_sort(vector<int> &v, int l, int r, string type){   // dividing the array to perform mergesort and count inversions
        if(l<r){
            int mid = l+(r-l)/2;
            merge_sort(v,l,mid,type);
            merge_sort(v,mid+1,r,type);
            merge(v,l,mid,r,type);
        }
    }
    
    void merge(vector<int> &arr, int l, int mid, int r, string type){   // to find no 0f inversions
        int n1 = mid-l+1;
        int n2 = r-mid;
        int l_arr[n1], r_arr[n2];

        for (int i=0; i<n1; i++){
            l_arr[i] = arr[l + i];
        }   
        for (int j=0; j<n2; j++){
            r_arr[j] = arr[mid+1+j];
        }

        int i=0, j=0, k=l;
        while(i<n1 && j<n2){
            Comparator comparator;
            if(comparator(type,l_arr[i],r_arr[j])){
                arr[k] = l_arr[i];
                i++;
            }
            else{
                arr[k] = r_arr[j];
                j++;
            }
            k++;
        }
        while(i<n1){
            arr[k] = l_arr[i];
            i++;
            k++;
        }
        while(j<n2){
            arr[k] = r_arr[j];
            j++;
            k++;
        }
    }

    void count_inversions(){             // count inversions through divide and conquer 
        vector<int> elements(n*n);
        int k=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                elements[k]=board[i][j];
                k++;
            }
        }
        merge_sort(elements,0,(n*n)-1);
        cout<<cnt<<endl;
    }

    int merge_sort(vector<int> &v, int l, int r){   // dividing the array to perform mergesort and count inversions
        int k;
        if(l<r){
            int mid = l+(r-l)/2;
            merge_sort(v,l,mid);
            merge_sort(v,mid+1,r);
            k = merge_and_count(v,l,mid,r);
        }
        return k;
    }
    
    int merge_and_count(vector<int> &arr, int l, int mid, int r){   // to find no 0f inversions
        int n1 = mid-l+1;
        int n2 = r-mid;
        int l_arr[n1], r_arr[n2];

        for (int i=0; i<n1; i++){
            l_arr[i] = arr[l + i];
        }
        for (int j=0; j<n2; j++){
            r_arr[j] = arr[mid+1+j];
        }

        int i=0, j=0, k=l;
        while(i<n1 && j<n2){
            if(l_arr[i] <= r_arr[j]){
                arr[k] = l_arr[i];
                i++;
            }
            else{
                arr[k] = r_arr[j];
                cnt += n1-i;
                j++;
            }
            k++;
        }
        while(i<n1){
            arr[k] = l_arr[i];
            i++;
            k++;
        }
        while(j<n2){
            arr[k] = r_arr[j];
            j++;
            k++;
        }   
        return cnt;
    }

    void closest_pair(vector<Point> &points){       // finding closest points
        sort(points.begin(),points.end(),[](Point &p1, Point &p2){
            return p1.x<p2.x;
        });
        auto close_pair = split(points,0,points.size()-1);
        cout<<close_pair.first.x<<" "<<close_pair.first.y<<" "<<close_pair.second.x<<" "<<close_pair.second.y<<endl;;
    }

    int square_distance(Point &p1, Point &p2 ){     // distance calculation
        return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
    }

    pair<Point,Point> split(vector<Point> &points, int l, int r){  // dividing w.r.t x
        int mn = INT64_MAX;
        if(r-l+1<=3){
            Point p1,p2;
            for(int i=l;i<=r;i++){
                for(int j=i+1;j<=r;j++){
                    if(square_distance(points[i],points[j])<mn){
                        mn = square_distance(points[i],points[j]);
                        p1=points[i];
                        p2=points[j];
                    }
                    //tie breaker
                    else if (square_distance(points[i],points[j])==mn){
                        if(points[i].x<p1.x || (points[i].x==p1.x &&points[i].y<p1.y) ||(points[i].x==p1.x &&points[i].y==p1.y && points[j].x<p2.x) ||(points[i].x==p1.x &&points[i].y==p1.y && points[j].x==p2.x && points[j].y<p2.y) ){
                            p1=points[i];
                            p2=points[j];
                        }
                    }
                }
            }
            if(p1.index<p2.index) return {p1,p2};
            else return {p2,p1};
        }
        if(l<r){
            int mid =l+(r-l)/2;
            auto left_closest = split(points,l,mid);
            auto right_closest = split(points,mid+1,r);

            int left_distance = square_distance(left_closest.first,left_closest.second);
            int right_distance = square_distance(right_closest.first,right_closest.second);
            int closest_distance;

            pair<Point,Point> close_pair;
            if(left_distance<right_distance){
                close_pair = left_closest;
                closest_distance = left_distance;
            }
            else if (left_distance==right_distance){
                if(left_closest.first.x<right_closest.first.x || (left_closest.first.x==right_closest.first.x && left_closest.first.y<right_closest.first.y) ||(left_closest.first.x==right_closest.first.x && left_closest.first.y==right_closest.first.y&& left_closest.second.x<right_closest.second.x)||(left_closest.first.x==right_closest.first.x && left_closest.first.y==right_closest.first.y&& left_closest.second.x==right_closest.second.x && left_closest.second.y<right_closest.second.y) ){
                    close_pair = left_closest;
                }
                else{
                    close_pair = right_closest;
                }
            }
            else{
                close_pair = right_closest;
                closest_distance = right_distance;
            }
            
            vector<Point> strip;    // strip of points between x-coordinate of p1 and p2 to find shortest lenth across the half
            for(int i=l;i<=r;i++){
                if((points[mid].x-points[i].x)*(points[mid].x-points[i].x)<closest_distance){
                    strip.push_back(points[i]);
                }
            }

            // sorting y coordinate in the strip
            sort(strip.begin(),strip.end(),[](Point a,Point b){
                return a.y<b.y;
            });

            int mn = closest_distance;
            for(int i=0;i<(int)strip.size();i++){
                int k = min((int)16,(int)(strip.size()-i));
                for(int j=i+1;j<k+i;j++){
                    int distance = square_distance(strip[i],strip[j]);
                    if(distance<mn){
                        mn = distance;
                        if(strip[i].index<strip[j].index)
                        close_pair = {strip[i],strip[j]};
                        else close_pair = {strip[j],strip[i]};
                    }
                    //tie breaker
                    else if (distance == mn){
                        if(strip[i].x<close_pair.first.x || (strip[i].x==close_pair.first.x &&strip[i].y<close_pair.first.y) ||(strip[i].x==close_pair.first.x &&strip[i].y==close_pair.first.y && strip[j].x<close_pair.second.x) ||(strip[i].x==close_pair.first.x &&strip[i].y==close_pair.first.y && strip[j].x==close_pair.second.x && strip[j].y<close_pair.second.y) ){
                            if(strip[i].index<strip[j].index)
                            close_pair = {strip[i],strip[j]};
                            else close_pair = {strip[j],strip[i]};
                            // close_pair = {strip[i],strip[j]};
                        }
                    }
                }
            }
            return close_pair;
        }
        return {points[0],points[1]};  // returning some default point 
    }
};

int32_t main(){
    Chess game;
    while(1){
        string choice;
        cin>>choice;
        if(choice == "END"){break;}
        if(choice == "CREATE_2D"){
            int n;
            cin>>n;
            game.board_size(n);
            vector<vector<int>> v(n,vector<int> (n));
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cin>>v[i][j];
                }
            }
            game.set_board(v);
        }
        if(choice == "DISPLAY_2D"){
            game.print();
        }
        if(choice == "INVERSION_2D"){
            cnt=0;
            game.count_inversions();
        }
        if(choice == "SORT_2D"){
            string type;
            cin>>type;
            game.sort_rows(type);
        }
        if(choice == "CLOSEST_2D"){
            int n;
            cin>>n;
            vector<Point> points(n);
            for(int i=0;i<n;i++){
                cin>>points[i].x>>points[i].y;
                points[i].index=i;
            }
            game.closest_pair(points);
        }
    }
}
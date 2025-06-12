// This Project includes
// Many Number-Theory concepts like
/* * Implementing Quick Sort
   * Fibonacci Generator using Matrix Exponentiation
   * Sieve of Eratosthenes and Segmented Sieve
   * Square-Free Numbers
   * Count and Sum of divisors 
*/

# include <bits/stdc++.h>
using namespace std;
#define int long long
int MOD = 1000000007;

int partition(vector<int>& arr, int low, int hi){
    int pivotIdx = hi;
    int pivot = arr[pivotIdx];
    int i = low;
    for(int j = low; j < hi; j++){
        if(arr[j] < pivot){
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[hi]);
    return i;
}

void quickSort(vector<int>& arr, int low, int hi){
    if(low < hi){
        int p = partition(arr, low, hi);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, hi);
    }
}

class CurrencySorter{    //To sort dollar bill serial number

    public:
    CurrencySorter(){}    // constructor
    void operator ()(vector<int> &v){
        //quicksort
        quickSort(v,0,v.size()-1);
        for(int i=0;i<v.size();i++){
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }

};

class FibonacciGenerator{

    public:

    void operator()(int i){
        cout<<fib(i)<<endl;
    }
    
    int fib(int i){                              // ith fibonacci number
        int Fibm[2][2] = {{1,1},{1,0}};
        int result[2][2];
        expo_matrix(Fibm, i-1, result);
        return result[0][0] % MOD;
    }
    void expo_matrix(int Fibm[][2],int n,int result[2][2]){   

        if(n==0) {
            result[0][0]=1;
            result[0][1]=0;
            result[1][0]=0;
            result[1][1]=1;
            return;
        }
        if(n==1) {
            result[0][0]=Fibm[0][0];
            result[0][1]=Fibm[0][1];
            result[1][0]=Fibm[1][0];
            result[1][1]=Fibm[1][1];
            return;
        };
        
        int matrix1[2][2];
        expo_matrix(Fibm,n/2,matrix1);

        matrix_multiplication(matrix1,matrix1);
        
        if(n%2==1) matrix_multiplication(matrix1,Fibm);
        result[0][0]=matrix1[0][0];
        result[0][1]=matrix1[0][1];
        result[1][0]=matrix1[1][0];
        result[1][1]=matrix1[1][1];
        
        return;
    }
    void matrix_multiplication(int matrix1[][2],int matrix2[][2]){
        
        int x=((matrix1[0][0]*matrix2[0][0])%MOD+(matrix1[0][1]*matrix2[1][0])%MOD)%MOD;
        int y=((matrix1[0][0]*matrix2[0][1])%MOD+(matrix1[0][1]*matrix2[1][1])%MOD)%MOD;
        int z=((matrix1[1][0]*matrix2[0][0])%MOD+(matrix1[1][1]*matrix2[1][0])%MOD)%MOD;
        int w=((matrix1[1][0]*matrix2[0][1])%MOD+(matrix1[1][1]*matrix2[1][1])%MOD)%MOD;
        matrix1[0][0]=x;
        matrix1[0][1]=y;
        matrix1[1][0]=z;
        matrix1[1][1]=w;
        return;
    }

};

class NumberAnalyzer{

    public:
    NumberAnalyzer(){}      // default constructor
    bool isSquareFree(int x){
        // to check whether x is square free or not
        if(x%(2)==0){
            x=x/2;
            if(x%2==0){
                cout<<"no"<<endl;
                return false;
            }
        }
        for(int i=3;(i*i)<=x;i=i+2){
            if(x%(i)==0){
                x/=i;
                if(x%(i)==0){
                cout<<"no"<<endl;
                return false;
                }
            }
        }
        cout<<"yes"<<endl;
        return true;
    }

    int countDivisors(int x){
        // count divisors of x
        int count=0;
        for(int i=1;i<=(int)sqrt(x);i++){
            if(x%i==0){
                count++;
                if(i != x/i) count++; // Count the complementary divisor
            }
        }
        return count;
    }

    int sumOfDivisors(int x){
        // to sum divisors of x
        int sum=0;
        for(int i=1;i<=(int)sqrt(x);i++){
            if(x%i==0){
                sum+=i;
                if(i != x/i) sum+=x/i; // Add the complementary divisor
            }
        }
        return sum;
    }
};

class PrimeCalculator{

    public:
    PrimeCalculator(){}     //default constructor
    void printPrimes(int l,int r){
        //prints primes starting from l till r inclusive
        vector<int> prime(1000000,1);
        prime[1]=0;
        if(l==1)l++;
        vector<int> primes;
        for(int i=2;i<=1000000;i++){
            if(prime[i]==1){
                primes.push_back(i);
                for(int j=i*i;j<=1000000;j+=i){    
                    prime[j]=0;
                }
            } 
        }
        
        vector<int> primes_in_l_to_r(r-l+1,1);
        for(auto prime: primes){
            if(prime>r) break;
            int i=prime*prime;
            if(i<l){
            i = (l/prime)*prime;
            if(i<l) i+=prime;
            }
            for(;i<=r;i+=prime){
                primes_in_l_to_r[i-l]=0;
            }
        }
        
        for(int i=0;i<primes_in_l_to_r.size();i++){
            if(primes_in_l_to_r[i]==1) cout<<i+l<<" ";
        }
        cout<<'\n';
        
    }
    
    int printPrimeSum(int l,int r){
        //prints sum of all primes starting from l till r inclusive
        vector<int> prime(1000000,1);
        prime[1]=0;
        if(l==1)l++;
        vector<int> primes;
        for(int i=2;i<=1000000;i++){
            if(prime[i]==1){
                primes.push_back(i);
                for(int j=i*i;j<=1000000;j+=i){    
                    prime[j]=0;
                }
            } 
        }

        vector<int> primes_in_l_to_r(r-l+1,1);
        for(auto prime: primes){
            if(prime>r) break;
            int i=prime*prime;
            if(i<l){
            i = (l/prime)*prime;
            if(i<l) i+=prime;
            }
            for(;i<=r;i+=prime){
                primes_in_l_to_r[i-l]=0;
            } 
        }
        
        int sum=0;
        for(int i=0;i<primes_in_l_to_r.size();i++){

            if(primes_in_l_to_r[i]==1) sum+=i+l;
        }
        return sum;
    }
};

int32_t main(){
    int choice;
    cin>>choice;
    if(choice==1){      // CurrencySorter
        int no_of_operations;
        cin>> no_of_operations;
        for(int i=0;i<no_of_operations;i++){
        int size;
        cin>>size;
        vector<int> v(size);
        for(int j=0;j<size;j++){
            cin>>v[j];
        }
        CurrencySorter cs;
        cs(v);
    }
    }
    if(choice==2){      // FibonacciGenerator
        int no_of_operations;
        cin>> no_of_operations;
        vector<int> v(no_of_operations);
        for(int i=0;i<no_of_operations;i++){
            cin>>v[i];
            FibonacciGenerator fg;
            fg(v[i]);
        }
    }
    if(choice==3){      //PrimeCalculator
        PrimeCalculator pc;
        int no_of_operations;
        cin>> no_of_operations;
        while(no_of_operations--){
            string cmd;
            cin>>cmd;
            if(cmd=="printPrimes"){
                int l,r;
                cin>>l>>r;
                pc.printPrimes(l,r);
            }
            else{
                int l,r;
                cin>>l>>r;
                cout<<pc.printPrimeSum(l,r)<<endl;
            }
        }
    }
    if(choice==4){      //NumberAnalyzer
        NumberAnalyzer na;
        int no_of_operations;
        cin>> no_of_operations;
        while(no_of_operations--){
            string cmd;
            cin>>cmd;
            if(cmd=="isSquareFree"){
                int x;
                cin>>x;
                na.isSquareFree(x);
            }
            if(cmd=="countDivisors"){
                int x;
                cin>>x;
                cout<<na.countDivisors(x)<<endl;;
            }
            if(cmd=="sumOfDivisors"){
                int x;
                cin>>x;
                cout<<na.sumOfDivisors(x)<<endl;
            }
        }
    }
}

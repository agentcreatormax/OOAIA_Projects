// This project includes
// Operations on Polynomials like
/* * Differentiation
   * Multiplication of polynomials using Karastuba
   * Evaluation
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define float long double

class Complex{
    private:
    int a;
    int b;

    public:
    // default constructor
    Complex (){ a=0; b=0;}

    Complex(int p, int q){
        a=p;
        b=q;
    }

    Complex operator * (Complex& C) {
        // Multiplying 2 complex numbers
        return Complex(a * C.a - b * C.b, a * C.b + b * C.a);
    }

    Complex operator + (Complex& C){
        // adding 2 complex numbers
        return Complex(a + C.a, b + C.b);
    } 

    Complex operator - (Complex& C){
        // subing 2 complex numbers
        return Complex(a - C.a, b - C.b);
    }

    int get_real(){
        return a;
    }

    int get_imagnary(){
        return b;
    }
     
};

ostream& operator<<(ostream& cout, Complex& C) {
    cout<<C.get_real() <<" "<<C.get_imagnary();
    return cout;   
}

template <typename T> class Multiplication{
    private:
    // polynomial
    vector<T> coeff;

    public:
    // constructor
    Multiplication(vector<T> P){
        coeff=P;
    }

    void operator * (Multiplication& C){
        // multiplying 2 polynomials using div and conq method
        // karastuba
        int k = C.coeff.size() + coeff.size() - 1;
        int mx= max(coeff.size(),C.coeff.size());
        double n = log2(mx);
        mx = pow(2,(int)ceil(n));
        coeff.resize(mx,T());
        C.coeff.resize(mx,T());
        vector<T> mul = karatsuba(coeff,C.coeff);
        for(int i=0;i<k;i++){
            // print resulting mul
            cout<<fixed<<setprecision(6);
            cout<<mul[i]<<" ";
        }
        cout << endl;
    }

    vector<T> karatsuba(vector<T>& P1, vector<T>& P2){
        int n = P1.size();
        if (n == 1) {
            return {P1[0] * P2[0]};
        }
        int half = n / 2;
        vector<T> P1_1stHalf(n/2);
        vector<T> P1_2ndHalf(n/2);
        vector<T> P2_1stHalf(n/2);
        vector<T> P2_2ndHalf(n/2);
        for(int i=0;i<n/2;i++){
            P1_1stHalf[i]=P1[i];
            P1_2ndHalf[i]=P1[i+n/2];
            P2_1stHalf[i]=P2[i];
            P2_2ndHalf[i]=P2[i+n/2];
        }
    
        vector<T> V1 = karatsuba(P1_1stHalf,P2_1stHalf);
        vector<T> V2 = karatsuba(P1_2ndHalf,P2_2ndHalf);

        vector<T> P1_sum(half);
        vector<T> P2_sum(half);
        for (int i = 0; i < half; i++) {
            P1_sum[i] = P1_1stHalf[i]+P1_2ndHalf[i];
            P2_sum[i] = P2_1stHalf[i]+P2_2ndHalf[i];
        }
        vector<T> V3 = karatsuba(P1_sum, P2_sum);

        for (int i=0; i<V3.size();i++){
            V3[i]=V3[i]-V1[i]-V2[i];
        }
        vector<T> result(2*n - 1, T());

        for (int i=0;i<V1.size();i++){
            result[i] = result[i] + V1[i];
        }
        for(int i=n/2;i<n/2+V3.size();i++){
            result[i] = result[i] + V3[i-n/2];
        }
        for(int i=n;i<n+V2.size();i++){
            result[i] = result[i] + V2[i-n];
        }

        return result;
    }

};

template <typename T> class Evaluation{
    private:
    // polynomial and value of x
    vector<T> A;

    public:
    // constructor
    Evaluation(vector<T> P){
        A=P;
    }

    void evaluate(int a,int x){ // for int input
        int n = A.size(); 
        int ans=0;
        for(int i=n-1;i>=0;i--){
            ans+=A[i]*pow(x,i);
        }
        cout<<ans<<endl;
    }

    void evaluate(float a, int  x){  // for float input
        int n = A.size(); 
        float ans=0;
        for(int i=n-1;i>=0;i--){
            ans+=A[i]*(float)pow(x,i);
        }
        cout << fixed << setprecision(6);
        cout<<ans<<endl;
    }

    void evaluate(string a, int x){  // for string input
        int n = A.size();
        string ans="";
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<(int)pow(x,i);j++){
                ans+=A[i];
            }
        }
        cout<<ans<<endl;
    }

};

template <typename T> class Differentiation{
    private:
    // polynomial
    vector<T> A;

    public:
    // constructor
    Differentiation(vector<T> P){
        A=P;
    }

    // differentiation
    void diff(){
        int n = A.size();
        if (n == 1) {
            cout << 0 << endl;
            return;
        }
        vector<T> diff_A(n-1);
        for(int i=0;i<n-1;i++){
            diff_A[i]=(i+1)*A[i+1];
        }
        // print polynomial
        for(int i=0;i<n-1;i++){
            cout << fixed << setprecision(6);
            cout<<diff_A[i]<<" ";
        }
        cout<<endl;
    }

};

int32_t main(){
    int queries;
    cin>>queries;
    while(queries--){
        int n;
        cin>>n;
        if(n==1){
            string type;
            cin>>type;
            if(type == "integer"){
                int poly1_no_of_coeff;
                cin>>poly1_no_of_coeff;
                vector<int> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                int poly2_no_of_coeff;
                cin>>poly2_no_of_coeff;
                vector<int> poly2_coeff(poly2_no_of_coeff);
                for(int i=0;i<poly2_no_of_coeff;i++){
                    cin>>poly2_coeff[i];
                }
                Multiplication<int> P1(poly1_coeff);
                Multiplication<int> P2(poly2_coeff);
                P1*P2;
            }
            else if(type == "float"){
                int poly1_no_of_coeff;
                cin>>poly1_no_of_coeff;
                vector<float> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                int poly2_no_of_coeff;
                cin>>poly2_no_of_coeff;
                vector<float> poly2_coeff(poly2_no_of_coeff);
                for(int i=0;i<poly2_no_of_coeff;i++){
                    cin>>poly2_coeff[i];
                }
                Multiplication<float> P1(poly1_coeff);
                Multiplication<float> P2(poly2_coeff);
                P1*P2;
            }
            else if(type == "complex"){
                int poly1_no_of_coeff;
                cin>>poly1_no_of_coeff;
                vector<Complex> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    int real,imag;
                    cin>>real>>imag;
                    poly1_coeff[i] = Complex(real,imag);
                }
                int poly2_no_of_coeff;
                cin>>poly2_no_of_coeff;
                vector<Complex> poly2_coeff(poly2_no_of_coeff);
                for(int i=0;i<poly2_no_of_coeff;i++){
                    int real,imag;
                    cin>>real>>imag;
                    poly2_coeff[i] = Complex(real,imag);
                }
                Multiplication<Complex> P1(poly1_coeff);
                Multiplication<Complex> P2(poly2_coeff);
                P1*P2;
            }
        }
        else if (n==2){
            string type;
            cin>>type;
            int poly1_no_of_coeff;
            cin>>poly1_no_of_coeff;
            if(type == "integer"){
                vector<int> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                int x;
                cin>>x;
                Evaluation<int> P1(poly1_coeff);
                P1.evaluate(poly1_coeff[0],x);
            }
            else if(type == "float"){
                vector<float> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                int x;
                cin>>x;
                Evaluation<float> P1(poly1_coeff);
                P1.evaluate(poly1_coeff[0],x);
            }
            else if (type == "string"){ 
                vector<string> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                int x;
                cin>>x;
                Evaluation<string> P1(poly1_coeff);
                P1.evaluate(poly1_coeff[0],x);
            }
        }
        else{
            string type;
            cin>>type;
            int poly1_no_of_coeff;
            cin>>poly1_no_of_coeff;
            if(type == "integer"){
                vector<int> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                Differentiation<int> P1(poly1_coeff);
                P1.diff();
            }
            else if(type == "float"){
                vector<float> poly1_coeff(poly1_no_of_coeff);
                for(int i=0;i<poly1_no_of_coeff;i++){
                    cin>>poly1_coeff[i];
                }
                Differentiation<float> P1(poly1_coeff);
                P1.diff();
            }
        }
    }
}
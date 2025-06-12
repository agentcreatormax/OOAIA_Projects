// This Project includes
/* * Greedy algorithm of patience sort */

#include <bits/stdc++.h>
using namespace std;
#define int long long

class Card{   // abstract class
    public:
    virtual void Area()=0;
    virtual int getArea()=0;
    virtual void print() = 0;
    Card* prev = nullptr;
};

ostream& operator<< (ostream& stream, Card* Card){    // output
    Card->print();
    return cout;
}


class Rectangle: public Card{
    private:
    int l; // length
    int b; // breadth
    int a; // area

    public:
    Rectangle(): Card(){}
    Rectangle(int length, int breadth): Card(){  // contructor
        l = length;
        b = breadth;
        a = 0;
    }
    void Area() override{  // area override
        a = (l*b);
    }

    int getArea(){   // getter
        return a;
    }

    void print(){   
        cout<<"RECTANGLE "<<l<<" "<<b<<"\n";
    }

    void setArea(int area){
        a = area;
    }
    friend istream& operator>> (istream& stream, Rectangle& Card);
};

istream& operator>> (istream& stream, Rectangle& Card){   //input
    stream >> Card.l >> Card.b;
    return stream;
}

class Square: public Card{
    private:
    int s; // side
    int a; // area

    public:
    Square(): Card(){}
    
    Square(int side): Card(){ 
        s = side;
        a = 0;
    }
    void Area() override{
        a = (s*s);
    }

    int getArea(){
        return a;
    }

    void print(){
        cout<<"SQUARE "<<s<<"\n";
    }

    void setArea(int area){
        a = area;
    }

    void setSide(int side){
        s= side;
    }
    friend istream& operator>> (istream& stream, Square& Card);
};

istream& operator>> (istream& stream, Square& Card){   //input
    stream>>Card.s;
    return stream;
}

class Triangle: public Card{
    private:
    int h; // height
    int b; // base
    int a = 0; //area

    public:
    Triangle(): Card(){}
    Triangle(int height, int base): Card(){
        h = height;
        b = base;
        a = 0;
    }
    void Area() override{
        a = ((h*b)/2);
    }

    int getArea(){
        return a;
    }

    void print(){
        cout<<"TRIANGLE "<<h<<" "<<b<<"\n";
    }

    void setArea(int area){
        a = area;
    }
    friend istream& operator>> (istream& stream, Triangle& Card);
};

istream& operator>> (istream& stream, Triangle& Card){   //input
    stream>>Card.h>>Card.b;
    return stream;
}


//comparator
class Comparator{     // to compare areas while pushing cards on piles and finding LIE
    public:
    bool operator()(Card* a , Card* b){
        return a->getArea() < b->getArea();
    }
};

class  CardOrganizer{
    private:
    vector<vector<Card*>> Piles; // no_of_piles
    // vector<int> Pile_area;  // total 
    vector<Card*> LIS_Cards;  // cards
    vector<Card*> PilesTop;  // top values of piles
    vector<int> PilesTopArea;

    public:
    CardOrganizer(){}

    // using patience sort algorithm
    void addCard(Card* a){  
        if(Piles.size()==0){
            Piles.push_back({a});
            PilesTop.push_back(a);
            PilesTopArea.push_back(a->getArea());
            return;
        }

        int index = lower_bound(PilesTopArea.begin(),PilesTopArea.end(),a->getArea()) - PilesTopArea.begin();
        if(index == PilesTopArea.size()){
            a->prev = PilesTop[PilesTop.size()-1];
            Piles.push_back({a});
            PilesTop.push_back(a);
            PilesTopArea.push_back(a->getArea());
            return;
        }

        if(index>0){
            a->prev = PilesTop[index - 1];
        }
    
        Piles[index].push_back(a);
        PilesTop[index] = a;
        PilesTopArea[index] = a->getArea();   
    }

    size_t getPileCount() const{
        return Piles.size();
    }

    vector<Card*> getLIS() {
        vector<Card*> LIS;
        Card* k = PilesTop[PilesTop.size()-1];
        while(k->prev!=NULL){
            LIS.push_back(k);
            k = k->prev;
        }
        LIS.push_back(k);
        reverse(LIS.begin(), LIS.end());
        return LIS;
    }
    
};

int32_t main(){
    int queries;
    cin >> queries;
    CardOrganizer organizer;
    for(int i = 0; i < queries; i++){
        int n;
        cin >> n;
        if(n==1){
            string shape;
            cin>>shape;
            if(shape == "RECTANGLE"){
                Rectangle* r = new Rectangle();
                cin>>*r;
                Card* card = r;
                card->Area();
                organizer.addCard(card);
            }
            if(shape == "SQUARE"){
                Square* s=new Square();
                cin>>*s;
                Card* card = s;
                card->Area();
                organizer.addCard(card);
            }
            if(shape == "TRIANGLE"){
                Triangle* t=new Triangle();
                cin>>*t;
                Card* card = t;
                card->Area();
                organizer.addCard(card);
            }
        }
        if(n==2){
            cout<<organizer.getPileCount()<<endl;
        }
        if(n==3){
            vector<Card*> v= organizer.getLIS();
            cout<<v.size()<<endl;
            for(auto Card: v){
                Card->print();
            }
        }
    }
}
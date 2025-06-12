// This Project includes
// Dynamic Programming
// Weighted interval- Scheduling

#include<bits/stdc++.h>
using namespace std;
#define int long long

class Event{
    protected:
    int start;
    int end;
     
    public:
    Event(){}  
    virtual double calculateProfit()=0; // pure virtual
    virtual void take()=0;  // pure virtual to take inputs
    int gets(){
        return start;
    }
    int gete(){
        return end;
    }
    friend istream &operator>>(istream &cin, Event *A);
};

// insertion overloading
istream &operator>>(istream &cin, Event *A){
    A->take();
    return cin;
}

class Concert: public Event{
    private:
    int TicketPrice;
    int TicketsSold;
    double Tax;
    int ArtisteFee;
    int LogisticCost;

    public:
    Concert(){}  // contructors
    Concert(int s, int e, int tp, int ts, int af, int lc):Event(){
        start = s;
        end = e;
        TicketPrice = tp;
        TicketsSold = ts;
        ArtisteFee = af;
        LogisticCost = lc;
    }

    double calculateProfit()override{   // profit calculation
        double Ticket_Revenue = (double)(TicketPrice*TicketsSold);
        Tax = (double)(0.18 * Ticket_Revenue);
        Ticket_Revenue = Ticket_Revenue - Tax;
        double Cost = ArtisteFee + LogisticCost;
        double profit = Ticket_Revenue - Cost;
        double Net_Profit;
        if(profit>2*Cost){
            Net_Profit = (double)(0.7*profit);
        }
        else{
            Net_Profit = profit;
        }
        return Net_Profit;
    }

    void take(){
        cin>>start >>end >>TicketPrice >>TicketsSold >>ArtisteFee >>LogisticCost;
    }
};

class TheaterShow: public Event{
    private:
    int BasePrice;
    int TotalSeats;
    int VenueCost;
    double Tax;

    public:
    TheaterShow(){}   // contructors
    TheaterShow(int s, int e, int bp, int ts, int vc):Event(){
        start = s;
        end = e;
        BasePrice = bp;
        TotalSeats = ts;
        VenueCost = vc;
    }

    double calculateProfit() override{    // profit calculation
        double Ticket_Revenue = (double)(0.25 * TotalSeats * (2 * BasePrice) + 0.75 * TotalSeats * BasePrice);
        double Tax = 0.18 * Ticket_Revenue;
        Ticket_Revenue= Ticket_Revenue - Tax;
        double PopcornPrice =150;
        double PopcornRevenue = (double) (0.25 * TotalSeats * PopcornPrice);
        double Net_Profit = Ticket_Revenue + (double)PopcornRevenue - (double)VenueCost;
        return Net_Profit;
    }

    void take(){
        cin>>start >>end >>BasePrice >>TotalSeats>> VenueCost;
    }

};

class Wedding: public Event{
    private:
    int BaseAmount;
    int DecorationCost;
    int GuestCount;
    int VenueCost;
    
    public:
    Wedding(){}   // contructors
    Wedding(int s, int e, int ba, int dc, int gc, int vc):Event(){
        start = s;
        end = e;
        BaseAmount = ba;
        DecorationCost = dc;
        GuestCount = gc;
        VenueCost = vc;
    }

    double calculateProfit()override{   // profit calculation
        if(GuestCount > 200){
            VenueCost = 3*VenueCost;
        }
        int Catering_cost;
        if(GuestCount > 100){
            Catering_cost = 70*GuestCount;
        }
        else{
            Catering_cost = 100*GuestCount;
        }
        double Net_Profit = (double)(BaseAmount - VenueCost - DecorationCost - Catering_cost);
        return Net_Profit;
    }


    // taking input
    void take(){
        cin>>start >>end>> BaseAmount >>DecorationCost >>GuestCount >>VenueCost;
    }
};

// to sort according to finsih times
class comparator{
    public:
    bool operator()(Event* A, Event* B){
        return A->gete() < B->gete();
    }
};
    // schedule events to maximize profit
class EventScheduler{
    private:
    int n;
    vector<int> start_times;
    vector<int> end_times;
    vector<double> profit;

    public:
    EventScheduler(vector<Event*> e){
        
        n = e.size();
        sort(e.begin(),e.end(), comparator());
        for(int i=0;i<(int)e.size();i++){
            start_times.push_back(e[i]->gets());
            end_times.push_back(e[i]->gete());
            profit.push_back(e[i]->calculateProfit());
        }
    }

    // Weighted interval scdehuling using dp
    double max_profit(){
        vector<int> p(n,-1);
        for (int i = 0; i < n; i++) {
            auto it = upper_bound(end_times.begin(), end_times.end(), start_times[i]);
            if (it == end_times.begin()) {
                p[i] = -1;
            } else {
                p[i] = (it - end_times.begin()) - 1;
            }
        }       
        vector<double> dp(n, 0);
        for (int i = 0; i < n; i++) {
            double include = profit[i];
            if (p[i] != -1) include += dp[p[i]];
            if (i == 0) dp[i] = include;
            else dp[i] = max(dp[i-1], include);
        }
        return dp[n-1];
    }
};

int32_t main(){
    int n;
    cin>>n;
    vector<Event*> events(n);
    // inputtng
    for(int i=0;i<n;i++){
        int choice;
        cin>>choice;
        if(choice==1){
            Concert *C = new Concert();
            cin >> C;
            Event *E = C;
            events[i] = E;
            
        }
        else if(choice==2){
            TheaterShow *TS = new TheaterShow();
            cin >> TS;
            Event *E = TS;
            events[i] = E;
        }
        else{
            Wedding *W = new Wedding();
            cin >> W;
            Event *E = W;
            events[i] = E;
        }
    }
    double maxprofit = EventScheduler(events).max_profit();
    cout << fixed << setprecision(2) << maxprofit << "\n";
}
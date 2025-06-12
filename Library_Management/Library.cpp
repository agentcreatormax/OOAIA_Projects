// This Project includes
// Basic OOPS opeartions of classes and objects

#include <bits/stdc++.h>
using namespace std;

class Book{
    private:
    string isbn;
    int copiesAvailable; 
    int	totalCopies;

    public:
    string title;
    string author;

    Book(){
        title = "UnknownTitle";
        author = "UnknownAuthor";
        isbn = "ISBN";
        copiesAvailable = 0;
        totalCopies = 5;
    }

    Book(string t,string a,string i,int ca,int	tc){
        title = t;
        author = a;
        isbn = i;
        copiesAvailable = ca;
        totalCopies = tc;
    }

    Book(Book& b, string &newI){  // creates copies with new isbn
        title = b.title;
        author = b.author;
        isbn = newI;
        copiesAvailable = b.copiesAvailable;
        totalCopies = b.totalCopies;

    }

    string getIsbn(){
        return isbn;
    }
    int getCopiesAvailable(){
        return copiesAvailable;
    }
    int getTotalCopies(){
        return totalCopies;
    }
    void updateCopies(int count){
        if(totalCopies < -count||copiesAvailable<-count){
            cout<<"Invalid request! Count becomes negative"<<endl;
        }
        else{
            totalCopies+=count;
            copiesAvailable+=count;
        }
    }
    bool borrowBook(){
        if(copiesAvailable>0){
            copiesAvailable--;
            return true;
        }
        else{
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
    }
    bool returnBook(){
        if(copiesAvailable>=totalCopies){
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
        }
        else{
            copiesAvailable++;
            return true;
        }
    }
    void printDetails(){
        cout<<title<<" "<<author<<endl;
    }
};

class Member{
    private:
    string memberID;
    map<string,int> borrowedBooks;
    int borrowLimit;

    public:
    string name;
    Member() {}
    Member(string memID, string n){
        memberID=memID;
        name=n;
        borrowLimit=3;
    }
    Member(string memID, string n, int bl){
        memberID=memID;
        name=n;
        borrowLimit=bl;
    }

    int getBorrowLimit(){
        return borrowLimit;
    }

    string getMemberID(){
        return memberID;
    }

    bool borrowBook(string isbn){
        if(borrowLimit<=0){
            cout<<"Invalid request! Borrow limit exceeded"<<endl;
            return false;
        }
        else{
            borrowLimit -= 1;
            borrowedBooks[isbn]++;
            return true;
        }
    }
    bool returnBook(string isbn){
        for(auto it=borrowedBooks.begin();it!=borrowedBooks.end();it++){
            if(it->first==isbn && it->second > 0){   // if book is in the map and has a copy
                it->second--;
                borrowLimit++;
                return true;
            }
        }
        cout<<"Invalid request! Book not borrowed"<<endl;
        return false;
    }
    void printDetails(){
        for(auto it=borrowedBooks.begin();it!=borrowedBooks.end();it++){
            if(it->second)
                cout<<memberID<<" "<<name<<" "<<it->first<<" "<<it->second<<endl;
        }
    }
};

class Library{
    private:
    vector<Book> books;
    vector<Member> members;

    public:
    bool addBook(Book& book){
        for(int i=0;i<(int)books.size();i++){
            if(books[i].getIsbn()==book.getIsbn()){
                cout<<"Invalid request! Book with same isbn already exists"<<endl;
                return false;
            }
        }
        books.push_back(book);
        return true;
    }
    bool registerMember(Member& member){
        for(int i=0;i<(int)members.size();i++){
            if(members[i].getMemberID()==member.getMemberID()){
                cout<<"Invalid request! Member with same id already exists"<<endl;
                return false;
            }
        }
        members.push_back(member);
        return true;
    }
    bool borrowBook(string memberID, string isbn){
        for(int i=0;i<(int)books.size();i++){
            if(books[i].getIsbn()==isbn){  
                if(books[i].borrowBook()){ // enters if book is borrowed
                    for(int j=0;j<(int)members.size();j++){
                        if(members[j].getMemberID()==memberID){
                            if(members[j].borrowBook(isbn))
                                return true;    
                        }
                    }
                    books[i].returnBook(); // returns the book back since the borrowlimit exceeds
                    return false;
                }    
            }
        }
        return false;
    }
    bool returnBook(string memberID, string isbn){
        for(int i=0;i<(int)books.size();i++){
            if(books[i].getIsbn()==isbn){
                if(books[i].returnBook()){ // enters if book is returned
                    for(int j=0;j<(int)members.size();j++){
                        if(members[j].getMemberID()==memberID){
                            if(members[j].returnBook(isbn))
                                return true;
                        }
                    }
                    books[i].borrowBook(); // borrows the book back since the member didnt took the book
                    return false;
                }  
                
            }
        }
        return false;
    }
    void printLibraryDetails(){
        for(int i=0;i<(int)books.size();i++){
            cout<< books[i].title<<" "<<books[i].author<<" "<<books[i].getCopiesAvailable()<<endl;
        }
        for(int i=0;i<(int)members.size();i++){
            cout<< members[i].getMemberID()<<" "<<members[i].name<<endl;
        }
    }
    Book& getBook(string isbn){
        for(int i=0;i<(int)books.size();i++){
            if(books[i].getIsbn()==isbn){
                return books[i];
            }
        }
        static Book book;
        return book;
    }
    Member& getMember(string memberID){
        for(int i=0;i<(int)members.size();i++){
            if(members[i].getMemberID()==memberID){
                return members[i];
            }
        }
        static Member member;
        return member;
    }
};

int main(){
    Library lib;
    while(1){
        string choice;
        cin>>choice;
        if(choice=="Done"){
            break;
        }
        if(choice=="Book"){
            string title;
            cin>>title;
            if(title=="ExistingBook"){
                string newisbn, oldisbn;
                cin>>oldisbn>>newisbn;
                Book oldbook = lib.getBook(oldisbn);
                Book book(oldbook, newisbn);
                lib.addBook(book);
            }
            else if(title== "None"){
                Book book;
                lib.addBook(book);
            }
            else{
                string author, isbn;
                int copiesAvailable, availableCopies;
                cin>>author>>isbn>>copiesAvailable>>availableCopies;
                Book book(title, author, isbn, copiesAvailable, availableCopies);
                lib.addBook(book);
            }
        }
        if(choice=="UpdateCopiesCount"){
            string isbn;
            int count;
            cin>>isbn>>count;
            Book& book=lib.getBook(isbn);
            book.updateCopies(count);
        }
        if(choice=="Member"){
            string memberid ;
            cin>>memberid;
            if(memberid=="NoBorrowLimit"){
                string memID;
                string name;
                cin>>memID>>name;
                Member member(memID, name);
                lib.registerMember(member);
            }
            else{
                string name;
                int borrowLimit;
                cin>>name>>borrowLimit;
                Member member(memberid, name, borrowLimit);
                lib.registerMember(member);
            }
        }
        if(choice=="Borrow"){
            string isbn;
            string memID;
            cin>>memID>>isbn;
            lib.borrowBook(memID,isbn);
        }
        if(choice=="Return"){
            string isbn;
            string memID;
            cin>>memID>>isbn;
            lib.returnBook(memID,isbn);
        }
        if(choice=="PrintBook"){
            string isbn;
            cin>>isbn;
            Book& book=lib.getBook(isbn);
            book.printDetails();
        }
        if(choice=="PrintMember"){
            string memID;
            cin>>memID;
            Member& member=lib.getMember(memID);
            member.printDetails();
        }
        if(choice=="PrintLibrary"){
            lib.printLibraryDetails();
        }
    }
} 
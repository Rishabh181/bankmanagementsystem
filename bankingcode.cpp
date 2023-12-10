#include<bits/stdc++.h>

using namespace std ;

class bank_account{
    int account_number ;
    char name[50] ;
    char type ;
    int money_deposit ;
    
    public :
    int retacno() const{
        return account_number ;
    }
    void create_account() ;
    void display_account() ;


};

void bank_account :: display_account(){
    cout<<"\t bank account number : "<<account_number<<endl;
    cout<<"\t account holder name : "<<name<<endl;
    cout<<"\t type of account : "<<type<<endl;
    cout<<"\t balance amount : "<<money_deposit<<endl;
}

void bank_account :: create_account(){
    system("cls") ;
    cout<<"\t enter the account number : " ;
    cin>>account_number ;
    cout<<"\t enter the name of the account holder: " ;
    cin.ignore() ;
    cin.getline(name, 50) ;
    cout<<"\t enter the type of the account(C/S) : " ;
    cin>>type ;
    type = toupper(type) ;
    cout<<"\t enter the initial amount (>=500 for saving account and >=1000 for current) : " ;
    cin>>money_deposit ;
   
    cout<<"\t account created.... :) " ;
     cout<<endl;
    
}

int main(){
    char ch ;
    int num ;
    cout<<"\t\t ..............................."<<endl;
    cout<<"\t\t !! Welcome to Maa Umiya Bank!! "<<endl;
    cout<<"\t\t ..............................."<<endl;

    cout<<endl;
    cout<<"\t -- main menu -- "<<endl;
    cout<<"\t 1. create account" <<endl;
    cout<<"\t 2. deposit money"<<endl;
    cout<<"\t 3. withdraw money"<<endl;
    cout<<"\t 4. balance enquiry"<<endl ;
    cout<<"\t 5. all account holder list "<<endl;
    cout<<"\t 6. close an account"<<endl;
    cout<<"\t 7. modify an account"<<endl;
    cout<<"\t 8. exit"<<endl;
    cout<<endl;

    cout<<"\t enter your choice (1-8) : ";
    cin>>ch ;

    switch (ch)
    {
        case '1':
        write_account() ;
        break;
        case '2':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        break;
        case '3':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        break;
        case '4':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        display_details(num) ;
        break;
        case '5':
        // display_all() ;
        break;
        case '6':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        delete_account(num) ;
        break;
        case '7':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        break;
        case '8':
        cout<<"\t Thanks for using maa Umiya bank " ;
        
        break;

    default:
        break;
    }

    // bank_account B ;
    // B.create_account() ;
    //  cout<<endl;
    // B.display_account() ;
    // return 0 ;
}

void write_account() {
    bank_account ac ;
    ofstream outfile ;
    outfile.open("account.dat" , ios::binary|ios::app) ;
    ac.create_account() ;
    outfile.write(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ;
    outfile.close() ;
}

void delete_account(int n){
    bank_account ac ;
    ifstream infile ; //input file stream
    ofstream  outfile ; //output file stream
    infile.open("account.dat" , ios::binary) ;
    if(!infile){
        cout<<"file could not be open !! press any key..." ;
        return ;
    }
    outfile.open("temp.dat", ios:: binary)
    infile.seekg(0 , ios::beg) ;
    while(infile.read(reinterpret_cast<char*> (&ac) , sizeof(bank_account))){

        if(ac.retacno() != n ){
            outfile.write(reinterpret_cast<char> (&ac) , sizeof(bank_account)) ;

        }
        infile.close() ;
        outfile.close() ;
        remove("bank_account.det") ;
        rename("temp.dat" , "bank_account.dat") ;
        cout<<"\t record has been deleted " ;
    }
}

void display_details(int n){
    bank_account ac ;
    bool flag = false ;
    ifstream infile ;
    infile.open("account.dat" , ios::binary) ;
    if(!infile){
        cout<<"file could not be open !! press any key..." ;
        return ;
    }
    cout<<"\t bank account details"<<endl ;
    while(infile.read(reinterpret_cast<char*> (&ac) , sizeof(bank_account))){
        if(ac.retacno() == n){
            ac.display_account() ;
            flag = true;
        }
    }
    infile.close() ;
    if(flag == false ){
        cout<<"\t account number does not exist"<<endl;
    }
}
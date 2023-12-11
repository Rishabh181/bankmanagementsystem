#include<bits/stdc++.h>

using namespace std ;

class bank_account{
    int account_number ;
    char name[50] ;
    char type ;
    int money_deposit ;
    
    public :
    void report() const ;
    int retacno() const{
        return account_number ;
    }
    void modify() ;
    void create_account() ;
    void display_account() ;
    void dep(int x){
        money_deposit += x ;
    }
    void draw(int x){
        money_deposit -= x ;
    }
    int retdeposit() const{
        return money_deposit ;
    }


};

void bank_account :: report() const{
    cout<<account_number<<setw(8)<<" "<<name<<setw(10)<<type<<setw(6)<<money_deposit<<endl;
}


void bank_account :: modify(){
    cout<<"\t Account number: "<<account_number<<endl;
    cout<<"\t modify account holder name: " ;
    cin.ignore() ;
    cin.getline(name, 50) ;
    cout<<"\t modify type of account: " ;
    cin>>type ;
    type = toupper(type) ;
    cout<<"\t modify balance account: " ;
    cin>>money_deposit ;
}

void write_account(); //function to write record in binary file
void display_details(int) ; //function to displa account details given by user
void delete_account(int) ; //function to delete record of file 
void display_all() ;
void money_deposit_withdraw(int , int) ;
void updation_bank_account(int) ;
// void dep

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

    do {
    cout<<"\t\t ..............................."<<endl;
    cout<<"\t\t !! Welcome to Maa Umiya Bank!! "<<endl;
    cout<<"\t\t ..............................."<<endl;

    cout<<endl;
    cout<<"\t -- main menu -- "<<endl;
    cout<<"\t 1. create account" <<endl; //done
    cout<<"\t 2. deposit money"<<endl;
    cout<<"\t 3. withdraw money"<<endl;
    cout<<"\t 4. balance enquiry"<<endl ; //done
    cout<<"\t 5. all account holder list "<<endl;
    cout<<"\t 6. close an account"<<endl; //done
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
        money_deposit_withdraw(num , 1) ;
        break;
        case '3':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        money_deposit_withdraw(num ,2 ) ;
        break;
        case '4':
        system("cls") ;
        cout<<"\t enter the account number: " ;
        cin>>num ;
        display_details(num) ;
        break;
        case '5':
        display_all() ;
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
        updation_bank_account(num) ; //update the data of the account 
        break;
        case '8':
        cout<<"\t Thanks for using maa Umiya bank " ;
        break;
    }
    cin.ignore() ;
    cin.get() ;
} while(ch != '8') ;

return 0 ;

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

void money_deposit_withdraw(int n , int option){
    int amt ;
    bool found = false ;
    bank_account ac ;
    fstream file ;
    file.open("account.dat" , ios::binary| ios::in|ios::out) ;
    if(!file){
        cout<<"file could not be open !! press any key... " ;
        return ;
    }
    while(!file.eof() && found == false ){
        file.read(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ;
        if(ac.retacno() == n){
            ac.display_account() ;
            if(option == 1){
                cout<<"\t enter the amount to be deposited : " ;
                cin>>amt ;
                ac.dep(amt) ;
            }
            if(option == 2){
                cout<<"\t enter the amount to be withdraw : " ;
                cin>>amt ;
                int balance = ac.retdeposit() - amt ;
                if(balance < 0){
                    cout<<"\t Insufficient balance"<<endl;
                }else{
                    ac.draw(amt) ;
                }
            }

            int pos = (-1)*static_cast<int>(sizeof(bank_account)) ;
            file.seekp(pos , ios :: cur) ; //move the pointer to the position of the file
            file.write(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ;
            cout<<"\t record updatec"<<endl;
            found = true ;
        }
    }
    file.close();
    if(found == false ){
        cout<<"\t record not found"<<endl;
    }
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
    outfile.open("temp.dat", ios:: binary) ;
    infile.seekg(0 , ios::beg) ;
    while(infile.read(reinterpret_cast<char*> (&ac) , sizeof(bank_account))){

        if(ac.retacno() != n ){
            outfile.write(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ;

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

void display_all() //function to display all account details
{
    system("cls") ;
    bank_account ac ;
    ifstream infile ;
    infile.open("account.dat" , ios::binary) ;
    if(!infile){
        cout<<"file could not be open !! press any key..." ;
        return ;
    }

    cout<<"\t Bank Account Holder List"<<endl;
    cout<<"=================================" <<endl;
    cout<<"A/C no.            Name          Type           Balance"<<endl;
    cout<<"=================================="<<endl;
    while(infile.read(reinterpret_cast<char*> (&ac), sizeof(bank_account))){
        ac.report() ;
    }
    infile.close() ;
}


void updation_bank_account(int n){
    bool found = false ;
    bank_account ac ;
    fstream file ;
    file.open(
         "account.dat", ios:: binary|ios::in|ios::out
    ) ; //open the file in binary mode

    if(!file){
        cout<<"file could bot be open !! press any key...." ;
        return ;
    }
    while(!file.eof() && found == false ){
        file.read(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ;
        if(ac.retacno() == n){
            cout<<"\t enter the new details of the account"<<endl;
            ac.modify() ;
            int pos = (-1)*static_cast<int>(sizeof(bank_account)) ;
            file.seekp(pos, ios::cur) ;
            file.write(reinterpret_cast<char*> (&ac) , sizeof(bank_account)) ; //write the record in the file
            cout<<"\t record updated "<<endl;
            found = true ;
        }
    }
    file.close() ;
    if(found == false ){
        cout<<"\t record not found" <<endl;
    }
}
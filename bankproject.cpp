#include <iomanip>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const string clientfilename = "clientsfile.txt";

void showmainmenue();

void showtransactionsScreen();

struct stclient {

    string accountnumber;
    
    string pincode;
    
    string name;
    
    string phone;
    
    double accountbalance=0;
    
    bool markfordelete= false;
};


vector<string>splitstring(string s1, string delim) {
    
    vector<string>vecstring;
   
    short pos = 0;
    
    string sword;
    
    while ((pos = s1.find(delim))!=std::string::npos) {
       
        sword = s1.substr(0, pos);
       
        if (sword != "") {

            vecstring.push_back(sword);



        }
        
    s1.erase(0, pos + delim.length());


    }

    if (s1 != "") {
        
      vecstring.push_back(s1);


    }
    return vecstring;

}

stclient convertlinetoclient(string line, string sep = "#//#") {
   
    stclient client;
    
    vector<string>vecstring;
   
    vecstring  = splitstring(line, sep);
    
    if (vecstring.size() >= 5) {
        
        client.accountnumber = vecstring[0];
        client.pincode = vecstring[1];
        client.name = vecstring[2];
        client.phone = vecstring[3];
        client.accountbalance = stod(vecstring[4]);
    }
    
    return  client;

}
string converclienttoline(stclient client, string sep = "#//#") {
   
    string line = "";

    line += client.accountnumber + sep;
    line += client.pincode + sep;
    line += client.name + sep;
    line += client.phone + sep;
    line += to_string(client.accountbalance) ;

    return line;
}

bool isclientexistbyaccountnumber(string accountnumber, string filename) {
    
    fstream myfile;
    
    myfile.open(filename, ios::in);
    
  

    if (myfile.is_open()) {
      
        stclient client;
       
        string line;

        while (getline(myfile, line)) {
           
            client = convertlinetoclient(line);
           
            if (client.accountnumber == accountnumber) {

                myfile.close();
               
                return true;
            }
           




        }
        myfile.close();
    }

return false;

}
stclient ReadNewClient() {
   
    stclient client;
    
    cout << "\nEnter the account number: ";
    
    getline(cin >> ws, client.accountnumber);

    while (isclientexistbyaccountnumber(client.accountnumber, clientfilename)) {

        cout << "The client is already exist .Please enter another one: ";
        
        getline(cin >> ws, client.accountnumber);
    }
    
    cout << "Enter the pincode: ";
    
    getline(cin, client.pincode);
    
    cout << "Enter the name:  ";
    getline(cin >> ws, client.name);

    cout << "Enter the phone number:  ";
    getline(cin >> ws, client.phone);


    cout << "Enter the account balance: ";
    cin >> client.accountbalance;


    return client;
}
vector<stclient>loadclientdatafromfile(string filename) {
    
    vector<stclient>vecstruct;

    fstream myfile;
    
    myfile.open(filename, ios::in);
    
    if (myfile.is_open()) {
        
        string line;
        stclient client;
       
        while (getline(myfile, line)) {
           
                client = convertlinetoclient(line);

                vecstruct.push_back(client);

        }
        

    myfile.close();

    }


    return vecstruct;
}
void printClientrecordline(stclient client) {
	
    cout << "| " << setw(15) << left << client.accountnumber;
	cout << "| " << setw(10) << left << client.pincode;
	cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
	cout << "| " << setw(12) << left << client.accountbalance;


}

void printclientrecordbalance(stclient client) {
   
    cout << left;
    
    cout << "|" << setw(15) << client.accountnumber;
    cout << "|" << setw(40) << client.name;
    cout << "|" << setw(12) << client.accountbalance;
}



void showallclientsScreen() {
    
    vector<stclient>vecstruct = loadclientdatafromfile("clientsfile.txt");
	
    cout << "\n\t\t\t\t\tclient list (" << vecstruct.size() << ")client(s)";
	cout <<
"\n_________________________________________________________ ";
	cout << "___________________________________________\n" << endl;
	cout << "| " << left << setw(15) <<  "accountnum";
	cout << "| " << left << setw(10) <<  "pincode";
	cout << "| " << left << setw(40) <<  "name";
    cout << "| " << left << setw(12) <<  "phone";
	cout << "| " << left << setw(12) <<  "acountbalance"   ;
	cout <<
"\n__________________________________________________________";
	cout << "__________________________________________\n" << endl;
	
    if (vecstruct.size() == 0) 
        cout << "no clients in the system. ";
    
    else
    for (stclient Client: vecstruct) 
	{
		printClientrecordline(Client);
		
		 cout << endl;
	}
	cout <<
"\n_________________________________________________________";
	cout << "___________________________________________\n" << endl;
	
}
void ptintclientcard(stclient client) {

    cout << "The client details:\n";

    cout << "Accountnumber:" << client.accountnumber ;
    cout << "\npincode:" << client.pincode ;
    cout << "\nName: " << client.name ;
    cout << "\nPhone number: " << client.phone ;
    cout << "\nAccountbalance: " << client.accountbalance << endl;
}

void showatotalbalances() {

    vector<stclient>vecstruct = loadclientdatafromfile(clientfilename);

    cout << "\t\t\tBalances list (" << vecstruct.size() << ") client(s).";
    cout << "\n"<<string(90,'=') << endl;
    cout << left;

    cout << "|" << setw(15) << "Acountnumber";
    cout << "|" << setw(40) << "Name";
    cout << "|" << setw(12) << "Accountbalance\n";

    cout << string(90, '=') << endl;

    double totalbalances = 0;

    if (vecstruct.size() == 0) {

        cout << "No clients available in the system\n";

    }
    else

        for (stclient client : vecstruct) {

            printclientrecordbalance(client);

            totalbalances += client.accountbalance;

            cout << endl;
        }
    cout << "\n" << string(90, '=') << endl;
        cout << "\t\t\t\t\tTotal balances = " << totalbalances;
}




bool findclientbyaccontnumber(string accountnumber, vector<stclient>vecstruct, stclient& client) {
     
    for (stclient& c : vecstruct) {

        if (c.accountnumber == accountnumber) {
            client = c;
            return true;


        }
}
    return false;
}
stclient changeclientrecordbyaccountnumber(string accountnumber) {

    stclient client;
    client.accountnumber = accountnumber;

    cout << "Enter the pincode: ";
    getline(cin >> ws, client.pincode);

    cout << "Enter the name: ";
    getline(cin>>ws, client.name);
   
    cout << "Enter the phone number: ";
  
    getline( cin>>ws , client.phone);

    cout << "Enter the account balance: ";
    
    cin >> client.accountbalance;

    return client;
}

bool markclientfordeletebyaccountnumber(string accountnumber, 
   
    vector<stclient>& vecstruct) {

    for (stclient& c : vecstruct) {

        if (c.accountnumber == accountnumber) {

            c.markfordelete = true;
           
            return true;


        }
    }
    return false;
 

}
vector<stclient>saveclientwithfalsetofil(string filename, 
    
    vector<stclient>vecstruct) {

    fstream myfile;
   
    myfile.open(filename, ios::out);
    
    string line;
   
    if (myfile.is_open()) {

        for (stclient c : vecstruct) {

            if (c.markfordelete == false) {

                line = converclienttoline(c);

                myfile << line << endl;
            }
        }

        myfile.close();


    }
return vecstruct;
}
void addclientDatalineTofile(string filename, string line) {
    
    fstream myfile;
   
    myfile.open(filename, ios::out | ios::app);

     
    if (myfile.is_open()) {
        myfile << line << endl;
        myfile.close();

    }
}

void addnewclient() {
    
    stclient client;

    client = ReadNewClient();

    addclientDatalineTofile(clientfilename, converclienttoline(client));
}

void addnewclients() {
    
    
    char addmore = 'Y';
    do
    {
        cout << "\nTo add new client: \n";
        addnewclient();
        cout << "The client added successfully. Do you want to add more? ";
        cin >> addmore;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (toupper(addmore == 'Y'));
}
     
bool deleteclientbyaccountnumber(string accountnumber, vector<stclient>& vecstruct) {
    stclient client;
    char answer = 'Y';
    if (findclientbyaccontnumber(accountnumber, vecstruct, client)) {
        cout << "The client by account number: \n";

        ptintclientcard(client);
        cout << "Are you sure you want to delete the client? 'Y'or 'N'?  ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (answer == 'Y' || answer == 'y') {

            markclientfordeletebyaccountnumber(accountnumber, vecstruct);

            saveclientwithfalsetofil(clientfilename, vecstruct);

            vecstruct = loadclientdatafromfile(clientfilename);
            cout << "Client deleted successfuly. ";

            return true;


        }

    }
    else {

        cout << "The client by account number "<<accountnumber<<" is not found.";
        return false;
    }
}

bool updateclientbyaccountnumber(string accountnumber, vector<stclient>& vecstruct) {
    
    stclient client;
   
    char answer = 'Y';
    
    if (findclientbyaccontnumber(accountnumber, vecstruct, client)) {

        cout << "\nThe client details:  \n";
        
        ptintclientcard(client);

        cout << "Are you sure you want to update the client? ";
        
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (answer == 'Y' || answer == 'y') {

          
            for (stclient& c : vecstruct) {

                if (c.accountnumber == accountnumber) {

                    c = changeclientrecordbyaccountnumber(accountnumber);
                    
                    cout << "Updated seccessfully.";
                      break;

                }

            }
         saveclientwithfalsetofil("clientsfile.txt", vecstruct);

            cout << "\nThe client updated successfully.";
          
           return true;


        }




    }
    else {
        cout << "the client is not found. ";
        
        return false;
    }
}

bool depositbalancebyaccountnumber(string accountnumber, vector<stclient>& vecstruct, double amount) {

    char answer = 'n';

    cout << "\nAre you sure you want to perform this transaction? ";
   
    cin >> answer;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (answer == 'y' || answer == 'Y')
    {
        for (stclient& c : vecstruct) {
             
            if (c.accountnumber == accountnumber) {

                c.accountbalance += amount;

                saveclientwithfalsetofil(clientfilename, vecstruct);

                cout << "\nDone successfully. The new balance is: " << 
                    
                 c.accountbalance;

                return true;

            }
        }
                          
        return false;
    }   
}





string readaccountnumber() {
    string accountnumber= "";
    cout << "\nEnter the account number: ";
    cin >> accountnumber;
    return accountnumber;
}

void showdeleteclientscreen() {

    cout << "\n_____________________________\n\n";
    cout << "Delete client screen";
 cout << "\n_____________________________\n";

    vector<stclient>vecstruct = loadclientdatafromfile(clientfilename);
    string accountnumber = readaccountnumber();
    deleteclientbyaccountnumber(accountnumber, vecstruct);
}


void showupdatescreen() {

    cout << "_____________________________\n";
    cout << "\nupdate client screen";
    cout << "\n_____________________________\n";

    vector<stclient>vecstruct = loadclientdatafromfile("clientsfile.txt");
   
          
          
    string accountnumber = readaccountnumber();

    updateclientbyaccountnumber(accountnumber, vecstruct);
}
void showaddnewclientscreen() {

    cout << "_____________________________\n";
   cout << "\nAdd new client screen";
    cout << "\n_____________________________\n";

    addnewclients();
    
}


void showfindclientscreen() {

    cout << "\n_____________________________\n";
    
    cout << "\t Find client screen";
    
    cout << "\n_____________________________\n";

    vector<stclient>vecstruct = loadclientdatafromfile("clientsfile.txt");
   
    stclient client;
    
   
    string accountnumber = readaccountnumber();
    
   
    if (findclientbyaccontnumber(accountnumber, vecstruct, client)) {
        
       ptintclientcard(client);

    }


    else
    {
       
    cout << "It's not found";

    }
}
void showendscreen() {

    cout << "\n_____________________________\n\n";
    
    cout << "\t Programm Ends :-)";
    
    cout << "\n_____________________________\n";
}

void showdepositScreen() {

    cout << string(40, '=') << endl;     
    
    cout << "\tDeposit screen: \n";
    
    cout << string(40, '=') << endl;

    stclient client;
        
     vector<stclient>vecstruct = loadclientdatafromfile("clientsfile.txt");

    string accountnumber = readaccountnumber();

    while (!findclientbyaccontnumber(accountnumber, vecstruct, client)) {

        cout << "It isn't exist. \n";

        accountnumber = readaccountnumber();
    }

    cout << "found\n";

    double amount = 0;

    cout << "please, enter deposit amount: \n";

    cin >> amount;

 depositbalancebyaccountnumber(accountnumber,vecstruct,amount);

}






void showwithdrawscreen() {

    cout << string(40, '=') << "\n";

    cout << "\tWithdraw screen:\n";

    cout << string(40, '=') << "\n";

    stclient client;

    vector<stclient>vecstruct = loadclientdatafromfile(clientfilename);

    string accountnumber = readaccountnumber();

    while (!findclientbyaccontnumber(accountnumber, vecstruct, client)) {

        cout << "It isn't exist. \n";

        accountnumber = readaccountnumber();

    }

    cout << "found\n";

    double amount = 0;

    cout << "please, enter withdraw amount: \n";

    cin >> amount;

    while (amount > client.accountbalance) {

        cout << "Amount exceeds the balance. You can withdraw to " << 
            
            client.accountbalance << endl;

      cout << "Please enter another amount: ";

      cin >> amount;
  }

   depositbalancebyaccountnumber(accountnumber,  vecstruct,amount * -1 );


}






void showtotalbalancescreen() {

    showatotalbalances();

}
enum  entransactionchoice {
   
    Deposit=1, Withdraw=2, totalbalances=3, mainmenue=4 };

enum enmainMenueOptions {
    
    enlistclients = 1, enaddnewclients = 2,
    
    enDeleteclient = 3, enupdateclient = 4,
    
    enfindclient = 5,etransactionmenue=6, enexit = 7
};
void gobacktomainmenue() {


    cout << "\nPress any key to go back to main menue ...";

    system("pause>0");   

    showmainmenue();
}

void gobacktotransactionmenue() {

    cout << "\nPress any key to go back to transaction menue ...";

    system("pause>0");   

    showtransactionsScreen();


}




short readtransactionchoice() {
    
    short transactionchoice;

    cout << "Enter your choice from (1  To 4): \n";

    cin >> transactionchoice;

    return   transactionchoice;
}



void performtransactionchoice(entransactionchoice transactionchoice) {

    switch (transactionchoice)
    {
    case  entransactionchoice::Deposit:

        system("cls");

        showdepositScreen();

        gobacktotransactionmenue();

        break;


    case  entransactionchoice::Withdraw:
        system("cls");
        showwithdrawscreen();
        gobacktotransactionmenue();
        break;


    case  entransactionchoice::totalbalances:

        system("cls");
        showtotalbalancescreen();
        gobacktotransactionmenue();
        break;
    case  entransactionchoice::mainmenue:
        system("cls");
        showmainmenue();

    default:
        break;
    }
}





void showtransactionsScreen() {
    system("cls");
    
    cout << "\n"<<string(50, '=') << endl;
    cout << "\t\tShow transaction screen\n";
    cout << string(50, '=') << endl;
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Total Balances\n";
    cout << "\t[4] Main Menue\n";
    cout << string(50, '=') << endl; 

    performtransactionchoice((entransactionchoice)readtransactionchoice());

}


short readmainmenueoption() {
    
    short choice;
    
    cout << "Show what do you want to do? [1 to 7]? ";
   
    cin >> choice;
  
    return choice;
}



void performMainMenueoption(enmainMenueOptions mainMenueOptions) {

    switch (mainMenueOptions)
    {
    case enmainMenueOptions::enlistclients:

        system("cls");     

        showallclientsScreen();

        gobacktomainmenue();

        break;
    case enmainMenueOptions::enaddnewclients:
        system("cls");

        showaddnewclientscreen();

        gobacktomainmenue();

        break;
    case enmainMenueOptions::enDeleteclient:
        system("cls");

        showdeleteclientscreen();


        gobacktomainmenue();

        break;
    case enmainMenueOptions::enupdateclient:
        system("cls");

        showupdatescreen();


        gobacktomainmenue();


        break;
    
     case enmainMenueOptions::enfindclient:

        system("cls");

        showfindclientscreen();

        gobacktomainmenue();

        break;

     case enmainMenueOptions:: etransactionmenue:
         
         system("cls");
         
         showtransactionsScreen();
         break;
     
     case enmainMenueOptions::enexit:

        system("cls");

        showendscreen();

        break;

    }
}




void showmainmenue() {

    system("cls");

    cout << string(40, '=') << endl;
    cout << "\t\tMain Menue Screen\n";
    cout << string(40, '=') << endl;
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";


    cout << string(40, '=') << endl;

    performMainMenueoption((enmainMenueOptions)readmainmenueoption());


}


int main()
{
    
   showmainmenue();
   

    
   
   






        


  

   

  

    
    
    
    
    
    
 
    return 0;
}



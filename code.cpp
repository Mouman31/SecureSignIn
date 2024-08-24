#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

using namespace std;

class SecureSignIn
{
    private:
        string Username;   //Data members
        string Password;
        string EmailID;
        string Name;
        string DOB;
    public:
        SecureSignIn():Username(""),Password(""),EmailID(""),Name(""),DOB(""){}
        //Member functions
        void setUN(string un){     //Function to store the value of the username
            Username = un;
        }
        void setPW(string pw){     //Function to store the value of the password
            Password = pw;
        }
        void setEI(string ei){     //Function to store the value of the email id
            EmailID = ei;
        }
        void setNM(string nm){     //Function to store the value of the name
            Name = nm;
        }
        void setDB(string db){     //Function to store the value of the date of birth
            DOB = db;
        }

        string getUN(){            //Functions to retrieve the values of the username, password, email id, name and date of birth respectively
            return Username;
        }
        string getPW(){
            return Password;
        }
        string getEI(){
            return EmailID;
        }
        string getNM(){
            return Name;
        }
        string getDB(){
            return DOB;
        }
};

 void signup(SecureSignIn log)   //Function used for sign up process
{

    system("cls");
    string un,pw,ei,nm,db,pw1;
    cout<<"\tEnter username: ";  //Username input
    cin>>un;
    log.setUN(un);

    bool pass_word=false;
    vector<string> errorMessages;
    try
    {
    while (!pass_word) //Code block for password validation
    {
            regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[-+_!@#$%^&*.,?]).+$");
            cout << "\tEnter password: ";
            cin >> pw;


                bool hasUppercase = regex_search(pw, regex("[A-Z]"));
                bool hasSpecialChar = regex_search(pw, regex("[-+_!@#$%^&*.,?]"));
                bool hasNumeric = regex_search(pw, regex("\\d"));

                if (!hasUppercase)
                {
                    errorMessages.push_back("\tThe password must contain at least one uppercase letter.");
                }

                if (!hasSpecialChar)
                {
                    errorMessages.push_back("\tThe password must contain at least one special character.");
                }

                if (!hasNumeric)
                {
                    errorMessages.push_back("\tThe password must contain at least one numeric character.");
                }
                if(!(pw.length() >= 8 && pw.length() <= 16))
                    {
                errorMessages.push_back("\tThe password should be 8-16 characters.");
                    }
             if (errorMessages.empty())  // No errors, set the password
                {
                    log.setPW(pw);
                    pass_word = true;
                }
                else
                {
                    // Display all accumulated error messages
                    for (const string &errorMsg : errorMessages)
                    {
                        cerr << errorMsg << endl;
                    }
                    errorMessages.clear();  // Clear the vector for the next attempt
                }
        }


    start1:
        cout<<"\tRe-enter the password: "; //Code block to check the correctness of the password
        cin>>pw1;
        if(pw==pw1){
            cout<<"\tThe password matches!!"<<endl;
            cout<<"\tPlease Wait";
            for(int i=0; i<3; i++){
                    cout<<".";
                    Sleep(800);
                    }
        }
        else{
            cout<<"\tThe password does not match"<<endl;
            goto start1;
        }

    system("cls");
    cout<<"\tPlease enter the following details"<<endl; //Input details such email,name and dob
    cout<<"\tEnter email id: ";
    cin>>ei;
    log.setEI(ei);
    cout<<"\tEnter name: ";
    cin>>nm;
    log.setNM(nm);
    cout<<"\tEnter date of birth: ";
    cin>>db;
    log.setDB(db);
    ofstream outfile("C:/Users/Manaswini/OneDrive/Desktop/PROJECTS/SecureSignIn/SecureSignIn.txt", ios::app);
    if(!outfile){
            throw runtime_error("\tError: File Can't Open!");
    }
    else{
            outfile<<"\t"<<log.getUN()<<" : "<<log.getPW()<<" : "<<log.getEI()<<" : "<<log.getNM()<<" : "<<log.getDB()<<endl<<endl;//Writing the above mentioned details into the file
            system("cls");
            cout<<"\tUser signed up successfully!"<<endl;
        }
    }
    catch(const exception &e)
    {
        cerr<<e.what()<<endl;
    }
    Sleep(2000);
}

void signin() //Function for sign in process
{
    try{
    start2:
    system("cls");
    string us, pw;
    cout<<"\tEnter username: ";
    cin>>us;
    cout<<"\tEnter password: ";
    cin>>pw;
    ifstream infile("C:/Users/Manaswini/OneDrive/Desktop/PROJECTS/SecureSignIn/SecureSignIn.txt");//Reading the file
    if(!infile){
            throw runtime_error("\tError: File Can't Open!");
    }
    else{
            string line;
            bool found = false;
            while(getline(infile,line)){ //Access one line at once from the text document
                    stringstream ss;     //stringstream ss to transfer the string obtained in the file to a variable
                    ss<<line;
                    string userID, userPW;
                    char delimiter; //delimiter = ':'
                    ss>>userID>>delimiter>>userPW>>delimiter;//Passing the data from ss to variables userID and userPW
                    if(us==userID && pw==userPW){ //Checking against the inputs given by the user
                            found = true;
                            cout<<"\tPlease Wait";
                            for(int i=0; i<3; i++){
                                    cout<<".";
                                    Sleep(800);
                                    }
                            system("cls");
                            cout<<"\tUser signed in successfully!"<<endl;
                            }
                    }
            if(!found){
                    cout<<"\tIncorrect username or password!"<<endl; //If the inputs given by the user are incorrect
                    cout<<"\tIf you are a new user press 1 to go back to the home page otherwise press 2 to continue sign-up"<<endl;
                    int value;
                    cin>>value;
                    if(value==1){
                        Sleep(800);
                    }
                    else{
                    goto start2;
                    }
            }
    }
    infile.close();
    Sleep(2000);
    }
    catch(const exception &e){
    cerr<<e.what()<<endl;
    }
}

int main()
{
SecureSignIn log; //Object creation

bool exit = false;
while(!exit){
system("cls");
int val;
cout<<"\tWelcome to the page!!"<<endl;
cout<<"\t************************************"<<endl; //Choices given to the user, whether they would like to sign-up, sign-in or exit
cout<<"\t1.Sign-up."<<endl;
cout<<"\t2.Sign-in."<<endl;
cout<<"\t3.Exit."<<endl;
cout<<"\tEnter Choice: ";
cin>>val;

if(val==1){
        signup(log);
        }

else if(val==2){
        signin();
        }

else if(val==3){
system("cls");
exit = true;
cout<<"\tPlease visit the page again!"<<endl;
Sleep(1000);
}
Sleep(1000);
}
}


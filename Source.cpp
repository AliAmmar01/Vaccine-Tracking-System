#include <iostream>
#include <fstream>  //This means it can create files, write/read data to/from files.
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <regex>
#include <stack>
#include <conio.h>  // for getch() fn

using namespace std;

#define ALL_RECORDS_TEXT_FILE_PATH "C:\\Users\\Ali Ammar\\source\\repos\\VTS\\MapRecord.csv"
#define Waitinglist_TEXT_FILE_PATH "C:\\Users\\Ali Ammar\\source\\repos\\VTS\\Waitinglist.csv"

class UserRecord{

    public:
        string FullName;
        long long NationalID = 0;    //To accept 13 digits
        string Pswd;
        string Gender;
        int Age = 0;
        string Governorate;
        int DosesReceived = 0;
};

ostream& operator<<(ostream& os, const UserRecord& UR)
{
    os << "National ID:\t\t" << "Full Name:\t\t" << "Gender:\t\t" << "Age:\t\t" << "Governorate:\t\t" << "Number Of Doses Received:\n";
    os << UR.NationalID << "\t\t" << UR.FullName << "\t\t" << UR.Gender << "\t\t" << UR.Age << "\t\t" << UR.Governorate << "\t\t\t" << UR.DosesReceived << endl;
    return os;
}

int NameFlag, GovFlag, PswdFlag = 0;
vector<UserRecord> WaitingList;
map<long long, UserRecord> Records;
vector<string> Gov = { "Alexandria", "Aswan", "Asyut", "Beheira", "Beni Suef", "Cairo", "Dakahlia", "Damietta", "Faiyum", "Gharbia", "Giza", "Ismailia", "Kafr El Sheikh", "Luxor", "Matruh", "Minya", "Monufia", "New Valley", "North Sinai", "Port Said", "Qalyubia", "Qena", "Red Sea", "Sharqia", "Sohag", "South Sinai", "Suez", "alexandria", "aswan", "asyut", "beheira", "beni suef", "cairo", "dakahlia", "damietta", "faiyum", "gharbia", "giza", "ismailia", "kafr el sheikh", "luxor", "matruh", "minya", "monufia", "new valley", "north sinai", "port said", "qalyubia", "qena", "red sea", "sharqia", "sohag", "south sinai", "suez" };

void WriteToTextFile()      
{
    ofstream MyFile;
    try {
        MyFile.open(ALL_RECORDS_TEXT_FILE_PATH, ios::out);
        if (MyFile.is_open())
        {
            for (auto it = Records.begin(); it != Records.end(); it++)
            {
                MyFile << it->second.FullName << ",";
                MyFile << it->second.NationalID << ",";
                MyFile << it->second.Pswd << ",";
                MyFile << it->second.Gender << ",";
                MyFile << it->second.Age << ",";
                MyFile << it->second.Governorate << ",";
                MyFile << it->second.DosesReceived << endl;
            }
        }
        MyFile.close();
    }
    catch (exception e)
    {
        cout << "Could Not Open File! " << e.what() << endl;
    }
    try {
        MyFile.open(Waitinglist_TEXT_FILE_PATH, ios::out);
        if (MyFile.is_open())
        {
            for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
            {
                MyFile << it->FullName << ",";
                MyFile << it->NationalID << ",";
                MyFile << it->Pswd << ",";
                MyFile << it->Gender << ",";
                MyFile << it->Age << ",";
                MyFile << it->Governorate << ",";
                MyFile << it->DosesReceived << endl;
            }
        }
        MyFile.close();
    }
    catch (exception e)
    {
        cout << "Could Not Open File! " << e.what() << endl;
    }
}

void ReadFromTextFile()     
{
    ifstream MyFile;
    try {
        MyFile.open(ALL_RECORDS_TEXT_FILE_PATH);
        if (MyFile.is_open())
        {
            string Line;
            long long Key;
            UserRecord Value;
            string MyCut;
            while (getline(MyFile, Line))
            {
                int pos = 0;
                while (pos != -1)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        pos = Line.find(",");   //finds the position of the first "," and stores it in pos
                        MyCut = Line.substr(0, pos);    //splits Line on pos and stores it in MyCut
                        if (i == 0)
                        {
                            Value.FullName = MyCut;     //on first iteration MyCut contains FullName as a string and it adds it to Value.FullName
                        }
                        if (i == 1)
                        {
                            Value.NationalID = stoll(MyCut);    //on second iteration MyCut contains NationalID as a string, stoll converts the string to long long and it adds it to Value.NationalID
                            Key = stoll(MyCut);     //MyCut contains NationalID as a string, stoll converts the string to long long and it adds it to Key used later in adding records to Records map
                        }
                        if (i == 2)
                        {
                            Value.Pswd = MyCut;     //on third iteration MyCut contains Pswd as a string and it adds it to Value.Pswd
                        }
                        if (i == 3)
                        {
                            Value.Gender = MyCut;   //on fourth iteration MyCut contains Gender as a string and it adds it to Value.Gender
                        }
                        if (i == 4)
                        {
                            Value.Age = stoi(MyCut);    //on fifth iteration MyCut contains Age as a string, stoi converts the string to int and it adds it to Value.Age
                        }
                        if (i == 5)
                        {
                            Value.Governorate = MyCut;      //on sixth iteration MyCut contains Governorate as a string and it adds it to Value.Governorate
                        }
                        if (i == 6)
                        {
                            Value.DosesReceived = stoi(MyCut);      //on seventh iteration MyCut contains DosesReceived as a string, stoi converts the string to int and it adds it to Value.DosesReceived
                        }
                        Line = Line.substr(pos + 1);
                    }
                    Records[Key] = Value;   //adds UserRecord Value into Records map @ Key
                }
            }
        }
        MyFile.close();
    }
    catch (exception e)
    {
        cout << "Could Not Open File! " << e.what() << endl;
    }
    try {
        MyFile.open(Waitinglist_TEXT_FILE_PATH);
        if (MyFile.is_open())
        {
            string Line;
            UserRecord Value;
            string MyCut;
            while (getline(MyFile, Line))
            {
                int pos = 0;
                while (pos != -1)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        pos = Line.find(",");   //finds the position of the first "," and stores it in pos
                        MyCut = Line.substr(0, pos);    //splits Line on pos and stores it in MyCut
                        if (i == 0)
                        {
                            Value.FullName = MyCut;     //on first iteration MyCut contains FullName as a string and it adds it to Value.FullName
                        }
                        if (i == 1)
                        {
                            Value.NationalID = stoll(MyCut);    //on second iteration MyCut contains NationalID as a string, stoll converts the string to long long and it adds it to Value.NationalID
                        }
                        if (i == 2)
                        {
                            Value.Pswd = MyCut;     //on third iteration MyCut contains Pswd as a string and it adds it to Value.Pswd
                        }
                        if (i == 3)
                        {
                            Value.Gender = MyCut;   //on fourth iteration MyCut contains Gender as a string and it adds it to Value.Gender
                        }
                        if (i == 4)
                        {
                            Value.Age = stoi(MyCut);    //on fifth iteration MyCut contains Age as a string, stoi converts the string to int and it adds it to Value.Age
                        }
                        if (i == 5)
                        {
                            Value.Governorate = MyCut;      //on sixth iteration MyCut contains Governorate as a string and it adds it to Value.Governorate
                        }
                        if (i == 6)
                        {
                            Value.DosesReceived = stoi(MyCut);      //on seventh iteration MyCut contains DosesReceived as a string, stoi converts the string to int and it adds it to Value.DosesReceived
                        }

                        Line = Line.substr(pos + 1);
                    }
                    WaitingList.push_back(Value);   //adds UserRecord Value into Waitinglist
                }
            }
        }
        MyFile.close();
    }
    catch (exception e)
    {
        cout << "Could Not Open File! " << e.what() << endl;
    }
}


void MaskingPswd(string& Pswd)  
{
    // Masking the password input as asterisks
    char c;
    while ((c = _getch()) != '\r')
    {  // '\r' is the Enter key
        if (c == '\b')
        {  // '\b' is the Backspace key
            if (!Pswd.empty())
            {
                Pswd.pop_back();
                cout << "\b \b";    // erase the asterisk and move the cursor back
            }
        }
        else
        {
            Pswd.push_back(c);
            cout << "*";       // print an asterisk instead of the actual character
        }
    }
    if (Pswd.length() > 8)
    {
        Pswd.erase(Pswd.begin(), Pswd.begin() + 8);
    }
    cout << endl;
}

void MainMenu()  
{
    cout << "1. Add Personal Record.\n";
    cout << "2. Sign In As User.\n";
    cout << "3. Sign In As Admin.\n";
    cout << "4. Exit.\n";
    cout << "Please Enter Your Choice: ";
}

// User Functions

void AddRecord()  
{
    UserRecord NewRecord, TestRecord;
    bool GovFound = false;
    while (true) {      //FullName Validation using regex library
        cout << "Please Enter Your Full Name: \n";
        if (NameFlag == 0) { cin.ignore(); }   // clear any previous input from the buffer 
        getline(cin, (TestRecord.FullName));
        regex name_regex("^[a-zA-Z]+([ ]{1}[a-zA-Z]+){2}$");   // First Name, Middle Name and Last Name are required
        if (regex_match(TestRecord.FullName, name_regex))
        {
            NewRecord.FullName = TestRecord.FullName;
            break;
        }
        else
        {
            NameFlag++;
            cout << "Full Name Is Invalid! Please Try Again." << endl;

        }
    }

    while (true) {      //National Id Validation
        cout << "Please enter your national ID (should be 13 numbers): \n";
        bool found = false;
        cin >> TestRecord.NationalID;
        if (TestRecord.NationalID >= 1000000000000 && TestRecord.NationalID <= 9999999999999)
        {
            for (auto it = Records.begin(); it != Records.end(); it++)
            {
                if (it->second.NationalID == TestRecord.NationalID)
                {
                    found = true;
                    break;
                }
            }
            if (found == true)
            {
                cout << "This ID Is Already Registered!\n";
                continue;
            }else
            {
                NewRecord.NationalID = TestRecord.NationalID;
                break;
            }
            
        }
        else
        {
            cout << "Invalid National ID! Please try again.\n";
        }
    }
    
    while (true) {  //Pswd Validation
        cout << "Please Enter Your Password (8 characters: At least 1 letter,At least 1 digit, At least 1 special): \n";
        // Masking the password input as asterisks
        MaskingPswd(TestRecord.Pswd);
        regex pswd_regex("^(?=.*[a-zA-Z])(?=.*\\d)(?=.*[!@#$%^&])[a-zA-Z\\d!@#$%^&]{8}$");  //Exactly 8 characters long, At least 1 letter(uppercase or lowercase), At least 1 digit, At least 1 special character(!@#$%^&)
        if (regex_match(TestRecord.Pswd, pswd_regex))
        {
            cout << "Strong Password!\n";
            NewRecord.Pswd = TestRecord.Pswd;
            break;
        }
        else {
            cout << "Weak Password! Please Try Again.\n";
        }
    }

    while (true) {      //Gender Validation
        cout << "Please Enter Your Gender(F/M): \n";
        cin >> TestRecord.Gender;
        if (TestRecord.Gender == "M" || TestRecord.Gender == "m" || TestRecord.Gender == "F" || TestRecord.Gender == "f")
        {
            NewRecord.Gender = TestRecord.Gender;
            break;
        }
        else {
            cout << "Invalid Gender! Please try again.\n";
        }
    }

    while (true) {     //Age Validation
        cout << "Please Enter Your Age: \n";
        cin >> TestRecord.Age;
        if (TestRecord.Age <= 120 && TestRecord.Age > 0)
        {
            NewRecord.Age = TestRecord.Age;
            break;
        }
        else {
            cout << "Invalid Age! Please try again.\n";
        }
    }

    while (true) {      //Governorate Validation using Gov vector containing Egyptian Governorates
        cout << "Please Enter Your Governorate: \n";
        if (GovFlag == 0) { cin.ignore(); }     // clear any previous input from the buffer 
        getline(cin, (TestRecord.Governorate));
        for (string gov : Gov)       // Iterate over the vector and compare each element with the input string
        {
            if (TestRecord.Governorate == gov)
            {
                GovFound = true;
                break;    // Exit for loop
            }
        }
        if (GovFound == true)
        {
            NewRecord.Governorate = TestRecord.Governorate;
            break;       // Exit while loop
        }
        else if (GovFound == false)
        {
            GovFlag++;
            cout << "Please Enter An Egyptian Governorate!\n";
        }
    }
    while (true) {      //DosesReceived Validation
        cout << "How Many Doses Have You Received? (0/1/2)\n";
        cin >> TestRecord.DosesReceived;
        if (TestRecord.DosesReceived == 0) // 0 DosesReceived --> Record is added to WaitingList queue and Records map
        {
            NewRecord.DosesReceived = 0;
            WaitingList.push_back(NewRecord);
            Records.insert(pair<long long, UserRecord>(NewRecord.NationalID, NewRecord));
            cout << "Your Record Has Been Added To User Records And To Waiting List Successfully! \n";
            break;
        }
        else if (TestRecord.DosesReceived == 1 || TestRecord.DosesReceived == 2) // 1 | 2 DosesReceived --> Record is added Records map only
        {
            NewRecord.DosesReceived = TestRecord.DosesReceived;
            Records.insert(pair<long long, UserRecord>(NewRecord.NationalID, NewRecord));
            cout << "Your Record Has Been Added Successfully!\n";
            break;
        }
        else {
            cout << "Invalid Number of Doses! Please Try Again. \n";
        }
    }
}

//Logged In User Functions

void DisplayRecord(long long Id)   
{
    bool found = false;
    for (auto it = Records.begin(); it != Records.end(); it++)
    {
        if (Id == it->first)
        {
            found = true;
            cout << it->second << endl;
            break;
        }
    }
    if (found == false)
    {
        cout << "The ID you entered was not found. Make Sure That It Is correct.\n";
    }
}

void EditRecord(long long ID)      
{
    UserRecord TestRecord;
    bool GovFound = false, exit = false;
    int EditChoice;
    while (true)
    {
        cout << "1. To Edit Your Full Name.\n2. To Edit Your Password.\n3. To Edit Your Age.\n4. To Edit Your Governorate.\n5. To Edit Your Doses Received.\nAny Other Number To Exit.\n Enter Your Choice: ";
        cin >> EditChoice;
        switch (EditChoice)
        {
        case 1:
            while (true)    //FullName Validation using regex library
            {      
                cout << "Please Enter Your Full Name: \n";
                if (NameFlag == 0) { cin.ignore(); }   // clear any previous input from the buffer 
                getline(cin, (TestRecord.FullName));
                regex name_regex("^[a-zA-Z]+([ ]{1}[a-zA-Z]+){2}$");   // First Name, Middle Name and Last Name are required
                if (regex_match(TestRecord.FullName, name_regex))
                {
                    if (Records.find(ID)->second.DosesReceived == 0)
                    {
                        for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
                        {
                            if (it->NationalID == ID)
                            {
                                it->FullName = TestRecord.FullName;
                                break;
                            }
                        }
                    }
                    Records.find(ID)->second.FullName = TestRecord.FullName;
                    break;
                }
                else
                {
                    NameFlag++;
                    cout << "Full Name Is Invalid! Please Try Again." << endl;
                }
            }
            cout << "Your Full Name Has Been Updated!\n";
            break;
        case 2:
            while (true) {  //Pswd Validation
                cout << "Please Enter Your Password (Exactly 8 characters: At least 1 letter,At least 1 digit, At least 1 special): \n";
                MaskingPswd(TestRecord.Pswd);
                regex pswd_regex("(?=.*[a-zA-Z])(?=.*\\d)(?=.*[!@#$%^&*])[A-Za-z\\d!@#$%^&*]{8}");  //Exactly 8 characters long, At least 1 letter(uppercase or lowercase), At least 1 digit, At least 1 special character(!@#$%^&*)
                if (regex_match(TestRecord.Pswd, pswd_regex))
                {
                    cout << "Strong Password!\n";
                    Records.find(ID)->second.Pswd = TestRecord.Pswd;
                    if (Records.find(ID)->second.DosesReceived == 0)
                    {
                        for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
                        {
                            if (it->NationalID == ID)
                            {
                                it->Pswd = TestRecord.Pswd;
                                break;
                            }
                        }
                    }
                    break;
                }
                else {
                    PswdFlag++;
                    cout << "Weak Password! Please Try Again.\n";
                }
            }
            cout << "Your Password Has Been Updated!\n";
            break;
        case 3:
            while (true) {   //Age Validation
                cout << "Please Enter Your Age: \n";
                cin >> TestRecord.Age;
                if (TestRecord.Age <= 120 && TestRecord.Age > 0)
                {
                    Records.find(ID)->second.Age = TestRecord.Age;
                    if (Records.find(ID)->second.DosesReceived == 0)
                    {
                        for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
                        {
                            if (it->NationalID == ID)
                            {
                                it->Age = TestRecord.Age;
                                break;
                            }
                        }
                    }                    
                    break;
                }
                else {
                    cout << "Invalid Age! Please try again.\n";
                }
            }
            cout << "Your Age Has Been Updated!\n";
            break;
        case 4:
            while (true) {      //Governorate Validation using Gov vector containing Egyptian Governorates
                cout << "Please Enter Your Governorate: \n";
                if (GovFlag == 0) { cin.ignore(); }     // clear any previous input from the buffer 
                getline(cin, (TestRecord.Governorate));
                for (string gov : Gov)       // Iterate over the vector and compare each element with the input string
                {
                    if (TestRecord.Governorate == gov)
                    {
                        GovFound = true;
                        break;    // Exit for loop
                    }
                }
                if (GovFound == true)
                {
                    Records.find(ID)->second.Governorate = TestRecord.Governorate;
                    if (Records.find(ID)->second.DosesReceived == 0)
                    {
                        for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
                        {
                            if (it->NationalID == ID)
                            {
                                it->Governorate = TestRecord.Governorate;
                                break;
                            }
                        }
                    }
                    break;       // Exit while loop
                }
                else if (GovFound == false)
                {
                    GovFlag++;
                    cout << "Please Enter An Egyptian Governorate!\n";
                }
            }
            cout << "Your Governorate Has Been Updated!\n";
            break;
        case 5:
            while (true) {      //DosesReceived Validation
                if (Records.find(ID)->second.DosesReceived == 2) { 
                    cout << "You cannot edit the number of doses received as you already have received 2 doses!\n";
                    break;
                }
                cout << "How Many Doses Have You Received? (0/1/2)\n";
                cin >> TestRecord.DosesReceived;
                if (TestRecord.DosesReceived == 0 || TestRecord.DosesReceived == 1 || TestRecord.DosesReceived == 2)
                {
                    if (Records.find(ID)->second.DosesReceived < TestRecord.DosesReceived)
                    {
                        if (Records.find(ID)->second.DosesReceived == 0 && (TestRecord.DosesReceived == 1 || TestRecord.DosesReceived == 2))
                        {
                            int pos = 0;
                            for (auto it = WaitingList.begin(); it != WaitingList.end(); it++)
                            {
                                if (it->NationalID == ID)
                                {
                                    WaitingList.erase(it);
                                    break;
                                }
                                pos++;
                            }
                        }
                        Records.find(ID)->second.DosesReceived = TestRecord.DosesReceived;
                    }
                    break;
                }
                else {
                    cout << "Invalid Number of Doses! Please Try Again. \n";
                }
            }
            cout << "Your Doses Received Has Been Updated!\n";
            break;
        default:
            exit = true;
            break;
        }
        if (exit == true)
        {
            break;
        }
    }
}

void DeleteRecord(long long ID)       
{
    int pos = 0;
    for (auto it =  WaitingList.begin(); it != WaitingList.end(); it++)
    {
        if (WaitingList.at(pos).NationalID == ID)
        {
            WaitingList.erase(it);
            break;
        }
        pos++;
    }
    Records.erase(ID);
    cout << "Your Record Has Been Deleted.\n";
}

//Admin Functions

void AdminMenu()        
{
    cout << "********************* Admin cannot edit or update any record **************** \n";
    cout << "1. View all or any record(s) by entering only the National ID.\n";
    cout << "2. Delete all or any record(s) by entering only the National ID.\n";
    cout << "3. View records filtered by the number of doses (1 dose or 2 doses).\n";
    cout << "4. View records of vaccinated users ordered by the age of the user.\n";
    cout << "5. View the waiting list.\n";
    cout << "6. View Basic statistics.\n";
    cout << "7. View Advanced Statistics.\n";
    cout << "Any Other Number To Exit.\n";
}

void Display()  
{
    while (true)
    {
        int DisplayChoice = 0;
        bool exit = false;
        cout << "1. Display All.\n2. Display A Specific Record.\nAny Other Number to Exit.\nEnter your choice: ";
        cin >> DisplayChoice;
        switch (DisplayChoice)
        {
        case 1:
            for (auto it = Records.begin(); it != Records.end(); it++)
            {
                cout << "\n" << it->second << endl;
            }
            break;
        case 2:
            long long ID;
            cout << "Enter The ID of the Record You Wish To Display: ";
            cin >> ID;
            if (ID >= 1000000000000 && ID <= 9999999999999)
            {
                DisplayRecord(ID);
            }
            else
            {
                cout << "Invalid National ID!\n";
            }
            break;
        default:
            exit = true;
            break;
        }
        if (exit == true)
        {
            break;
        }
    }
}

void Delete()   
{
    while (true)
    {
        int DeleteChoice = 0;
        bool exit = false;
        cout << "1. Delete All.\n2. Delete A Specific Record.\nAny Other Number to Exit.\nEnter your choice: ";
        cin >> DeleteChoice;
        switch (DeleteChoice)
        {
        case 1:
            Records.clear();
            cout << "All records have been deleted.\n";
            break;
        case 2:
            long long ID;
            cout << "Enter The ID of the Record You Wish To Delete: ";
            cin >> ID;
            if (ID >= 1000000000000 && ID <= 9999999999999)
            {
                DeleteRecord(ID);
            }
            else
            {
                cout << "Invalid National ID!\n";
            }
            break;
        default:
            exit = true;
            break;
        }
        if (exit == true)
        {
            break;
        }
    }
}

void FilterByDoseNumber()   
{
    while (true)
    {
        int FilterChoice = 0;
        bool exit = false;
        cout << "1. To Display Users Who Received 1 Dose.\n2. To Display Users Who Received 2 Doses.\nAny Other Number To Exit.\nEnter Your Choice: ";
        cin >> FilterChoice;
        if (FilterChoice != 2 && FilterChoice != 1)
        {
            exit = true;
        }
        else
        {
            for (auto it = Records.begin(); it != Records.end(); it++)
            {

                if (it->second.DosesReceived == FilterChoice)
                {
                    cout << it->second << endl;
                }
            }
        }
        if (exit == true)
        {
            break;
        }
    }
}

void SortByAge()    
{
    // Copy Records into a temporary vector to allow sorting
    vector<UserRecord> temp;
    for (auto it = Records.begin(); it != Records.end(); it++)
    {
        temp.push_back(it->second);
    }

    // Sort the temporary vector by age
    sort(temp.begin(), temp.end(), [](const UserRecord& a, const UserRecord& b){ return a.Age < b.Age; });

    while (true)
    {
        int SortChoice = 0;
        bool exit = false;
        queue<UserRecord> SortYoungestToOldestQueue;
        stack<UserRecord> SortOldestToYoungestStack;
        for (auto it = temp.begin(); it != temp.end(); it++)
        {
            SortYoungestToOldestQueue.push(*it);
            SortOldestToYoungestStack.push(*it);
        }
        cout << "1. To Sort From Youngest To Oldest.\n2. To Sort From Oldest To Youngest.\nAny Other Number To Exit.\nEnter Your Choice: ";
        cin >> SortChoice;
        switch (SortChoice)
        {
        case 1:
            // Print sorted elements from youngest to oldest using a queue
            
            while (!SortYoungestToOldestQueue.empty())
            {
                cout << SortYoungestToOldestQueue.front() << endl;
                SortYoungestToOldestQueue.pop();
            }
            break;
        case 2:
            // Print sorted elements from oldest to youngest using a stack
            
            while (!SortOldestToYoungestStack.empty())
            {
                cout << SortOldestToYoungestStack.top() << endl;
                SortOldestToYoungestStack.pop();
            }
            break;
        default:
            exit = true;
            break;
        }
        if (exit == true)
        {
            break;
        }
    }
}

void DisplayWaitingList()       
{
    cout << "\t\t\t\t\******************** Waiting List *************************\n";
    for (int i = 0; i < WaitingList.size(); i++) 
    {
        cout << WaitingList[i] << endl;
    }
}

void ViewBasicStatistics()      
{
    int totalReceivedFirstDose = 0;
    int totalReceivedBothDoses = 0;
    int totalFemales = 0;

    for (auto it = Records.begin(); it != Records.end(); it++)
    {
        if (it->second.DosesReceived == 1) // Check if registered user has been vaccinated
        {
            totalReceivedFirstDose++; // Increment counter for people who have received the first dose
        }

        if (it->second.DosesReceived == 2)
        {
            totalReceivedBothDoses++; // Increment counter for people who have received both doses
        }


        if (it->second.Gender == "F" || it->second.Gender == "f") // Check gender of registered user
        {
            totalFemales++; // Increment counter for females
        }
    }

    cout << "Percentage of people registered in the system who aren't vaccinated: " << (float)((WaitingList.size() * 100.0) / Records.size()) << "%" << endl;
    cout << "Percentage of people registered in the system who have received the first dose: " << (float)((totalReceivedFirstDose * 100.0) / Records.size()) << "%" << endl;
    cout << "Percentage of people registered in the system who have received both doses: " << (float)((totalReceivedBothDoses * 100.0) / Records.size()) << "%" << endl;
    cout << "Percentage of females registered in the system: " << (float)((totalFemales * 100.0) / Records.size()) << "%" << endl;
    cout << "Percentage of males registered in the system: " << (float)(((Records.size() - totalFemales) * 100.0) / Records.size()) << "%" << endl << endl;
}

void GovernorateInfo()  
{
    do
    {
        bool GovFound = false;
        char exit;
        int Counter = 0, MaleCounter = 0, VaccinatedCounter = 0;
        string Governorate, Gover;
        cout << "Enter The Governorate: ";
        if (GovFlag == 0) { cin.ignore(); }     // clear any previous input from the buffer 
        getline(cin, (Governorate));
        for (auto i = 0; i < Gov.size() / 2; i++)       // Iterate over the vector and compare each element with the input string
        {
            if (Governorate == Gov[i] || Governorate == Gov[i + Gov.size() / 2])
            {
                GovFound = true;
            }
            if (GovFound == true)
            {
                for (auto it = Records.begin(); it != Records.end(); it++)
                {
                    if (it->second.Governorate == Gov[i] || it->second.Governorate == Gov[i + Gov.size() / 2])
                    {
                        Counter++;
                        if (it->second.Gender == "M" || it->second.Gender == "m")
                        {
                            MaleCounter++;
                        }
                        if (it->second.DosesReceived == 1 || it->second.DosesReceived == 2)
                        {
                            VaccinatedCounter++;
                        }
                        cout << it->second;
                    }
                }
                cout << "\nPercentage of people registered in the system who are from " << Gov[i] << ": " << (float)((Counter * 100.0) / Records.size()) << "%" << endl;
                cout << "\nPercentage of Males registered in the system who are from " << Gov[i] << ": " << (float)((MaleCounter * 100.0) / Counter) << "%" << endl;
                cout << "\nPercentage of Females registered in the system who are from " << Gov[i] << ": " << (float)(((Counter - MaleCounter) * 100.0) / Counter) << "%" << endl;
                cout << "\nPercentage of Vaccinated people registered in the system who are from " << Gov[i] << ": " << (float)((VaccinatedCounter * 100.0) / Counter) << "%" << endl;
                cout << "\nPercentage of Unvaccinated people registered in the system who are from " << Gov[i] << ": " << (float)(((Counter-VaccinatedCounter) * 100.0) / Counter) << "%" << endl;
                break;       // Exit for loop
            }
        }
        if (GovFound == false)
        {
            GovFlag++;
            Counter = 0;
            cout << "Please Enter An Egyptian Governorate!\n";
            continue;
        }
        cout << "Do You Want To Exit? (Y To Exit/Any Other Character To Proceed): ";
        cin >> exit;
        if (exit == 'y' || exit == 'Y')
        {
            break;
        }
    }while(true);
}

void AgeGroupInfo() 
{
    do
    {
        int MinAge, MaxAge, Counter = 0, MaleCounter = 0, VaccinatedCounter = 0;
        char exit;
        cout << "Enter The Lower Limit Of The Age Group: ";
        cin >> MinAge;
        cout << "Enter The Upper Limit Of The Age Group: ";
        cin >> MaxAge;
        for (auto it = Records.begin(); it != Records.end(); it++) 
        {
            if (it->second
                
                
                
                
                
                .Age >= MinAge && it->second.Age <= MaxAge)
            {
                Counter++;
                if (it->second.Gender == "M" || it->second.Gender == "m")
                {
                    MaleCounter++;
                }
                if (it->second.DosesReceived == 1 || it->second.DosesReceived == 2)
                {
                    VaccinatedCounter++;
                }
                cout << it->second;
            }
        }
        cout << "\nPercentage of people registered in the system who are between " << MinAge << " and " << MaxAge << " years old or older: " << (float)((Counter * 100.0) / Records.size()) << "%" << endl;
        cout << "\nPercentage of Males registered in the system who are between " << MinAge << " and " << MaxAge << " years old or older: " << (float)((MaleCounter * 100.0) / Counter) << "%" << endl;
        cout << "\nPercentage of Females registered in the system who are between " << MinAge << " and " << MaxAge << " years old or older: " << (float)(((Counter - MaleCounter) * 100.0) /Counter) << "%" << endl;
        cout << "\nPercentage of Vaccinated people registered in the system who are between " << MinAge << " and " << MaxAge << " years old or older: " << (float)((VaccinatedCounter * 100.0) / Counter) << "%" << endl;
        cout << "\nPercentage of Unvaccinated people registered in the system who are between " << MinAge << " and " << MaxAge << " years old or older: " << (float)(((Counter - VaccinatedCounter) * 100.0) / Counter) << "%" << endl;

        cout << "Do You Want To Exit? (Y To Exit/Any Other Character To Proceed): ";
        cin >> exit;
        if (exit == 'y' || exit == 'Y')
        {
            break;
        }
    } while (true);
}

void ViewAdvancedStatistics()     
{
    while (true)
    {
        int StatisticsChoice = 0;
        bool exit = false;
        cout << "1. To View Each Governorate Info.\n2. To View Each Age Group Info\n Any Other Number To Exit.\n";
        cin >> StatisticsChoice;
        switch (StatisticsChoice)
        {
        case 1:
            GovernorateInfo();
            break;
        case 2:
            AgeGroupInfo();
            break;
        default:
            exit = true;
            break;
        }
        if (exit == true)
        {
            break;
        }
    }
}

void main()
{
    ReadFromTextFile();
    string AdminPswd, Password, UserName;
    int Choice, AdminChoice, UserChoice;
    long long NationalID;
    cout << "\t\t\t\t-----------------------------------------------------\n";
    cout << " \t\t\t\t\tWelcome To Our Vaccine Tracking System! \n";
    cout << "\t\t\t\t-----------------------------------------------------\n";
    cout << "\t\t\t\t\t\tTotal number of users: " << Records.size() << endl;
    while (true)
    {
        MainMenu();
        bool IdFound = false;
        cin >> Choice;
        switch (Choice)
        {
        case 1:
            AddRecord();
            break;
        case 2:
            cout << "Please Enter Your National ID:\n";
            cin >> NationalID;
            cout << "Please Enter Your Password: \n";
            MaskingPswd(Password);
            for (auto it = Records.begin(); it != Records.end(); it++)
            {
                if (it->second.NationalID == NationalID && it->second.Pswd == Password)
                {
                    UserName = it->second.FullName;
                    IdFound = true;
                    break;
                }
                
            }
            if (IdFound == true)
            {
                cout << "Welcome " << UserName << endl;
                while (true)
                {
                    bool exit = false;
                    cout << "1. Display Your Own Record.\n2. Edit/Update Your Own Record.\n3. Delete Your Own Record.\nAny Other Number To Exit\nPlease Enter Your Choice: \n";
                    cin >> UserChoice;
                    switch (UserChoice)
                    {
                    case 1:
                        DisplayRecord(NationalID);
                        break;
                    case 2:
                        EditRecord(NationalID);
                        break;
                    case 3:
                        DeleteRecord(NationalID);
                        break;
                    default:
                        exit = true;
                        break;
                    }
                    if (exit == true)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "User Credentials Were Not Found!\n";
            }
            break;
        case 3:
            cout << "Please Enter The Admin Password: \n";
            MaskingPswd(AdminPswd);
            if (AdminPswd == "admin123")
            {
                while (true)
                {
                    bool exit = false;
                    AdminMenu();
                    cout << "Please Enter Your Choice: \n";
                    cin >> AdminChoice;
                    switch (AdminChoice)
                    {
                    case 1:
                        // view record(s)
                        Display();
                        break;
                    case 2:
                        // delete record(s)
                        Delete();
                        break;
                    case 3:
                        // view filtered by the number of doses (1 dose or 2 doses)
                        FilterByDoseNumber();
                        break;
                    case 4:
                        // View records of vaccinated users ordered by the age of the user
                        SortByAge();
                        break;
                    case 5:
                        //View the record of the user that needs to be vaccinated from the waiting list.
                        DisplayWaitingList();
                        break;
                    case 6:
                        // View Basic statistics
                        ViewBasicStatistics();
                        break;
                    case 7:
                        // View Basic statistics
                        ViewAdvancedStatistics();
                        break;
                    default:
                        exit = true;
                        break;
                    }

                    if (exit == true)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Incorrect Password!\n";
            }
            break;
        case 4:
            return; //terminates program
        default:
            cout << "Invalid Choice! Please try again.\n";
            break;
        }
        WriteToTextFile();
    }
}
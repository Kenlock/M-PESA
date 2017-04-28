#include "classes.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <sstream>      //Convert int to string
#include <conio.h>
#include <cstdlib>
#include <ctime>

#define ENTER 13        //For password
#define TAB 9
#define SPACE 32
#define BKSP 8

using namespace std;

string mobile, userFile;     //Used in all functions

Classes::Classes()
{
    amt = 0;        //Initialize amount to zero
}

int Classes::main_menu(){
    int n;
    cout << endl << endl;
    cout << "\t--------  MAIN MENU --------" << endl;
    cout << "\t1. Send Money" << endl;
    cout << "\t2. Deposit Cash" << endl;
    cout << "\t3. Withdraw Cash" << endl;
    cout << "\t4. Buy Airtime" << endl;
    cout << "\t5. Loans and Savings" << endl;
    cout << "\t6. Lipa na M-pesa" << endl;
    cout << "\t7. My Account" << endl;
    cout << "\t0. Quit" << endl;
    cout << endl << "Selection: ";
    cin >> n;
    return n;
}


//Function sign up
void Classes::sign_up(){
    std::string pword0, pword1; //Password and confirmation

    cout << "\n\tEnter mobile number: " ;
    cin >> mobile;

    cout << "\n\tEnter your national ID number: ";
    cin >> id_no;
    cout << "\n\tEnter your full names";
    cout << "\n\n\tName: ";
    cin.ignore();
    getline(cin, name);

    userFile = mobile + ".txt";    //Name of file

    fstream userfile;
    userfile.open(userFile.c_str(), ios::in | ios::out | ios::app);
    if(!userfile.is_open()){
        cout << "Error while opening file!" << endl;
    }else{
        LOOP1:cout << "\n\n\tEnter password: ";
        pword0 = passwd();
        cout << "\n\n\tConfirm password: ";
        pword1 = passwd();
        cout << endl << endl;

       if(pword0 == pword1){
            userfile << pword0;
            userfile << "\nUserMobileNo:" << mobile;
            userfile.seekp(0, ios_base::end);

            userfile << endl << "Name:" << name << "\tID.No:" << id_no;
            userfile << endl << amt; //first amount is initialized to 0 in the user's file

            cout << "\n You have been successfully registered for M-Pesa services" << endl << "\n\t\tSafaricom The Better Option" << endl;
            cout << "\n\tPress ENTER ...";
            getch();
            cout << endl << endl ;
            }else{
            cout << "Passwords Mismatch!" << endl;
            goto LOOP1;
        }
    }
    userfile.close();
}//End sign_up



//Login function
int Classes::login(){
    string buffer, buffer2;
    LOGINS:cout << "\n\tEnter mobile number: ";
    cin >> mobile;

    userFile = mobile + ".txt";    //Name of file

    ifstream userfile(userFile.c_str(), ios::in);
    if(!userfile.is_open()){
        cout <<"\n\n\tError opening file" << endl;
        cout << "\tYou are not a member" << endl;
        goto LOGINS;
        return 0;
    }else{
        cout << "\n\tEnter password: ";
        buffer = passwd();
        userfile.seekg(0, ios::beg);//Location of password in file
        getline(userfile, buffer2);
        if(buffer == buffer2){
            cout << "\n\n\t\tSuccess..." << endl;
            return 1;
        }else{
            cout << "\n\tWrong password!" << endl;
            userfile.close();
            goto LOGINS;
            return 0;
        }
    }
    userfile.close();
    return 0;
}//End of login function



//Password function
string Classes::passwd(){
    char password[4];
    char ch;
    int i = 0;

    while(i < 4){
        ch = getch();
        if (ch == ENTER){
            password[i] = '\0';     //NULL
            break;
        }else if(ch == BKSP){
            if (i>0){
                i--;
                cout << ("\b \b");
            }
        }else if (ch == TAB || ch == SPACE){
            continue;
        }else{
            password[i] = ch;
            i++;
            cout << ("*");
        }
        password[i]='\0';
        string str(password); //Convert to string
    }//End while
    return password;
}//End-func


//Function to display contents of my acc
int My_account::display_my_acc(){
    int n;
    cout << endl << endl;
    cout << "\t\t------- MY ACCOUNT -------" << endl;
    cout << "\t\t1. Mini Statement" << endl;
    cout << "\t\t2. Check balance" << endl;
    cout << "\t\t3. Change pin" << endl;
    cout << "\t\t4. Change language" << endl;
    cout << "\t\t5. Update Customer menu" << endl;
    cout << "\t\t0. Quit" << endl;
    cout << endl << "\tSelection: ";
    cin >> n;
    return n;
}//End Display


//Mini statement function
void My_account::mini_statement(){
    ifstream statement(userFile.c_str());
    cout << endl << "\t\t\t***Mini Statement****" << endl;
    getline(statement, buffer);     //First line has password
    cout << "\t------------------------------------------------" << endl;

    while(!statement.eof()){
        getline(statement, buffer);
        cout << "\t" << buffer << endl;
        }//End while

    time_t now = time(0);       //Get current time
    char* dt = ctime(&now);     //convert to string form
    cout << "\n\n\t\t\tRecords are upto date at \n\t\t\t" << dt;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t\tPress ENTER ...";
    getch();
    cout << endl << endl;
}//End mini statement function


//Check balance function
int My_account::check_balance(){
    ifstream file(userFile.c_str(), ios::in);
    if(!file){
        cout << "Error while opening file" << endl;
        return 0;
    }else{
        file.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            file.get(ch);   //Get current byte's data

            if((int)file.tellg() <= 1){   //If the data was at or before the 0th byte
                file.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                file.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        file >> cash;
        return cash;
    }//End if
    return 0;
}//End check balance function


//Change pin function
void My_account::change_pin(){
    Classes clsObj;

    string pword0, pword1;

    cout << "\n\tPin will be changed" <<endl;
    cout << "\n\n\tEnter new pin:";
    pword0 = clsObj.passwd();
    cout << "\n\n\tConfirm password: ";
    pword1 = clsObj.passwd();
    cout << "\n\n\tError while modifying password.";
    return;
}

//Function to change the language
void My_account::change_language(){
    cout << endl << " ------Sorry, English is the only language currently supported------" << endl;
    cout << "****Thank you for contacting us! We will keep you updated on future changes.****" << endl;
    cout << "\n\tVisit www.safaricom.co.ke/m_pesa-languages to learn more." << endl << endl;
}

//Update customer menu function
void My_account::update_customer_menu(){
    cout << endl << "\n\n\tYou are currently using the latest version!" << endl;
    cout << "\n\tVisit www.safaricom.co.ke/m_pesa_menu to learn more" << endl << endl;
}

//Deposit cash function
void account::dep(){
	int amt;
	fstream File;

	File.open(userFile.c_str(),ios::in);
	if(!File){
		cout<<"\n\tFile could not be open!!";
		return;
		}

        File.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            File.get(ch);   //Get current byte's data

            if((int)File.tellg() <= 1){   //If the data was at or before the 0th byte
                File.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                File.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File >> cash;
        File.close();

        ofstream file(userFile.c_str(),ios::out | ios::app);       //Adding to file
        if(!file){
            cout << "\n\tError opening file" << endl;
        }else{
            cout<<"\n\n\tDEPOSIT AMOUNT ";
            cout<<"\n\n\tEnter The amount to be deposited : ";
            cin >> amt;
            cash+=amt;

            file.seekp(0,ios::end);

            file << endl << cash;
            cout << "\n\n\tYou successfully deposited KSH " << amt;
            cout << "\n\n\tMPESA balance is now KSH " << cash;
            cout << "\n\n\t\tPress ENTER ... ";
            getch();
            file.close();
            }//End if
}//End of deposit function


//Function to withdraw cash
void account::withd(){
    int amt,x;
	fstream File;
	string mfile;

	File.open(userFile.c_str(),ios::in);
	if(!File)
	{
		cout<<"\n\tFile could not be open !!\n\tNot Registered!";
		return;
	}

        File.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            File.get(ch);   //Get current byte's data

            if((int)File.tellg() <= 1){   //If the data was at or before the 0th byte
                File.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                File.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File >> cash;
        File.close();

        ofstream file(userFile.c_str(),ios::app | ios::out);
        if(!file){
            cout << "Error opening file" << endl;
        }else{


				cout<<"\n\n\tWITHDRAW AMOUNT ";
				cout << "\n\n\tAgent Number: ";
				int buffer;
				cin >> buffer;
				cout<<"\n\n\tWithdraw amount: ";
				cin>>amt;
				if(cash < amt){
                    cout << "\n\t****Insufficient balance****" << endl;
                    cout << "\n\n\tMPESA balance is: " << cash;
				}else{
				    if(amt>=10 && amt<=49)
                        {
                            x=0;
                            amt+=x;
                        }
                        else if(amt>=50 && amt<=100)
                        {
                            x=10;
                            amt+=x;
                        }
                        else if(amt>=101 && amt<=500)
                        {
                            x=27;
                            amt+=x;
                        }
                        else if(amt>=501 && amt<=1000)
                        {
                            x=27;
                            amt+=x;
                        }
                        else if(amt>=1001 && amt<=1500)
                        {
                           x=27;
                           amt+=x;
                        }
                        else if(amt>=1501 && amt<=2500)
                        {
                           x=27;
                           amt+=x;
                        }
                        else if(amt>=2501 && amt<=3500)
                        {
                           x=49;
                           amt+=x;
                        }
                        else if(amt>=3501 && amt<=5000)
                        {
                            x=66;
                           amt+=x;
                        }
                        else if(amt>=5001 && amt<=7500)
                        {
                            x=82;
                           amt+=x;
                        }
                        else if(amt>=7501 && amt<=10000)
                        {
                            x=110;
                           amt+=x;
                        }
                        else if(amt>=10001 && amt<=15000)
                        {
                            x=159;
                           amt+=x;
                        }
                        else if(amt>=15001 && amt<=20000)
                        {
                            x=176;
                           amt+=x;
                        }
                        else if(amt>=20001 && amt<=35000)
                        {
                            x=187;
                           amt+=x;;
                        }
                        else if(amt>=35001 && amt<=50000)
                        {
                            x=275;
                           amt+=x;
                        }
                        else if(amt>=50001 && amt<=70000)
                        {
                            x=330;
                           amt+=x;
                        }
                        else
                        {
                            cout<<"********N/A************";
                        }
                    cash-=amt;
                    file.seekp(0,ios::end);
                    file << endl << cash;       //Write to file
                    cout <<"\n\n\tTransaction charge is KSH "<< x;
                    cout << "\n\n\tMPESA balance is KSH" << cash;
                    cout << "\n\tThank you for using M-pesa services....."<<endl;
                    cout << "\n\n\t\tPress ENTER ...";
                    getch();
				}
        file.close();
        }
}//End of withdraw function


//Buy airtime function
void account::buy_airtime(){

	fstream file(userFile.c_str(), ios::in | ios::ate);
	if(!file.is_open()){
		cout<<"\tFile could not be open !!\n\tNot Registered!";
		return;
		}else{
		    //Read most recent value
		    file.seekg(-1, ios_base::end);  //go to one spot before the eof
		    bool keepLooping = true;
            while (keepLooping){
                char ch;
                file.get(ch);   //Get current byte's data

                if((int)file.tellg() <= 1){   //If the data was at or before the 0th byte
                    file.seekg(0);  //Then first line is the last line
                    keepLooping = false;    //Then we need to exit the loop
                }else if(ch == '\n'){   //If the data was a new line
                    keepLooping = false;     //Stop at the current position
                }else{
                    file.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
                    }
                }//End while
            file >> cash;

            cout<<"\n\tBUY AIRTIME ";
            cout<<"\n\n\tAmount of Credit: ";
            cin>>amt;
            if(cash < amt){
                cout << "\t****Insufficient balance****" << endl;
                cout << "\n\n\t Your account balance is:" << cash;
            }else{
                cash-=amt;
                file.seekp(0,ios::end);
                file << endl << cash;
                cout << "\n\n\tYou have successfully purchased airtime of KSH " << amt ;
                cout << "\n\n\tMPESA balance is now KSH " << cash;
                cout << "\n\n\tSafaricom The Better Option."<<endl;
                cout << "\n\n\t\tPress ENTER ..." ;
                getch();
            }
        file.close();
        }//End if
}//end of buy airtime function


//Send money function
void account::send_money(){
    int amt;
    int charge,x;
    int cash1;
	fstream File,File_rec;
	string mobile_rec;
	string mfile_rec;

	File.open(userFile.c_str(),ios::in);
	if(!File)
	{
		cout<<"\n\tFile could not be open !!\n\tNot Registered!";
		return;
	}
	else
    {
        File.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            File.get(ch);   //Get current byte's data

            if((int)File.tellg() <= 1){   //If the data was at or before the 0th byte
                File.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                File.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File >> cash;
        File.close();
    }

    cout << "\n\tReceiver's mobile: ";
    cin >> mobile_rec;

    mfile_rec = mobile_rec + ".txt";

	File_rec.open(mfile_rec.c_str(),ios::in);
	if(!File_rec)
	{
		cout<<"\n\tFile could not be open !!\n\tReceiver is not Registered!";
		return;
	}
	else
        {
        File_rec.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping1 = true;

        while (keepLooping1){
            char ch;
            File_rec.get(ch);   //Get current byte's data

            if((int)File_rec.tellg() <= 1){   //If the data was at or before the 0th byte
                File_rec.seekg(0);  //Then first line is the last line
                keepLooping1 = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping1 = false;     //Stop at the current position
            }else{
                File_rec.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File_rec >> cash1;
        File_rec.close();
}

        ofstream file(userFile.c_str(),ios::app | ios::out);
        if(!file){
            cout << "\n\tError opening user's file!" << endl;
        }else{
				cout<<"\n\n\tSEND MONEY";
				cout<<"\n\n\tAmount to send: ";
				cin>>amt;
				if(cash < amt){
                    cout << "\t****Insufficient balance****" << endl;
                    cout << "\n\n\tYour account balance is KSH " << cash;
				}else{
                        if(amt>=10 && amt<=49)
                        {
                            x=1;
                            charge=amt+x;
                        }
                        else if(amt>=50 && amt<=100)
                        {
                            x=3;
                            charge=amt+x;
                        }
                        else if(amt>=101 && amt<=500)
                        {
                            x=11;
                            charge=amt+x;
                        }
                        else if(amt>=501 && amt<=1000)
                        {
                            x=15;
                            charge=amt+x;
                        }
                        else if(amt>=1001 && amt<=1500)
                        {
                            x=25;
                            charge=amt+x;
                        }
                        else if(amt>=1501 && amt<=2500)
                        {
                            x=40;
                            charge=amt+x;
                        }
                        else if(amt>=2501 && amt<=3500)
                        {
                            x=55;
                            charge=amt+x;
                        }
                        else if(amt>=3501 && amt<=5000)
                        {
                            x=60;
                            charge=amt+x;
                        }
                        else if(amt>=5001 && amt<=7500)
                        {
                            x=75;
                            charge=amt+x;
                        }
                        else if(amt>=7501 && amt<=10000)
                        {
                            x=85;
                            charge=amt+x;
                        }
                        else if(amt>=10001 && amt<=15000)
                        {
                            x=95;
                            charge=amt+x;
                        }
                        else if(amt>=15001 && amt<=20000)
                        {
                            x=100;
                            charge=amt+x;
                        }
                        else if(amt>=20001 && amt<=35000)
                        {
                            x=110;
                            charge=amt+x;
                        }
                        else if(amt>=35001 && amt<=50000)
                        {
                            x=110;
                            charge=amt+x;
                        }
                        else if(amt>=50001 && amt<=70000)
                        {
                            x=110;
                            charge=amt+x;
                        }
                        else
                        {
                            cout<<"********N/A************";
                        }
                    cash-=charge;
                    file.seekp(0,ios::end);
                    file << endl << cash;
                    cout<<"\n\n\t****Sender's message****"<<endl;
                    cout << "\tTransaction cost is KSH "<<x;
                    cout << "\n\tMPESA balance is KSH " << cash;
                    cout << "\n\tThank you for using M-pesa services....."<<endl;
                    cout << "\n\n\t\tPress ENTER ... ";
                    getch();
				}
        file.close();
        }
        ofstream file_rec(mfile_rec.c_str(),ios::app | ios::out);
        if(!file_rec){
            cout << "\n\tError opening receiver's file!" << endl;
        }
        else{
                    cash1+=amt;
                    file_rec.seekp(0,ios::end);
                    file_rec << endl << cash1;
                    cout<<"\n\n\t****Receivers message****"<<endl;
                    cout << "\tMPESA balance is KSH " << cash1;
                    cout << "\n\t\tSafaricom The Better Option!"<<endl;
                    cout << "\n\n\t\tPress ENTER ... ";
                    getch();
				}
        file_rec.close();
        return;

}//End of send money function



void account::lipa_na_mpesa(){
    int opt;
	account ac;
	fstream File,File_rec;
	string mobile_rec;
	string mfile_rec;


    cout<<"\n\n\t 1.Pay bill"<<endl;
    cout<<"\n\t 2.Buy goods and services"<<endl;

    cout<<"\nEnter option: ";
    cin >> opt;

    if(opt==1)
    {
        pay_bill();
    }
    if(opt==2)
    {
        buy_goods_and_sercices();

    }
        return;

}


//Work with pay bills
void account::pay_bill()
{
    int amt;
    int cash1;
	fstream File,File_rec;
	string mobile,mobile_rec;
	string mfile,mfile_rec;

	File.open(userFile.c_str(),ios::in);
	if(!File)
	{
		cout<<"File could not be open !!\n\tNot Registered!";
		return;
	}
	else
    {
        File.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            File.get(ch);   //Get current byte's data

            if((int)File.tellg() <= 1){   //If the data was at or before the 0th byte
                File.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                File.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File >> cash;
        File.close();
    }

    cout << "\n\tEnter business number: ";
    cin >> mobile_rec;

    mfile_rec = mobile_rec + ".txt";

	File_rec.open(mfile_rec.c_str(),ios::in);
	if(!File_rec)
	{
		cout<<"\n\tFile could not be open !!\n\tNot Registered!";
		return;
	}
	else
        {
        File_rec.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping1 = true;

        while (keepLooping1){
            char ch;
            File_rec.get(ch);   //Get current byte's data

            if((int)File_rec.tellg() <= 1){   //If the data was at or before the 0th byte
                File_rec.seekg(0);  //Then first line is the last line
                keepLooping1 = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping1 = false;     //Stop at the current position
            }else{
                File_rec.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File_rec >> cash1;
        File_rec.close();
}

        ofstream file(userFile.c_str(),ios::app | ios::out);
        if(!file){
            cout << "\n\tError opening user's file." << endl;
        }
        else{
				cout<<"\n\n\tAmount: ";
				cin>>amt;
				if(cash < amt){
                    cout << "\t****Insufficient balance****" << endl;
                    cout << "\n\n\tYour account balance is:" << cash;
				}else{
                    cash-=amt;
                    file.seekp(0,ios::end);
                    file << endl << cash;
                    cout<<"\n\n\tYou paid KSH "<<amt<<" to business number "<<mobile_rec<<endl;
                    cout << "\n\n\tMPESA balance is KSH " << cash;
                    cout << "\n\n\t\tPress ENTER ...";
                    getch();
				}
        file.close();
        }
        ofstream file_rec(mfile_rec.c_str(),ios::app | ios::out);
        if(!file_rec){
            cout << "\n\tError opening business user file!" << endl;
        }
        else{
                    cash1+=amt;
                    file_rec.seekp(0,ios::end);
                    file_rec << endl << cash1;
				}
        file_rec.close();
}


//Buy goods and services
void account::buy_goods_and_sercices()
{
    int cash1;
	fstream File,File_rec;
	string mobile_rec;
	string mfile_rec;

	File.open(userFile.c_str(),ios::in);
	if(!File)
	{
		cout<<"File could not be open !!\n\tNot Registered!";
		return;
	}
	else
    {
        File.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping = true;

        while (keepLooping){
            char ch;
            File.get(ch);   //Get current byte's data

            if((int)File.tellg() <= 1){   //If the data was at or before the 0th byte
                File.seekg(0);  //Then first line is the last line
                keepLooping = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping = false;     //Stop at the current position
            }else{
                File.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File >> cash;
        File.close();
    }

    cout << "\n\tBusiness Number: ";
    cin >> mobile_rec;

    mfile_rec = mobile_rec + ".txt";

	File_rec.open(mfile_rec.c_str(),ios::in);
	if(!File_rec)
	{
		cout<<"\n\tFile could not open (Business)!!\n\tNot Registered!";
		return;
	}
	else
        {
        File_rec.seekg(-1, ios_base::end);  //go to one spot before the eof

        bool keepLooping1 = true;

        while (keepLooping1){
            char ch;
            File_rec.get(ch);   //Get current byte's data

            if((int)File_rec.tellg() <= 1){   //If the data was at or before the 0th byte
                File_rec.seekg(0);  //Then first line is the last line
                keepLooping1 = false;    //Then we need to exit the loop
            }else if(ch == '\n'){   //If the data was a new line
                keepLooping1 = false;     //Stop at the current position
            }else{
                File_rec.seekg(-2, ios::cur);   //Move to front of data, then to front of byte before it
            }
        }//End while
        File_rec >> cash1;
        File_rec.close();
}

        ofstream file(userFile.c_str(),ios::app | ios::out);
        if(!file){
            cout << "\n\tError opening file" << endl;
        }
        else{
				cout<<"\n\n\tBUY GOODS AND SERVICES.";
				cout<<"\n\n\tAmount: ";
				cin>>amt;
				if(cash < amt){
                    cout << "\t****Insufficient balance****" << endl;
                    cout << "\n\n\tYour account balance is:" << cash;
				}else{
                    cash-=amt;
                    file.seekp(0,ios::end);
                    file << endl << cash;
                    cout<<"\n\n\tYou paid KSH "<<amt<<" to TILL NO "<<mobile_rec<<endl;
                    cout << "\n\tMPESA balance is now KSH " << cash;
                    cout << "\n\n\t\tPress ENTER ... ";
                    getch();
				}
        file.close();
        }
        ofstream file_rec(mfile_rec.c_str(),ios::app | ios::out);
        if(!file_rec){
            cout << "Error opening file" << endl;
        }
        else{
                    cash1+=amt;
                    file_rec.seekp(0,ios::end);
                    file_rec << endl << cash1;
				}
        file_rec.close();
}//end of function buy goods and services

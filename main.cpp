//This M-Pesa clone program was created to accomplish a project as a satisfaction
//of learning C++
//  -----------------------           MPESA              -----------------------
//
//          1. NJOROGE ALICE WANJIKU    C026-01-1207/2016
//          2. DAISY GESARE             C026-01-1234/2016
//          3. EMMANUEL KARANJA         C026-01-1179/2016
//          4. BRIAN MANOTI OKINYI      C026-01-1210/2016
//          5. KELVIN KINDA             C026-01-1191/2016
//
//
// We acknowledge our instructor Mr. Morris Kaburu for the support during
//                  development of this project
//
//  ------------------------------------------------------------------------------

#include "classes.h"

#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

main()
{
    int n;
    LOGIN:cout << "\n\t1. Login" << endl << "\t2. Sign up" << "\n\n" << "Selection: ";
    cin >> n;

    if (n == 1){
        Classes clsObj;        //class Classes
        My_account accObj;      //My Account object
        account account2Obj;

              //  For goto
        int status = clsObj.login();
        RETURN: while(status == 1){
            int r = clsObj.main_menu();
            if(r==0){
                return 0;
            }//     Quit
            switch(r){
        case 1:
            account2Obj.send_money();
            break;
        case 2:
            account2Obj.dep();
            break;
        case 3:
            account2Obj.withd();        //Withdraw function
            break;
        case 4:
            account2Obj.buy_airtime();      //Buy airtime
            break;
        case 5:
            break;
        case 6:
            account2Obj.lipa_na_mpesa(); //lipa na m-pesa function
            break;
        case 7:
            int d = accObj.display_my_acc();

                if(d==0){
                    goto RETURN;
                }

                switch(d){
                case 1:     //Wants mini_statement
                    accObj.mini_statement();
                    break;
                case 2:     //Wants acc balance
                    cout << "\n\tYour account balance is KSH " << accObj.check_balance() << endl;
                    cout << "\n\n\t\tPress ENTER ...";
                    getch();
                    break;
                case 3:
                    accObj.change_pin();
                    cout << "\n\tPress ENTER ...";
                    getch();
                    break;
                case 4:
                    accObj.change_language();
                    cout << "\n\tPress ENTER ...";
                    getch();
                    break;
                case 5:
                    accObj.update_customer_menu();
                    cout << "\n\tPress ENTER ...";
                    getch();
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    cout << "\n\tPress ENTER ...";
                    getch();
                    break;
                }
            }
        }//End while
    }else{
        Classes classObj;
        classObj.sign_up();
        goto LOGIN;
    }
}//End main

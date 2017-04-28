#ifndef CLASSES_H
#define CLASSES_H

#include <string>
using namespace std;

class Classes
{
    public:
        Classes();
        int main_menu(void);
        void ret_rec();
        void sign_up();
        int login();
        string passwd();

    protected:
        string mobile;
        string buffer;      //Temp data
        string mfile;      //Name of file
        int id_no;  //Global variables
        string name;       //Users name
        int amt;

    private:

};

class My_account: public Classes
{
    int cash;
public:
    int display_my_acc();
    void mini_statement();
    int check_balance();
    void change_pin();
    void change_language();
    void update_customer_menu();
};



class account: public Classes
{
private:
    int cash;

public:
   void dep();
   void withd();
   void send_money();
   void buy_airtime();
   void lipa_na_mpesa();
   void pay_bill();
   void buy_goods_and_sercices();
   int charges(int ch);

};         //Class definition ends

#endif // CLASSES_H

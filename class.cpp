#include <iostream>
#include "class.h"

using namespace std;
KeyProDev keydev;

Account::Account(int a,int b ,int c)
{
	this->a = a;
	this->b = b;
	//this->c = c;
}

void Account::PPP()
{
        cout<<"I am PPP"<<endl;
	cout<<this->a<<endl;
}

extern bool airoha_int(char *str,int *error_code);

int main(){
	int gg;
	char txt;
	Account act = {40, 20 ,30};
	cout<<"Hello World"<<endl;
	act.PPP();

	keydev.dev_func.write_key = airoha_int;
	keydev.bt_mac[0] = 10;
	printf("%d",keydev.bt_mac[0]);
	keydev.dev_func.write_key("haha",&gg);

	return 0;
}

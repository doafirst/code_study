#include <iostream>
#include "class.h"

using namespace std;

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

int main(){
	Account act = {40, 20 ,30};
	cout<<"Hello World"<<endl;
	act.PPP();


	keydev.bt_mac[0] = 10;
	printf("%d",keydev.bt_mac[0]);


	return 0;
}

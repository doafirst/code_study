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
	cout<< endl;
	cout<<"Hello World"<<endl;
	act.PPP();
	return 0;
}

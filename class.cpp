#include <iostream>

using namespace std;

class Account {
	public:
		Account(int a,int b ,int c);//Constructor
		~Account(){delete text;};//Desctructor that use for memory release
		void PPP();
		char *text;
	private:
		int a;
		int b;
		int c;

};

//Account::Account(int ddd)
//{
//	cout<<"I am DDD"<<endl;
//	cout<<ddd<<endl;
//}

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
	Account act = {40, 20 ,30}; //Constructor method 1
	Account act2(999,11,22); // Constructor metohd 2
	cout<< endl;
	cout<<"Hello World"<<endl;
	act.PPP();
	act2.PPP();
	act.text = new char[4]; //malloc
	act2.text = new char[4]; //malloc 
	printf("sizeof %d \n\n",sizeof(act.text));

	return 0; // When exit main function ~Account(){delete text;} will release memory
}

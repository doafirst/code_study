class Account {
	public:
		Account(int a,int b ,int c);
		void PPP();
	private:
		int a;
		int b;
		int c;

};

typedef bool (*CALLBACK)(char *str,int *error_code);
typedef struct _DevFunc{
	CALLBACK INIT;
	CALLBACK GET_MAC;
	CALLBACK GET_NAME;
	CALLBACK GET_KEY;
	CALLBACK WRITE_KEY;
}DevFunc;

class KeyProDev{
	public:
		DevFunc dev_func;
		unsigned char bt_mac[8];
		unsigned char bt_name[40];
		unsigned char key[128];
};

KeyProDev keydev;

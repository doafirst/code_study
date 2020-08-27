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
	CALLBACK init;
	CALLBACK get_mac;
	CALLBACK get_name;
	CALLBACK get_key;
	CALLBACK write_key;
}DevFunc;

class KeyProDev{
	public:
		DevFunc dev_func;
		unsigned char bt_mac[8];
		unsigned char bt_name[40];
		unsigned char key[128];
};
extern KeyProDev keydev;


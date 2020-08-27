typedef bool (*CALLBACK)(char *str,int *error_code);

typedef struct _DevFunc{
	char platform_name[30];
	CALLBACK init;
	CALLBACK get_mac;
	CALLBACK get_uuid;
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


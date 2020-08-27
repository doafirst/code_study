#include <iostream>
#include "class.h"
#include <memory.h>

using namespace std;
KeyProDev keydev;

extern DevFunc airo_dev_func;
extern DevFunc bes_dev_func;

int main(){
	int error_code;
	char g[] = "HELLO";

	printf("Func struct sizeof %d\n",(int)sizeof(DevFunc));
	//Copy Airoha platfom struct
	memcpy(&keydev.dev_func,&airo_dev_func, sizeof(DevFunc) );
	printf("\nPlatform:%s\n",keydev.dev_func.platform_name);
	keydev.dev_func.init(g,&error_code);
	keydev.dev_func.get_mac(g,&error_code);
	keydev.dev_func.get_uuid(g,&error_code);
	keydev.dev_func.get_name(g,&error_code);
	keydev.dev_func.get_key(g,&error_code);
	keydev.dev_func.write_key(g,&error_code);

	//Copy BES platfom struct
	memcpy(&keydev.dev_func,&bes_dev_func, sizeof(DevFunc) );
	printf("\nPlatform:%s\n",keydev.dev_func.platform_name);
	keydev.dev_func.init(g,&error_code);
	keydev.dev_func.get_mac(g,&error_code);
	keydev.dev_func.get_uuid(g,&error_code);
	keydev.dev_func.get_name(g,&error_code);
	keydev.dev_func.get_key(g,&error_code);
	keydev.dev_func.write_key(g,&error_code);
	return 0;
}

#include <iostream>
#include "class.h"
#include "memory.h"

using namespace std;
KeyProDev keydev;

extern DevFunc airo_dev_func;
int main(){
	int gg;
	char g[] = "HELLO";
	memcpy(&keydev.dev_func,&airo_dev_func, sizeof(airo_dev_func) );
	printf("Platform:%s\n",keydev.dev_func.platform_name);
	keydev.dev_func.init(g,&gg);
	keydev.dev_func.get_mac(g,&gg);
	keydev.dev_func.get_uuid(g,&gg);
	keydev.dev_func.get_name(g,&gg);
	keydev.dev_func.get_key(g,&gg);
	keydev.dev_func.write_key(g,&gg);

	return 0;
}

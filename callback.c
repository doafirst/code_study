#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

typedef void *(*callback)(char *);

typedef struct _Platform_Func{
	callback GetKey;
	callback GetName;
	callback SetKey;
}Platform_Func;

/*=======AIROHA FUNCTIONS=======*/
void *Airoha_GetKey(char *aaa){
	*aaa = 10;	
	printf("Airoha_GetKey\n");
	return aaa;
}

void *Airoha_GetName(char *aaa){
	*aaa = 20;	
	printf("Airoha_GetName\n");
	return aaa;
}
void *Airoha_SetKey(char *aaa){
	*aaa = 30;	
	printf("Airoha_SetKey\n");
	return aaa;
}

/*=======BES FUNCTIONS=======*/
void *BES_GetKey(char *aaa){
	*aaa = 10;	
	printf("BES_GetKey\n");
	return aaa;
}

void *BES_GetName(char *aaa){
	*aaa = 20;	
	printf("BES_GetName\n");
	return aaa;
}
void *BES_SetKey(char *aaa){
	*aaa = 30;	
	printf("BES_SetKey\n");
	return aaa;
}

Platform_Func airoha_func = 
	{
	 Airoha_GetKey 
	,Airoha_GetName 
	,Airoha_SetKey
	};

Platform_Func bes_func = 
	{
	 BES_GetKey 
	,BES_GetName 
	,BES_SetKey
	};


/*=======MAIN=======*/
int main(int argc, char** argv)
{
	char a;

	printf("size of %ld \n",sizeof(bes_func));
	Platform_Func now_platform;

	memcpy(&now_platform, &airoha_func,sizeof(Platform_Func));

	now_platform.GetKey(&a);
	now_platform.GetName(&a);
	now_platform.SetKey(&a);

	memcpy(&now_platform, &bes_func,sizeof(Platform_Func));

	now_platform.GetKey(&a);
	now_platform.GetName(&a);
	now_platform.SetKey(&a);

	return 0;
}

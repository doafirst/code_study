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

typedef void *(*callback)(void *);

void *CallBack_Function(void *aaa){
	static char bbb[] = "Return Call Back\n";
	printf("CallBack Function %s\n",(char *)aaa);
	return bbb;
}

typedef struct _moho
{
	unsigned char a1:4;
	unsigned char a2:2;
	unsigned char a3:1;
	unsigned char a4:1;
	unsigned char b1:4;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:2;
	unsigned char c1:4;
	unsigned char c2:1;
	unsigned char c3:1;
	unsigned char c4:2;
	char ad[20];
	callback callback1;
	int *code;
}/*__attribute__ ((packed))*/  moho ,*moho_p;

void *harry_thread (void *arg)
{
	static int a[2] ;
	a[0] = 10;
	printf("\nHarry Thread %s\n",(char *) arg);
	pthread_exit((void *)a);
}
int main(int argc, char** argv)
{
	pthread_t t;
	void *aaa;
	printf("Thread Start ");
	pthread_create(&t, NULL, harry_thread, "Child");
	
	//sleep(1);
	pthread_join(t,&aaa);
	printf("aaa = %d\n",*(int *)aaa);
	moho moho1;
	memset(&moho1,0x73,sizeof(moho));
	printf("%X %X %X %X sizde=%ld \n",moho1.a1,moho1.a2,moho1.a3,moho1.a4 ,sizeof(moho));
	printf("MOHO1= %x\n",&moho1);

	moho1.callback1 = CallBack_Function;
	aaa = moho1.callback1("aa");
	printf("%s",(char *)aaa);

}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int test(char ** s){

}

int main(int argc ,char **argv){
	//char a[2][10]={"hello","OK"};
	//s = test();
	//printf("%s %s \n",a[0],a[1]);
	char *a[2];
	printf("================String In Array================\n");
	a[0] = malloc(strlen("HAHA")+1);
	a[1] = malloc(strlen("IM OOK")+1);
	a[0] = "HAHA";
	a[1] = "IM OOK";
	printf("%s %s \n",a[0],a[1]);
	printf("a[0] -> %x %x \n",a,a[0]);
	printf("a[1] -> %x %x \n",a+1,a[1]);

	printf("================Double Array================\n");
	char b[10][20];
	printf("b = %x\n",b);
	printf("b[0] = %x\n",b[0]);
	printf("&b[0][1] = %x\n",&b[0][1]);
	printf("&b[0][19] = %x\n",&b[0][19]);
	printf("b[1] = %x\n",b[1]);
	printf("================ARGC ARGC================\n");
	
	printf("addr line1 = %x %x\n",argv,argv+1);
	printf("addr line2 = %x %x\n",*argv,*(argv+1));
	printf("argc = %d\n",argc);
	for(int i =0 ; i < argc ; i++)
	{
		printf("addr = %x\n",argv[i]);
		printf("argv%d = %s\n",i,argv[i]);
		printf("\n");
	}
}

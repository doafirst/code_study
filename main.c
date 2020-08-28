#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int test(char ** s){

}

int main(int argc ,char **argv){
	char a[2][10]={"hello","OK"};
	//s = test();
	printf("%s %s \n",a[0],a[1]);

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

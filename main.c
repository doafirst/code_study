#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool isMatch(char *s, char *p){
	printf("mismatch %s %s %ld %ld \n",s,p,strlen(s),strlen(p));
}

int main(){
	isMatch("aa","bbvvvv");
}

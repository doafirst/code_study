#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
char * intToRoman(int num){
	static char roma_str[40] = "XXI";

	return(roma_str);
}

int main(){
	char *s;
	s = intToRoman(12);
	printf("XXI\n");
}

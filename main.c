#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
char * intToRoman(int num){
	int slash_num=0,cnt=0;	
	static char roma_str[40];

	if(  (num/1000) > 0)
	{
		slash_num = num/1000;
		printf("%d\n",slash_num);
		while(slash_num>0)
			{
			roma_str[cnt]='M';
			slash_num--;
			cnt++;
			}
	}
	if( ((num%1000)/100) > 0)
	{
		slash_num = (num%1000)/100;
		printf("%d\n",slash_num);
		while(slash_num>0)
			{
			if(slash_num == 9)
			{
				roma_str[cnt]='C';
				cnt++;
				roma_str[cnt]='M';
				cnt++;
				slash_num=0;
				continue;
			}
			if(slash_num >= 5)
			{
				roma_str[cnt]='D';
				cnt++;
				slash_num=slash_num - 5;
				continue;
			}
			roma_str[cnt]='C';
			slash_num--;
			cnt++;
			}
	}
	if( ((num%100)/10) > 0)
	{
		slash_num = (num%100)/10;
		printf("%d\n",slash_num);
		while(slash_num>0)
			{
			if(slash_num == 9)
			{
				roma_str[cnt]='X';
				cnt++;
				roma_str[cnt]='C';
				cnt++;
				slash_num=0;
				continue;
			}
			if(slash_num >= 5)
			{
				roma_str[cnt]='L';
				cnt++;
				slash_num=slash_num - 5;
				continue;
			}
			roma_str[cnt]='X';
			slash_num--;
			cnt++;
			}
	}
	if( (num%10) > 0)
	{
		slash_num = num%10;
		printf("%d\n",slash_num);
		while(slash_num>0)
			{
			if(slash_num == 9)
			{
				roma_str[cnt]='I';
				cnt++;
				roma_str[cnt]='X';
				cnt++;
				slash_num=0;
				continue;
			}
			if(slash_num >= 5)
			{
				roma_str[cnt]='V';
				cnt++;
				slash_num=slash_num - 5;
				continue;
			}
			roma_str[cnt]='I';
			slash_num--;
			cnt++;
			}
	}



	return(roma_str);
}

int main(){
	char *s;
	s = intToRoman(3);
	printf("%s\n",s);
}

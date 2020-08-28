#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int longestValidParentheses(char * s){
    //printf("str %d",strlen(s));
    int length = strlen(s);
    int quate_a=0;
    int quate_b=0;
    int i=0;
    int sum=0;
    int sum_max=0;
    int index = 0;
    for(index=0;index<(length-1);index++)
    {
        //printf("index=%d\n",index);
        sum = 0;
        quate_a = 0;
        quate_b = 0;
        if(s[index] == ')')
            continue;
        for(i=index;i<length;i++)
        {
            //printf("\n%d %c",i,s[i]);
            if(s[i] == '(')
            {
                quate_a++;
            }
            if(s[i] == ')')
            {
                if(quate_a > 0)
                {    
                    quate_a--;
                    quate_b++;
                    if(quate_a == 0)
                    {
                        sum=sum+quate_b*2;
                        quate_b=0;
                        //printf("sum %d\n",sum);
                    }
                }
                else
                {
                    break;
                }

            }
        }
        if(sum>sum_max)
        {
            sum_max = sum;
        }
    }
    return sum_max;
}

int main(){
	int s;
	s = longestValidParentheses("()()((()())(((()()()()");
	printf("%d\n",s);
}

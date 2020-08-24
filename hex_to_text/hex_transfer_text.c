#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char str1[10];
int get_file_data(void)
{
	FILE *FP,*FP_W;
	unsigned char get_word;
	unsigned int index=0, count=0;
	short length;
	int ret;
	FP = fopen("./AUDIO_IN.lhdc","rb+");
	if(!FP)
	{
		printf("File OPEN FAIL\n");
		fclose(FP);
		return -1;
	}
	FP_W = fopen("./Output.txt","wb");
	if(!FP_W)
	{
		printf("File FP_W OPEN FAIL\n");
		fclose(FP_W);
		return -1;
	}
	printf("File OPEN PASS\n");
	while(1)
	{
		count++;
		/*get_word=fgetc(FP);
		if(get_word==EOF)*/
		ret = fread(&get_word,1,1,FP);
		if(ret==0)
		{
			printf("\nEOF1 break\n");
			break;
		}
		printf(",0x%02x %d ",get_word,ret);
		sprintf(str1,",0x%02x ",get_word);
		//printf("%s ",str1);
		fwrite(str1,1,6,FP_W);
		if(count%10 == 0)
		{
			printf(" -> %d \n",count);
			fwrite("\n",1,1,FP_W);
		}
		/*
		if(count >= 172294 )
		{
			break;
		}
		*/

	}
	fclose(FP);
	return 0;
}
int main()
{
	printf("Hex transfer to text \n", 0);
	get_file_data();
    return 0;
}

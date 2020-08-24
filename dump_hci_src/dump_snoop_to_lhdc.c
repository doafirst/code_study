#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "dump_snoop_log_to_wav.h"

//#define PAUSE_CHECK
//#define LOG_PRINT
#define EVENT_LOG_PRINT
//#define FRAME_BREAK_COUNT 750
//#define FIXED_HANDLE 4
//#define FIXED_SAMPLE_RATE 441

unsigned char buff[1500];
FILE *FP_SNOOP,*FP_LHDC;
unsigned int lhdc_sequence_number,lhdc_frame_count;
unsigned char sequence_error_count ,handle,handle_flag=0;
unsigned char capability_temp[9];
unsigned char capability[9];
unsigned short Dst_CID[2];
unsigned short Src_CID[2];
unsigned char Dst_CID_Direction;
unsigned char Src_CID_Direction;
unsigned char Now_Direction;
unsigned short avdtp_sequence=1;
char avdtp_set_flag=0;
unsigned int Frame=0 , output_file_index=0 ,first_write=0, continue_write=0;
int acl_count = 0; 
unsigned char hci_time[8];
struct acl_list {
  unsigned int  acl_frame;
  unsigned long long acl_time;
  unsigned long long  avdtp_timestamp;
  struct acl_list *acl_next;
};
struct acl_list *acl_head  = NULL;
struct acl_list *acl_tail  = NULL;
struct acl_list *acl_now  = NULL;
unsigned long long avdtp_media_first_event_time = 0;
#ifdef FIXED_SAMPLE_RATE
unsigned int sample_rate = FIXED_SAMPLE_RATE;
#else
unsigned int sample_rate ;
#endif

void hex_dump(unsigned char *input_char ,int length)
{
	int count=0;
	while(count < length)
	{
		printf("%02X ", *(input_char+count));
		count++;
		if(count%8 == 0)
			{
			printf("\n");
			}
	}
	printf("\n");
}

void fgets2(char *buff_temp, int length,FILE *FP_TEMP)
{
	int i;
	for(i=0;i<length;i++)
	{
        buff[i] = getc(FP_TEMP);
	}
}

void cid_parser(unsigned int index,unsigned int length)
{
	fseek(FP_SNOOP, index,SEEK_SET);
	fgets2(buff,length+1,FP_SNOOP);
	if(*(short *)(buff+7) == 0x01) 
	{
		if(buff[9]==0x02 && *(short *)(buff+13)==0x0019)
		{
			avdtp_set_flag=1;
		}
		if(buff[9]==0x03 && buff[17]<=0x01 && avdtp_set_flag==1) 
		{
			if(Dst_CID[0] == 0)
				Dst_CID[0] = *(short *)(buff+13);
			else
				Dst_CID[1] = *(short *)(buff+13);

			if(Src_CID[0] == 0)
				Src_CID[0] = *(short *)(buff+15);
			else
				Src_CID[1] = *(short *)(buff+15);

			avdtp_set_flag=0;

			#ifdef LOG_PRINT
			printf("AVDTP Signal CID: SRC=%x DST=%x\n",Src_CID[0],Dst_CID[0]);
			printf("AVDTP Media CID:  SRC=%x DST=%x\n",Src_CID[1],Dst_CID[1]);
			#endif
			if(Now_Direction)
			{
				Dst_CID_Direction=0;
				Src_CID_Direction=1;
				#ifdef LOG_PRINT
				printf("Source Device(Phone) Dst=%d Src=%d \n",Dst_CID_Direction,Src_CID_Direction);
				#endif
			}
			else
			{
				Dst_CID_Direction=1;
				Src_CID_Direction=0;
				#ifdef LOG_PRINT
				printf("Sink Device(Speaker) Dst=%d Src=%d \n",Dst_CID_Direction,Src_CID_Direction);
				#endif
			}
			#ifdef PAUSE_CHECK
			system("pause");
			#endif
		}
	}
}

void set_sample_rate(unsigned char bit6)
{
	if(bit6 ==1)
		sample_rate = 960;
	else if (bit6 ==4)
		sample_rate = 480;
	else
		sample_rate = 441;

#ifdef FIXED_SAMPLE_RATE
sample_rate = FIXED_SAMPLE_RATE;
#endif

}
int a2dp_ota_response_time_array[11];
int a2dp_send_plus_response_time_array[11];
void a2dp_transfer_time_count(unsigned long long a2dp_ota_response_time,unsigned long long a2dp_send_time)
{
long long sum_time = a2dp_send_time+a2dp_ota_response_time;

#ifdef EVENT_LOG_PRINT
printf("      %lld + %lld = %lld ms \n",a2dp_ota_response_time,a2dp_send_time,sum_time);
#endif

if(a2dp_ota_response_time  < 30)
	{
	a2dp_ota_response_time_array[0]++;
	}
else if(a2dp_ota_response_time < 60)
	{
	a2dp_ota_response_time_array[1]++;
	}
else if(a2dp_ota_response_time < 90)
	{
	a2dp_ota_response_time_array[2]++;
	}
else if(a2dp_ota_response_time < 120)
	{
	a2dp_ota_response_time_array[3]++;
	}
else if(a2dp_ota_response_time < 150)
	{
	a2dp_ota_response_time_array[4]++;
	}
else if(a2dp_ota_response_time < 180)
	{
	a2dp_ota_response_time_array[5]++;
	}
else if(a2dp_ota_response_time < 210)
	{
	a2dp_ota_response_time_array[6]++;
	}
else if(a2dp_ota_response_time < 240)
	{
	a2dp_ota_response_time_array[7]++;
	}
else if(a2dp_ota_response_time < 270)
	{
	a2dp_ota_response_time_array[8]++;
	}
else if(a2dp_ota_response_time < 300)
	{
	a2dp_ota_response_time_array[9]++;
	}
else if(a2dp_ota_response_time >= 300)
	{
	a2dp_ota_response_time_array[10]++;
	}

if(sum_time  < 30)
	{
	a2dp_send_plus_response_time_array[0]++;
	}
else if(sum_time < 60)
	{
	a2dp_send_plus_response_time_array[1]++;
	}
else if(sum_time < 90)
	{
	a2dp_send_plus_response_time_array[2]++;
	}
else if(sum_time < 120)
	{
	a2dp_send_plus_response_time_array[3]++;
	}
else if(sum_time < 150)
	{
	a2dp_send_plus_response_time_array[4]++;
	}
else if(sum_time < 180)
	{
	a2dp_send_plus_response_time_array[5]++;
	}
else if(sum_time < 210)
	{
	a2dp_send_plus_response_time_array[6]++;
	}
else if(sum_time < 240)
	{
	a2dp_send_plus_response_time_array[7]++;
	}
else if(sum_time < 270)
	{
	a2dp_send_plus_response_time_array[8]++;
	}
else if(sum_time < 300)
	{
	a2dp_send_plus_response_time_array[9]++;
	}
else if(sum_time >= 300)
	{
	a2dp_send_plus_response_time_array[10]++;
	}
}

void avdtp_parser(unsigned int index,unsigned int length)
{
	fseek(FP_SNOOP, index,SEEK_SET);
	fgets2(buff,length+1,FP_SNOOP);

		//printf("AVDTP CID = %x %x %x\n",*(short *)(buff+7),Src_CID[1],Dst_CID[1]);
		if(*(short *)(buff+7)==Dst_CID[0] && length >= 11 && Dst_CID_Direction==Now_Direction)
		{
			if(buff[10]==0x03) 
			{
				if(buff[18]==0xff && buff[19]==0x3a && buff[20]==0x05) 
				{
					memcpy(capability_temp,buff+19,9);	
					#ifdef LOG_PRINT
					printf("SETCAPABILITY - LHDC\n");
					#endif
				}
				else 
				{
					memset(capability_temp,0,9);
					#ifdef LOG_PRINT
					printf("SETCAPABILITY - OTHER CODEC\n");
					#endif
				}
				#ifdef PAUSE_CHECK
				system("pause");
				#endif
			}
			if(buff[10]==0x05) 
			{
				if(buff[15]==0xff && buff[16]==0x3a && buff[17]==0x05)
				{
					memcpy(capability_temp,buff+16,9);	
					#ifdef LOG_PRINT
					printf("RECONFIGURE - LHDC\n");
					#endif
				}
				else 
				{
					memset(capability_temp,0,9);
					#ifdef LOG_PRINT
					printf("RECONFIGURE - OTHER CODEC\n");
					#endif
				}
			#ifdef PAUSE_CHECK
			system("pause");
			#endif
			}
			if(buff[10]==0x07)
			{
			#ifdef LOG_PRINT
			printf("AVDTP START\n");
			#endif
			avdtp_media_first_event_time = 0;
			memset(a2dp_ota_response_time_array,0,44);
			memset(a2dp_send_plus_response_time_array,0,44);
			}
		}
		else if (*(short *)(buff+7)==Src_CID[0]&& Src_CID_Direction==Now_Direction)  
		{
			if(buff[10]==0x03 || buff[10]==0x05) 
			{
				if((buff[9]&0x0F)==0x02) 
				{
					if(capability_temp[0]==0x3a && capability_temp[1]==0x05)
					{
						memcpy(capability,capability_temp,9);
						#ifdef LOG_PRINT
						printf("CAPABILITY ACCETP - LHDC %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",capability[0],capability[1],capability[2],capability[3],capability[4],capability[5],capability[6],capability[7],capability[8]);
						#endif
						fwrite(capability_temp,1,9,FP_LHDC);
						output_file_index += 9;
						set_sample_rate(capability[6]&0x0F);
					}
					else 
					{
						#ifdef LOG_PRINT
						printf("CAPABILITY ACCETP - OTHER CODEC %x\n",Src_CID[0]);
						#endif
					}
					#ifdef PAUSE_CHECK
					system("pause");
					#endif
				}
			}
		}	
		else if ((*(short *)(buff+7)==Dst_CID[1] && Dst_CID_Direction==Now_Direction)||(*(short *)(buff+7)==Src_CID[1]&& Src_CID_Direction==Now_Direction))
		{
			if(handle == buff[1]) 
			{
				#ifdef LOG_PRINT
				printf("  -> Write - First CID=%x AVDTP_SEQ=%d LHDC_SEQ=%x Output_Index=%d Length=%d \n",*(short *)(buff+7),(buff[11]*0x100)+buff[12],lhdc_sequence_number,output_file_index,length -23);
				#endif

				if((lhdc_sequence_number&0xFF) != buff[22])
				{
					//sequence_error_count++;
					#ifdef LOG_PRINT
					printf("LHDC SEQ EXPECT %x REAL GET %x\n",lhdc_sequence_number,buff[22]);
					#endif
					*(unsigned char *)&lhdc_sequence_number = buff[22];
					#ifdef PAUSE_CHECK
					system("pause");
					#endif
				}
				lhdc_sequence_number++;
				lhdc_frame_count++;

				if(avdtp_sequence != (buff[11]*0x100)+buff[12])
				{
					sequence_error_count++;
					#ifdef LOG_PRINT
					printf("AVDTP SEQ EXPECT %d REAL GET %d\n",avdtp_sequence,(buff[11]*0x100)+buff[12]);
					#endif
					avdtp_sequence = (buff[11]*0x100)+buff[12];
					#ifdef PAUSE_CHECK
					system("pause");
					#endif
				}
				avdtp_sequence++;
				first_write++;
				acl_tail->avdtp_timestamp =  buff[13]*0x1000000 + buff[14]*0x10000 + buff[15]*0x100 + buff[16];
				fwrite(buff+23,1,length -23 ,FP_LHDC);
				output_file_index += (length -23);
			}
			
		}
}

void handl_update(unsigned char receive_handle)
{
	#ifdef LOG_PRINT
	#ifdef FIXED_HANDLE
	printf("Handle now = %02x , receive = %02x , fixed = %02x\n",handle,receive_handle,FIXED_HANDLE);
	#else
	printf("Handle now = %02x , receive = %02x\n",handle,receive_handle);
	#endif
	#endif
	handle_flag = 1;
	if(handle != receive_handle)
		{
		handle = receive_handle;
		Dst_CID[0] = 0;
		Dst_CID[1] = 0;
		Src_CID[0] = 0;
		Src_CID[1] = 0;
		#ifdef LOG_PRINT
		printf("Handle mismatch & Update %02x",handle);
		#endif
		}
	#ifdef PAUSE_CHECK
	system("pause");
	#endif
}

int dump_hci(void)
{
	unsigned int index=0;
	unsigned int acl_data_length,hci_length;
	

	FP_SNOOP = fopen("./btsnoop_hci.cfa","rb+");
	if(!FP_SNOOP)
	{
		printf("FILE btsnoop_hci.cfa OPEN FAIL !!!!\n");
		fclose(FP_SNOOP);
		return -1;
	}

	
	

	FP_LHDC = fopen("./AUDIO_IN.lhdc","wb");
	if(!FP_LHDC)
	{
		printf("File FP_LHDC OPEN FAIL\n");
		fclose(FP_LHDC);
		return -1;
	}
	
	
	printf("Check bt snoop log title\n");
	fgets2(buff,11,FP_SNOOP);

	if(memcmp(buff,"btsnoop",8)==0)
	{
		printf("String:%s -> btsnoop log correct\n",buff);
	}
	else
	{
		printf("String:%s -> btsnoop log incorrect -> Return\n",buff);
		return 0;
	}
	
	index = index+16;
	fseek(FP_SNOOP, index+24,SEEK_SET);  

	fgets2(buff,5,FP_SNOOP);
	printf("First Command: %x %x %x %x \n",buff[0],buff[1],buff[2],buff[3]);
	if(buff[0]==0x01 && buff[1]==0x03 && buff[2]==0x0C && buff[3]==0x00)
	{
		printf("HCI Reset command \n",buff);
	}
	else if(buff[0]==0x01 && buff[1]==0x09 && buff[2]==0x10 && buff[3]==0x00)
	{
		printf("Not HCI Read BD ADDR \n");
	}
	else
		{
		printf("Not HCI Reset or Read BD ADDR -> Return \n");
		//return 0;
		#ifdef PAUSE_CHECK 
		system("pause");
		#endif
	}
	
	while(1)
	{
		Frame++; 
		#ifdef FRAME_BREAK_COUNT
		if(Frame > FRAME_BREAK_COUNT)
			break;
		#endif

		memset(buff,0,1500);
		fseek(FP_SNOOP, index,SEEK_SET); 
		fgets2(buff,24,FP_SNOOP);

		hci_length = (buff[2]*0x100) + buff[3];
		Now_Direction = buff[11] & 0x01;
		hci_time[7] = buff[16];
		hci_time[6] = buff[17];
		hci_time[5] = buff[18];
		hci_time[4] = buff[19];
		hci_time[3] = buff[20];
		hci_time[2] = buff[21];
		hci_time[1] = buff[22];
		hci_time[0] = buff[23];
		#ifdef LOG_PRINT
		printf("%d Length=%d Direction=%d Time=%llX -",Frame,hci_length,Now_Direction,*(unsigned long long *)hci_time);
		#endif
		//hex_dump(buff,24);

		memset(buff,0,1500);
		fseek(FP_SNOOP, index+24,SEEK_SET);
		fgets2(buff,9,FP_SNOOP);
		//hex_dump(buff,8);
		
		switch(buff[0])
		{
			case 0x01:
				//index = index + 4 + buff[3] +24; 
				#ifdef LOG_PRINT
				printf(" HCI Command ,L:%d\n",4+buff[3]);
				#endif
				break;

			case 0x04:
				//index = index + 3 + buff[2] +24; 
				#ifdef LOG_PRINT
				printf(" HCI Event ,L:%d",3+buff[2]);
				#endif
				if(buff[1]==0x03)
					{
					handl_update(buff[4]);
					#ifdef LOG_PRINT
					printf("\n");
					#endif
					}
				else if(buff[1]==0x13 && buff[4]==handle  && handle_flag==1 && Now_Direction == 1)
					{
					acl_count = acl_count - buff[6];
					acl_now = acl_head;
					#ifdef EVENT_LOG_PRINT
					printf(" B:%d--\n",acl_count);
					#endif
					if( acl_now->avdtp_timestamp!=1 )
						{
						if(avdtp_media_first_event_time == 0)
							{
							avdtp_media_first_event_time = acl_now->acl_time;
							}
						#ifdef EVENT_LOG_PRINT
						printf("  <- ACK Time(%d %llX) = %d ms\n",acl_now->acl_frame,acl_now->acl_time,(*(unsigned long long *)hci_time - acl_now->acl_time)/1000);
						printf("     Stamp=%lld Stamp_Time=%lld Real_Time=%d",acl_now->avdtp_timestamp,((acl_now->avdtp_timestamp*10000)/sample_rate)/1000, (acl_now->acl_time - avdtp_media_first_event_time)/1000);
						printf(" %d ms\n",(signed)((acl_now->acl_time - avdtp_media_first_event_time)- ((acl_now->avdtp_timestamp*10000)/sample_rate))/1000);
						#endif
						a2dp_transfer_time_count((*(unsigned long long *)hci_time - acl_now->acl_time)/1000,(signed)((acl_now->acl_time - avdtp_media_first_event_time)- ((acl_now->avdtp_timestamp*10000)/sample_rate))/1000);
						}
					if(acl_head == acl_tail)
						{
						acl_head = NULL;
						acl_tail = NULL;
						}
					else
						acl_head = acl_head->acl_next;
					free(acl_now);
					}
				else
					{
					#ifdef LOG_PRINT
					printf("\n");
					#endif
					}
				break;

			case 0x02:
				#ifdef FIXED_HANDLE
					if(FIXED_HANDLE != buff[1])
						{
						#ifdef LOG_PRINT
						printf(" Mismatch Handle = %x\n",buff[1]);
						#endif
						break;
						}
				#else
					if(handle != buff[1])
						{
						#ifdef LOG_PRINT
						printf(" Mismatch Handle = %x\n",buff[1]);
						#endif
						break;
						}
				#endif

				acl_data_length = buff[3] + ((buff[4]&0x0F)*256);
				if((acl_data_length+5)!=hci_length)
				{
					#ifdef LOG_PRINT
					printf("acl_data_length+5=%d hci_length=%d !!!!!!!!!",(acl_data_length+5), hci_length);
					#endif
					//system("pause");
				}
				#ifdef LOG_PRINT
				printf(" Acl Data ,L:%d", 5+acl_data_length);
				#endif
				if(buff[1]==handle  && handle_flag==1 && Now_Direction == 0)
					{
					acl_count++;

					acl_now = (struct acl_list *)malloc(sizeof(struct acl_list));
					memset(acl_now,0,sizeof(struct acl_list));
					acl_now->acl_frame = Frame;
					acl_now->acl_time = *(unsigned long long *)hci_time;
					acl_now->avdtp_timestamp = 1;
					if(acl_tail!=NULL)
						acl_tail->acl_next = acl_now;
					else
						acl_head = acl_now;
					acl_tail= acl_now;

					#ifdef LOG_PRINT
					printf(" B:%d++",acl_count);
					#endif
					}
				if(buff[2]==0x20|| buff[2]==0x00)
					{
					#ifdef LOG_PRINT
					printf(" => First Data\n");
					#endif
					if(*(short *)(buff+7) == 0x01)
						cid_parser(index+24, hci_length);
					else if(Dst_CID[0] > 1 && Src_CID[0] > 1 && *(short *)(buff+7) > 1)
						avdtp_parser(index+24, hci_length/*5 + acl_data_length*/);
					}
				else if(buff[2]==0x10)
					{
					#ifdef LOG_PRINT
					printf(" => Continue Data\n");
					#endif
					if(Dst_CID[0] > 1 && Src_CID[0] > 1)
						{
						fseek(FP_SNOOP, (index+24),SEEK_SET);
						fgets2(buff,hci_length,FP_SNOOP);

						#ifdef LOG_PRINT
						printf("  -> Write - Continue CID=%x Output_Index=%d Length=%d \n",*(short *)(buff+7),output_file_index,hci_length-5);
						hex_dump(buff+5,hci_length-5);
						printf("\n");
						#endif
						continue_write++;
						fwrite(buff+5,1,hci_length-5 ,FP_LHDC);
						output_file_index += (hci_length -5);
						}
					}
				else
					{
					#ifdef LOG_PRINT
					printf(" => Other Data\n");
					#endif
					//system("pause");
					}

				//index = index + 5 + acl_data_length +24; 
				break;

			default:
				printf("DEFAULT BREAK %x %x %x\n",buff[0],buff[1],buff[2]);
				printf("Total Frame = %d  avdtp_seq = %d  first_write = %d  continue_write =%d lhdc_seq=%d lhdc_num =%d\n",Frame,avdtp_sequence-1, first_write, continue_write,lhdc_sequence_number - 1,lhdc_frame_count -1 );
				printf("Sequence Error Count = %d \n",sequence_error_count);
				printf("                 <30   <60   <90  <120  <150  <180  <210  <240  <270  <300 300up \n");
				printf("ACK Time Sum   %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d\n",a2dp_ota_response_time_array[0],a2dp_ota_response_time_array[1],a2dp_ota_response_time_array[2],a2dp_ota_response_time_array[3],a2dp_ota_response_time_array[4],a2dp_ota_response_time_array[5],a2dp_ota_response_time_array[6],a2dp_ota_response_time_array[7],a2dp_ota_response_time_array[8],a2dp_ota_response_time_array[9],a2dp_ota_response_time_array[10]);
				printf("Total Response %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d\n",a2dp_send_plus_response_time_array[0],a2dp_send_plus_response_time_array[1],a2dp_send_plus_response_time_array[2],a2dp_send_plus_response_time_array[3],a2dp_send_plus_response_time_array[4],a2dp_send_plus_response_time_array[5],a2dp_send_plus_response_time_array[6],a2dp_send_plus_response_time_array[7],a2dp_send_plus_response_time_array[8],a2dp_send_plus_response_time_array[9],a2dp_send_plus_response_time_array[10]);

				fclose(FP_SNOOP);
				fclose(FP_LHDC);
				system("pause");
				return 0;
		}
		index = index + hci_length +24;

	}
} 
int main()
{
    printf("BT snoop log parsing start !\n");

	dump_hci();
	
    return 0;
}

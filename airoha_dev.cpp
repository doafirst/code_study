#include <iostream>
#include "class.h"


bool airoha_init(char *str,int *error_code)
{
	printf("airoha_int \n");
	return 0;
}

bool airoha_get_mac(char *str,int *error_code)
{
	printf("airoha_get_mac \n");
	return 0;
}

bool airoha_get_uuid(char *str,int *error_code)
{
	printf("airoha_get_uuid \n");
	return 0;
}

bool airoha_get_name(char *str,int *error_code)
{
	printf("airoha_get_name \n");
	return 0;
}

bool airoha_get_key(char *str,int *error_code)
{
	printf("airoha_get_key \n");
	return 0;
}

bool airoha_write_name(char *str,int *error_code)
{
	printf("airoha_write_name \n");
	return 0;
}

bool airoha_write_key(char *str,int *error_code)
{
	printf("airoha_write_key \n");
	return 0;
}

bool airoha_deinit(char *str,int *error_code)
{
	printf("airoha_deinit \n");
	return 0;
}

DevFunc airo_dev_func = {
	"AIROHA ab155x"
	,airoha_init
	,airoha_get_mac
	,airoha_get_uuid
	,airoha_get_name
	,airoha_get_key
	,airoha_write_name
	,airoha_write_key
	,airoha_deinit
};

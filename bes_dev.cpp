#include <iostream>
#include "class.h"


bool bes_init(char *str,int *error_code)
{
	printf("bes_init \n");
	return 0;
}

bool bes_get_mac(char *str,int *error_code)
{
	printf("bes_get_mac \n");
	return 0;
}

bool bes_get_uuid(char *str,int *error_code)
{
	printf("bes_get_uuid \n");
	return 0;
}

bool bes_get_name(char *str,int *error_code)
{
	printf("bes_get_name \n");
	return 0;
}

bool bes_get_key(char *str,int *error_code)
{
	printf("bes_get_key \n");
	return 0;
}

bool bes_write_name(char *str,int *error_code)
{
	printf("bes_write_name \n");
	return 0;
}

bool bes_write_key(char *str,int *error_code)
{
	printf("bes_write_key\n");
	return 0;
}

bool bes_deinit(char *str,int *error_code)
{
	printf("bes_deinit \n");
	return 0;
}

DevFunc bes_dev_func = {
	"BES"
	,bes_init
	,bes_get_mac
	,bes_get_uuid
	,bes_get_name
	,bes_get_key
	,bes_write_name
	,bes_write_key
	,bes_deinit
};

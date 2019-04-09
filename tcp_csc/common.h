/*************************************************************************
	> File Name: common.h
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 11:05:26 2019
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include "head.h"

int socket_create(int port);

int socket_connect(int port, char *host);

int get_conf_value(char *pathname, char * key_name, char *value);

#endif

#ifndef COMMON_H
#define COMMON_H

#include "head.h"


int socket_create(int port);


int socket_connect(int port, char *host);

int get_conf_value(char *pathname, char* key_name, char *value);


#endif

/*************************************************************************
	> File Name: test_conf.c
	> Author: 
	> Mail: 
	> Created Time: Sat 23 Feb 2019 15:46:11 CST
 ************************************************************************/

#include "common.h"

int main() {
    char *file = "mycs.conf";
    char start[20] = {0};
    get_conf_value(file, "start", start);
    return 0;
}


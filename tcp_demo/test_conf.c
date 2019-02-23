/*************************************************************************
	> File Name: test_conf.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 15:46:26 2019
 ************************************************************************/

#include "common.h"

int main(){
    char *file = "/etc/pihealthd.conf";
    char start[20] = {0};
    get_conf_value(file, "start", start);
    printf("start=%s\n", start);
    return 0;
}

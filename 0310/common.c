/*************************************************************************
	> File Name: common.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 二  3/ 5 18:49:53 2019
 ************************************************************************/

#include "common.h"
#define SAVE_PATH "./log/PiHealthLog.log"
struct Node{
    char client_addr;
    struct Node *next;
};


int write_Pi_log(char *PiHealthLog, const char *format, ...){
    FILE * fp = fopen(PiHealthLog, "a+");
    va_list arg;//这是啥
    va_start(arg, format);//这又是啥
    time_t logintime = time(NULL);
    struct tm* tm_log = localtime(&logintime);
    fprintf(fp ,"%d-%02d-%02d %02d:%02d:%02d : ", tm_log->tm_year + 1900, tm_log->tm_mon + 1, tm_log->tm_mday, tm_log->tm_hour, tm_log->tm_min, tm_log->tm_sec);
    vfprintf(fp, format, arg);
    fprintf(fp, "\n");
    va_end(arg);
    fflush(fp);//强制刷新缓冲区
    fclose(fp);

    return 0;
    
}
int socket_create(int port){
    int server_listen;

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket:");
        return -1;
    }
    int yes = 1;
    /*端口复用*/
    if(setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
        close(server_listen);
        perror("setsockopt");
        return 1;
    }
    if(bind(server_listen, (struct sockaddr*)(&server_addr), sizeof(server_addr)) < 0){
        perror("bind:");
        close(server_listen);
        return -1;
    }
    if(listen(server_listen, 20) < 0){
        perror("listen:");
        close(server_listen);
        return -1;
    }
    return server_listen;
}

int socket_connect(int port, char *host){
    int client_listen;

    struct sockaddr_in client_addr;

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(host);

    client_listen = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(client_listen, (struct sockaddr *)(&client_addr), sizeof(client_addr)) < 0){
        perror("connect");
        close(client_listen);
        return -1;
    }

    return client_listen;
}

int get_conf_value(char *pathname, char * key_name, char *value){

    FILE *fd = NULL;
    char *line = NULL;
    char *substr = NULL;
    ssize_t read;
    size_t len = 0;


    fd = fopen(pathname, "r");
    if(fd == NULL){
        perror("fopen");
        exit(1);
    }

    while((read = getline(&line, &len, fd)) != 1){
        //printf("%s", line);
        substr = strstr(line, key_name);
        if(substr == NULL){
            continue;
        } else {
            int tmp = strlen(key_name);
            if(line[tmp] == '='){

                strncpy(value, &line[tmp + 1], (int)read - tmp - 1);
                tmp = strlen(value);
                *(value + tmp - 1) = '\0';
                break;
            } else {
                printf("Next\n");
                continue;
            }
        }
    }


    return 0;

}

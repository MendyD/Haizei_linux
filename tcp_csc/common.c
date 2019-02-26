/*************************************************************************
	> File Name: common.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  2/23 11:03:29 2019
 ************************************************************************/

#include "common.h"
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
    
    if((client_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("client_listen");
        close(client_listen);
        return -1;
    }

    if(connect(client_listen, (struct sockaddr *)(&client_addr), sizeof(client_addr)) < 0){
        perror("connect");
        close(client_listen);
        return -1;
    }
        
    return client_listen;
}

int get_conf_value(char *pathname, char* key_name, char *value){
    
    FILE *fd = NULL;
    char *line = NULL;
    char *substr = NULL;
    ssize_t read = 0;
    size_t len = 0;
    

    fd = fopen(pathname, "r");
    if(fd == NULL){
        printf("Error in Open!\n");
        exit(1);
    }

    while((read = getline(&line, &len, fd)) != 1){
        printf("%s", line);
        fflush(stdout);
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
}

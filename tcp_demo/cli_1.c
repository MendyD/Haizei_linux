/*************************************************************************
	> File Name: cli.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 五  2/22 17:02:52 2019
 ************************************************************************/
#include "head.h"
int main(int argc, char *argv[]){

    if(argc != 4){
        printf("Useage: ./cli IP PORT USERNAME\n");
        return -1;
    }

    int sockfd_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *name = argv[3];

    struct sockaddr_in client_sock;

    client_sock.sin_family = AF_INET;
    client_sock.sin_port = htons(8828);
    client_sock.sin_addr.s_addr = inet_addr("192.168.2.29");

    int con = connect(sockfd_client, (struct sockaddr*)(&client_sock), sizeof(struct sockaddr));
    if(con == -1){
        printf("connect wrong\n");
        perror("/root/noexitfile");
        return 1;
    }

    char buff[128];
    buff[sizeof(buff) - 1] = '\0';
    send(sockfd_client, name, strlen(name) + 1, 0);
    while(1){
        scanf("%[^\n]s", buff);

        getchar();
        if(send(sockfd_client, buff, sizeof(buff), 0) == -1){
            printf("send wrong\n");
        }
        memset(buff, 0, sizeof(buff));
    }
//    close(sockfd_client);
    return 0;
}

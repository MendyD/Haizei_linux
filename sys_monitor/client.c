/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2019 14:28:13 CST
 ************************************************************************/

#include<stdio.h>
#include "common.h"
#define MAX_SIZE 200
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
struct sm_msg{
    int flag;
    int sm_time;
    pthread_mutex_t sm_mutex;
    pthread_cond_t sm_ready;
};

<<<<<<< HEAD
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927

void *buff_log(){
    char buff[MAX_SIZE] = {0};
    int j = 0;
    FILE *popen_mem, *popen_disk, *popen_cpu;
    FILE *fop_mem, *fop_disk, *fop_cpu;
    int read_mem, read_disk, read_cpu;
    while(1){
        int i = 0;
<<<<<<< HEAD
<<<<<<< HEAD
        popen_mem = popen("./script/./MemLog.sh 24", "r");
        fop_mem = fopen("./log/mem.log", "a+");
        read_mem = fread(buff, 1, MAX_SIZE, popen_mem);
        fprintf(fop_mem, "inner while i = %d : MemLog.sh -> %s\n", i,  buff);
        fclose(fop_mem);
        
        memset(buff, 0, sizeof(buff));

        popen_disk = popen("./script/./DiskLog.sh", "r");
        fop_disk = fopen("./log/disk.log", "a+");
        read_disk = fread(buff, 1, MAX_SIZE, popen_disk);
        fprintf(fop_disk, "inner while i = %d : DiskLog.sh -> %s\n", i,  buff);
        fclose(fop_disk);

        memset(buff, 0, sizeof(buff));
        
        popen_cpu = popen("./script/CpuLog.sh", "r");
        fop_cpu = fopen("./log/cpu.log", "a+");
        read_cpu = fread(buff, 1, MAX_SIZE, popen_cpu);
        fprintf(fop_cpu, "inner while i = %d : CpuLog.sh -> %s\n", i,  buff);
        fclose(fop_cpu);
        
        memset(buff, 0, sizeof(buff));
        
=======
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927

        char arr[7][25] = {0};
        strcpy(arr[0], "script/MemLog.sh 24");
        strcpy(arr[1], "script/DiskLog.sh");
        strcpy(arr[2], "script/CpuLog.sh");

        char to[7][25] = {0};
        strcpy(to[0], "log/mem.log");
        strcpy(to[1], "log/disk.log");
        strcpy(to[2], "log/cpu.log");
       
        for(int i = 0; i < 3; i++){
            popen_mem = popen(arr[i], "r");
            fop_mem = fopen(to[i], "a+");
            read_mem = fread(buff, 1, MAX_SIZE, popen_mem);
            fprintf(fop_mem, "%s\n", buff);
            fclose(fop_mem);
            memset(buff, 0, sizeof(buff));
        }
<<<<<<< HEAD
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
        fflush(stdout);
        sleep(10);
    }
    pclose(popen_disk);
    pclose(popen_disk);
    pclose(popen_disk);

}

int main(){
    int sockfd;
    char temp_port[6] = {0};
    char temp_ip[20] = {0};
    char *config = "./chat_c.conf";
    int client_port, server_ip;
    get_conf_value(config, "Client_Port", temp_port);
    get_conf_value(config, "Server_Ip", temp_ip);
    printf("%s\n", temp_port);
    printf("%s\n", temp_ip);
    client_port = atoi(temp_port);
<<<<<<< HEAD
<<<<<<< HEAD

    pthread_t log_t;
    int i = 0;
    while(1){
        if((sockfd = socket_connect(client_port, temp_ip)) < 0){
            perror("socket_create");
            return -1;
        }
        printf("----------%d---------\n", i);
        pthread_create(&log_t, NULL, buff_log, NULL);
        printf("sleep ----------------\n");
        i++;
=======
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
    
    FILE *fopro_mem;//fopen_readonly
    struct sockaddr_in client_addr;

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);
    client_addr.sin_addr.s_addr = inet_addr(temp_ip);


    pthread_t log_t;
    pthread_rwlock_t writelock, readlock;
    int i = 0;
    while(1){
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("client_sockfd");
            close(sockfd);
            return -1;
    }
        printf("---------%d----------\n", i);
        pthread_create(&log_t, NULL, buff_log, NULL);
        if(connect(sockfd, (struct sockaddr *)(&client_addr), sizeof(client_addr)) < 0){
            printf("sockfd < 0 \n");
            close(sockfd);
        } else {
            char buff[MAX_SIZE] = {0};
            sprintf(buff, "hello");
            send(sockfd, buff, strlen(buff), 0);
        }
        i++;
        printf("---------sleep----------\n");
<<<<<<< HEAD
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
=======
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
        sleep(3);
    }
    close(sockfd);
    //pthread_rwlock_t wr_lock;
   // pthread_rwlock_wrlock(wr_lock);
<<<<<<< HEAD
<<<<<<< HEAD
=======
    pthread_join(&log_t, NULL);
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
=======
    pthread_join(&log_t, NULL);
>>>>>>> d3850d090465df8b65263946c37f0a24e7b27927
    return 0;
}

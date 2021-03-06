/*************************************************************************
	> File Name: master.c
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Mar 2019 18:10:05 CST
 ************************************************************************/

#include<stdio.h>
#include "master.h"

int main(){
    char *config = "./chat_c.conf";
    int start[4];
    int finish[4];
    char start_ip[20] = {0};
    char finish_ip[20] = {0};
    char port_t[6] = {0};
    char port_m[6] = {0};
    char ins_s[5] = {0};
    int ins = 0, port, port_M;

    pthread_t print_t, heart_t;

    get_conf_value(config, "From", start_ip);
    get_conf_value(config, "To", finish_ip);
    get_conf_value(config, "INS", ins_s);
    get_conf_value(config, "client_port", port_t);
    get_conf_value(config, "master_port", port_m);

    ins = atoi(ins_s);
    port = atoi(port_t);
    port_M = atoi(port_m);
    transip(start_ip, start);
    transip(finish_ip, start);
    
    int *sum = (int *)malloc(ins *sizeof(int));

    memset(sum, 0, ins * sizeof(int));//置零


    printf("start = %d.%d.%d.%d\n", start[0], start[1], start[2], start[3]);
    //DBG("start = %d.%d.%d.%d\n", start[0], start[1], start[2], start[3]);

    LinkedList *linkedlist = (LinkedList *) malloc(ins * sizeof(LinkedList));
    
    struct sockaddr_in initaddr;
    initaddr.sin_family = AF_INET;
    initaddr.sin_port = htons(port);
    initaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    //初始化队列头结点
    for(int i = 0; i < ins; ++i){
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = initaddr;
        p->next = NULL;
        linkedlist[i] = p;
    }
    //调试
    printf("%s\n", inet_ntoa(linkedlist[0]->client_addr.sin_addr));
    char host[20] = {0};
    
    //字符串拼接
    //插入5个队列中最短的里面
    for(int i = start[3]; i <= finish[3]; ++i){
        sprintf(host, "%d.%d.%d.%d", start[0], start[1], start[2], i);
        initaddr.sin_addr.s_addr = inet_addr(host);
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = initaddr;
        p->next = NULL;
        int sub = find_min(sum, ins);
        insert(linkedlist[sub], p);
        sum[sub]++;
    }

    print("before pthread_create\n");
    fflush(stdout);
    
    struct HEART heartarg;
    heartarg.head = linkedlist[0];
    heartarg.ins = ins;
    heartarg.sum = sum;
    
    if(pthread_create(&heart_t, NULL, heartbeat, (void *)&heartarg) == -1){
        printf("error in pthread_create for heartbeat");
        //DBG("error in pthread_create for heartbeat");
    }


    //每个队列元素打印
    struct PRINT print_para[ins];
    pthread_t t[ins];
    for(int i = 0; i < ins; i++){
        print_para[i].index = i;
        print_para[i].head = linkedlist[i];
        if(pthread_create(&t[i], NULL, print, (void *)&print_para[i]) == -1) {
            printf("error in pthread_create!\n");
            //DBG("error in pthread_create!\n");
            return -1;
        }
    }
    

    int server_listen;
    if((server_listen = socket_create(port_M)) < 0){
        printf("%s\n", strerror(errno));
        //DBG("%s\n", strerror(errno));
        close(server_listen);
        return 1;
    }

    while(1){
        int fd;
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        if((fd = accept(server_listen, (struct sockaddr *)&client_addr, &len) < 0)){
            //DBG("%s\n", strerror(errno));
            printf("%s\n", strerror(errno));
            close(fd);
            continue;
        }
        printf("--> %s\n", inet_ntoa(client_addr.sin_addr));
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        p->client_addr = client_addr;
        p->next = NULL;
        if(check(linkedlist, client_addr, ins) != -1){
            int sub = find_min(sum, ins);
            insert(linkedlist[sub], p);
        }    
    }

    //线程等待
    for(int i = 0; i < ins; i++){
        pthread_join(t[i], NULL);
    }
    pthread_join(print_t, NULL);
    return 0;
}


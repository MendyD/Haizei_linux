/*************************************************************************
	> File Name: master.h
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Mar 2019 18:09:07 CST
 ************************************************************************/

#ifndef _MASTER_H
#define _MASTER_H
#include "common.h"
typedef struct Node {
    struct sockaddr_in client_addr;
    struct Node *next;
}Node, *LinkedList;

struct PRINT{
    LinkedList head;//list0;
    int index;//并发度
};

/*心跳接头体*/
struct HEART{
    LinkedList *head;//linst0
    int ins;//并发度
    int *sum;
};

struct CHECK{
    LinkedList *head;//linst0
    int ins;//并发度
};

int transip(char* sip, char* ip){
    if(sip == NULL){
        return -1;
    }
    char temp[4];
    int count = 0;
    while(1){
        int index = 0;
        while(*sip != '\0' && *sip != '.' && count < 4){
            temp[index++] = *sip;
            sip++;
        }
        if(index == 4) return -1;
        temp[index] = '\0';
        ip[count] = atoi(temp);
        printf("ip[%d] = %d\n", count, ip[count]);
        count++;
        if(*sip == '\0'){
            if(count == 4) return 0;
        } else {
            sip++;
        }
        printf("\n");
        return 0;
    }
}

int insert(LinkedList head, Node *node){
    Node *p;
    p = head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = node;
    return 1;
}

int find_min(int *sum, int ins){
    int ans = 0;
    for(int i = 0; i < ins; i++){
        if(*(sum + i) < *(sum + ans)){
            ans = i;
        }
    }
    return ans;
}


void *print(void *arg){
    struct PRINT *print_para = (struct PRINT*)arg;
    int index = print_para->index;
    printf("index = %d, %d\n", index, print_para->index);
    char filename[50] = {0};
    sprintf(filename, "./%d.log", index);
    int temp = 0;
    while(1) {
        FILE *file  = fopen(filename, "w");
        Node *p = print_para->head;
        while (p->next != NULL){
           // printf("%s : %d\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
            fprintf(file, "%s : %d\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
            p = p->next;
        }
        fclose(filename);
        sleep(1);
    }
    return NULL;
}

int connect_sock(struct sockaddr_in addr){
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        DBG("%s\n", strerror(errno));
        return -1;
    }

    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        printf("%s\n" , strerror(errno));
        //DBG("%s\n" , strerror(errno));
        close(sockfd);
        return -1;
    }

    close(sockfd);
    return 0;
}

int check(LinkedList *head, struct sockaddr_in addr,int ins){
    for(int i = 0; i < ins; i++){
        Node *p;
        p = head[i];
        while(p->next != NULL){
            if(addr.sin_addr.s_addr == p->next->client_addr.sin_addr.s_addr){
                //DBG("%s *** in linst***\n", inet_ntoa(p->next->client_addr.sin_addr));
                printf("%s *** in linst***\n", inet_ntoa(p->next->client_addr.sin_addr));
                return -1;
            }
            p = p->next;
        }
    }
    return 0;
}


/*心跳函数*/
void *heartbeat(void *arg){
    struct HEART *heart;
    heart = (struct HEART *)arg;
    while(1){
        for(int i = 0; i < heart->ins; i++){
            Node *p, *q;
            p = heart->head[i];
            while(p != NULL && p->next != NULL){
                //char ip[20] = {0};
                //strcpy(ip, inet_ntoa(p->next->client_addr.sin_addr));
                printf("sum in %ded list is %d\n", i, heart->sum[i]);
                if(connect_sock(p->next->client_addr) < 0){
                    q = p->next;
                    p->next = p->next->next;
                    free(q);
                    heart->sum[i]--; 
                } else {
                    printf("%s : %d online\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
                    //DBG("%s : %d online\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
                }
                p = p->next;
            }
            sleep(5);
        }
    }
    return NULL;
}
#endif

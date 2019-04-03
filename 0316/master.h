/*************************************************************************
	> File Name: master.h
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Mar 2019 18:09:07 CST
 ************************************************************************/
#include "common.h"
typedef struct Node {
    struct sockaddr_in client_addr;
    int node_sock;
    struct Node *next;
}Node, *LinkedList;

struct PRINT{
    LinkedList head;//list0;
    int index;//并发度
};

/*心跳接头
* int node_sock;:体*/
struct HEART{
    LinkedList *head;//linst0
    int ins;//并发度
    int *sum;
    long timeout;
};

struct CHECK{
    LinkedList *head;//linst0
    int ins;//并发度
};

int transip(char *sip, int *ip){
    if(sip == NULL) return -1;
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
    }
    printf("\n");
    return 0;
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
    struct PRINT *print_para = (struct PRINT *)arg;
    int index = print_para->index;
    printf("index = %d, %d\n", index, print_para->index);
    char filename[50] = {0};
    sprintf(filename, "./%d.log", index);
    int temp = 0;
    while(1) {
        FILE *file  = fopen(filename, "w");
        Node *p = print_para->head;
        while (p->next != NULL){
            fprintf(file, "%s : %d\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
            p = p->next;
        }
        fclose(file);
        sleep(1);
    }
    return NULL;
}

int connect_sock( struct sockaddr_in addr){
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        return -1;
    }
    //设置非阻塞fcntl
    if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        close(sockfd);
        return -1;
    }
    //close(sockfd);
    return 0;
}

int check(LinkedList *head, struct sockaddr_in addr,int ins){
    for(int i = 0; i < ins; i++){
        Node *p;
        p = head[i];
        while(p->next != NULL){
            if(addr.sin_addr.s_addr == p->next->client_addr.sin_addr.s_addr){
                DBG("\033[46;30m%s *** in list%d***\033[0m\n", inet_ntoa(p->next->client_addr.sin_addr), i);
                return -1;
            }
                p = p->next;
        }
    }
    return 0;
}

void *heartbeat(void *arg){
    struct HEART *heart;
    heart = (struct HEART *)arg;
    while(1){
        for(int i = 0; i < heart->ins; i++){
            Node *p;
            DBG("\033[34m in 😊  %d\033[0m\n", i);
            fflush(stdout);
            p = heart->head[i];
            while(p != NULL && p->next != NULL){
                //char ip[20] = {0};
                //strcpy(ip, inet_ntoa(p->next->client_addr.sin_addr))
                DBG("sum in \033[33m%ded\033[0m list is \033[33m%d\033[0m\n", i, heart->sum[i]);
                if(connect_sock(p->next->client_addr) < 0){
                    DBG("\033[35mdelete\033[0m -- %s : %d\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
                    Node *temp;
                    temp = p->next;
                    p->next = p->next->next;
                    free(temp);
                    heart->sum[i]--;
                    /*if(heart->sum[i] > 0){
                        heart->sum[i]--;
                    } else {
                        heart->sum[i] = 0;
                    }*/
                } else {
                    DBG("%s : %d \033[35monline\033[0m\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
                    p = p->next;
                }
                printf("--------------------heartbeat\n");
            }
            //sleep(2);
        }
    }
    return NULL;
}
void *heartbeat1(void *arg){
    struct HEART *heart;
    heart = (struct HEART *)arg;
    struct timeval tm;
    tm.tv_sec  = 0;
    tm.tv_usec = 30000;
    while(1){
        sleep(10);//十秒心跳一次
        DBG("-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        for(int i = 0; i < heart->ins; i++){
            DBG("i = %d\n", i);
            Node *p;
            p = heart->head[i];
            fd_set wfd;
            FD_ZERO(&wfd);
            int max;
            while(p != NULL && p->next != NULL){
                
                int sock = -1;//此处sock为什么要初始化
                if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
                    DBG("socket");
                }
                unsigned long ul = 1;
                ioctl(sock, FIONBIO, &ul);//设置非阻塞状态此处ul什么意思
                connect(sock, (struct sockaddr *)&(p->next->client_addr),sizeof(struct sockaddr));
                FD_SET(sock, &wfd);//加入到wfd集合中
                max = sock;
                p->next->node_sock = sock;//加入到链表中
                DBG("SOCK %d\n", sock);
                p = p->next;
            }
            usleep(300000);//0.3s = 300000μm 1s = 1000000μm由于sleep不可以使用小数，且增加cpu效率使用usleep只有linux系统可以windows不可以
            int sel_temp;
            sel_temp = select((max + 1), NULL, &wfd, NULL, &tm);
            DBG("Sel_temp = %d\n", sel_temp);
            if(sel_temp < 0){
                perror("error");
                continue;
            } 
            p = heart->head[i];
            if(sel_temp == 0){
                //表示超时
                //delete;
                if(p->next != NULL && p != NULL){
                    FD_CLR(p->next->node_sock, &wfd);
                    close(p->next->node_sock);
                    DBG("%s:%d-------\033[32mdeleting\033[0m\n");
                    Node *temp;
                    temp = p->next;
                    p->next = p->next->next;
                    free(temp);
                    heart->sum[i]--;
                }
            } else {
                //>0表示已准备好的sock
                int fd_isset;
                while(p != NULL && p->next != NULL){
                    if(FD_ISSET(p->next->node_sock, &wfd)){
                        int value = -1;//为什么等于-1
                        int len = sizeof(int);
                        getsockopt(p->next->node_sock, SOL_SOCKET, SO_ERROR, &value, (socklen_t *)&len);
                        if(value == 0){ 
                            FD_CLR(p->next->node_sock, &wfd);
                            struct sockaddr_in temp;
                            int temp_len = sizeof(temp);
                            getpeername(p->next->node_sock, (struct sockaddr *)&temp, (socklen_t *)&temp_len);
                            close(p->next->node_sock);
                            DBG("%s:%d-------%d-------\033[32monline\033[0m\n",inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port), p->next->node_sock);
                            p = p->next;
                        } else {
                            FD_CLR(p->next->node_sock, &wfd);
                            close(p->next->node_sock);
                            DBG("%s:%d------\033[32mdeleting\033[0m\n", inet_ntoa(p->next->client_addr.sin_addr), ntohs(p->next->client_addr.sin_port));
                            Node *temp;
                            temp = p->next;
                            p->next = p->next->next;
                            free(temp);
                            heart->sum[i]--;
                        }
                    } else {
                        FD_CLR(p->next->node_sock, &wfd);
                        close(p->next->node_sock);
                        Node *temp;
                        temp = p->next;
                        p->next = p->next->next;
                        free(temp);
                        heart->sum[i]--;
                    }
                }
            }
        }
    }
    return NULL;
}

#include "common.h"
#include "head.h"

struct Message{
        char from[20];
        int flag;
        char message[1024];

};
typedef struct Node{
    int fd;
    char name[20];
    struct Node *next;
}Node, *Linkedlist;

Linkedlist linklist;

Linkedlist insert(Linkedlist head, Node *node) {
    Node *p;
    p = head;
    while (p->next != NULL) {
        p = p->next;
    } 
    p->next = node;
    return head;
}


void delete(Linkedlist head, char *name) {
    Node *p, *q;
    p = head;
    while (p->next != NULL && strcmp(p->next->name, name)) {
        p = p->next;
    }
    if (p->next == NULL) {
        return ;
    }
    q = p->next;
    p->next = p->next->next;
    free(q);
}


void *print() {
    Linkedlist temp;
    while (1) {
        temp = linklist;
        fflush(stdout);
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }
}

int check(char *name) {
    Linkedlist temp;
    temp = linklist;
    while (temp->next != NULL) {
        if (strcmp(temp->next->name, name) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


int check_fd(char *name) {
    Linkedlist temp;
    temp = linklist;
    while (temp->next != NULL) {
        if (strcmp(temp->next->name, name) == 0) {
            return temp->next->fd;
        }
        temp = temp->next;
    }
    return 0;
}

int sum(Linkedlist head){
    if(head == NULL){
        return 0; 
    }
    Node *current_node = head;
    int i = 0;
    while(current_node != NULL){
        current_node = current_node->next;
        i++;
    }
    return i;
}

void output(Linkedlist head){
    if(head == NULL){
        printf("nobody online!"); 
    }
    Node *current_node = head;
    while(current_node != NULL){
        printf("%s ", current_node->name);
        current_node = current_node->next;
    }
    printf("\n");
}
void send_to (char *name, struct Message msg) {
    int fd = check_fd(name);
    send(fd, (char *)&msg, sizeof(msg), 0);
}


void send_all (Linkedlist linklist, struct Message msg) {
    Linkedlist temp;
    temp = linklist;
    while (temp->next != NULL) {
        send_to(temp->next->name, msg);
        temp = temp->next;
    }
}

pthread_mutex_t now_t;
void *addnode(void *argv) {
    Node *p;
    p = (Node *)argv;
    pthread_mutex_lock(&now_t);
    linklist = insert(linklist, p);
    pthread_mutex_unlock(&now_t);
    int people_sum = sum(linklist);
    char welcome[1024];
    struct Message msg;
    sprintf(msg.message, "%s 您已登录服务器!\n", p->name);
    msg.flag = 2;
    send_to(p->name, msg);
    fflush(stdout);
    sprintf(msg.message, "%s 上线了，快来和他打个招呼吧! 在线人数： %d 个人\n", p->name, people_sum - 1);
    printf(msg.message, "%s 上线了，快来和他打个招呼吧! 在线人数： %d 个人\n", p->name, people_sum - 1);
    msg.flag = 2;
    send_all(linklist, msg);
    char buffer[1024] = {0};
    while (recv(p->fd, buffer, sizeof(buffer), 0) > 0) {
        struct Message msg;
        printf("%s: %s\n", p->name, buffer);
        strcpy(msg.from, p->name);
        strcpy(msg.message, buffer);
        msg.flag = 0;
        fflush(stdout);
        if (buffer[0] == '#') {
            pthread_mutex_lock(&now_t);
            printf("%s 查询在线人数！\n", p->name);
            sprintf(msg.message, "在线人数： %d 个人", sum(linklist) - 1);
            output(linklist);
            send_to(p->name, msg);
            pthread_mutex_unlock(&now_t);
        } else if (buffer[0] == '@') {
            char to[20] = {0};
            int i = 0;
            for (; i < 20; i++) {
                if (buffer[i] == ' ') break;
            }
            strncpy(to, buffer + 1, i - 1);
            if (check(to)){
                printf("发送私聊信息! -> [%s] \n", to);
                msg.flag = 1;
                send_to(to, msg);
            } else {
                sprintf(msg.message,"非法用户名！-> [%s]\n", to);
                send_to(p->name, msg);

            }
        } else {
            send_all(linklist, msg);
        }
        memset(buffer, 0, sizeof(buffer));
    }
    fflush(stdout);
    sprintf(msg.message, "%s 已下线，在线人数 %d\n", p->name, sum(linklist) - 2);
    msg.flag = 2;
    send_all(linklist, msg);
    printf("%s 已下线, 在线人数 : %d\n", p->name, sum(linklist) - 2);
    delete(linklist, p->name);
}


int main() {
    pthread_t print_t, addnode_t;
    int socketfd, server_port, server_listen;
    char temp_port[5] = {0};
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, "");
    p->next = NULL;
    linklist = p;

    pthread_create(&print_t, NULL, print, NULL);

    char *config = "./chat.conf";
    
    get_conf_value(config, "Server_Port", temp_port);

    server_port = atoi(temp_port);

    if ((server_listen = socket_create(server_port)) < 0){
        printf("Error in create socket!\n");
        return 1;
    }

    while (1) {
        
        char name[20] = {0};

        if ((socketfd = accept(server_listen, NULL, NULL)) < 0) {
            printf("accept");
            return 1;
        }

        recv(socketfd, name, sizeof(name), 0);
        if (!check(name)) {
            Node *node;
            node = (Node *)malloc(sizeof(Node));
            node->fd = socketfd;
            strcpy(node->name, name);
            node->next = NULL;
            printf("用户%s已登录！\n", node->name);
            pthread_create(&addnode_t, NULL, addnode, (void *)node);
        }
    }    
    pthread_join(&print_t, NULL);
    return 0;

}




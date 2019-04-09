/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 10 Mar 2019 14:28:13 CST
 ************************************************************************/

#include<stdio.h>
#include "common.h"
struct sm_msg{
    int flag;//检测心跳次数
    int sm_time;//心跳时间
    pthread_mutex_t sm_mutex;//线程互斥量
    pthread_cond_t sm_ready;
};

char *config = "./chat_c.conf";
char *share_memory = NULL;
char log_dir[50] = {0};
char log_backup[50] = {0};
char back_logdir[50] = {0};
double dyaver = 0;
int Max_KeepAlive_Interval = 0;
int ctrlport;
int sock_ctrl;

struct sm_msg *msg;

pthread_mutexattr_t m_attr;
pthread_condattr_t c_attr;

//心跳
bool client_heart(char *ip, int port){
    bool reg = true;
    int sockfd;
    if((sockfd = socket_connect(port, ip)) < 0){
        reg = false;
    }
    char buff_send[256] = {0};
    char buff_recv[256] = {0};
    char hostname[32];
    struct passwd *pwd;
    gethostname(hostname, strlen(hostname));
    pwd = getpwuid(getuid());
    sprintf(buff_send, "Login -> %s | on %s", pwd->pw_name, hostname);
    send(sockfd, buff_send, strlen(buff_send), 0);
    if (recv(sockfd, buff_recv, sizeof(buff_recv), 0) > 0) {
        DBG("\033[32m%s\033[0m\n", buff_recv);
    } else {
        close(sockfd);
    }
    return reg;
}

//系统检测
void sys_detect(int type){
    int time_i = 0;
    char temp_sc[20];
    sprintf(temp_sc, "Src%d", type);
    char run[100] = {0};
    char buffer[4096] = {0};
    char src[50] = {0};
    get_conf_value(config, temp_sc, src);
    FILE *fstream = NULL;
    int times = 0;
    int Inactive_Interval = 0;
    char temp[4] = {0};
    char logname[50] = {0};
    get_conf_value(config, "WriteEveryTimes", temp);
    times = atoi(temp);
    get_conf_value(config, "Inactive_Interval", temp);
    Inactive_Interval = atoi(temp);

    //printf("=======switch type = %d ======\n", type);
    switch(type){
        case 100://cpu
            time_i = 1;
            sprintf(logname, "%s/cpu.log", log_dir);
            //printf("%s/cpu.log\n", log_dir);
            break;
        case 101://mem
            time_i = 5;
            sprintf(logname, "%s/mem.log", log_dir);
            //printf("%s/mem.log\n", log_dir);
            break;
        case 102://disk
            time_i = 60;
            sprintf(logname, "%s/disk.log", log_dir);
            //printf("%s/disk.log\n", log_dir);
            break;
        case 103://proc
            time_i = 30;
            sprintf(logname, "%s/pro.log", log_dir);
            //printf("%s/pro.log\n", log_dir);
            break;
        case 104://sysinfo
            time_i = 60;
            sprintf(logname, "%s/sys.log", log_dir);
            //printf("%s/sys.log\n", log_dir);
            break;
        case 105://userinfo
            time_i = 60;
            sprintf(logname, "%s/user.log", log_dir);
            //printf("%s/user.log\n", log_dir);
            break;
    }
    sprintf(run, "bash ./script/%s", src);
    //printf("---------bash ./script/%s\n", src);
    fflush(stdout);
    if(type == 101) {
        sprintf(run, "bash ./script/%s %f", src, dyaver);
        fflush(stdout);
    }
    while(1){
        for(int i = 0; i < times; i++){
            char buff[400] = {0};
            memset(buffer, 0, sizeof(buffer));
            if(NULL == (fstream = popen(run, "r"))){
                DBG("popen error!\n");
                exit(1);
            }
            //printf("---------run = %s\n", run);
            if(type == 101){
                if(NULL != fgets(buff, sizeof(buff), fstream)){
                    strcat(buffer, buff);
                }
                if(NULL != fgets(buff, sizeof(buff), fstream)){
                    dyaver = atof(buff);
                } else{
                    dyaver = 0;
                }
            } else {
                while(NULL != fgets(buff, sizeof(buff), fstream)){
                    strcat(buffer, buff);
                }
            }

            sleep(time_i);
            pclose(fstream);
        }
        if(type == 100){
            DBG("\033[31m --❤-- \033[0m ");
            fflush(stdout);
            pthread_mutex_lock(&msg->sm_mutex);
            if(msg->flag++ >= Inactive_Interval -1) {
                if(msg->sm_time == 0){
                    DBG("\n系统自检超过 \033[33m%d\033[0m 次, Master 无连接\n", msg->flag);
                    pthread_cond_signal(&msg->sm_ready);
                    DBG("发送信号，开启心跳程序 💕\n");
                }
                msg->flag = 0;
            }
            pthread_mutex_unlock(&msg->sm_mutex);
        }
        FILE *fd = fopen(logname, "a+");
        //printf("---------logname = %s\n", logname);
        if(NULL == fd){
            DBG("error open logfile!\n");
            exit(1);
        }
        if(flock(fd->_fileno, LOCK_EX) < 0){
            DBG("flock : %s\n", strerror(errno));
        }
        fwrite(buffer, 1, strlen(buffer), fd);
        fclose(fd);
    }
}


int main(){
    int shmid;
    int heart_listen;
    int port_heart, port_master;
    char ip_master[20] = {0};
    char port_temp[6] = {0};
    char max_temp[1] = {0};
    get_conf_value(config, "ClientPort", port_temp);
    port_heart = atoi(port_temp);
    get_conf_value(config, "MasterPort", port_temp);
    port_master = atoi(port_temp);
    get_conf_value(config, "Master", ip_master);
    get_conf_value(config,"LogDir", log_dir);
    get_conf_value(config, "BackupLogDir", back_logdir);
    get_conf_value(config, "Max_KeepAlive_Interval", max_temp);
    Max_KeepAlive_Interval = atoi(max_temp);
    get_conf_value(config, "CtrlPort", port_temp);
    ctrlport = atoi(port_temp);
    //mkdir(log_dir, 0755);
    //mkdir(log_backup, 0755);

    if((shmid = shmget(IPC_PRIVATE, sizeof(struct sm_msg), 0666|IPC_CREAT)) == -1){
        DBG("Error in shmget: %s\n", strerror(errno));
        return -1;
    }
    if((share_memory = (char *)shmat(shmid, 0, 0)) == NULL){
        DBG("shmat: %s\n", strerror(errno));
        return -1;
    }

    msg = (struct sm_msg *)share_memory;
    msg->flag = 0;
    msg->sm_time = 0;
    pthread_mutexattr_init(&m_attr);
    pthread_condattr_init(&c_attr);
    pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);
   
    pthread_mutex_init(&msg->sm_mutex, &m_attr);
    pthread_cond_init(&msg->sm_ready, &c_attr);
    int pid;
    connect_noblock(port_master, ip_master, 1);
    
    printf("hello\n");
    if((pid = fork()) < 0){
        DBG("fork error\n");
        return -1;
    }
    //子进程监听心跳
    if(pid != 0){
        if((heart_listen = socket_create(port_heart)) < 0){
            DBG("Error in socket_create!");
            return -1;
        }
        printf("hello_heart_listen\n");
        while(1){
            int fd;
            int b = 0;
            printf("hello_accept%d\n", b);
            if((fd = accept(heart_listen, NULL, NULL) < 0)){
                DBG("accept error!\n");
                close(fd);
            }
            DBG("\033[35m❤ \033[0m");
            fflush(stdout);
            char temp[3] = {0};
            strcpy(temp, "OK");

            if(recv(fd, temp, sizeof(temp), 0) == 0){
                close(fd);
                DBG("🐇");
                fflush(stdout);
                pthread_mutex_lock(&msg->sm_mutex);
                msg->sm_time = 0;
                msg->flag = 0;
                pthread_mutex_unlock(&msg->sm_mutex);
            }
        }
    } else {
        int pid1;
        printf("pid1\n");
        if((pid1 = fork()) < 0){
            DBG("fork error pid1!\n");
            return -1;
        }
        if(pid1 == 0){
            printf("心跳开始 pid = 0\n");
            float i = 0;
            while(1){
                //心跳与server端连接:
                pthread_mutex_lock(&msg->sm_mutex);
                DBG("孙子进程等待信号开启心跳!\n");
                pthread_cond_wait(&msg->sm_ready, &msg->sm_mutex);
                DBG("获得心跳信号，开始心跳💕\n");
                pthread_mutex_unlock(&msg->sm_mutex);
                while(1){
                    if(client_heart(ip_master, port_master)){
                        DBG("if 第 %d次：💕 👌 \n", msg->sm_time);
                        pthread_mutex_lock(&msg->sm_mutex);
                        msg->sm_time = 0;
                        msg->flag = 0;
                        pthread_mutex_unlock(&msg->sm_mutex);
                        fflush(stdout);
                        break;
                    } else {
                        DBG("else 第 %d 次：💕 ✘\n", msg->sm_time);
                        pthread_mutex_lock(&msg->sm_mutex);
                        msg->sm_time++;
                        pthread_mutex_unlock(&msg->sm_mutex);
                        fflush(stdout);
                    }
                    sleep(6 * msg->sm_time);
                    if(msg->sm_time > Max_KeepAlive_Interval) msg->sm_time = Max_KeepAlive_Interval;
                    pthread_mutex_unlock(&msg->sm_mutex);
                }
            }
        } else {
            printf("pid1 = %d\n", pid1);
            int x = 0;
            int pid2;
            for(int i = 100; i < 106; ++i){
                x = i;
                printf("pid2 %d\n", i);
                if((pid2 = fork()) < 0){
                    DBG("error fork pid2\n");
                    continue;
                }
                if(pid2 == 0) break;
            }
            if(pid2 == 0){
                sys_detect(x);
            } else {
                DBG("Father!\n");
                int client_listen;
                if((client_listen = socket_create(ctrlport)) < 0){
                    DBG("create client_listen error : %s\n", strerror(errno));
                }
                while(1){
                    if((sock_ctrl = accept(client_listen, NULL, NULL)) < 0){
                        DBG("client_listen : ----- %d\n", client_listen);
                        DBG("Error accept client_listen : %s\n", strerror(errno));
                        continue;
                    }
                    DBG("\033[35m🌹\033[0m");
                    fflush(stdout);
                    pthread_mutex_lock(&msg->sm_mutex);
                    msg->flag = 0;
                    pthread_mutex_unlock(&msg->sm_mutex);
                    close(sock_ctrl);
                }
            }
        }
    }
}

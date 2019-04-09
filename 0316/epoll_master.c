/*************************************************************************
	> File Name: epoll.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 四  4/ 4 19:17:30 2019
 ************************************************************************/

#include<stdio.h>
#include "common.h"
#define MAX 1024
int main(){
    int server_listen;
    if((server_listen = socket_create(7731)) < 0){
        perror;
    }
    
    int epollfd, nfds;
    char buff[1024] = {0};
    epollfd = epoll_create(500);
    struct epoll_event ev, events[MAX];
    ev.events = EPOLLIN;
    ev.data.fd = server_listen;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev);
    while(1){
        nfds = epoll_wait(epollfd, events, MAX, -1);
        for(int i = 0; i < nfds; ++i){
            if(events[i].data.fd == server_listen && events[i].events & EPOLLIN){
                int sockfd = accept(server_listen, NULL, NULL);
                if(sockfd == -1){
                    perror("accept");
                }
                ev.data.fd = sockfd;
                ev.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);
            } else if(events[i].events & EPOLLIN){
                int recvn = recv(events[i].data.fd, buff, sizeof(buff), 0);
                if(recv == 0){
                    ev.data.fd = events[i].data.fd;
                    close(ev.data.fd);
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                } else {
                    printf("%s\n", buff);
                    fflush(stdout);
                    ev.data.fd = events[i].data.fd;
                    ev.events = EPOLLOUT;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
                }
            } else if(events[i].events & EPOLLOUT){
                send(events[i].data.fd, buff, strlen(buff), 0);
                ev.events = EPOLLIN;
                ev.data.fd = events[i].data.fd;
                epoll_ctl(epollfd, EPOLL_CTL_MOD, events[i].data.fd, &ev);
            }
        }
    }
    return 0;

}

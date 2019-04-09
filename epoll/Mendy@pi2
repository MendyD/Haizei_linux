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
            } else if(event[i].events & EPOLLIN){
                char buff[1024] = {0};
                int recvn = recv(event[i].data.fd, buff, sizeof(buff), 0);
                ev.data.fd = event[i].data.fd;
                ev.events = EPOLLOUT;
                ev.data.ptr
                epoll_ctl(epollfd, EPOLL_CTL_MOD, event[i].data.fd, &ev);
            } else if(event[i].events & EPOLLOUT){
                send(event[i].data.fd, "hi", 4, 0);
                close(event[i].data.fd);
                epoll_ctl(epollfd, EPOLL_CTL_DEL, event[i].data.fd, &ev);
            }
        }
    }
    return 0;

}

/*************************************************************************
	> File Name: main.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 一  1/21 22:34:53 2019
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CMD 50

int buildin_command(char **argv){
    if(strcmp(argv[0],"exit")==0){
        exit(0);
    }
    if(strcmp(argv[0],"cd")==0){
        if(chdir(argv[1])){
            //chdir 相当于cd.成功返回0失败返回-1
            printf("wrong input:%s%s:no such directory\n",argv[0], argv[1]);
        }
        return 1;
    }
    return 0;
}

int parseline(char *buf,char**argv){ 
    while(*buf==' '){
        buf++;
    }
    int delim = 0;
    int argc = 0;

    while(*buf!='\n'){
        while(buf[delim]!='\n'&&buf[delim]!=' '){
            delim++;
        }

        if(buf[delim] == '\n'){
            buf[delim] = '\0';
            argv[argc++] = buf;
            break;
        }
        buf[delim] = '\0';
        argv[argc++] = buf; 

        buf+=delim+1;
        /*指示器indicator=0*/
        delim = 0;
        while(*buf==' '){
            buf++;
        }
    }
    argv[argc] = NULL;
    return 0;
}

void eval(char *cmdstring){
    char *argv[MAX_CMD];
    char buf[MAX_CMD];

    strcpy(buf,cmdstring);
    parseline(buf,argv);
    if(argv[0]==NULL){
        return;
    }
    if(buildin_command(argv)) return;
    int pid = fork();
    if(pid == 0){
        if(execvp(argv[0],argv)<0){
            printf("%s:command not found.\n",argv[0]);
            exit(0);
        }
    }
    wait(&pid);
}

int main(int argc,char *argv[]){

    char cmdstring[MAX_CMD];
    int n;
    while(1){
        printf("*myls*>\n");
        /*read 返回值为读到的字节数0,n, 错误为-1*/
        if((n=read(0,cmdstring,MAX_CMD))<0){
            printf("read error");
        }
        eval(cmdstring);
    }
    return 0;
}

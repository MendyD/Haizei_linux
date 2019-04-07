/*************************************************************************
	> File Name: common.h
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 六  4/ 6 19:28:07 2019
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#define PATHNAME .
#define PROJ_ID 123

int create_shm(int size);
int get_shm(int size);
int destory(int shmid);

#endif

/*************************************************************************
	> File Name: a.c
	> Author: Mendy
	> Mail: dolai_c@163.com
	> Course: 
	> Created Time: 一  1/21 23:20:48 2019
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
int main(void)
{
    void* buf ;
    int handle;
    int bytes ;
    buf=malloc(10);
    /*
    Looks for a file in the current directory named TEST.$$$ and attempts
    to read 10 bytes from it.To use this example you should create the
    file TEST.$$$
    */
    handle=open("TEST.$$$",O_RDONLY|O_BINARY,S_IWRITE|S_IREAD);
    if(handle==-1)
    {
        printf("ErrorOpeningFile\n");
        exit(1);
    }
    bytes=read(handle,buf,10);
    if(bytes==-1)
    {
        printf("ReadFailed.\n");
        exit(1);
    }
    else 
    {
        printf("Read:%dbytesread.\n",bytes);
    }
    return 0 ;
}

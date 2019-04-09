/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Feb 2019 09:44:45 CST
 ************************************************************************/

#include<stdio.h>
int main(){
    FILE *fpOut=fopen("chat.log","wt+");
    int a=1;
    fprintf(fpOut,"%d",a);
    fclose(fpOut);
    return 0;
}

/*************************************************************************
	> File Name: ab.c
	> Author: 
	> Mail: 
	> Created Time: Wed 20 Mar 2019 18:03:11 CST
 ************************************************************************/

#include<stdio.h>
void swap(int c, int d){
    int temp;
    temp = c;
    c = d;
    d = temp;
    printf("c = %d, d = %d\n", c, d);
}

void swap1(int *e, int *f){
    int temp;
    temp = *e;
    *e = *f;
    *f = temp;
    printf("e = %p, f = %p\n", e, f);
}


int main(){
    
    int a = 10;
    int b = 20;

    printf("a = %d, b = %d\n", a, b);
    swap(a, b);
    printf("swap a = %d, b = %d\n", a, b);
    swap1(&a, &b);
    printf("swap1 a = %d, b = %d\n", a, b);

    return 0;
}

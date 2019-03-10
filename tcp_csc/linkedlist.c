/*************************************************************************
	> File Name: linkedlist.c
	> Author: 
	> Mail: 
	> Created Time: Wed 27 Feb 2019 10:23:47 CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    struct Node *next;
    char name[20];
} Node, *LinkedList;

LinkedList insert_node(LinkedList head, Node *node){
    if(head = NULL){
        head = node;
        return head;
    }
    node->next = head; 
    head = node;
    return head;
}
void output(LinkedList head){
    if(head == NULL){
        return ;
    }
    Node *current_node = head;
    while(current_node != NULL){
        printf("%s ", current_node->name);
        current_node = current_node->next;
    }
    printf("\n");
}
void clear(LinkedList head){
    Node *current_node = head;
    while(current_node != NULL){
        Node *delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);
    }
}
int main(){
    LinkedList linkedlist = NULL;
    char name[20] = {0};
    
    while(scanf("%s", name) != EOF){
        Node *node = (Node *)malloc(sizeof(Node));
        strcpy(node->name, name);
        node->next = NULL;
        linkedlist = insert_node(linkedlist, node);
        output(linkedlist);
        free(node);
    }
    clear(linkedlist);
    return 0;
}

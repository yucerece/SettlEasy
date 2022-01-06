#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int getIndexofthemem(MemberInfo* mem, char name[], int len){
    int index = -1;
    for(int i = 0; i < len; i++){
        if(strcmp(mem[i].name, name) == 0) index = i;
    }
    return index;
}

int bfs(float **expenseGraph, float** rGraph, int s, int t, int parent[], int visited[]){
    for(int i = 0; i <= t; i++) visited[i] = 0;
    for(int i = 0; i <= t; i++) parent[i] = -1;

    Queue* queue = NULL;
    queue = push(queue, s);
    visited[s] = 1;
    parent[s] = -1;

    while(is_queue_empty(queue)){
        int front = queue->node;
        queue = pop(queue);

        for(int v = 0; v <= t; v++){
            //the edge between the nodes is same direction as the others or there are two edges that are opposite
            if((visited[v] == 0) && (expenseGraph[front][v] > 0)){
                if(v == t){
                    parent[v] = front;
                    visited[v] = 1;
                    return 1;
                }
                queue = push(queue, v);
                parent[v] = front;
                visited[v] = 1;
            }
            //if the direction of the edge is opposite with the others
            else if((visited[v] == 0) && (rGraph[v][front] > 0)){
                if(v == t){
                    parent[v] = front;
                    visited[v] = 1;
                    return 1;
                }
                queue = push(queue, v);
                parent[v] = front;
                visited[v] = 1;
            }
        }
    }
    return 0;
}

Queue* push(Queue* queue, int s){
    Queue* new = (Queue*) calloc(1, sizeof(Queue));
    new->node = s;
    if(queue == NULL){
        queue = new;
        queue->next = NULL;
        return(queue);
    } 
    new->next = queue;
    return(new);
}

int is_queue_empty(Queue* queue){
    int count = 0;
    for(Queue* curr = queue; curr != NULL; curr = curr->next) count++;
    if(count != 0) return 1;
    else return 0;
}

Queue* pop(Queue* queue){
    Queue* del, *head;
    del = queue;
    head = queue->next;
    free(del);
    del = NULL;
    return head;
}

float fordFulkerson(float **expenseGraph, float** rGraph, int s, int t){
    float maxflow = 0, pathflow, j = 1;
    int u, v, parent[t+1], visited[t+1];

    while(bfs(expenseGraph, rGraph, s, t, parent, visited)){
        //max int
        pathflow = 1000;
        for(v = t; v != s; v = parent[v]){
            u = parent[v];
            //if the direction of the edge is opposite with the others
            if((expenseGraph[u][v] == 0) && (rGraph[v][u] > 0)) pathflow = getmin(pathflow, rGraph[v][u]);
            else pathflow = getmin(pathflow, expenseGraph[u][v]);
        }

        for(v = t; v != s; v = parent[v]){
            u = parent[v];
            if((expenseGraph[u][v] == 0) && (rGraph[v][u] > 0)){
                expenseGraph[v][u] += pathflow;
                ////if the direction of the edge is opposite with the others
                rGraph[v][u] -= pathflow;
            }
            else expenseGraph[u][v] -= pathflow;
        }

        maxflow += pathflow;
    }
    return maxflow;
}

float getmin(float x, float y){
    if(x <= y) return x;
    else return y;
}

int isInteger(float val){
    int val2 = (int)val;
    if(val2 == val) return 1;
    else return 0;
}
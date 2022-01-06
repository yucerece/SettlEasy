#ifndef SPLIT_H_
#define SPLIT_H_
#define MAX 100

typedef struct MemberInfo{
    char name[10];
    char surname[12];
}MemberInfo;

typedef struct Queue{
    int node;
    struct Queue* next;
}Queue;


int getIndexofthemem(MemberInfo* mem, char name[], int len);
int bfs(float **expenseGraph, float** rGraph, int s, int t, int parent[], int visited[]);
Queue* push(Queue* queue, int s);
int is_queue_empty(Queue* queue);
Queue* pop(Queue* queue);
float fordFulkerson(float **expenseGraph, float** rGraph, int s, int t);
float getmin(float x, float y);
int isInteger(float val);


#endif
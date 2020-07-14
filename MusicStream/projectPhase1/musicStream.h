#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h> 

struct treeNode {
    int songID;
    struct treeNode * parent;
    struct treeNode *lc;
    struct treeNode *rc;
    pthread_mutex_t lock;
};

struct queueNode {
    int songID;
    struct queueNode *next;
};

struct queue {
    struct queueNode *Head;
    struct queueNode *Tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
};

struct queueList{
    int queueID;
    struct queue * node;
    struct queueList * next;
};

struct list {
    struct listNode *head;
    struct listNode *tail;
};

struct listNode {
    int songID;
    struct listNode *next;
    pthread_mutex_t lock;
};

struct queueList * header;

struct list * administrators;

int numberOfThreads;
struct treeNode * treeRoot;
pthread_mutex_t treeNodeLock;
pthread_barrier_t barrier_p;
pthread_barrier_t barrier_p1;
pthread_barrier_t barrier_p2;
pthread_barrier_t barrier_p3;
pthread_barrier_t barrier_p4;

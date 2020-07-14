#include "musicStream.h"

struct queueNode * newQueueNode(int songID){
    struct queueNode * new = malloc(sizeof(struct queueNode));
    new->songID=songID;
    new->next=NULL;
    return new;
}

struct queue * queueInit(){

    struct queue * q;
    struct queueNode* new; 

    q=malloc(sizeof(struct queue));
    
    new = newQueueNode(-1);
    q->Head=new;
    q->Tail=new;
    pthread_mutex_init(&q->headLock, NULL);
    pthread_mutex_init(&q->tailLock, NULL);

    return q;
}

void initListQueues(){
    int i;
    
    i=0;

    while(i<numberOfThreads/2){
        struct queueList * new;
       
        new=malloc(sizeof(struct queueList));
        new->queueID=i;
        new->node=queueInit();
        new->next=header;
        header=new;

        i++;

    }
}

void enqueue(struct queue * q,int songID){
    struct queueNode * new ;

    new = newQueueNode(songID);

    pthread_mutex_lock(&q->tailLock);
    q->Tail->next=new;
    q->Tail=new;
    pthread_mutex_unlock(&q->tailLock);
}

struct queueNode* dequeue(struct queue* q){
    struct queueNode* result;

    pthread_mutex_lock(&q->headLock);

    if(q->Head->next==NULL){
        result=NULL;
    }else{
        result=q->Head->next;
        q->Head=q->Head->next;
    }

    pthread_mutex_unlock(&q->headLock);
    return result;
    
}


struct queue* getQueue(int queueID){

    struct queueList* temp;

    temp=header;

    while(temp!=NULL && temp->queueID!=queueID){
        temp=temp->next;
    }

    if(temp==NULL){
        printf("There is no queue with that ID %d\n",queueID);
        return NULL;
    }else{
        return temp->node;
    }
}

void printListQueues(){
    struct queueList* temp;
    struct queue* tempq;
    struct queueNode* temp_node;

    temp=header;

    while(temp!=NULL){
        tempq=temp->node;
        temp_node=tempq->Head->next;
        printf(" Queue %d\n",temp->queueID);
        while(temp_node!=NULL && temp_node->songID!=-1){
            printf("  songID: %d\n",temp_node->songID);
            temp_node=temp_node->next;
        }
        temp=temp->next;
    }
    printf("\n");
}

int countQueues(){
    struct queueList* temp;
    struct queue* tempq;
    struct queueNode* temp_node;
    int count;
    
    count=0;
    temp=header;

    while(temp!=NULL){
        tempq=temp->node;
        temp_node=tempq->Head->next;
        while(temp_node!=NULL && temp_node->songID!=-1){
            count++;
            temp_node=temp_node->next;
        }
        temp=temp->next;
    }
    return count;
}

int sumQueues(){
    struct queueList* temp;
    struct queue* tempq;
    struct queueNode* temp_node;
    int sum;
    
    sum=0;
    temp=header;

    while(temp!=NULL){
        tempq=temp->node;
        temp_node=tempq->Head->next;
        while(temp_node!=NULL && temp_node->songID!=-1){
            sum=sum+temp_node->songID;
            temp_node=temp_node->next;
        }
        temp=temp->next;
    }
    return sum;
}

void checkQueues(){
    int expectedSize;
    unsigned long expectedKeysum;

    expectedSize=numberOfThreads*numberOfThreads;
    expectedKeysum=numberOfThreads*numberOfThreads*(numberOfThreads-1)*(numberOfThreads+1)/2;

    if(countQueues()==expectedSize){
        printf("Total size check passed (expected: %d found: %d)\n",expectedSize,treeCount(treeRoot));
    }else{
        printf("The total size check failed! Expected: %d found: %d\n",expectedSize,treeCount(treeRoot));
        exit(0);
    }

    if(sumQueues()==expectedKeysum){
        printf("Total keysum check passed (expected: %d found %d)\n\n",expectedKeysum,treeSum(treeRoot));
    }else{
        printf("The total keysum check failed!Expected: %d found: %d\n\n",expectedKeysum,treeSum(treeRoot));
        exit(0);
    }
}
#include "musicStream.h"

void * producerActions(void * v){

    int i;
    struct queue * temp;
    struct queue * temp2;
    struct treeNode* searchNode;
    struct treeNode* searchNode1;
    struct queueNode *tempNode;
    int step;
    int step2;

    step=((int)v+1)%(numberOfThreads/2);

    for(i=0; i<numberOfThreads; i++){

        int tempSongID=i*numberOfThreads+(int)v;
        BSTinsert(treeRoot,tempSongID);
    }
    pthread_barrier_wait(&barrier_p);

    if((int)v==0){
        printf("Uploads:\n");
        InorderPrint(treeRoot);
        printf("\n");
        checkTree(numberOfThreads);
    }
    
    for(i=numberOfThreads*(int)v; i<=(numberOfThreads*(int)v)+(numberOfThreads-1); i++){
        searchNode=(struct treeNode*)BSTsearch(i);
       if(searchNode!=NULL){
            temp=(struct queue *)getQueue(step);
            if(temp!=NULL){
                enqueue(temp,i);
            }
       }else{
           return;
       }

        step++;
       if(step >= (numberOfThreads/2-1)){
           step=((int)v+1)%(numberOfThreads/2);
       }
    }
    pthread_barrier_wait(&barrier_p);
    
    if((int)v==0){
        printf("Users' Queues:\n");
        printListQueues();
        checkQueues();
    }
    pthread_barrier_wait(&barrier_p);

    step2=((int)v+1)%(numberOfThreads/2);
    for(i=0; i<numberOfThreads/2; i++){
        temp2=(struct queue*)getQueue(step2);
        if(temp2!=NULL){
            tempNode=(struct queueNode*)dequeue(temp2);
            searchNode1=(struct treeNode*)BSTsearch(tempNode->songID);
            if(searchNode1!=NULL){
                BSTdelete(treeRoot,tempNode->songID);
                LL_insert(tempNode->songID);
            }else{
                printf("There is no song with this songID\n");
            }
        }else{
            printf("No queue here\n");
        }
        step2++;
        if(step2 >= (numberOfThreads/2-1)){
           step2=((int)v+1)%(numberOfThreads/2);
       }
      
    }

    pthread_barrier_wait(&barrier_p);

    if((int)v==0){
        printf("Users' Queues:\n");
        printListQueues();
        printf("Songs Tree:\n");
        InorderPrint(treeRoot);
        printList();
        finalChecks();
    }

    pthread_barrier_wait(&barrier_p);

}

int main(int argc, char * argv[]){

    void * t;
    struct treeNode * tree;
    int i;
     
    pthread_mutex_init(&treeNodeLock,NULL);


    numberOfThreads=atoi(argv[1]);

    pthread_t producers[numberOfThreads];

    initListQueues();
    initList();

    pthread_barrier_init(&barrier_p,NULL,numberOfThreads);
    t=NULL;

    for(i=0; i<numberOfThreads; i++){
        pthread_create(&producers[i],NULL,producerActions,(void *)i);
    }
    for(i=0; i<numberOfThreads; i++){
        pthread_join(producers[i], NULL);
    }
  return 0;
}
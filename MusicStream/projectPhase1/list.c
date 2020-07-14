#include "musicStream.h"

void initList(){

    struct listNode * temp;
    administrators=malloc(sizeof(struct list));

    temp=malloc(sizeof(struct listNode));
    temp->songID=-1;
    temp->next=NULL;
    pthread_mutex_init(&temp->lock,NULL);

    administrators->head=temp;
    administrators->tail=temp;
}

int countList(){
    struct listNode* temp;
    int count;

    count=0;

    temp=administrators->head->next;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count;
}

void printList(){
    struct listNode* temp;

    temp=administrators->head->next;
    printf("Administrators' List: \n");
    while(temp!=NULL){
        printf(" SongID: %d\n",temp->songID);
        temp=temp->next;
    }
    printf("\n");
}

void finalChecks(){
    int expectedSize;

    expectedSize=(numberOfThreads*numberOfThreads)/2;

    if(countQueues()==expectedSize && countList()==expectedSize){
        printf("Total size check passed (expected: %d found: %d)\n",expectedSize,countList());
    }else{
        printf("The total size check failed! Expected: %d found: %d\n",expectedSize,countList());
        exit(0);
    }

}

unsigned int validate(struct listNode* pred, struct listNode *curr) {
    struct listNode *tmp = administrators->head;
    while (tmp->songID <= pred->songID) {
        if (tmp == pred) {
            if (pred->next == curr) {
                return 1;
            }else{
                 return 0;
            }  
        }
        tmp = tmp->next;
    }
    return 0;
}

unsigned int LL_insert(int tempSongID){
    struct listNode * pred;
    struct listNode * curr;
    int result,flag;

    flag=0;

    while(1){
        pred=administrators->head;
        curr=pred->next;

        while(curr!=NULL && curr->songID < tempSongID){
            pred=curr;
            curr=curr->next;
        }
        pthread_mutex_lock(&pred->lock);
        if(curr!=NULL){
            pthread_mutex_lock(&curr->lock);
        }
    
        if(validate(pred,curr)==1){
            if(curr!=NULL && tempSongID==curr->songID){
                result=0;
                flag=1;
            }else{
                struct listNode * new;
                new=malloc(sizeof(struct listNode));
                
                new->songID=tempSongID;
                pthread_mutex_init(&new->lock,NULL);
              /*  if(pred==administrators->head && pred->songID > tempSongID){
                    printf("first of the list %d\n",pred->songID);
                    new->next=administrators->head;
                    administrators->head=new;
                }else{
                  
                }*/ 
                  new->next=curr;
                    pred->next=new;
                result=1;
                flag=1;
            }
        }
        pthread_mutex_unlock(&pred->lock);
        if(curr!=NULL){
            pthread_mutex_unlock(&curr->lock);
        }
        if(flag==1){
            return result;
        }
    }
    return result;
}
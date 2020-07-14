#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include <stddef.h> 
#include <time.h>

#define SIZE 500

int candidates_counter;

enum action_type{
    ACK,LEFT_NEIGHBOR,RIGHT_NEIGHBOR,UPLOAD,UPDATE,REQUEST_SHUTDOWN,SHUTDOWN_OK,SHUTDOWN,START_LEADER_ELECTION,LEADER_ELECTION_DONE,CANDIDATE_ID,CONNECT,CLIENT,UPLOAD_FAILED,UPLOAD_ACK,UPLOAD_OK,RETRIEVE,RETRIEVE_FAILED,RETRIEVE_ACK,RETRIEVE_OK,INITIALIZE,CLIENT_ACK,UPDATE_FAILED,VERSION_CHECK,VERSION_OUTDATED,UPDATE_ACK,UPDATE_OK
};
enum types{
    COORDINATOR,SERVER,CLIENT_TYPE
};

struct record{
    int key;
    struct queue_node* front;
    struct queue_node* back;
    struct record * next;

};

struct hash_table{
    struct record * table[SIZE];
    int numberOfRecords;
};

int hashFunction(int file_id){
    return file_id%SIZE;
}

struct queue_node{
    int client_id;
    int count;
    enum action_type type;
    int version;
    struct queue_node* next;
};

void insertQueue(struct record* record_node,struct queue_node* node){
    if(record_node==NULL){
        printf("ERROR NO NODE HERE!!!!!!!!!!!!!!!\n");
        return;
    }else{
        if(record_node->front==NULL){
            record_node->front=node;
            record_node->back=node;
            record_node->front->next=NULL;
        }else{
            node->next=record_node->back;
            record_node->back=node;
        }
    }
}

void dequeue(struct record* record_node){
    if(record_node==NULL){
        return;
    }else{
        struct queue_node* temp;
        struct queue_node *prev;

        temp=record_node->back;

        while(temp!=record_node->front){
            prev=temp;
            temp=temp->next;
        }
        if(record_node->back=record_node->front){
            free(temp);
            record_node->front=NULL;
            record_node->back=NULL;
            return;
        }
        free(temp);
        prev->next=NULL;
        record_node->front=prev; 
    }
}

struct hash_table* insertHashTable(int file_id,struct hash_table * server_leader,int client_id,int count){
    struct record* file=malloc(sizeof(struct record));

    file->key=file_id;
    file->front=NULL;
    file->back=NULL;

    int hash=hashFunction(file_id);
    if(server_leader->table[hash]==NULL){
        server_leader->table[hash]=file;
    }else{
        file->next=server_leader->table[hash];
        server_leader->table[hash]=file;
    }
/*
    struct queue_node* node=malloc(sizeof(struct queue_node));
    node->client_id=client_id;
    node->count =count;

    insertQueue(server_leader->table[hash],node);
*/
    return server_leader;
}



struct record* searchHashTable(int file_id,struct hash_table * server_leader){
    int hash=hashFunction(file_id);

    struct record* temp;
    temp=server_leader->table[hash];

    while(temp!=NULL && temp->key!=file_id){
        temp=temp->next;
    }
    if(temp==NULL){
        printf("No record with this key!\n");
        return NULL;
    }
    return temp;
}




struct queue_node* setQueueNodeStats(int count,enum action_type type,int version,struct queue_node* node){
    node->count=count;
    node->type=type;
    node->version=version;
    return node;
}

void printQueue(struct record * node){
    struct queue_node* qnode;

    if(node==NULL){
        printf("ERROR NO NODE HERE!!!!!!!!!!!!!\n");
        return;
    }
    qnode=node->back;

    while(qnode!=NULL){
        printf("Client id %d Type %d Count %d\n",qnode->client_id,qnode->type,qnode->count);
        qnode=qnode->next;
    }
}
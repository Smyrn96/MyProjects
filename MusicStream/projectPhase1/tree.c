#include "musicStream.h"

int treeCount(struct treeNode *root)
{
    int count = 1;
    if (root->lc != NULL) {
       count += treeCount(root->lc);
    }
    if (root->rc != NULL) {
        count += treeCount(root->rc);
    }
    return count;
}

unsigned long treeSum(struct treeNode * root){
    
    if(root==NULL){
        return 0;
    }

    return ((unsigned long)root->songID + treeSum(root->lc) + treeSum(root->rc));
}
void InorderPrint(struct treeNode * root){

    if(root==NULL){
        return;
    }

    InorderPrint(root->lc);
    printf(" songID : %d\n",root->songID);
    InorderPrint(root->rc);

}

struct treeNode * createSong(int songID,struct treeNode * parent){
    struct treeNode * new ;

    new=malloc(sizeof(struct treeNode));
    new->songID=songID;
    new->parent=parent;
    new->lc=NULL;
    new->rc=NULL;
    pthread_mutex_init(&new->lock, NULL);
    
    return new;
}

void checkTree(int numberOfThreads){
    int expectedSize;
    unsigned long expectedKeysum;

    expectedSize=numberOfThreads*numberOfThreads;
    expectedKeysum=numberOfThreads*numberOfThreads*(numberOfThreads-1)*(numberOfThreads+1)/2;

    if(treeCount(treeRoot)==expectedSize){
        printf("Total size check passed (expected: %d found: %d)\n",expectedSize,treeCount(treeRoot));
    }else{
        printf("The total size check failed! Expected: %d found: %d\n",expectedSize,treeCount(treeRoot));
        exit(0);
    }

    if(treeSum(treeRoot)==expectedKeysum){
        printf("Total keysum check passed (expected: %d found %d)\n\n",expectedKeysum,treeSum(treeRoot));
    }else{
        printf("The total keysum check failed!Expected: %d found: %d\n\n",expectedKeysum,treeSum(treeRoot));
        exit(0);
    }

}


struct treeNode* BSTsearch(int tempSongID){

    struct treeNode * temp;

     pthread_mutex_lock(&treeNodeLock);

        if(treeRoot==NULL){
            printf("There is no song with this ID\n");
            pthread_mutex_unlock(&treeNodeLock);
            return NULL;
        }else{
            pthread_mutex_lock(&treeRoot->lock);
            temp=treeRoot;
            pthread_mutex_unlock(&treeNodeLock);

            while(temp!=NULL){
                if(tempSongID < temp->songID){
                   if(temp->lc==NULL){
                        printf("There is no song with this ID %d\n",tempSongID);
                        pthread_mutex_unlock(&temp->lock);
                        return NULL;
                    }else{
                        pthread_mutex_lock(&temp->lc->lock);
                        pthread_mutex_unlock(&temp->lock);
                        temp=temp->lc;
                    }
                }else if(tempSongID > temp->songID){
                    if(temp->rc==NULL){
                        printf("There is no song with this ID %d\n",tempSongID);
                        pthread_mutex_unlock(&temp->lock);
                        return NULL;
                    }else{
                        pthread_mutex_lock(&temp->rc->lock);
                        pthread_mutex_unlock(&temp->lock);
                        temp=temp->rc;
                    }
                }else{
                    pthread_mutex_unlock(&temp->lock);
                    return temp;
                }
            }
        }
        return NULL;
}

void * BSTinsert(struct treeNode* root,int tempSongID){

    struct treeNode * temp;
    struct treeNode * prev;

        pthread_mutex_lock(&treeNodeLock);

        if(treeRoot==NULL){
            treeRoot=createSong(tempSongID,NULL);
            pthread_mutex_unlock(&treeNodeLock);
        }else{
            pthread_mutex_lock(&treeRoot->lock);
            temp=treeRoot;
            prev=NULL;
            pthread_mutex_unlock(&treeNodeLock);

            while(temp!=NULL){
                if(tempSongID < temp->songID){
                   if(temp->lc==NULL){
                        prev=temp;
                        pthread_mutex_unlock(&temp->lock);
                        break;
                    }else{
                        pthread_mutex_lock(&temp->lc->lock);
                        prev=temp;
                        pthread_mutex_unlock(&temp->lock);
                        temp=temp->lc;
                    }
                }else if(tempSongID > temp->songID){
                    if(temp->rc==NULL){
                        prev=temp;
                        pthread_mutex_unlock(&temp->lock);
                        break;
                    }else{
                        pthread_mutex_lock(&temp->rc->lock);
                        prev=temp;
                        pthread_mutex_unlock(&temp->lock);
                        temp=temp->rc;
                    }
                    
                }
            }

            pthread_mutex_lock(&prev->lock);
            if(tempSongID < prev->songID){
                prev->lc=createSong(tempSongID,prev);
                pthread_mutex_unlock(&prev->lock);
            }else if(tempSongID > prev->songID){
                prev->rc=createSong(tempSongID,prev);
                pthread_mutex_unlock(&prev->lock);
            }
             pthread_mutex_unlock(&prev->lock);
        }
}

struct treeNode * successorOrPredecessor(struct treeNode* root,int flag){

    struct treeNode* temp;
    struct treeNode* parent;

    parent=root;

    if(flag==0){
        temp=parent->lc;
        pthread_mutex_lock(&temp->lock);
        while(temp!=NULL && temp->lc!=NULL){
            temp=temp->lc;
            pthread_mutex_unlock(&parent->lock);
            pthread_mutex_lock(&temp->lock);
            parent = temp->parent;
        }
    }else{
        pthread_mutex_lock(&temp->lock);
        temp=parent->rc;
        while(temp!=NULL && temp->rc!=NULL){
            temp=temp->rc;
            pthread_mutex_unlock(&parent->lock);
            pthread_mutex_lock(&temp->lock);
            parent = temp->parent;
        }
    }
    return temp;   
}

struct treeNode *  treeNodeToBeRemoved(struct treeNode* root,int tempSongID){
    if(root->songID==tempSongID){
        return root;
    }

    if(root->songID > tempSongID){
        if (root->lc == NULL) {
            pthread_mutex_unlock(&root->lock);
            return NULL;
        } else {
            pthread_mutex_lock(&root->lc->lock);
            if (tempSongID == root->lc->songID) {
                return root->lc;
            } else {
                pthread_mutex_unlock(&root->lock);
                return treeNodeToBeRemoved(root->lc,tempSongID);
            }
        }
    }else{
        if (root->rc == NULL) {
            pthread_mutex_unlock(&root->lock);
            return NULL;
        } else {
            pthread_mutex_lock(&root->rc->lock);
            if (tempSongID == root->rc->songID) {
                return root->rc;
            } else {
                pthread_mutex_unlock(&root->lock);
                return treeNodeToBeRemoved(root->rc,tempSongID);
            }
        }
    }
    return NULL;
}

void BSTdelete(struct treeNode *root,int tempSongID){
    struct treeNode * temp;
    struct treeNode * prev;
    struct treeNode *treeNodeDelete;
    struct treeNode* parent;
    struct treeNode * inorder_successor;
    struct treeNode * inorder_successor_parent;
    struct treeNode * inorder_predecessor;
    struct treeNode * inorder_predecessor_parent;
    
    treeNodeDelete=NULL;
    pthread_mutex_lock(&treeNodeLock);

    if(treeRoot==NULL){
        printf("There is no song with this ID\n");
        pthread_mutex_unlock(&treeNodeLock);
        return;
    }

    root=treeRoot;
    pthread_mutex_lock(&root->lock);

    if (tempSongID == root->songID && root->lc == NULL && root->rc == NULL) {
        treeRoot = NULL;
        pthread_mutex_unlock(&treeNodeLock);
        return;
    }

    treeNodeDelete=treeNodeToBeRemoved(root,tempSongID);
  
    if(treeNodeDelete==NULL){
        printf("The song with the %d ID cannot be found\n",tempSongID);
        pthread_mutex_unlock(&treeNodeLock);
        return;
    }

    parent=treeNodeDelete->parent;
    
    pthread_mutex_unlock(&treeNodeLock);

    if(treeNodeDelete->lc==NULL && treeNodeDelete->rc==NULL){
        if(treeNodeDelete->songID < parent->songID){
            parent->lc=NULL;
            pthread_mutex_unlock(&parent->lock);
            return;
        }else{
            parent->rc=NULL;
            pthread_mutex_unlock(&parent->lock);
            return;
        }
    }


    if (parent != NULL) {
        pthread_mutex_unlock(&parent->lock);
    }
     
    if (treeNodeDelete->rc != NULL) {
        
        pthread_mutex_lock(&treeNodeDelete->rc->lock);
        if (treeNodeDelete->rc->lc == NULL) {
            inorder_successor = treeNodeDelete->rc;

            if (inorder_successor->rc != NULL) {
                pthread_mutex_lock(&inorder_successor->rc->lock);
                treeNodeDelete->songID = inorder_successor->songID;
                treeNodeDelete->rc = inorder_successor->rc;
                inorder_successor->rc->parent = treeNodeDelete;
                pthread_mutex_unlock(&inorder_successor->rc->lock);
            } else {
                treeNodeDelete->songID = inorder_successor->songID;
                treeNodeDelete->rc = NULL;
            }
            pthread_mutex_unlock(&treeNodeDelete->lock);
            return;
        }else{
            inorder_successor = successorOrPredecessor(treeNodeDelete->rc,0);//edw stamatisa
            inorder_successor_parent = inorder_successor->parent;

            if (inorder_successor->rc != NULL) {
                pthread_mutex_lock(&inorder_successor->rc->lock);
                inorder_successor_parent->lc = inorder_successor->rc;
                inorder_successor->rc->parent = inorder_successor_parent;
                treeNodeDelete->songID = inorder_successor->songID;
                pthread_mutex_unlock(&inorder_successor->rc->lock);
            } else {
                treeNodeDelete->songID = inorder_successor->songID;
                inorder_successor_parent->lc = NULL;
            }
            pthread_mutex_unlock(&inorder_successor_parent->lock);
            pthread_mutex_unlock(&treeNodeDelete->lock);
            return ;
        }
    }
    

    if (treeNodeDelete->lc != NULL) {
        pthread_mutex_lock(&treeNodeDelete->lc->lock);
        if (treeNodeDelete->lc->rc == NULL) {
            inorder_predecessor = treeNodeDelete->lc;

            if (inorder_predecessor->lc != NULL) {
                pthread_mutex_lock(&inorder_predecessor->lc->lock);
                treeNodeDelete->songID = inorder_predecessor->songID;
                treeNodeDelete->lc = inorder_predecessor->lc;
                inorder_predecessor->lc->parent = treeNodeDelete;
                pthread_mutex_unlock(&inorder_predecessor->lc->lock);
            } else {
                treeNodeDelete->songID = inorder_predecessor->songID;
                treeNodeDelete->lc = NULL;
            }
            pthread_mutex_unlock(&treeNodeDelete->lock);
            return ;
        }else{
            inorder_predecessor = successorOrPredecessor(treeNodeDelete->lc,1);
            inorder_predecessor_parent = inorder_predecessor->parent;

            if (inorder_predecessor->lc != NULL) {
                pthread_mutex_lock(&inorder_predecessor->lc->lock);
                inorder_predecessor_parent->rc = inorder_predecessor->lc;
                inorder_predecessor->lc->parent = inorder_predecessor_parent;
                treeNodeDelete->songID = inorder_predecessor->songID;
                pthread_mutex_unlock(&inorder_predecessor->lc->lock);
            } else {
                treeNodeDelete->songID = inorder_predecessor->songID;
                inorder_predecessor_parent->rc = NULL;
            }
            pthread_mutex_unlock(&inorder_predecessor_parent->lock);
            pthread_mutex_unlock(&treeNodeDelete->lock);
            return ;
        }
       
    }
    return;
}
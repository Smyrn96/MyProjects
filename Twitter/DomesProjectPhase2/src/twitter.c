/***************************************************
 *                                                 *
 * file: twitter.c                                 *
 *                                                 *
 * @Author  Iacovos G. Kolokasis                   *
 * @Version 30-03-2018                             *
 * @email   kolokasis@csd.uoc.gr                   *
 *                                                 *
 * @brief   Implementation of tweeter.h            *
 *                                                 *
 ***************************************************
 */

#include "twitter.h"

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize()
{
	users_s=malloc(sizeof(user_t));
	users_s->uid=-1;
	users_s->followers=NULL;
	users_s->wall_head=NULL;
	users_s->lc=NULL;
	users_s->rc=NULL;

	users_p=users_s;

	tweetHashTable==NULL;


	return 1;
}

/**
 * @brief Register user
 *
 * @param uid The user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_user(int uid)
{
	user_t * iterator;
	user_t * prev;
	user_t * newUser;
	user_t * print;

	iterator=users_p;
	prev=users_s;

	while(iterator->uid!=-1){

		if(iterator->uid==uid){
			printf("The user with the particular uid is already in the tree\n");
			return 0;
		}

		prev=iterator;
		if(uid < iterator->uid){
			iterator=iterator->lc;
		}else if(uid > iterator->uid){
			iterator=iterator->rc;
		}

	}

	newUser=malloc(sizeof(user_t));
	newUser->uid=uid;
	newUser->lc=users_s;
	newUser->rc=users_s;

	if(prev->uid==-1){
		users_p=newUser;
	}else if(uid < prev->uid){
		prev->lc=newUser;
		newUser->par=prev;
	}else if(uid > prev->uid){
		prev->rc=newUser;
		newUser->par=prev;
	}

	printf("Users= ");

	print=users_p;

	printR(print);

	printf("\n");

	return 1;
}

/**
 * @brief User uid1 is now following user uid2
 *
 * @param uid1 The 1st user's id
 * @param uid2 The 2nd user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int subscribe(int uid1, int uid2)
{
	user_t * iterator;
	user_t * prev;
	follower_t * temp;
	follower_t * previous;
	follower_t * newF;
	follower_t * print;

	iterator=users_p;
	prev=users_s;

	while(iterator->uid!=-1){

		if(uid1==iterator->uid){
			prev=iterator;
			break;
		}else if(uid1<iterator->uid){
			iterator=iterator->lc;
		}else if(uid1>iterator->uid){
			iterator=iterator->rc;
		}
	}

	if(prev->uid==-1){
		printf("No user with that uid in the tree\n");
		return 0;
	}

	temp=prev->followers;
	previous=NULL;

	while(temp!=NULL){

		if(temp->uid==uid2){
			printf("The follower with the particular uid is already in the tree\n");
			return 0;
		}

		previous=temp;
		if(uid2<temp->uid){
			temp=temp->lc;
		}else if(uid2>temp->uid){
			temp=temp->rc;
		}

	} 

	newF=malloc(sizeof(follower_t));
	newF->uid=uid2;
	newF->lc=NULL;
	newF->rc=NULL;

	if(previous==NULL){
		prev->followers=newF;
	}else if(uid2<previous->uid){
		previous->lc=newF;
	}else if(uid2>previous->uid){
		previous->rc=newF;
	}

	printf("Followers= ");

	print=prev->followers;

	printF(print);

	printf("\n");


	return 1;
}

/**
 * @brief New tweet event
 * 
 * @param uid       The user who posted the tweet
 * @param tid       The tweet's id
 * @param timestamp The time the tweet was posted
 *
 * @return 1 on success
 *         0 on failure
 */
int tweet(int uid, int tid, int timestamp)
{
	user_t * iterator;
	user_t * prev;
	user_t * temp_iterator;
	user_t * min;
	user_t * temp_min;
	user_t * print_u;
	tweet_t * temp;
	tweet_t * temp1;
	tweet_t * temp2;
	tweet_t * temp3;
	tweet_t * iterator_T;
	tweet_t * previous;
	tweet_t * inOrderIterator;
	tweet_t * inOrderPrevious;
	tweet_t * inOrderTemp;
	tweet_t * inOrderTemp1;
	tweet_t * inOrderTemp2;
	tweet_t * inOrderTemp3;
	follower_t * traversal_in;
	follower_t * inordertemp;
	follower_t * pre;


	iterator=users_p;
	prev=users_s;

	while(iterator->uid!=-1){

		if(uid==iterator->uid){
			prev=iterator;
			break;
		}else if(uid<iterator->uid){
			iterator=iterator->lc;
		}else if(uid>iterator->uid){
			iterator=iterator->rc;
		}
	}

	if(prev->uid==-1){
		printf("No user with that uid in the tree\n");
		return 0;
	}

	iterator_T=prev->wall_head;
	previous=NULL;
	temp2=prev->wall_head;
	temp3=NULL;


	while(iterator_T!=NULL){

		if(iterator_T->tid==tid){
			printf("The tweet with the particular tid is already in the tree\n");
			return 0;
		}

		previous=iterator_T;
		if(timestamp<iterator_T->timestamp){
			iterator_T=iterator_T->lc;
		}else if(timestamp>iterator_T->timestamp){
			iterator_T=iterator_T->rc;
		}else if(timestamp==iterator_T->timestamp){
			printf("The tweet with the particular tid is already in the tree\n");
			return 0;
		}

	}

	temp1=malloc(sizeof(tweet_t));
	temp1->tid=tid;
	temp1->uid=uid;
	temp1->timestamp=timestamp;
	temp1->rc=NULL;
	temp1->lc=NULL;

	while(temp2!=NULL){
		temp3=temp2;
		temp2=temp2->lc;
	}


	if(previous==NULL){
		prev->wall_head=temp1;
		prev->wall_head->next=NULL;
	}else if(timestamp<previous->timestamp){
		previous->lc=temp1;
		temp=malloc(sizeof(tweet_t));
		temp->tid=previous->tid;
		temp->uid=previous->uid;
		temp->timestamp=previous->timestamp;
		temp->lc=NULL;
		temp->rc=NULL;
		previous->rc=temp;
		previous->uid=temp1->uid;
		previous->tid=temp1->tid;
		previous->timestamp=temp1->timestamp;
		previous->lc->next=previous->rc;
		previous->rc->next=previous->next;
	}else if(timestamp>previous->timestamp){
		previous->rc=temp1;
		temp=malloc(sizeof(tweet_t));
		temp->tid=previous->tid;
		temp->uid=previous->uid;
		temp->timestamp=previous->timestamp;
		temp->lc=NULL;
		temp->rc=NULL;
		previous->lc=temp;
		previous->uid=temp1->uid;
		previous->tid=temp1->tid;
		previous->timestamp=temp1->timestamp;
		previous->lc->next=previous->rc;
		previous->rc->next=previous->next;

		if(temp3->next!=NULL){
			(temp3->next)->next=previous->lc;
		}else{
			temp3->next=previous->lc;
		}
	}

	temp_iterator=users_p;
	traversal_in=prev->followers;

	while(temp_iterator->uid!=-1){
		min=temp_iterator;
		temp_iterator=temp_iterator->lc;
	}

	temp_min=min;

	while(traversal_in!=NULL){
		if(traversal_in->lc==NULL){
			inordertemp=traversal_in;
			traversal_in=traversal_in->rc;

			while(min->uid!=inordertemp->uid){
				min=inOrderSuccessorU(users_p,min);
			}

			inOrderIterator=min->wall_head;
			inOrderPrevious=NULL;
			inOrderTemp2=min->wall_head;
			inOrderTemp3=NULL;

			while(inOrderIterator!=NULL){

			if(inOrderIterator->tid==tid){
				printf("The tweet with the particular tid is already in the tree\n");
				return 0;
			}	

			inOrderPrevious=inOrderIterator;
			if(timestamp<inOrderIterator->timestamp){
				inOrderIterator=inOrderIterator->lc;
			}else if(timestamp>inOrderIterator->timestamp){
				inOrderIterator=inOrderIterator->rc;
			}else if(timestamp==inOrderIterator->timestamp){
				printf("The tweet with the particular tid is already in the tree\n");
				return 0;
			}

		}
			inOrderTemp1=malloc(sizeof(tweet_t));
			inOrderTemp1->tid=tid;
			inOrderTemp1->uid=uid;
			inOrderTemp1->timestamp=timestamp;
			inOrderTemp1->rc=NULL;
			inOrderTemp1->lc=NULL;

		while(inOrderTemp2!=NULL){
			inOrderTemp3=inOrderTemp2;
			inOrderTemp2=inOrderTemp2->lc;
		}

		if(inOrderPrevious==NULL){
		min->wall_head=inOrderTemp1;
		min->wall_head->next=NULL;
	}else if(timestamp<inOrderPrevious->timestamp){
		inOrderPrevious->lc=inOrderTemp1;
		inOrderTemp=malloc(sizeof(tweet_t));
		inOrderTemp->tid=inOrderPrevious->tid;
		inOrderTemp->uid=inOrderPrevious->uid;
		inOrderTemp->timestamp=inOrderPrevious->timestamp;
		inOrderTemp->lc=NULL;
		inOrderTemp->rc=NULL;
		inOrderPrevious->rc=inOrderTemp;
		inOrderPrevious->uid=inOrderTemp1->uid;
		inOrderPrevious->tid=inOrderTemp1->tid;
		inOrderPrevious->timestamp=inOrderTemp1->timestamp;
		inOrderPrevious->lc->next=inOrderPrevious->rc;
		inOrderPrevious->rc->next=inOrderPrevious->next;
	}else if(timestamp>inOrderPrevious->timestamp){
		inOrderPrevious->rc=inOrderTemp1;
		inOrderTemp=malloc(sizeof(tweet_t));
		inOrderTemp->tid=inOrderPrevious->tid;
		inOrderTemp->uid=inOrderPrevious->uid;
		inOrderTemp->timestamp=inOrderPrevious->timestamp;
		inOrderTemp->lc=NULL;
		inOrderTemp->rc=NULL;
		inOrderPrevious->lc=inOrderTemp;
		inOrderPrevious->uid=inOrderTemp1->uid;
		inOrderPrevious->tid=inOrderTemp1->tid;
		inOrderPrevious->timestamp=inOrderTemp1->timestamp;
		inOrderPrevious->lc->next=inOrderPrevious->rc;
		inOrderPrevious->rc->next=inOrderPrevious->next;

		if(inOrderTemp3->next!=NULL){
			(inOrderTemp3->next)->next=inOrderPrevious->lc;
		}else{
			inOrderTemp3->next=inOrderPrevious->lc;
		}
	}

	min=temp_min;

		}else{
			pre=traversal_in->lc;
			while(pre->rc!=NULL && pre->rc!=traversal_in){
				pre=pre->rc;
			}

			if(pre->rc==NULL){
				pre->rc=traversal_in;
				traversal_in=traversal_in->lc;
			}else{
				pre->rc=NULL;
				inordertemp=traversal_in;
				traversal_in=traversal_in->rc;
				while(min->uid!=inordertemp->uid){
				min=inOrderSuccessorU(users_p,min);
			}

			inOrderIterator=min->wall_head;
			inOrderPrevious=NULL;
			inOrderTemp2=min->wall_head;
			inOrderTemp3=NULL;

			while(inOrderIterator!=NULL){

			if(inOrderIterator->tid==tid){
				printf("The follower with the particular uid is already in the tree\n");
				return 0;
			}	

			inOrderPrevious=inOrderIterator;
			if(timestamp<inOrderIterator->timestamp){
				inOrderIterator=inOrderIterator->lc;
			}else if(timestamp>inOrderIterator->timestamp){
				inOrderIterator=inOrderIterator->rc;
			}

			}

			inOrderTemp1=malloc(sizeof(tweet_t));
			inOrderTemp1->tid=tid;
			inOrderTemp1->uid=uid;
			inOrderTemp1->timestamp=timestamp;
			inOrderTemp1->rc=NULL;
			inOrderTemp1->lc=NULL;

		while(inOrderTemp2!=NULL){
			inOrderTemp3=inOrderTemp2;
			inOrderTemp2=inOrderTemp2->lc;
		}

		if(inOrderPrevious==NULL){
		min->wall_head=inOrderTemp1;
		min->wall_head->next=NULL;
	}else if(timestamp<inOrderPrevious->timestamp){
		inOrderPrevious->lc=inOrderTemp1;
		inOrderTemp=malloc(sizeof(tweet_t));
		inOrderTemp->tid=inOrderPrevious->tid;
		inOrderTemp->uid=inOrderPrevious->uid;
		inOrderTemp->timestamp=inOrderPrevious->timestamp;
		inOrderTemp->lc=NULL;
		inOrderTemp->rc=NULL;
		inOrderPrevious->rc=inOrderTemp;
		inOrderPrevious->uid=inOrderTemp1->uid;
		inOrderPrevious->tid=inOrderTemp1->tid;
		inOrderPrevious->timestamp=inOrderTemp1->timestamp;
		inOrderPrevious->lc->next=inOrderPrevious->rc;
		inOrderPrevious->rc->next=inOrderPrevious->next;
	}else if(timestamp>inOrderPrevious->timestamp){
		inOrderPrevious->rc=inOrderTemp1;
		inOrderTemp=malloc(sizeof(tweet_t));
		inOrderTemp->tid=inOrderPrevious->tid;
		inOrderTemp->uid=inOrderPrevious->uid;
		inOrderTemp->timestamp=inOrderPrevious->timestamp;
		inOrderTemp->lc=NULL;
		inOrderTemp->rc=NULL;
		inOrderPrevious->lc=inOrderTemp;
		inOrderPrevious->uid=inOrderTemp1->uid;
		inOrderPrevious->tid=inOrderTemp1->tid;
		inOrderPrevious->timestamp=inOrderTemp1->timestamp;
		inOrderPrevious->lc->next=inOrderPrevious->rc;
		inOrderPrevious->rc->next=inOrderPrevious->next;

			if(inOrderTemp3->next!=NULL){
				(inOrderTemp3->next)->next=inOrderPrevious->lc;
			}else{
				inOrderTemp3->next=inOrderPrevious->lc;
			}
		}

			}
		}
	}
	

	if(tweetHashTable==NULL){
		int i=0;
		while(i<160){
			if(primes_g[i]<max_tweets_g){
				i++;
			}else{
				break;
			}
		}
		max_tweets_g=primes_g[i];
		tweetHashTable=malloc(sizeof(t_hashTable)*max_tweets_g);

		for(int j=0; j<max_tweets_g; j++){
			tweetHashTable[j].tid=0;
			tweetHashTable[j].uid=0;
			tweetHashTable[j].timestamp=0;
			tweetHashTable[j].remove=1;
		}

	}

		int hash_t=HFUNC_1(tid);
		int k=0;

		while(tweetHashTable[hash_t].remove!=1){
			k++;
			hash_t=(HFUNC_1(tid)+ k*HFUNC_2(tid))%max_tweets_g;
		}


		tweetHashTable[hash_t].tid=tid;
		tweetHashTable[hash_t].uid=uid;
		tweetHashTable[hash_t].timestamp=timestamp;
		tweetHashTable[hash_t].remove=0;
	

	print_u=users_p;
	printT(print_u);
	printf("\n");

	

	return 1;
}

/**
 * @brief User uid1 stopped following user uid2
 *
 * @param uid1 The 1st user's id
 * @param uid2 The 2nd user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int unsubscribe(int uid1, int uid2)
{
	user_t * iterator;
    user_t * prev;
	user_t * iterator1;
	user_t * prev1;
	user_t * print_u;
    follower_t * temp;
	tweet_t * iterator_t;


        iterator=users_p;
        prev=users_s;

        while(iterator->uid!=-1){

                if(uid1==iterator->uid){
                        prev=iterator;
                        break;
                }else if(uid1<iterator->uid){
                        iterator=iterator->lc;
                }else if(uid1>iterator->uid){
                        iterator=iterator->rc;
                }
        }

        if(prev->uid==-1){
                printf("No user with that uid in the tree\n");
                return 0;
        }

	temp=prev->followers;

	temp=delete_f(temp,uid2);


	iterator1=users_p;
        prev1=users_s;

        while(iterator1->uid!=-1){

                if(uid2==iterator1->uid){
                        prev1=iterator1;
                        break;
                }else if(uid2<iterator1->uid){
                        iterator1=iterator1->lc;
                }else if(uid2>iterator1->uid){
                        iterator1=iterator1->rc;
                }
        }

        if(prev1->uid==-1){
                printf("No user with that uid in the tree\n");
                return 0;
        }

	iterator_t=prev1->wall_head;

  	print_u=users_p;
    printT(print_u);
    printf("\n");

	return 1;
}

/**
 * @brief Delete user account
 * 
 * @param uid The id of the user account to delete
 * 
 * @return 1 on success
 *         0 on failure
 */
int delete_user(int uid)
{
	user_t * iterator;
	user_t * iterator1;
    user_t * prev;
	user_t * print;
	tweet_t * iterator_t;

        iterator=users_p;
        iterator1=users_p;
        prev=users_s;

        while(iterator->uid!=-1){

                if(uid==iterator->uid){
                        prev=iterator;
                        break;
                }else if(uid<iterator->uid){
                        iterator=iterator->lc;
                }else if(uid>iterator->uid){
                        iterator=iterator->rc;
                }
        }

        if(prev->uid==-1){
                printf("No user with that uid in the tree\n");
                return 0;
        }

	iterator_t=prev->wall_head;

	delete_whole_tree(prev->wall_head);
	prev->wall_head=NULL;

	inOrderUnsubscribe(prev->followers);

	iterator1=deleteTheUser(iterator1,uid);

	int i=0;

	while(i<max_tweets_g){
		if(tweetHashTable[i].uid==uid){
			tweetHashTable[i].uid=0;
			tweetHashTable[i].tid=0;
			tweetHashTable[i].timestamp=0;
			tweetHashTable[i].remove=1;
		}
		i++;
	}

	print=users_p;
	printT(print);
	printf("\n");

	return 1;
}

/**
 * @brief Get the history of the user tweets
 *
 * @param uid The id of the user account
 * 
 * @return  1 on success
 *          0 on failure
 */
int history(int uid, int timestamp1, int timestamp2)
{
	user_t * iterator;
	user_t * prev;
	tweet_t * iterator_t;

	iterator=users_p;
    prev=users_s;

    while(iterator->uid!=-1){

        if(uid==iterator->uid){
            prev=iterator;
            break;
        }else if(uid<iterator->uid){
            iterator=iterator->lc;
        }else if(uid>iterator->uid){
            iterator=iterator->rc;
        }
    }

    if(prev->uid==-1){
        printf("No user with that uid in the tree\n");
        return 0;
    } 

    iterator_t=iterator->wall_head;

    while(iterator_t->lc!=NULL){
    	iterator_t=iterator_t->lc;
    }

    if(iterator_t->timestamp <= timestamp1){
    	iterator_t=iterator_t->next;
   }
   printf("User= ");

    while(iterator_t->timestamp <= timestamp2 || iterator_t!=NULL){
    	printf("%d %d %d ",iterator_t->tid,iterator_t->uid,iterator_t->timestamp);
    	iterator_t=iterator_t->next;
    }

printf("\n");

    return 1;
}

/**
 * @brief Lookup tweet the tweets hash table.
 * 
 * @param tid The tweet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int lookup(int tid)
{
	int i=0;

	while(i<max_tweets_g){
		if(tweetHashTable[i].tid==tid){
			printf("Tweet = %d %d %d \n",tweetHashTable[i].tid,tweetHashTable[i].uid,tweetHashTable[i].timestamp);
			break;
		}else{
			i++;
		}
	}
	return 1;
}

/**
 * @brief Print all active users
 *
 * @return 1 on success
 *         0 on failure
 */
int print_users(void)
{
	user_t * iterator;

	iterator=users_p;

	print_users_details(iterator);

	return 1;
}

/**
 * @brief Print all tagged tweets
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tweets(void)
{
	printf("Tweets:\n");
	int i=0;
	while(i<max_tweets_g){
		printf("Tweet %d = %d %d %d\n",i,tweetHashTable[i].tid,tweetHashTable[i].uid,tweetHashTable[i].timestamp);
		i++;
	}

	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
	return 1;
}


user_t * inOrderSuccessorU(user_t * root,user_t * pointer){

	user_t * temp;
	user_t * iterator;

	temp=users_s;

	if(pointer->rc->uid!=-1){
		temp=pointer->rc;
		while(temp->lc->uid!=-1){
			temp=temp->lc;
		}
	}else{
		iterator=root;
		while(iterator->uid!=pointer->uid){
			if(pointer->uid<=iterator->uid){
				temp=iterator;
				iterator=iterator->lc;
			}else{
				iterator=iterator->rc;
			}
		}

	}

	return temp;

}



void printR(user_t * root){

	if(root==NULL || root->uid==-1){ 
		return ;
	}

	printR(root->lc);
	printf("%d ",root->uid);
	printR(root->rc);

}

void  printF(follower_t * root){

	if(root==NULL){
		return ;
	}

	printF(root->lc);
	if(root->uid!=0){
		printf("%d ",root->uid);
	}
	printF(root->rc);

}

void  printT(user_t * root_t){

	tweet_t * temp;
	tweet_t * root;
	tweet_t * temp_rc;



	if(root_t==NULL || root_t->uid==-1){ 
		return ;
	}

	printT(root_t->lc);
	printf("\n %d :",root_t->uid);
	root=root_t->wall_head;
	temp_rc=root_t->wall_head;
	if(root!=NULL){
	
		while(temp_rc->rc!=NULL){
			temp_rc=temp_rc->rc;
		}

		temp_rc->next=NULL;

		while(root!=NULL){
			temp=root;
			root=root->lc;
		}
		while(temp!=NULL){
			printf("%d %d %d ",temp->uid ,temp->tid ,temp->timestamp);
			temp=temp->next;
		}
	}
	printf("\n");
	printT(root_t->rc);

}

follower_t * delete_f(follower_t * root, int uid2){
	
	if(root==NULL){
		return root;
	}else if(uid2<root->uid){
		root->lc=delete_f(root->lc,uid2);
	}else if(uid2>root->uid){
		root->rc=delete_f(root->rc,uid2);
	}else{
		if(root->rc==NULL && root->lc==NULL){
			free(root);
			root=NULL;
		}else if(root->lc==NULL){
			follower_t * temp=root;
			root=root->rc;
			free(temp);
		}else if(root->rc==NULL){
			follower_t * temp=root;
			root=root->lc;
			free(temp);
		}else{
			follower_t * temp1;
		        temp1=root->rc;

			while(temp1->lc!=NULL){
				temp1=temp1->lc;
			}
			root->uid=temp1->uid;
			root->rc=delete_f(root->rc,temp1->uid);
		}
	}
	return root;
}
	
void delete_t(tweet_t * root, int uid1){
	
	if(root==NULL){
		return;
	}
	
	delete_t(root->lc,uid1);
	if(root->uid==uid1){
		root=delete_tweet(root,root->timestamp);
	}
	delete_t(root->rc,uid1);
}

tweet_t * delete_tweet(tweet_t * root, int timestamp){

        if(root==NULL){
                return root;
	}
               	if(root->rc==NULL && root->lc==NULL){
                        free(root);
                        root=NULL;
                }else if(root->lc==NULL){
                        tweet_t * temp=root;
                        root=root->rc;
                        free(temp);
                }else if(root->rc==NULL){
                        tweet_t * temp=root;
                        root=root->lc;
                        free(temp);
                }else{
                        tweet_t * temp1;
                        temp1=root->rc;

                        while(temp1->lc!=NULL){
                                temp1=temp1->lc;
                        }
                        root->timestamp=temp1->timestamp;
                        root->rc=delete_tweet(root->rc,temp1->timestamp);
                }
        
        return root;
}



void delete_whole_tree(tweet_t * root){

	if(root==NULL){
		return;
	}

	delete_whole_tree(root->lc);
	delete_whole_tree(root->rc);
	free(root);
	root->next=NULL;
}

void inOrderUnsubscribe(follower_t * root){
	
	if(root==NULL){
		return;
	}

	inOrderUnsubscribe(root->lc);
	inOrderUnsubscribe(root->rc);
	free(root);
}


user_t * deleteTheUser(user_t * root, int uid){
	
	if(root==users_s){
		return root;
	}else if(uid<root->uid){
		root->lc=deleteTheUser(root->lc,uid);
	}else if(uid>root->uid){
		root->rc=deleteTheUser(root->rc,uid);
	}else{
		if(root->rc==users_s && root->lc==users_s){
			free(root);
			root=users_s;
		}else if(root->lc==users_s){
			user_t * temp=root;
			root=root->rc;
			free(temp);
		}else if(root->rc==users_s){
			user_t * temp=root;
			root=root->lc;
			free(temp);
		}else{
			user_t * temp1;
		        temp1=root->rc;

			while(temp1->lc!=users_s){
				temp1=temp1->lc;
			}
			root->uid=temp1->uid;
			root->rc=deleteTheUser(root->rc,temp1->uid);
		}
	}
	return root;
}


void print_users_details(user_t * root_t){

	follower_t * iterator_f;
	tweet_t * root;
	tweet_t * temp;

	if(root_t==NULL || root_t->uid==-1){
		return ;
	}

	print_users_details(root_t->lc);
	printf("Uid : %d\n",root_t->uid);

    iterator_f=root_t->followers;
    printf("Followers : ");
    printF(iterator_f);
    printf("\n");

    printf("Tweets : ");
	root=root_t->wall_head;
	if(root!=NULL){

		while(root!=NULL){
			temp=root;
			root=root->lc;
		}
		while(temp!=NULL){
			printf("%d ",temp->timestamp);
			temp=temp->next;
		}
	}
	printf("\n");


    print_users_details(root_t->rc);


}

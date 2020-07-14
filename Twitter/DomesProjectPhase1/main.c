/*********************************************************//**
 * @file   main.c                                            *
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  	     *
 *                                                    	     *
 * @brief  Source file for the needs of cs-240b project 2018 *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "twitter.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize()
{
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
	struct user* pointer;
	struct user* temp;
	struct user* found;
	struct user* temp_pointer;
	struct tweet* senti;

	pointer=usersList;
	temp=NULL;

	while(pointer!=NULL && pointer->uid<uid){
		temp=pointer;
		pointer=pointer->next;
	}

	found=malloc(sizeof(struct user));
	found->uid=uid;
	found->next=pointer;
	found->followers=NULL;
	senti=malloc(sizeof(struct tweet));
	found->wall_sentinel=senti;
	found->wall_sentinel->uid=-1;
	found->wall_sentinel->tid=-1;
	found->wall_sentinel->next=NULL;
	found->wall_head=found->wall_sentinel;

	if(temp==NULL){
		usersList=found;
	}else{
		temp->next=found;
	}

	temp_pointer=usersList;

	if(temp_pointer==NULL){
		DPRINT("No users\n");
	}
	DPRINT("Users =");
	while(temp_pointer!=NULL){
		if(temp_pointer->next==NULL){
			DPRINT(" %d \n",temp_pointer->uid);
			temp_pointer=temp_pointer->next;
			continue;
		}
		DPRINT(" %d,",temp_pointer->uid);
		temp_pointer=temp_pointer->next;
	}

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
	struct user* pointer;
	struct follower* fpointer;
	struct follower* temp;
	struct follower* found;
	struct follower* temp_pointer;

	pointer=usersList;

	while(pointer!=NULL && pointer->uid!=uid1){
		pointer=pointer->next;
	}

	if(pointer==NULL){
		DPRINT("There is no user with that uid\n");
		return 0;
	}

	if(pointer->uid==uid2){
		DPRINT("Cant subscribe himself\n");
		return 0;
	}

	fpointer=pointer->followers;
	temp=NULL;

	while(fpointer!=NULL && fpointer->uid<uid2){
		temp=fpointer;
		fpointer=fpointer->next;
	}

	found=malloc(sizeof(struct follower));
	found->uid=uid2;
	found->next=fpointer;

	if(temp==NULL){
		pointer->followers=found;
	}else{
		temp->next =found;
	}

	temp_pointer=pointer->followers;

	if(temp_pointer==NULL){
		DPRINT("No followers\n");
	}
	DPRINT("Followers = ");
	while(temp_pointer!=NULL){
		if(temp_pointer->next==NULL){
			DPRINT(" %d \n",temp_pointer->uid);
			temp_pointer=temp_pointer->next;
			continue;
		}
		DPRINT(" %d,",temp_pointer->uid);
		temp_pointer=temp_pointer->next;
	}


	return 1;
}


/**
 * @brief New tweet event
 * 
 * @param uid            The user who posted the tweet
 * @param tid            The tweet's id
 * @param tag            The tweet's hashtag
 * @param timestamp      The time the tweet was posted
 * @param time_relevance How long the tweet was relevant/trending
 *
 * @return 1 on success
 *         0 on failure
 */
int tweet(int uid, int tid, int tag, int timestamp, int time_relevance)
{
	struct user* pointer;
	struct user* follower_to_user;
	struct tweet* ftemp;
	struct follower* fpointer;
	struct tweet* iterator1;
	struct tweet* temp;
	struct user* iterator;
	struct tagged_tweet* ttpointer;
	struct tagged_tweet* temp_tt;
	struct tagged_tweet* current;
	int uid_temp;

	pointer=usersList;

	while(pointer!=NULL && pointer->uid!=uid){
		pointer=pointer->next;
	}

	if(pointer==NULL){
		DPRINT("There is no user with that uid\n");
		return 0;
	}

	ftemp=malloc(sizeof(struct tweet));
	ftemp->uid=uid;
	ftemp->tid=tid;
	ftemp->next=pointer->wall_head;
	pointer->wall_head=ftemp;

	fpointer=pointer->followers;

	while(fpointer!=NULL){
		uid_temp=fpointer->uid;
		
		if(uid_temp<pointer->uid){
			
			follower_to_user=usersList;
			while(follower_to_user!=pointer){
				if(uid_temp==follower_to_user->uid){
					temp=malloc(sizeof(struct tweet));
					temp->tid=tid;
					temp->uid=uid;
					temp->next=follower_to_user->wall_head;
					follower_to_user->wall_head=temp;
					break;
				}
				follower_to_user=follower_to_user->next;
			}

		}else{
			follower_to_user=pointer->next;
			while(follower_to_user!=NULL){
				if(uid_temp==follower_to_user->uid){
					temp=malloc(sizeof(struct tweet));
					temp->tid=tid;
					temp->uid=uid;
					temp->next=follower_to_user->wall_head;
					follower_to_user->wall_head=temp;
					break;
				}
				follower_to_user=follower_to_user->next;
			}
		}

		fpointer=fpointer->next;
	}
	if(tag>9 || tag<0){
		return 0;
	}

	ttpointer=Hashtags[tag];
	temp_tt=malloc(sizeof(struct tagged_tweet));
	temp_tt->tid=tid;
	temp_tt->uid=uid;
	temp_tt->timestamp=timestamp;
	temp_tt->time_relevance=time_relevance;
	temp_tt->next=NULL;
	temp_tt->prev=NULL;

	if(ttpointer==NULL){
		Hashtags[tag]=temp_tt;
	}else if(temp_tt->timestamp<=ttpointer->timestamp){
		temp_tt->next=Hashtags[tag];
		temp_tt->next->prev=temp_tt;
		Hashtags[tag]=temp_tt;
	}else{
		current=Hashtags[tag];
		while(current->next!=NULL && current->next->timestamp < temp_tt->timestamp){
			current=current->next;
		}
		temp_tt->next=current->next;
		if(current->next!=NULL){
			temp_tt->next->prev=temp_tt;
		}
		current->next=temp_tt;
		temp_tt->prev=current;
	}

	iterator=usersList;

	while(iterator!=NULL){
		iterator1=iterator->wall_head;
		DPRINT("%d = ",iterator->uid);
		while(iterator1->uid!=iterator->wall_sentinel->uid){
			DPRINT(" %d,%d ",iterator1->uid,iterator1->tid);
			iterator1=iterator1->next;
		}
		DPRINT("\n");
		iterator=iterator->next;
	}
	

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
	struct user* pointer;
	struct follower* fpointer;
	struct follower* temp;
	struct user* iterator;
	struct user*iterator1;
	struct follower* header;
	struct tweet* prev;
	struct tweet* tpointer;
	struct tweet* test;
	int uid_temp;

	pointer=usersList;
	header=NULL;

	while(pointer!=NULL && pointer->uid!=uid1){
		pointer=pointer->next;
	}

	if(pointer==NULL){
		DPRINT("There is no user with that uid\n");
		return 0;
	}

	fpointer=pointer->followers;
	temp=NULL;

	if(fpointer!=NULL && fpointer->uid==uid2){
		header=pointer->followers;
	}

	while(fpointer!=NULL && fpointer->uid!=uid2){
		temp=fpointer;
		fpointer=fpointer->next;
	}

	if(fpointer==NULL){
		DPRINT("There is no follower with that id\n");
		return 0;
	}
	uid_temp=fpointer->uid;
	iterator=usersList;

	while(iterator!=NULL && iterator->uid!=uid_temp){
		iterator=iterator->next;
	}

	if(iterator==NULL){
		DPRINT("There is no user with that uid\n");
		return 0;
	}


	tpointer=iterator->wall_head;

	if(iterator->wall_head->uid==iterator->wall_sentinel->uid){
		return 0;
	}

	while(tpointer->uid!=iterator->wall_sentinel->uid && tpointer->uid==uid1){
		iterator->wall_head=tpointer->next;
		free(tpointer);
		tpointer=iterator->wall_head;
	}
	while(tpointer->uid!=iterator->wall_sentinel->uid){
		while(tpointer->uid!=iterator->wall_sentinel->uid && tpointer->uid!=uid1){
			prev=tpointer;
			tpointer=tpointer->next;
		}

		if(tpointer->uid==iterator->wall_sentinel->uid){
			break;
		}

		prev->next=tpointer->next;
		free(tpointer);
		tpointer=prev->next;
	}


	if(header!=NULL){
		pointer->followers=header->next;
		free(header);
	}else{
		temp->next=fpointer->next;
		free(fpointer);
	}

	iterator1=usersList;

	while(iterator1!=NULL){
		test=iterator1->wall_head;
		DPRINT("%d = ",iterator1->uid);
		while(test->uid!=iterator1->wall_sentinel->uid){
			DPRINT(" %d,%d ",test->uid,test->tid);
			test=test->next;
		}
		DPRINT("\n");
		iterator1=iterator1->next;
	}
	DPRINT("\n");
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
	struct user* pointer;
	struct user* ppointer;
	struct user* header;
	struct tweet* tpointer;
	struct tweet* temp;
	struct tweet* iterator1;
	struct user* iterator;
	struct follower* fpointer;
	
	temp=NULL;
	ppointer=NULL;
	header=NULL;
	pointer=usersList;

	if(pointer!=NULL && pointer->uid==uid){
		header=usersList;
	}

	while(pointer!=NULL && pointer->uid!=uid){
		ppointer=pointer;
		pointer=pointer->next;
	}

	if(pointer==NULL){
		DPRINT("There is no user with that uid\n");
		return 0;
	}

	tpointer=pointer->wall_head;

	while(tpointer->uid!=pointer->wall_sentinel->uid){
		temp=tpointer->next;
		free(tpointer);
		tpointer=temp;
	}
	pointer->wall_head=pointer->wall_sentinel;

	fpointer=pointer->followers;

	while(fpointer!=NULL){
		unsubscribe(uid,fpointer->uid);
		fpointer=fpointer->next;
	}

	if(header!=NULL){
		usersList=header->next;
		free(header);
	}else{
		ppointer->next=pointer->next;
		free(pointer);
	}

	iterator=usersList;

	while(iterator!=NULL){
		iterator1=iterator->wall_head;
		DPRINT("%d = ",iterator->uid);
		while(iterator1->uid!=iterator->wall_sentinel->uid){
			DPRINT("%d,%d ",iterator1->uid,iterator1->tid);
			iterator1=iterator1->next;
		}
		DPRINT("\n");
		iterator=iterator->next;
	}


	return 1;
}

/**
 * @brief Lookup tweet in user's wall
 * 
 * @param uid The user's id
 * @param tid The tweet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int lookup(int uid, int tid)
{
	struct user* pointer;
	struct tweet* tpointer;
	struct tweet* temp;

	pointer=usersList;
	temp=NULL;

	while(pointer!=NULL && pointer->uid!=uid){
		pointer=pointer->next;
	}

	if(pointer==NULL){
		DPRINT("There is no user with that uid\n")
		return 0;
	}

	tpointer=pointer->wall_head;

	while(tpointer->uid!=pointer->wall_sentinel->uid){
		if(tpointer->tid==tid){
			temp=tpointer;
			break;
		}
	}

	if(temp==NULL){
		DPRINT("There is no tweet with that tid\n");
		return 0;
	}

	DPRINT("Tweet = %d:%d \n",temp->tid,temp->uid);


	return 1;
}

/**
 * @brief Combine tweets that have following tags
 * 
 * @param tag1 The first tag
 * @param tag2 The second tag
 *
 * @return 1 on success
 *         0 on failure
 */
int merge(int tag1, int tag2)
{
	struct tagged_tweet* iterator1;
	struct tagged_tweet* iterator2;
	struct tagged_tweet* temp;
	struct tagged_tweet* print1;
	struct tagged_tweet*print2;

	if((tag1>9 || tag1<0) || (tag2>9 || tag2<1)){
		DPRINT("There is no hashtag like that\n");
		return 0;
	}

	iterator1=Hashtags[tag1];
	iterator2=Hashtags[tag2];

	print1=Hashtags[tag1];
	print2=Hashtags[tag2];

	if(iterator1==NULL){
		temp=iterator2;
	}
	if(iterator2==NULL){
		temp=iterator1;
	}
	DPRINT("Merged= ");

	if(iterator1->timestamp < iterator2->timestamp){
		temp=iterator1;
		iterator1=temp->next;
	}else{
		temp=iterator2;
		iterator2=temp->next;
	}
	DPRINT("%d:%d:%d:%d ",temp->tid,temp->uid,temp->timestamp,temp->time_relevance);

	while(iterator1!=NULL && iterator2!=NULL){

		if(iterator1!=NULL && iterator2!=NULL){

				if(iterator1->timestamp <= iterator2->timestamp){
					temp->next=iterator1;
					temp=iterator1;
					iterator1=temp->next;
				}else if(iterator1->timestamp > iterator2->timestamp){
					temp->next=iterator2;
					temp=iterator2;
					iterator2=temp->next;
				}
				DPRINT("%d:%d:%d:%d ",temp->tid,temp->uid,temp->timestamp,temp->time_relevance);
		}else if(iterator1==NULL){
			temp->next=iterator2;
			temp=iterator2;
			iterator2=temp->next;
		}else if(iterator2==NULL){
			temp->next=iterator1;
			temp=iterator1;
			iterator1=temp->next;
		}
		DPRINT("%d:%d:%d:%d ",temp->tid,temp->uid,temp->timestamp,temp->time_relevance);
	}

	DPRINT("\nTweets1= ");
	while(print1!=NULL){
		DPRINT("%d:%d:%d:%d ",print1->tid,print1->uid,print1->timestamp,print1->time_relevance);
		print1=print1->next;
	}

	DPRINT("\nTweets2= ");
	while(print2!=NULL){
		DPRINT("%d:%d:%d:%d ",print2->tid,print2->uid,print2->timestamp,print2->time_relevance);
		print2=print2->next;
	}
	DPRINT("\n");	
	return 1;
}

/**
 * @brief Find tweets of the same tag that were trending
 *        at the same time as the current tweet
 *
 * @param tid The tweet's id
 * @param tag The tweet's hashtag
 *
 * @return 1 on success
 *         0 on failure
 */
int time_relevant(int tid, int tag)
{
	struct tagged_tweet* iterator1;
	struct tagged_tweet* iterator_down;
	struct tagged_tweet* iterator_up;
	int limit_down,limit_up;


	if(tag>9 || tag<0){
		DPRINT("There is no hashtag like that\n");
		return 0;
	}

	iterator1=Hashtags[tag];

	while(iterator1!=NULL && iterator1->tid!=tid){
		iterator1=iterator1->next;
	}

	if(iterator1==NULL){
		DPRINT("There is no tagged tweet with that tid\n");
		return 0;
	}

	limit_down=iterator1->timestamp - iterator1->time_relevance;
	limit_up=iterator1->timestamp + iterator1->time_relevance;

	iterator_down=iterator1->prev;
	iterator_up=iterator1->next;

	DPRINT("Relevant tweets= ");

	while(iterator_down!=NULL && iterator_down->timestamp >= limit_down){
		DPRINT("%d:%d:%d:%d ", iterator_down->tid,iterator_down->uid,iterator_down->timestamp,iterator_down->time_relevance);
		iterator_down=iterator_down->prev;
	}

	while(iterator_up!=NULL && iterator_up->timestamp <= limit_up){
		DPRINT("%d:%d:%d:%d ", iterator_up->tid,iterator_up->uid,iterator_up->timestamp,iterator_up->time_relevance);
		iterator_up=iterator_up->next;
	}	
	DPRINT("\n");

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
	struct user* pointer;
	struct follower* fpointer;
	struct tweet* tpointer;

	pointer=usersList;

	while(pointer!=NULL){
		fpointer=pointer->followers;
		tpointer=pointer->wall_head;

		DPRINT("User = %d\n",pointer->uid);
		DPRINT("Followers : ");
		while(fpointer!=NULL){
			DPRINT("%d ",fpointer->uid);
			fpointer=fpointer->next;
		}
		DPRINT("\n");
		DPRINT("Tweets : ");
		while(tpointer->uid!=pointer->wall_sentinel->uid){
			DPRINT("%d ",tpointer->tid);
			tpointer=tpointer->next;
		}
		DPRINT("\n");
		pointer=pointer->next;
	}
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
	struct tagged_tweet* current_iterator;
	int i;

	i=0;

	while(i<10){
		current_iterator=Hashtags[i];
		DPRINT("hashtag%d:",i);
		while(current_iterator!=NULL){
			DPRINT(" %d %d %d %d ",current_iterator->uid,current_iterator->tid,current_iterator->timestamp,current_iterator->time_relevance);
			current_iterator=current_iterator->next;
		}
		DPRINT("\n");
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

/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

			/* Register user
			 * R <uid> */
			case 'R':
				{
					int uid;

					sscanf(buff, "%c %d", &event, &uid);
					DPRINT("%c %d\n", event, uid);

					if (register_user(uid)) {
						DPRINT("R %d succeeded\n", uid);
					} else {
						fprintf(stderr, "R %d failed\n", uid);
					}

					break;
				}

			/* User uid1 is now following user uid2
			 * S <uid1> <uid2> */
			case 'S':
				{
					int uid1, uid2;

					sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
					DPRINT("%c %d %d\n", event, uid1, uid2);

					if (subscribe(uid1, uid2)) {
						DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
					}

					break;
				}

			/* New tweet event
			 * T <uid> <tid> <hashtag> <timestamp> <time_relevance> */
			case 'T':
				{
					int uid, tid, tag, timestamp, time_relevance;

					sscanf(buff, "%c %d %d %d %d %d", &event, &uid, &tid, &tag, &timestamp, &time_relevance);
					DPRINT("%c %d %d %d %d %d\n", event, uid, tid, tag, timestamp, time_relevance);

					if (tweet(uid, tid, tag, timestamp, time_relevance)) {
						DPRINT("%c %d %d %d %d %d succeeded\n", event, uid, tid, tag, timestamp, time_relevance);
					} else {
						fprintf(stderr, "%c %d %d %d %d %d failed\n", event, uid, tid, tag, timestamp, time_relevance);
					}

					break;
				}

			/* User uid1 stopped following user uid2
			 * U <uid1> <uid2> */
			case 'U':
				{
					int uid1, uid2;

					sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
					DPRINT("%c %d %d\n", event, uid1, uid2);

					if (unsubscribe(uid1, uid2)) {
						DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
					}

					break;
				}

			/* Delete user account
			 * D <uid> */
			case 'D':
				{
					int uid;

					sscanf(buff, "%c %d", &event, &uid);
					DPRINT("%c %d\n", event, uid);

					if (delete_user(uid)) {
						DPRINT("%c %d succeeded\n", event, uid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, uid);
					}

					break;
				}

			/* Lookup tweet in user's wall
			 * L <uid> <tid> */
			case 'L':
				{
					int uid, tid;

					sscanf(buff, "%c %d %d\n", &event, &uid, &tid);
					DPRINT("%c %d %d\n", event, uid, tid);

					if (lookup(uid, tid)) {
						DPRINT("%c %d %d succeeded\n", event, uid, tid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid, tid);
					}

					break;
				}

			/* Combine tweets that have following tags
			 * M <hashtag1> <hashtag2> */
			case 'M':
				{
					int tag1, tag2;

					sscanf(buff, "%c %d %d", &event, &tag1, &tag2);
					DPRINT("%c %d %d\n", event, tag1, tag2);

					if (merge(tag1, tag2)) {
						DPRINT("%c %d %d succeeded\n", event, tag1, tag2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, tag1, tag2);
					}

					break;
				}

			/* Find tweets of the same tag that were trending
			 * at the same time as the current tweet
			 * F <tid> <hashtag> */
			case 'F':
				{
					int tid, tag;

					sscanf(buff, "%c %d %d", &event, &tid, &tag);
					DPRINT("%c %d %d\n", event, tid, tag);

					if (time_relevant(tid, tag)) {
						DPRINT("%c %d %d succeeded\n", event, tid, tag);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, tid, tag);
					}

					break;
				}

			/* Print all active users
			 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_users()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print all tagged tweets
			 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_tweets()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Empty line */
			case '\n':
				break;

			/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}

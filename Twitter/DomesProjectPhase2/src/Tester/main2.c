
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Darwin.h"

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
int initialize (void)
{  int i;
	for(i=0;i<=4;i++){
		continents[i]=malloc(sizeof(struct ContinentTree));
		continents[i]->sentinel=malloc(sizeof(struct ContinentPopulation));
		continents[i]->sentinel->gid=-1;
		continents[i]->sentinel->lc=NULL;
		continents[i]->sentinel->rc=NULL;
		continents[i]->population_root=continents[i]->sentinel;
	}


	return 1;
}

struct Species *find(struct Species* root, int sid){
	
	if(root==NULL  || sid==root->sid){
       return root;
	}
		struct Species* temp=find(root->lc,sid);
		if(temp!=NULL && temp->sid==sid){
			return temp;
		}else{
			struct Species* temp1=find(root->rc,sid);
			return temp1;
		}
		
}


struct Species *add_species(struct Species * root, int sid){
	struct Species *temp_species;
	if (root==NULL){
		temp_species= malloc(sizeof(struct Species));
		temp_species->sid=sid;
		temp_species->rc=NULL;
		temp_species->lc=NULL;
		root=temp_species;
		return root;

	}
	if(sid>root->sid){
		temp_species=malloc(sizeof(struct Species));
		temp_species->sid=sid;
		temp_species->rc=NULL;
		temp_species->lc=root;
		return temp_species;
	}
	else{
		if(sid<root->sid){
			if(root->lc!=NULL && sid>root->lc->sid){
				root->rc=add_species(root->rc, sid);
				return root;
			}else{
				root->lc=add_species(root->lc,sid);
				return root;
			}
		}
	}
}

void print_post_order(struct Species* head){
	if(head==NULL){
		return;
	}
	print_post_order(head->lc);

	print_post_order(head->rc);


	DPRINT("%d\t",head->sid);

}


/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid)
{
	struct Species* temp_species;

	temp_species=add_species(Species_root,sid);

	Species_root=temp_species;
    print_post_order(Species_root);

    DPRINT("\n");



	return 1;
}

struct Population* add_population(int gid, int sid, int cid,struct Population* head){
	struct Population* temp_population;
   if(head==NULL){
	   temp_population=malloc(sizeof(struct Population));
	   temp_population->gid=gid;
	   temp_population->cid=cid;
	   temp_population->sid=sid;
	   temp_population->lc=NULL;
	   temp_population->rc=NULL;
	   return temp_population;

   }
   if(head->gid > gid){
	   head->lc=add_population(gid,sid,cid,head->lc);
   }else{
	   head->rc=add_population(gid,sid,cid,head->rc);

   }
   return head;

}
void print_in_order(struct Population *head){
	if(head==NULL){
		return;
	}
	print_in_order(head->lc);
	DPRINT("%d %d,", head->gid, head->cid);
	print_in_order(head->rc);
}
/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){
      
	struct Species* temp_species;
	struct Population* temp_population;

	temp_species=find(Species_root,sid);
    if(temp_species==NULL){
		DPRINT("SID NOT FOUND\n");
		return 0;
	}
	temp_population=add_population(gid,sid,cid,temp_species->population_root);

	temp_species->population_root=temp_population;
	
	DPRINT("%d\n\t",sid);
	print_in_order(temp_population);
	DPRINT("\n");


	return 1;
}

struct Population* find_population(struct Population * head, int gid){
	if(head==NULL || head->gid==gid){
		return head;
	}
	if(head->gid<gid){
		return find_population(head->rc,gid);
	}else{
		return find_population(head->lc,gid);
	}

}

struct Population* find_parent(struct Population* head, struct Population* p1, struct Population* p2 ){
	
	if(head==NULL){
		return NULL;
	}
	if(head==p1 || head==p2){
		return head;
	}
	struct Population * new_head=find_parent(head->lc,p1,p2);
	struct Population* new_head2=find_parent(head->rc,p1,p2);
	if(new_head!=NULL && new_head2!=NULL){
		return head;
	}
	if(new_head!=NULL){
		return new_head;
	}else{
		return new_head2;
	}
}

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2){
	struct Population* temp_population1;
	struct Population* temp_population2;
	struct Species * temp_species;
	struct Population * temp_population3;

	temp_species=find(Species_root,sid);

    if(temp_species==NULL){
		DPRINT("SID NOT FOUND\n");
		return 0;
	}


	temp_population1=find_population(temp_species->population_root,gid1);
	temp_population2=find_population(temp_species->population_root,gid2);
    if(temp_population1==NULL || temp_population2==NULL){
		DPRINT("GID NOT FOUND\n");
		return 0;
	}
    temp_population3= find_parent(temp_species->population_root,temp_population1,temp_population2);
	if(temp_population3==NULL){
		DPRINT("ANSCSTOR NOT FOUND \n");
		return 0;
	}

   DPRINT("Lowest Common Ancestor : %d\n",temp_population3->gid);

	return 1;
}

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
	return 1;
}

struct ContinentPopulation * make_continent_tree(struct ContinentPopulation * head, int gid ,int cid){
	if(head->gid==-1){
		struct ContinentPopulation *temp_population;
	    temp_population=malloc(sizeof(struct ContinentPopulation));
		temp_population->gid=gid;
		temp_population->lc=continents[cid]->sentinel;
		temp_population->rc=continents[cid]->sentinel;
		return temp_population;
	}
	if(gid<head->gid){

		head->lc=make_continent_tree(head->lc,gid,cid);
	}
	else{
		head->rc=make_continent_tree(head->rc,gid,cid);
	}
	return head;
}

void traverse_population_tree(struct Population * head){
	if(head==NULL){
		return;

	}
	
	continents[head->cid]->population_root=make_continent_tree(continents[head->cid]->population_root,head->gid,head->cid);
	traverse_population_tree(head->lc);
	traverse_population_tree(head->rc);
}


void traverse_species_tree(struct Species * head){
	if(head==NULL){
		return;
	}
	

	traverse_population_tree(head->population_root);

	traverse_species_tree(head->lc);
	traverse_species_tree(head->rc);

}
/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){

    traverse_species_tree(Species_root);

	print_continents();

	return 1;
}


struct Population *find_the_smallest(struct Population * head){
	if(head==NULL){
		return NULL;
	}
	if(head->lc==NULL){
		return head;
	}
	head=find_the_smallest(head->lc);

}

struct ContinentPopulation * find_the_smallest_continents(struct ContinentPopulation * head){

	if(head->lc->gid=-1){
		return head;
	}
	head->lc=find_the_smallest_continents(head->lc);

}

struct ContinentPopulation * remove_continents(struct ContinentPopulation * head, int gid , int cid ){
	if(head->gid==-1){
		return head;
	}
	if(head->gid>gid){
		head->lc=remove_continents(head->lc,gid,cid);
	}
	else if(head->gid<gid){
		head->rc=remove_continents(head->rc,gid,cid);
	}else{
		struct ContinentPopulation* temp_population;
		if( head->lc->gid == -1 && head->rc->gid!=-1){
			 temp_population=head->rc;
			free(head);
            return temp_population;
		}else if(head->rc->gid ==-1 && head->lc->gid!=-1){
			temp_population=head->lc;
			free(head);
			return temp_population;
		}else if (head->rc->gid==-1 && head->lc->gid==-1){
			free(head);
			return continents[cid]->sentinel;
		}else{
		 	temp_population=find_the_smallest_continents(head->rc);
			head->gid=temp_population->gid;
			head->rc=remove_continents(head->rc,head->gid,cid);
			return head;

		}
	}
}

struct Population *remove_population(struct Population *head ,int gid){
	if(head==NULL){
		return NULL ;
	}
	if(head->gid>gid){
		head->lc=remove_population(head->lc,gid);
	}
	else if(head->gid<gid){
		head->rc=remove_population(head->rc,gid);
	}else{
		struct ContinentPopulation * temp_population2;
		struct Population* temp_population;
		temp_population2=remove_continents(continents[head->cid]->population_root,gid,head->cid);
		continents[head->cid]->population_root=temp_population2;
		if( head->lc == NULL && head->rc!=NULL){
			 temp_population=head->rc;
			free(head);
			head->rc=NULL;
            return temp_population;
		}else if(head->rc==NULL && head->lc!=NULL){
			temp_population=head->lc;
			free(head);
			head->lc=NULL;
			return temp_population;

		}else if (head->rc==NULL && head->lc==NULL){
			free(head);
			return NULL;
		}else{
		 temp_population=find_the_smallest(head->rc);
			head->gid=temp_population->gid;
			head->sid=temp_population->sid;
			head->cid=temp_population->cid;
			head->rc=remove_population(head->rc,head->gid);
			return head;

		}
	}
}



/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
	struct Species * temp_species;
	struct Population *temp_population;

	temp_species=find(Species_root,sid);
    if(temp_species==NULL){
		DPRINT ("SID NOT FOUND\n");
		return 0;
	}
	temp_population =remove_population(temp_species->population_root,gid);
	temp_species->population_root=temp_population;

   print_populations();
   
   print_continents();

	return 1;
}



struct Species * find_the_smallest_species(struct Species* head){
	struct Species* temp;
	struct Species* temp1=NULL;
	struct Species* head2;

	if(head==NULL){
		return NULL;
	}

	while(head->lc!=NULL){
		temp=head;
		head=head->lc;
	}
	if(head->rc!=NULL){
		head2=head->rc;
		while(head2->lc!=NULL){
			temp1=head2;
			head2=head2->lc;
		}
		if(temp1==NULL){
			head->rc=NULL;
			return head;
		}else{
			temp1->lc=NULL;
			return head2;
		}
	}else{
		temp->lc=NULL;
		return head;
	}
}
	

void deleteTree(struct Population* node){
	
	if(node==NULL){
		return;
	}

	deleteTree(node->lc);
	continents[node->cid]->population_root=remove_continents(continents[node->cid]->population_root,node->gid,node->cid);
	deleteTree(node->rc);
	free(node);
}

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(){
   struct Species *temp_species;

   temp_species=find_the_smallest_species(Species_root);
   if(temp_species==NULL){
	   DPRINT("SID NOT FOUND\n");
	   return 0;
   }
	   	
	deleteTree(temp_species->population_root);

   	free(temp_species);
  	temp_species->lc=NULL;
  	temp_species->rc=NULL;
   	temp_species=NULL;

   print_populations();
   print_continents();

	return 1;
}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){
	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){
	return 1;
}

/**
 * @brief Print species' leaves list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){
	print_post_order(Species_root);
	return 1;
}
/*in order print*/
void print_p_i_t(struct Population *head){
	if(head==NULL){
		return ;
	}
	print_p_i_t(head->lc);
	DPRINT("%d  %d,", head->gid, head->cid);
	print_p_i_t(head->rc);
}

/*post order print*/
void print_p_o_t(struct Species * head){
	if(head==NULL){
		return;
	}
	print_p_o_t(head->lc);
	print_p_o_t(head->rc);
	DPRINT("%d\n ", head->sid);
	print_p_i_t(head->population_root);
	DPRINT("\n");

}
/**
 * @brief Print species' tree with population trees
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations(){
	print_p_o_t(Species_root);

	return 1;
}

void print_in_order_continent(struct ContinentPopulation * head){
	if(head->gid==-1){
		return;
	}
	print_in_order_continent(head->lc);
	DPRINT("%d,",head->gid);
	print_in_order_continent(head->rc);
}
/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	int i;
	for(i=0;i<=4;i++){
        DPRINT("Continent %d :" , i);
		print_in_order_continent(continents[i]->population_root);
		DPRINT("\n");
	}
	return 1;
}

/**
 * @brief Print homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){
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

				/* Insert Species
				 * S <sid> */
			case 'S':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (insert_species(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Insert population
				 * G <gid> <sid> <cid> */
			case 'G':
				{
					int gid, sid, cid;

					sscanf(buff, "%c %d %d %d", &event, &gid, &sid, &cid);
					DPRINT("%c %d %d %d\n", event, gid, sid, cid);

					if (insert_population(gid, sid, cid)) {
						DPRINT("%c %d %d %d succeeded\n", event, gid, sid, cid);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, gid, sid, cid);
					}

					break;
				}

				/* Lowest Common Ancestor
				 * L <sid> <gid1> <gid2> */
			 case 'L':
				{
					int sid, gid1, gid2;

					sscanf(buff, "%c %d %d %d", &event, &sid, &gid1, &gid2);
					DPRINT("%c %d %d %d\n", event, sid, gid1, gid2);

					if (lowest_common_ancestor(sid, gid1, gid2)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid, gid1, gid2);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid, gid1, gid2);
					}

					break;
				}

				/* Merge species
				 * M <sid1> <sid2> <sid3> */
			case 'M':
				{
					int sid1, sid2, sid3;

					sscanf(buff, "%c %d %d %d", &event, &sid1, &sid2, &sid3);
					DPRINT("%c %d %d %d\n", event, sid1, sid2, sid3);

					if (merge_species(sid1, sid2, sid3)) {
						DPRINT("%c %d %d %d succeeded\n", event, sid1, sid2, sid3);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, sid1, sid2, sid3);
					}

					break;
				}

				/* Distribute species
				 * D */
			case 'D':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (distribute()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Delete population
				 * K <gid> <sid> */
			case 'K':
				{
					int gid, sid;

					sscanf(buff, "%c %d %d", &event, &gid, &sid);
					DPRINT("%c %d %d\n", event, gid, sid);

					if (delete_population(gid, sid)) {
						DPRINT("%c %d %d succeeded\n", event, gid, sid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, gid, sid);
					}

					break;
				}

				/* Delete species
				 * F */
			case 'F':
				{
					DPRINT("%c \n", event);

					if (delete_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Evolution to homo sapiens
				 * E */
			case 'E':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (evolution()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Species' statistics
				 * N */
			case 'N':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (species_statistics()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Population statistics
				 * J <sid> */
			case 'J':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (population_statistics(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
					}

					break;
				}

				/* Print species
				 * P */
			case 'P':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_species()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print populations
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_populations()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print continents
				 * C */
			case 'C':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_continents()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print homo sapiens
				 * W */
			case 'W':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_homo_sapiens()) {
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

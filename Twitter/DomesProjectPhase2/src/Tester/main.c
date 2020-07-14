
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
{
	int i;

	for(i=0; i<5; i++){
		continents[i]=malloc(sizeof(struct ContinentTree));
		continents[i]->sentinel=malloc(sizeof(struct ContinentPopulation));
		continents[i]->population_root=malloc(sizeof(struct ContinentPopulation));
		continents[i]->sentinel->gid=-1;
		continents[i]->sentinel->lc=NULL;
		continents[i]->sentinel->rc=NULL;
		continents[i]->population_root=continents[i]->sentinel;

	//	continents[i]->population_root->lc=continents[i]->sentinel;
	}

	return 1;
}

struct Species * PostOrderInsertion(struct Species * node, int key){

	struct Species * newNode;

	if(node==NULL){
		newNode=malloc(sizeof(struct Species));
		newNode->sid=key;
		node=newNode;
		return node;
	}
      if(node->sid<key){
		newNode=malloc(sizeof(struct Species));
		newNode->sid=key;
		newNode->lc=node;
		return newNode;
      }else{
		  if(node->sid>key && node->lc!=NULL && key>node->lc->sid){
			node->rc=PostOrderInsertion(node->rc,key);    
			return node;
		  }else{
			node->lc=PostOrderInsertion(node->lc,key);    
			return node;
		  }
    }
}


void inOrderTraversal(struct Population * tmp){
	if(tmp==NULL){
		return;
	}

	inOrderTraversal(tmp->lc);
	DPRINT("<%d><%d> ,",tmp->gid,tmp->cid);

	inOrderTraversal(tmp->rc);
}

/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid)
{
	Species_root=PostOrderInsertion(Species_root,sid);
 	
	print_species();

	return 1;
}


/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid){

	struct Population * tmp;
	struct Population * newNode;
	struct Species * tmp1;
	struct Population * populationNode;

	newNode=malloc(sizeof(struct Population));
	populationNode=NULL;

	newNode->gid=gid;
	newNode->sid=sid;
	newNode->cid=cid;


	tmp1=Species_root;

	while(tmp1!=NULL && tmp1->sid!=sid){
		if(tmp1->rc!=NULL && tmp1->rc->sid==sid){
			tmp1=tmp1->rc;
			break;
		}
		tmp1=tmp1->lc;
	}


	if(tmp1!=NULL && tmp1->sid==newNode->sid){
		tmp=tmp1->population_root;

		while(tmp!=NULL){
			populationNode=tmp;
			if(newNode->gid<tmp->gid){
				tmp=tmp->lc;
			}else if(newNode->gid>tmp->gid){
				tmp=tmp->rc;
			}
		}
		if(populationNode==NULL){
			tmp1->population_root=newNode;
		}else if(populationNode->gid<newNode->gid){
			newNode->parent=populationNode;
			populationNode->rc=newNode;
		}else if(populationNode->gid > newNode->gid){
			newNode->parent=populationNode;
			populationNode->lc=newNode;
		}
	}
	
    inOrderTraversal(tmp1->population_root);
	DPRINT("\n");

	return 1;
 
}
struct Population * LCAhelper(struct Population * node,int gid1,int gid2){

	if(node==NULL){
		return NULL;
	}

	if(node->gid>gid1 && node->gid>gid2){
		return LCAhelper(node->lc,gid1,gid2);
	}

	if(node->gid<gid1 && node->gid<gid2){
		return LCAhelper(node->rc,gid1,gid2);
	}

	return node;
}

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2){
	struct Species * tmp1;
	
	struct Population * anc;
	
	tmp1=Species_root;

	while(tmp1!=NULL && tmp1->sid!=sid){
		if(tmp1->rc!=NULL && tmp1->rc->sid==sid){
			tmp1=tmp1->rc;
			break;
		}
		tmp1=tmp1->lc;
	}

	anc=LCAhelper(tmp1->population_root,gid1,gid2);
    
	DPRINT("Lowest Common Ancestor : <%d> \n",anc->gid);

	return 1;
}




//for merging
void storeArrayInorder(struct Population * node , int array[] , int * ptr ){

	if(node==NULL){
		return;
	}

	storeArrayInorder(node->lc,array,ptr);
	array[*ptr]=node->gid;
	(*ptr)++;
	
	storeArrayInorder(node->rc,array,ptr);

}

//for merging
int * merge_arrays(int array[],int array1[],int size1,int size2){

	int tmpArray[size1+size2];
	int * mergedArray;
	int i=0,j=0,k=0;
	
	while(i<size1 && j<size2){
		if(array[i]<array1[j]){
			tmpArray[k]=array[i];
			i++;
		}else{
			tmpArray[k]=array1[j];
			j++;
		}
		k++;
	}
	
	while(i<size1){
		tmpArray[k]=array[i];
		i++;
		k++;
	}

	while(j<size2){
			tmpArray[k]=array1[j];
			j++;
			k++;
	}

	mergedArray=tmpArray;
	
	return mergedArray;
}
//for merging
struct Population * sortedArrayToTree(int array[],int start,int end){
	int mid;
	struct Population * node;

	if(start>end){
		return NULL;
	}

	mid=(start+end)/2;
	node=malloc(sizeof(struct Population));
	node->gid=array[mid];
	
	node->lc=sortedArrayToTree(array,start,mid-1);
	node->rc=sortedArrayToTree(array,mid+1,end);

	return node;


}

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
/*
	struct Population * mergedTreeRoot;
	struct Species * tmp1;
	struct Species * tmp2;
	struct Species * tmp3;
	int * ptrArray1;
	int * ptrArray2;
	int * mArray;
	//big arrays ?????????????????? static arrays???
	int array1[3000];
	int array2[3000];
	int i=0;
	int j=0;

	tmp1=Species_root;
	tmp2=Species_root;
	tmp3=Species_root;
	ptrArray1=array1;
	ptrArray2=array2;
	//insert sid3 .
	insert_species (sid3);

    //search sid1.

	while(tmp1!=NULL && tmp1->sid!=sid1){
		if(tmp1->rc!=NULL && tmp1->rc->sid==sid1){
			tmp1=tmp1->rc;
			break;
		}
		tmp1=tmp1->lc;
	}
	//search sid2.

	while(tmp2!=NULL && tmp2->sid!=sid2){
		if(tmp2->rc!=NULL && tmp2->rc->sid==sid2){
			tmp2=tmp2->rc;
			break;
		}
		tmp2=tmp2->lc;
	}
	//in order tree to array(sorted.)
	storeArrayInorder(tmp1->population_root,ptrArray1,&i);
	//for both trees. ( sid1/ sid2.)
	storeArrayInorder(tmp2->population_root,ptrArray2,&j);

	
	// merging 2 arrays in 1 (sorted by gid.)
	mArray=merge_arrays(ptrArray1,ptrArray2,i+1,j+1);
	// the sorted array is made into a in order tree.
	mergedTreeRoot=sortedArrayToTree(mArray,0,i+j+2);
	// search for sid3.

	while(tmp3!=NULL && tmp3->sid!=sid3){
		if(tmp3->rc!=NULL && tmp3->rc->sid==sid3){
			tmp3=tmp3->rc;
			break;
		}
		tmp3=tmp3->lc;
	}
	//new (merged) tree is saved into SID3 as asked.
	tmp3->population_root=mergedTreeRoot;
	//print it out.
	print_populations();
 */
	return 1;
}



void preOrderDistributionHelper(struct Population * node){

	struct ContinentPopulation * tmp;
	struct ContinentPopulation * tmp2;
	struct ContinentPopulation * prev;

	prev=NULL;
	
	if(node==NULL){
		return;
	}

	tmp=malloc(sizeof(struct ContinentPopulation));
	tmp->gid=node->gid;

	tmp2=continents[node->cid]->population_root;

	while(tmp2!=NULL && tmp2->gid!=-1){
		prev=tmp2;

		if(tmp->gid<tmp2->gid){
			tmp2=tmp2->lc;
		}else{
			tmp2=tmp2->rc;
		}
	}
	if(prev==NULL){
		continents[node->cid]->population_root=tmp;
		continents[node->cid]->population_root->lc=continents[node->cid]->sentinel;
	}else if(tmp->gid<prev->gid){
		prev->lc=tmp;
	}else{
		prev->rc=tmp;
	}
	
	preOrderDistributionHelper(node->lc);
	preOrderDistributionHelper(node->rc);

}
void PostOrderTraversalDistribute(struct Species * node){
	if(node==NULL){
		return;
	}

	PostOrderTraversalDistribute(node->lc);
	PostOrderTraversalDistribute(node->rc);
	
	preOrderDistributionHelper(node->population_root);

}


/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){

	struct Species * it;
	struct Population * pop;
	
	it=Species_root;
	
	PostOrderTraversalDistribute(it);

	print_continents();


	return 1;
}


struct Population * minValue(struct Population * node){
	struct Population * tmp;
	tmp=node;

	while(tmp!=NULL && tmp->lc!=NULL){
		tmp=tmp->lc;
	}
	return tmp;
}

struct ContinentPopulation * minValueCon(struct ContinentPopulation * node){
	struct ContinentPopulation * tmp;
	tmp=node;

	while(tmp!=NULL && tmp->lc!=NULL){
		tmp=tmp->lc;
	}
	return tmp;
}


struct ContinentPopulation * deleteNodeCon(struct ContinentPopulation * node,int gid){
	struct ContinentPopulation * tmp;
	
	
	if(node==NULL){
		return node;
	}

	if(gid<node->gid){
		node->lc=deleteNodeCon(node->lc,gid);
	}else if(gid>node->gid){
		node->rc=deleteNodeCon(node->rc,gid);
	}else{
		if(node->lc==NULL){
			tmp=node->rc;
			free(node);
			return tmp;
		}else if(node->rc==NULL){
			tmp=node->lc;
			free(node);
			return tmp;
		}

	tmp=minValueCon(node->rc);

	node->gid=tmp->gid;
	node->rc=deleteNodeCon(node->rc,tmp->gid);

	}
	return node;
}

struct Population * deleteNodePop(struct Population * node,int gid){
	struct Population *  tmp;
	
	
	if(node==NULL){
		return node;
	}

	if(gid<node->gid){
		node->lc=deleteNodePop(node->lc,gid);
	}else if(gid>node->gid){
		node->rc=deleteNodePop(node->rc,gid);
	}else{
		
	continents[node->cid]->population_root=deleteNodeCon(continents[node->cid]->population_root , gid);

		if(node->lc==NULL){
			tmp=node->rc;
			free(node);
			return tmp;
		}else if(node->rc==NULL){
			tmp=node->lc;
			free(node);
			return tmp;
		}

	tmp=minValue(node->rc);

	node->gid=tmp->gid;
	node->rc=deleteNodePop(node->rc,tmp->gid);

	}
	return node;

	

}

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
	struct Population * tmp;
	struct Species * tmp1;
	struct Population * populationNode;
	struct Population * prev;

	tmp1=Species_root;

	while(tmp1!=NULL && tmp1->sid!=sid){
		if(tmp1->rc!=NULL && tmp1->rc->sid==sid){
			tmp1=tmp1->rc;
			break;
		}
		tmp1=tmp1->lc;
	}


	if(tmp1==NULL){
		DPRINT("node doesnt exist");
		return 0;
	}
	tmp=tmp1->population_root;


	tmp1->population_root=deleteNodePop(tmp,gid);

	print_populations();
	print_continents();
	
	
	return 1;
}

void deletePopulationTree(struct Population* node){

	if(node==NULL){
		return;
	}

	deletePopulationTree(node->lc);
	deletePopulationTree(node->rc);

	continents[node->cid]->population_root=deleteNodeCon(continents[node->cid]->population_root,node->gid);
	free(node);
}

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species(){

	struct Species * it;
	struct Population * rt;
	struct Species * prev;
	struct Species * prev1;

	prev=NULL;
	prev1=NULL;
	it=Species_root;

		while(it->lc!=NULL){
			prev=it;
			it=it->lc;	
		}
		if(it->rc!=NULL){
			while(it->rc!=NULL){
				prev1=it;
				it=it->rc;
			}
		}
		
	deletePopulationTree(it->population_root);

	if(it==Species_root){
		free(it);
	}else if(prev!=NULL && prev1==NULL){
		prev->lc=it->lc;
		free(it);
	}else{
		prev1->rc=it->rc;
		free(it);
	}

	
	print_populations();
	
	print_continents();

	return 1;
}


struct Species * preOrderSpecies(struct Species * node){

	if(node==NULL){
		return node;
	}

	DPRINT("sid %d \n",node->sid);

	preOrderSpecies(node->lc);
	preOrderSpecies(node->rc);

}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution(){

	struct Species * tmp;
	tmp=Species_root;

	preOrderSpecies(tmp);


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

void PostOrderTraversal(struct Species * tmp){
	if(tmp==NULL){
		return;
	}

	PostOrderTraversal(tmp->lc);
	PostOrderTraversal(tmp->rc);

	DPRINT("<%d> ",tmp->sid);
}

/**
 * @brief Print species' leaves list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){

	struct Species * tmp;
	tmp=Species_root;

	PostOrderTraversal(tmp);
	DPRINT("\n");

	return 1;
}

void printPopulationsHelper(struct Species * tmp){
	if(tmp==NULL){
		return;
	}
	printPopulationsHelper(tmp->lc);
	printPopulationsHelper(tmp->rc);

	DPRINT("%d",tmp->sid);
	DPRINT("\n");
	inOrderTraversal(tmp->population_root);
	DPRINT("\n");
	
}


/**
 * @brief Print species' tree with population trees
 *
 * @return 1 on success
 *         0 on failure
 */

int print_populations(){
	struct Species * tmp;
	tmp=Species_root;

	printPopulationsHelper(tmp);

	return 1;
}


void inOrderTraversalContinents(struct ContinentPopulation * tmp){
	if(tmp==NULL || tmp->gid==-1){
		return;
	}
	inOrderTraversalContinents(tmp->lc);
	DPRINT(" <%d> ,",tmp->gid);
	inOrderTraversalContinents(tmp->rc);
}



/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	
	int i=0;

	for (i=0; i<5; i++){
		DPRINT("Continent %d : ",i);
		inOrderTraversalContinents(continents[i]->population_root);
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

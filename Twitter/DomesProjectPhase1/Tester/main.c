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
int print_populations();

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize (void)
{
	struct ContinentPopulation* temp;

	int i = 0;

	Species_head = NULL;
	Species_tail = NULL;

	for (i=0;i<5;i++){
		temp= malloc(sizeof(struct ContinentPopulation));
		continents[i]=malloc(sizeof(struct ContinentList));
		temp->gid=-1;
		temp-> next=NULL;
		continents[i]->sentinel=temp;
		continents[i]->populationList=temp;
	}

	hs_L = NULL;

	//Species_head = (struct Species*)malloc(sizeof(struct Species));

	/*for (i=0;i<5;i++){
		continents[i]=(struct ContinentList*)malloc(sizeof(struct ContinentList));
	}*/

	//hs_L = (struct Population*)malloc(sizeof(struct Population));

	return 1;
}


/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species (int sid)
{
	struct Species * temp_species;
	struct Species * new_species;
	int flag = 0;
	struct Species * c;
	struct Population *cp;

	if (Species_head != NULL) {
		//if the list is not empty

		if (sid < Species_head->sid) {
			//if we insert at the beginning

			new_species = (struct Species*)malloc(sizeof(struct Species));
			new_species->sid = sid;
			new_species->prev = NULL;
			new_species->Population_head = NULL;
			new_species->Population_tail = NULL;
			new_species->next = Species_head;

			Species_head->prev = new_species;

			Species_head = new_species;
		}
		else{
			//if we dont insert at the beginning
			temp_species= Species_head;

			while (temp_species->next!=NULL) {
				if (temp_species->next->sid > sid) {
					flag=1;
					break;
				}
				temp_species = temp_species->next;
			}


			new_species = (struct Species*)malloc(sizeof(struct Species));
			new_species->sid = sid;
			new_species->Population_head = NULL;
			new_species->Population_tail = NULL;

			if (flag==1) {
				//if we insert in the middle

				new_species->next = temp_species->next;
				temp_species->next->prev = new_species;

				temp_species->next = new_species;
				new_species->prev = temp_species;
			}
			else {
				//if we insert in the end
				temp_species->next = new_species;
				new_species->prev = temp_species;
				new_species->next=NULL;
				Species_tail = new_species;
			}


		}


	}
	else {
		//if the list is empty

		Species_head = (struct Species*)malloc(sizeof(struct Species));
		Species_head->sid = sid;
		Species_head->next = NULL;
		Species_head->prev = NULL;
		Species_head->Population_head = NULL;
		Species_head->Population_tail = NULL;

		Species_tail = Species_head;


	}
   
 print_populations();


	return 1;
}

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
 int insert_population(int gid, int sid, int cid){
    struct Species * temp_species = Species_head;
    struct Population * new_popul = (struct Population*)malloc(sizeof(struct Population));
    struct Population * temp_popul;
    int species_found = 0, popul_found=0;
    
    while (temp_species!=NULL) {

        if (temp_species->sid == sid) {
            species_found = 1;
            break;
        }

        temp_species=temp_species->next;
    }

    if (species_found == 0) {
        printf("Error couldn't find sid\n");
        return 0;
    }
    
    if (temp_species->Population_head==NULL) {

        temp_species->Population_head = (struct Population*)malloc(sizeof(struct Population));
        temp_species->Population_head->cid = cid;
        temp_species->Population_head->gid = gid;
		temp_species->Population_head->sid = sid;
        temp_species->Population_head->next = NULL;
        temp_species->Population_head->next_species = NULL;
        temp_species->Population_tail = temp_species->Population_head;
    }
    else {

        /*if insert at head*/
        if (temp_species->Population_head->gid > gid) {

            new_popul->gid = gid;
            new_popul->cid = cid;
            new_popul->sid = sid;

            new_popul->next_species = NULL;

            new_popul->next = temp_species->Population_head;

            temp_species->Population_head = new_popul;
        }
        else {

            temp_popul = temp_species->Population_head;

            while (temp_popul->next != NULL) {
                if (temp_popul->next->gid > gid) {
                    popul_found = 1;
                    break;
                }
                temp_popul = temp_popul->next;
            }

            new_popul->cid = cid;
            new_popul->gid = gid;
            new_popul->sid = sid;

            new_popul->next_species = NULL;

            /*if insert at tail*/
            if (popul_found==0) {
                temp_popul->next = new_popul;
                new_popul->next = NULL;
                temp_species->Population_tail = new_popul;
            }
            /*if insert at somewhere in the middle*/
            else {
                new_popul->next = temp_popul->next;
                temp_popul->next = new_popul;
            }

        }
    }
	print_populations();
    return 1;
 }

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3){
	struct Species *temp_species1;
	struct Species *temp_species2;
	struct Species *new_species;
	struct Population *p;
	struct Population *q;
	struct Population * temp_population;
	struct Population * merging;


    insert_species (sid3);
	printf("Insert sid3 ended here\n");

	temp_species1=Species_head;
	temp_species2=Species_head;
	new_species=Species_head;
	while(new_species!=NULL){
		if (sid3==new_species->sid){
			break;
		}
		new_species=new_species->next;
	}

	while(temp_species1!=NULL){
		if(sid1==temp_species1->sid) break;
		temp_species1=temp_species1->next;
	}	
		while(temp_species2!=NULL){
		if(sid2==temp_species2->sid) break;
		temp_species2=temp_species2->next;
	}
	if(temp_species1==NULL || temp_species2==NULL){
		printf("SID NOT FOUND \n");
		return 0 ;
	}else{
		p=temp_species1->Population_head;
		q=temp_species2->Population_head;
		if(p==NULL){
			new_species->Population_head=q;
			q->sid=new_species->sid;
		}else if(q==NULL){
			new_species->Population_head=p;
			p->sid=new_species->sid;
		}else{
			if(p->gid>q->gid){
				merging=q;
				q=merging->next;
			}else{
				merging=p;
				p=merging->next;
			}
			merging->sid=new_species->sid;
			new_species->Population_head=merging;
			//temp_population=new_species->Population_head;
			while(p!=NULL && q!= NULL){
				if(p->gid>q->gid){
					merging->next=q;
					merging=q;
					q=merging->next;
					//temp_population=temp_population->next;
					//q=q->next;

				}else{
					//temp_population->next=p;
					merging->next=p;
					merging=p;
					p=merging->next;
					//temp_population=temp_population->next;
					//p=p->next;
				}
				merging->sid=new_species->sid;
			}
			if(p==NULL){
				merging->next=q;
				merging->next->sid=new_species->sid;
			}
			else{
				merging->next=p;
				merging->next->sid=new_species->sid;
			}
		}

	}
	//print_populations();
	delete_species(sid1);
	printf("Delete sid1 ended here\n");
	delete_species(sid2);
	printf("Delete sid2 ended here\n");

	
	return 1;
}

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute(){
	struct Species * temp_species;
	struct Population* temp_population;
	struct ContinentPopulation* temp_cont;
	struct ContinentPopulation* temp_cont1;
	int i;


	temp_species= Species_head; 


	while(temp_species!=NULL){
		temp_population=temp_species->Population_head;
		while(temp_population!=NULL){
			temp_cont=malloc(sizeof(struct ContinentPopulation));
			temp_cont->gid= temp_population->gid;
			
			temp_cont->next=continents[temp_population->cid]->populationList;
            continents[temp_population->cid]->populationList=temp_cont;
			temp_population=temp_population->next;

		}
		temp_species=temp_species->next;

	}
for(i=0;i<5;i++){
	temp_cont1=continents[i]->populationList;
	printf("Continent %d :",i );

	while(temp_cont1->gid != -1){
		printf("%d,",temp_cont1->gid);
		temp_cont1=temp_cont1->next;
	}
    printf("\n");
}


	return 1;
}

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid){
	struct Species * temp_species;
	struct Population* temp_population;
	struct Population * prev_population;
	int c;
	struct ContinentPopulation* temp_c;
	struct ContinentPopulation* prev_c;
	struct Population* temp_population1;
	struct ContinentPopulation* temp_c1;

	temp_species= Species_head;


	while(temp_species!=NULL){
		if(temp_species->sid==sid){
			break;
		}
		temp_species=temp_species->next;

	}
	if(temp_species!=NULL){
		prev_population=NULL;
		temp_population=temp_species->Population_head;
		if(temp_population!= NULL && temp_population->gid==gid){
			temp_species->Population_head=temp_population->next;
			c=temp_population->cid;
			free(temp_population);
		}else{
			while(temp_population!=NULL && temp_population->gid!=gid ){
			prev_population=temp_population;
			temp_population=temp_population->next;
		}
		if(prev_population!=NULL){
			c=temp_population->cid;
			prev_population->next=temp_population->next;
			free(temp_population);


		}
		}
		
		temp_c=continents[c]->populationList;
		prev_c=NULL;
		if(temp_c->gid!=-1 && temp_c->gid==gid){
			continents[c]->populationList=temp_c->next;
			free(temp_c);
		}else{
			
		while(temp_c->gid!=-1 && temp_c->gid!=gid){
			prev_c=temp_c;
			temp_c=temp_c->next;
		}
		if(prev_c!=NULL){
			prev_c->next=temp_c->next;
			free(temp_c);
		}

		}



	}

	printf("SPECIES\n"); 
	printf("%d\n", temp_species->sid);
	temp_population1=temp_species->Population_head;
	while(temp_population1!=NULL){
		printf("\t%d  ",temp_population1->gid);
		temp_population1=temp_population1->next;

	}
	printf("\nCONTINENTS\n");
	printf("Continent %d :",c);
	temp_c1=continents[c]->populationList;
	while(temp_c1->gid!=-1){
		printf("%d\t", temp_c1->gid);
		temp_c1=temp_c1->next;
	}
	printf("\n");




	return 1;
}

/**
 * @brief delete species with ID <sid> and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
 int delete_species(int sid){
	 struct Species * temp_species;
	 struct Species * prev_species;
	 struct Population* temp_population;
	 struct Population* prev_population;
	 struct ContinentPopulation* temp_cp;
	 struct ContinentPopulation* prev_cp;

	 temp_species=Species_tail;
	 prev_species=NULL;
	 while(temp_species!=NULL && temp_species->sid!=sid){
		 prev_species=temp_species;
		 temp_species=temp_species->prev;

	 }
	
	 if(temp_species==NULL){
		  printf("Specie doesnt exist \n");
		 return 0;
	 }
	  temp_population=temp_species->Population_head;
	 if(temp_population==NULL){
		 printf("population list is empty\n");
		 return 0;
	 }
	 while(temp_population!=NULL){
		 temp_cp=continents[temp_population->cid]->populationList;
		 prev_cp=NULL;
		 if(temp_cp->gid!=-1 && temp_cp->gid==temp_population->gid){
			 continents[temp_population->cid]->populationList=temp_cp->next;
			 free(temp_cp);
		 }
		 else{
			 while(temp_cp!=NULL && temp_cp->gid!=-1 && temp_cp->gid!=temp_population->gid){
			 prev_cp=temp_cp;
			 temp_cp=temp_cp->next;
			 }
		 if(prev_cp !=NULL && temp_cp!=NULL){
			 prev_cp->next=temp_cp->next;
			 free(temp_cp);

		 }

		 
		}
		temp_species->Population_head=temp_population->next;
		temp_population=temp_population->next;
		//free(temp_population);
		//temp_population=temp_species->Population_head;
		 
	 }
	 
	 if(temp_species->prev==NULL){
		 prev_species->prev=temp_species->prev;
		 Species_head=prev_species;
	 }else if(temp_species->next==NULL){
		 Species_tail=temp_species->prev;
		 temp_species->prev->next=NULL;
	 }else{
		 prev_species->prev=temp_species->prev;
		 temp_species->prev->next=prev_species; 
	 }
	 
	 free(temp_species);


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
	struct Species* temp_species;
	struct Species* temp;
	struct Population * temp_population;
	struct Population* temp_population2;
	struct Population* temp_population3;



	temp_species=Species_head; 

	while(temp_species->next!=NULL){
		if(hs_L==NULL){
			hs_L=temp_species->Population_head;
			hs_L->next_species=temp_species->next->Population_head;
		}else{
			if(temp_species->Population_head==NULL){
				temp_species=temp_species->next;
			}else if(temp_species->next->Population_head==NULL && temp_species->next->next!=NULL){
				temp=temp_species->next;
				while(temp->next!=NULL){
					if(temp->Population_head!=NULL){
						break;
					}
					temp=temp->next;
				}
				if(temp->next!=NULL){
					temp_species->Population_head->next_species=temp->Population_head;
				}
				temp_species=temp;
			}else{
				temp_species->Population_head->next_species=temp_species->next->Population_head;
				temp_species=temp_species->next;
			}
		}
	}

	
	

	
    print_homo_sapiens();

	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics(){
	struct Population* temp_population;
	int counter=0;

	temp_population=hs_L;
	while(temp_population!=NULL){
		printf("HERE %d\n",temp_population->sid);
		counter++;
		temp_population=temp_population->next_species;
	}

 printf("Homo Sapiens species: %d\n", counter);


	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid){
	struct Population* temp_population;
	int counter=0;

	temp_population=hs_L;
	while(temp_population!=NULL){
		if(temp_population->sid==sid){
			break;
		}
		temp_population=temp_population->next_species;


	}
	if(temp_population!=NULL){
		while(temp_population!=NULL){
			counter++;
			temp_population=temp_population->next;
		}

	}else{
		DPRINT("SID NOT FOUND\n");
		return 0;
	}

  DPRINT("Homo Sapiens populations: %d\n", counter);



	return 1;
}

/**
 * @brief Print species' list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species(){

    struct Species* temp_species = Species_head;

    while (temp_species!=NULL) {
        printf("<%d>\n", temp_species->sid);

        temp_species = temp_species->next;
    }

	return 1;
}

/**
 * @brief Print species' list with population lists
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations(){
	struct Species * c;
	struct Population *cp;
      c=Species_head;
	while(c!=NULL){
		DPRINT ("<%d>\n",c-> sid);
		cp= c->Population_head;
		while(cp!=NULL){
			DPRINT("%d,%d\t", cp->gid, cp->cid);
			cp=cp->next;
		}
		DPRINT("\n");
		c=c->next;

	}

	return 1;
}

/**
 * @brief Print continents array with each continent's population list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents(){
	int i;
	struct ContinentPopulation* temp_cont1;
	
	
	for(i=0;i<5;i++){
	temp_cont1=continents[i]->populationList;
	printf("Continent %d :",i );

	while(temp_cont1!=NULL && temp_cont1->gid != -1){
		printf("%d,",temp_cont1->gid);
		temp_cont1=temp_cont1->next;
	}
    printf("\n");
}

    

	return 1;
}

/**
 * @brief Print homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens(){
	struct Population * temp_population2;
	struct Population * temp_population3;
	
	
	temp_population2=hs_L;
	printf("Homo Sapiens:");

    while(temp_population2!=NULL){
		
		temp_population3=temp_population2;
		printf("[");
		while(temp_population3!=NULL){
			printf("%d %d,",temp_population3->gid,temp_population3->sid);
			temp_population3=temp_population3->next;
		}
		printf("]\t");
		temp_population2=temp_population2->next_species;
	}
	printf("\n");



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
				 * F <sid> */
			case 'F':
				{
					int sid;

					sscanf(buff, "%c %d", &event, &sid);
					DPRINT("%c %d\n", event, sid);

					if (delete_species(sid)) {
						DPRINT("%c %d succeeded\n", event, sid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, sid);
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

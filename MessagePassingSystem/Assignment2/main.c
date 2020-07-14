#include "library.h"


int main(int argc, char *argv[]){

	int rank, world_size, i;
	int index_server;
    char* parameters;
    FILE *fp;
    char buff[100];
	int temp_array[4];
    int servers;
	int left_neighbor;
	int right_neighbor;
	int status_code;
	
	int leader_links_index;
	enum types type;

	type=-1;
	
	MPI_Status status; 

    parameters=argv[argc-1];
    servers=atoi(argv[argc-2]);
	/** MPI Initialisation **/
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int leader_server_array[servers];
	int leader_links[servers/2 +1];

	for (i=0; i<servers; i++){
		leader_server_array[i]=0;
	}

	struct hash_table *server_leader;

	int active_requests;

	active_requests=0;
	index_server=0;
	leader_links_index=0;

   
	if(rank == 0){
		// Coordinator

		char buff[20];
		int server_rank;
		int left_rank;
		int right_rank;
		int temp_var;
		int temp_var2;
		int file_id;
		int client_rank;
		int i;
		int leader_id;
		int clients[100];
		int clients_index=0;
		srand ( time(NULL) );

		for(i=0; i<100; i++){
			clients[i]=-1;
		}
		type=COORDINATOR;

     	fp = fopen(parameters, "r");
		printf("[rank: %d] Coordinator started\n", rank);
		server_leader=malloc(sizeof(struct hash_table));
	
		while(fscanf(fp,"%s",buff)!=EOF){
			if(!strcmp(buff,"SERVER")){
				fscanf(fp,"%d",&server_rank);
				fscanf(fp,"%d",&left_rank);
				fscanf(fp,"%d",&right_rank);

				//left to server
				MPI_Send(&left_rank,1,MPI_INT,server_rank,LEFT_NEIGHBOR,MPI_COMM_WORLD);
				MPI_Recv(&temp_var,1,MPI_INT,server_rank,ACK,MPI_COMM_WORLD,0);

				//right to server
				MPI_Send(&right_rank,1,MPI_INT,server_rank,RIGHT_NEIGHBOR,MPI_COMM_WORLD);
				MPI_Recv(&temp_var,1,MPI_INT,server_rank,ACK,MPI_COMM_WORLD,0);

				// server to left
				/*MPI_Send(&server_rank,1,MPI_INT,left_rank,RIGHT_NEIGHBOR,MPI_COMM_WORLD);
				MPI_Recv(&temp_var,1,MPI_INT,left_rank,ACK,MPI_COMM_WORLD,0);
				
				//server to right
				MPI_Send(&server_rank,1,MPI_INT,right_rank,LEFT_NEIGHBOR,MPI_COMM_WORLD);
				MPI_Recv(&temp_var,1,MPI_INT,right_rank,ACK,MPI_COMM_WORLD,0);
*/
				printf("[rank: %d] SERVER started\n", server_rank);
			}else if(!strcmp(buff,"START_LEADER_ELECTION")){
				for(i=1; i<world_size;i++){
					MPI_Send(&temp_var,1,MPI_INT,i,START_LEADER_ELECTION,MPI_COMM_WORLD);
				}
				MPI_Recv(&temp_var,1,MPI_INT,MPI_ANY_SOURCE,LEADER_ELECTION_DONE,MPI_COMM_WORLD,0);
				leader_id=temp_var;
				
				for(i=1; i<world_size; i++){
					MPI_Send(&temp_var,1,MPI_INT,i,CLIENT,MPI_COMM_WORLD);
					MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);
					if(temp_var2>0){
						printf("[rank: %d] CLIENT started\n", temp_var2);
						int i;
						for(i=0; i<100; i++){
							if(clients[i]==-1){
								clients[i]=temp_var2;
								break;
							}
						}
						MPI_Send(&temp_var2,1,MPI_INT,temp_var,CLIENT_ACK,MPI_COMM_WORLD);
						MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);
					}
				}
			}else if(!strcmp(buff,"UPLOAD")){

				fscanf(fp,"%d",&client_rank);
				fscanf(fp,"%d",&file_id);
				
				MPI_Send(&file_id,1,MPI_INT,client_rank,UPLOAD,MPI_COMM_WORLD);
				MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);
			}else if(!strcmp(buff,"RETRIEVE")){
				fscanf(fp,"%d",&client_rank);
				fscanf(fp,"%d",&file_id);
				MPI_Send(&file_id,1,MPI_INT,client_rank,RETRIEVE,MPI_COMM_WORLD);
				MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);

			}else if(!strcmp(buff,"UPDATE")){
				fscanf(fp,"%d",&client_rank);
				fscanf(fp,"%d",&file_id);
				MPI_Send(&file_id,1,MPI_INT,client_rank,UPDATE,MPI_COMM_WORLD);
				MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);

			}else if(!strcmp(buff,"REQUEST_SHUTDOWN")){
				for(i=0; i<100;i++){
					if(clients[i]==-1){
						break;
					}
					MPI_Send(&temp_var,1,MPI_INT,clients[i],REQUEST_SHUTDOWN,MPI_COMM_WORLD);
					MPI_Recv(&temp_var2,1,MPI_INT,MPI_ANY_SOURCE,SHUTDOWN_OK,MPI_COMM_WORLD,0);
					if(temp_var2==1){
						clients_index++;
					}
				}
				
				if(clients_index==world_size-servers-1){
					MPI_Send(&temp_var,1,MPI_INT,leader_id,REQUEST_SHUTDOWN,MPI_COMM_WORLD);
					MPI_Recv(&temp_var2,1,MPI_INT,leader_id,SHUTDOWN_OK,MPI_COMM_WORLD,0);
					break;
				}
			}else if(!strcmp(buff,"SHUTDOWN")){
				for(i=1; i<world_size; i++){
					MPI_Send(&temp_var,1,MPI_INT,i,SHUTDOWN,MPI_COMM_WORLD);
					MPI_Recv(&temp_var2,1,MPI_INT,i,ACK,MPI_COMM_WORLD,0);
				}
				
			}
		}
		
		fclose(fp);

		for(i=0; i<100;i++){
			if(clients[i]==-1){
				break;
			}
			MPI_Send(&temp_var,1,MPI_INT,clients[i],REQUEST_SHUTDOWN,MPI_COMM_WORLD);
			MPI_Recv(&temp_var2,1,MPI_INT,clients[i],SHUTDOWN_OK,MPI_COMM_WORLD,0);
			if(temp_var2==1){
				clients_index++;
			}
		}

		if(clients_index==world_size-servers-1){
			MPI_Send(&temp_var,1,MPI_INT,leader_id,REQUEST_SHUTDOWN,MPI_COMM_WORLD);
			MPI_Recv(&temp_var2,1,MPI_INT,leader_id,SHUTDOWN_OK,MPI_COMM_WORLD,0);
		}


	}else{
		
			int leader_id;
			int flag=0;
			int i;
			int connected_to;
			int server_file_array[100][2];
			int server_clients[100];
			int counter=0;
			int flagReq=0;
			
			leader_id=rank;
			connected_to=-1;

			for(i=0; i<servers/2 +1; i++){
				leader_links[i]=-1;
			}

			for(i=0; i<100; i++){
				server_file_array[i][0]=-1;
				server_file_array[i][1]=0;
			}


			int client_file_array[100][2];

			for(i=0; i<100; i++){
				client_file_array[i][0]=-1;
				client_file_array[i][1]=0;
			}


			server_leader=malloc(sizeof(struct hash_table));
			server_leader->numberOfRecords=0;
			for(i=0; i<SIZE; i++){
				server_leader->table[i]=NULL;
			}
			for(i=0; i<100; i++){
				server_clients[i]=-1;
			}

			while(1){
				MPI_Recv(&temp_array,4,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
				
				if(status.MPI_TAG==LEFT_NEIGHBOR){
				
					left_neighbor=temp_array[0];
					type=SERVER;
				
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==RIGHT_NEIGHBOR){
					
					right_neighbor=temp_array[0];
					type=SERVER;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				
				}else if(status.MPI_TAG==START_LEADER_ELECTION && type==SERVER){
					if(flag==0){
						MPI_Send(&leader_id,1,MPI_INT,left_neighbor,CANDIDATE_ID,MPI_COMM_WORLD);
						flag=1;
					}
				}else if(status.MPI_TAG==CANDIDATE_ID && type==SERVER){
				//	if(flag==0){
					//	MPI_Send(&leader_id,1,MPI_INT,left_neighbor,CANDIDATE_ID,MPI_COMM_WORLD);
					//	flag=1;
				//	}else{
						if(leader_id<temp_array[0]){
							leader_id=temp_array[0];
						}
						
						leader_server_array[index_server++]=temp_array[0];
						//printf("index_server %d rank %d\n",index_server,rank);
						if(temp_array[0]!=rank){
							MPI_Send(&temp_array[0],1,MPI_INT,left_neighbor,CANDIDATE_ID,MPI_COMM_WORLD);
						}else if(rank==temp_array[0] && index_server==servers && leader_id==rank){
							int connect_index=servers-3;
							int number_of_edges=connect_index/4;

							while(number_of_edges>=1){
								int index;
								srand (clock());
								index=rand() % (servers-3)+ 1;
								for(i=0; i<servers/2 +1; i++){
									while(leader_links[i]==leader_server_array[index]){
										index=rand() % (servers-3)+ 1;
									}
								}
								MPI_Send(&leader_id,1,MPI_INT,leader_server_array[index],CONNECT,MPI_COMM_WORLD);
								MPI_Recv(&temp_array,1,MPI_INT,MPI_ANY_SOURCE,ACK,MPI_COMM_WORLD,0);
								if(temp_array[0]>0){	
									printf("%d CONNECTED TO %d\n",temp_array[0],leader_id);
									leader_links[leader_links_index++]=temp_array[0];
									number_of_edges--;
								}
							}
							MPI_Send(&rank,1,MPI_INT,0,LEADER_ELECTION_DONE,MPI_COMM_WORLD);
						}

					//}



				}else if(status.MPI_TAG==CONNECT ){
					if(type==SERVER){
						connected_to=temp_array[0];
						MPI_Send(&rank,1,MPI_INT,temp_array[0],ACK,MPI_COMM_WORLD);
					}else{
						connected_to=-1;
						MPI_Send(&rank,1,MPI_INT,temp_array[0],ACK,MPI_COMM_WORLD);
					}
				}else if(status.MPI_TAG==CLIENT_ACK){
					for(i=0; i<100; i++){
							if(temp_array[0]==server_clients[i]){
								break;
							}else if(server_clients[i]==-1){
								
								server_clients[i]=temp_array[0];
								break;
							}
						}
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);

				}else if(status.MPI_TAG==UPLOAD && type==SERVER){
					int i,j;
					int flag=0;
					int index;
					int randomNums[100];
					if(rank==leader_id && temp_array[2]!=1){
						
						int index=hashFunction(temp_array[0]);

						if(server_leader->table[index]!=NULL){
							MPI_Send(&temp_array,1,MPI_INT,temp_array[1],UPLOAD_FAILED,MPI_COMM_WORLD);
						}else{
							int count=((servers-1)/2) +1;
							server_leader=insertHashTable(temp_array[0],server_leader,temp_array[1],(servers-1)/2 + 1);
							server_leader->numberOfRecords++;
							struct record* node=searchHashTable(temp_array[0],server_leader);
							struct queue_node* qnode=malloc(sizeof(struct queue_node));
    						qnode->client_id=temp_array[1];
    						qnode->count =(servers-1)/2 + 1;
							qnode->type=UPLOAD;
							qnode->version=1;

    						insertQueue(node,qnode);
							

							for(i=0; i<100; i++){
								randomNums[i]=-1;
							}
							index=0;
							
							while(count>0){
								int r=rand() % (leader_id-1) + 1 ;

								for(i=0; i<100; i++){
									while(r==randomNums[i] || server_clients[i]==r){
 										r=rand() % (leader_id-1) + 1 ;
										i=0;
									}
								}
								randomNums[index++]=r;						
								for(i=0; i<servers/2 +1; i++){
									if(leader_links[i]==r){
										temp_array[1]=r;
										MPI_Send(&temp_array,2,MPI_INT,r,UPLOAD,MPI_COMM_WORLD);
										flag=1;
										break;
									}
								}
								if(flag==0){
									int temp;

									for(i=0; i<servers; i++){
										if(leader_server_array[i]==r){
											flag=1;
											break;
										}
									}
									if(flag==1){
										j=0;
										for(i=0; i<servers; i++){
											while(j<servers/2 +1){
												if(leader_links[j]==leader_server_array[i]){
													temp_array[1]=r;
													temp_array[2]=1;
													MPI_Send(&temp_array,3,MPI_INT,leader_server_array[i],UPLOAD,MPI_COMM_WORLD);
													flag=0;
													break;
												}

												j++;
											}	
											if(flag==0){
												break;
											}
											j=0;
										}
									}
								}
								flag=0;
								count--;
							}
							for(i=0; i<100; i++){
								randomNums[i]=-1;
							}
							index=0;
						}
					}else{
						
						if(temp_array[1]!=rank){
							MPI_Send(&temp_array,3,MPI_INT,left_neighbor,UPLOAD,MPI_COMM_WORLD);
						}else{
								for(i=0; i<100; i++){
									if(temp_array[0]==server_file_array[i][0]){
									server_file_array[i][1]++;
									break;
								}else if(server_file_array[i][0]==-1){
									
									server_file_array[i][0]=temp_array[0];
									server_file_array[i][1]++;
									break;
								}
								
							}

							
							if(connected_to==leader_id){
								temp_array[1]=rank;
								MPI_Send(&temp_array,2,MPI_INT,connected_to,UPLOAD_ACK,MPI_COMM_WORLD);
							}else{
								MPI_Send(&temp_array,2,MPI_INT,left_neighbor,UPLOAD_ACK,MPI_COMM_WORLD);
							}
						}
					}


				}else if(status.MPI_TAG==UPLOAD_ACK && type==SERVER){
					if(rank!=leader_id){
						if(connected_to!=leader_id){
							MPI_Send(&temp_array,2,MPI_INT,left_neighbor,UPLOAD_ACK,MPI_COMM_WORLD);
						}else{
							MPI_Send(&temp_array,2,MPI_INT,connected_to,UPLOAD_ACK,MPI_COMM_WORLD);
						}
					}else{
						//MPI_Recv(&temp_array,2,MPI_INT,MPI_ANY_SOURCE,UPLOAD_ACK,MPI_COMM_WORLD,0);
						struct record* node=searchHashTable(temp_array[0],server_leader);
						node->front->count--;

						if(node->front->count==0){
							MPI_Send(&temp_array,1,MPI_INT,node->front->client_id,UPLOAD_OK,MPI_COMM_WORLD);
							//printQueue(node);
							dequeue(node);
							
						}
					}
					
				}else if(status.MPI_TAG==RETRIEVE && type==SERVER){
					if(rank==leader_id && temp_array[2]!=1){
						int index;
						int randomNums[100];
						int j=0;
						struct record* node=searchHashTable(temp_array[0],server_leader);

						if(node==NULL){
							MPI_Send(&temp_array,1,MPI_INT,temp_array[1],RETRIEVE_FAILED,MPI_COMM_WORLD);
						}else{
							struct queue_node* qnode=malloc(sizeof(struct queue_node));
							qnode->client_id=temp_array[1];
							qnode->count=(servers-1)/2 +1;
							qnode->type=RETRIEVE;
							//isws version
							insertQueue(node,qnode);
							//printQueue(node);
							if(qnode==node->front){
								int count=((servers-1)/2) +1;
							
								for(i=0; i<100; i++){
									randomNums[i]=-1;
								}
								index=0;
								flag=0;
								while(count>0){
									int r=rand() % (leader_id-1) + 1 ;

									for(i=0; i<100; i++){
										while(r==randomNums[i] || server_clients[i]==r){
											r=rand() % (leader_id-1) + 1 ;
											i=0;
										}
									}
									randomNums[index++]=r;							
									for(i=0; i<servers/2 +1; i++){
										if(leader_links[i]==r){
											temp_array[1]=r;
											MPI_Send(&temp_array,2,MPI_INT,r,RETRIEVE,MPI_COMM_WORLD);
											flag=1;
											break;
										}
									}
									if(flag==0){
										int temp;

										for(i=0; i<servers; i++){
											if(leader_server_array[i]==r){
												flag=1;
												break;
											}
										}
										if(flag==1){
											j=0;
											for(i=0; i<servers; i++){
												while(j<servers/2 +1){
													if(leader_links[j]==leader_server_array[i]){
														temp_array[1]=r;
														temp_array[2]=1;
														MPI_Send(&temp_array,3,MPI_INT,leader_server_array[i],RETRIEVE,MPI_COMM_WORLD);
														flag=0;
														break;
													}

													j++;
												}	
												if(flag==0){
													break;
												}
												j=0;
											}
										}
									}
									flag=0;
									count--;
								}
								for(i=0; i<100; i++){
									randomNums[i]=-1;
								}
								index=0;
							}
						}
					}else if(rank!=temp_array[1]){
						MPI_Send(&temp_array,3,MPI_INT,left_neighbor,RETRIEVE,MPI_COMM_WORLD);
					}else{
						int flag=0;
						for(i=0; i<100; i++){
							if(temp_array[0]==server_file_array[i][0]){
								if(connected_to==leader_id){
									temp_array[2]=server_file_array[i][1];
									MPI_Send(&temp_array,3,MPI_INT,leader_id,RETRIEVE_ACK,MPI_COMM_WORLD);
								}else{
									temp_array[2]=server_file_array[i][1];
									temp_array[1]=leader_id;
									MPI_Send(&temp_array,3,MPI_INT,left_neighbor,RETRIEVE_ACK,MPI_COMM_WORLD);
								}
								flag=1;
								break;
							}
						}
						if(flag==0){

							if(connected_to==leader_id){
									temp_array[2]=0;
									MPI_Send(&temp_array,3,MPI_INT,leader_id,RETRIEVE_ACK,MPI_COMM_WORLD);
								}else{
									temp_array[2]=0;
									temp_array[1]=leader_id;
									MPI_Send(&temp_array,3,MPI_INT,left_neighbor,RETRIEVE_ACK,MPI_COMM_WORLD);
								}
						}
					}
					
				}else if(status.MPI_TAG==RETRIEVE_ACK && type==SERVER){
					int max;
					if(rank==leader_id){
						
						struct record* node=searchHashTable(temp_array[0],server_leader);
						
						node->front->count--;

						if(node->front->version<temp_array[2]){
							node->front->version=temp_array[2];
							temp_array[2]=node->front->version;
						}
						if(node->front->count==0){
							temp_array[2]=node->front->version;
							MPI_Send(&temp_array,3,MPI_INT,node->front->client_id,RETRIEVE_OK,MPI_COMM_WORLD);
							//printQueue(node);
							dequeue(node);
						}

					}else{
						if(connected_to==leader_id){
							MPI_Send(&temp_array,3,MPI_INT,leader_id,RETRIEVE_ACK,MPI_COMM_WORLD);
						}else{
							MPI_Send(&temp_array,3,MPI_INT,left_neighbor,RETRIEVE_ACK,MPI_COMM_WORLD);
						}
					}

				}else if(status.MPI_TAG==UPDATE && type==SERVER){
					if(rank==leader_id && temp_array[2]!=1){
						int index;
						int randomNums[100];
						int j=0;
						int temp_array2[4];
						struct record* node=searchHashTable(temp_array[0],server_leader);

						if(node==NULL){
							MPI_Send(&temp_array,1,MPI_INT,temp_array[1],UPDATE_FAILED,MPI_COMM_WORLD);
						}else{
							for(i=0; i<4; i++){
								temp_array2[i]=temp_array[i];
							}
							struct queue_node* qnode=malloc(sizeof(struct queue_node));
							qnode->client_id=temp_array[1];
							qnode->count=(servers-1)/2 +1;
							qnode->type=UPDATE;
							qnode->version=temp_array[3];
							insertQueue(node,qnode);

							if(node->front==qnode){
								temp_array[1]=temp_array[3];
								temp_array[2]=1;
								MPI_Send(&temp_array,3,MPI_INT,left_neighbor,VERSION_CHECK,MPI_COMM_WORLD);
							}
							
						}
					}else if(rank!=temp_array[3]){
						temp_array[2]=1;
						MPI_Send(&temp_array,4,MPI_INT,left_neighbor,UPDATE,MPI_COMM_WORLD);
					}else{
						for(i=0; i<100; i++){
							if(temp_array[0]==server_file_array[i][0]){
								if( temp_array[1]>=server_file_array[i][1]){
									temp_array[1]++;
									server_file_array[i][1]=temp_array[1];
								}
								break;
							}
						}
						if(connected_to==leader_id){
							MPI_Send(&temp_array,3,MPI_INT,leader_id,UPDATE_ACK,MPI_COMM_WORLD);
						}else{
							MPI_Send(&temp_array,3,MPI_INT,left_neighbor,UPDATE_ACK,MPI_COMM_WORLD);
						}
					}

				}else if(status.MPI_TAG==UPDATE_ACK && type==SERVER){
					if(rank==leader_id){
						
						struct record* node=searchHashTable(temp_array[0],server_leader);
						
						node->front->count--;
						if(node->front->count==0){
							MPI_Send(&temp_array,3,MPI_INT,node->front->client_id,UPDATE_OK,MPI_COMM_WORLD);
							//printQueue(node);
							dequeue(node);
						}


					}else{
						if(connected_to==leader_id){
							MPI_Send(&temp_array,3,MPI_INT,leader_id,UPDATE_ACK,MPI_COMM_WORLD);
						}else{
							MPI_Send(&temp_array,3,MPI_INT,left_neighbor,UPDATE_ACK,MPI_COMM_WORLD);
						}
					}

				}else if(status.MPI_TAG==VERSION_CHECK && type==SERVER){
					if(temp_array[2]==1){

						if(rank==leader_id){
							int count=((servers-1)/2) +1;
							int index;
							int randomNums[100];
							int j=0;

							for(i=0; i<100; i++){
								randomNums[i]=-1;
							}
							index=0;
							
							while(count>0){
								int r=rand() % (leader_id-1) + 1 ;

								for(i=0; i<100; i++){
									while(r==randomNums[i] || server_clients[i]==r){
 										r=rand() % (leader_id-1) + 1 ;
										i=0;
									}
								}
								randomNums[index++]=r;
								flag=0;								
								for(i=0; i<servers/2 +1; i++){
									if(leader_links[i]==r){
										temp_array[3]=r;
										MPI_Send(&temp_array,4,MPI_INT,r,UPDATE,MPI_COMM_WORLD);
										flag=1;
										break;
									}
								}
								if(flag==0){
									int temp;

									for(i=0; i<servers; i++){
										if(leader_server_array[i]==r){
											
											flag=1;
											break;
										}
										
									}
									if(flag==1){
										j=0;
										for(i=0; i<servers; i++){
											while(j<servers/2 +1){
												if(leader_links[j]==leader_server_array[i]){
													temp_array[2]=1;
													temp_array[3]=r;
													MPI_Send(&temp_array,4,MPI_INT,leader_server_array[i],UPDATE,MPI_COMM_WORLD);
													flag=0;
													break;
												}

												j++;
											}	
											if(flag==0){
												break;
											}
											j=0;
										}
									}
								}
								flag=0;
								count--;
							}
							for(i=0; i<100; i++){
								randomNums[i]=-1;
							}
							index=0;

						}else{
							for(i=0; i<100; i++){
								if(temp_array[0]==server_file_array[i][0]){
									temp_array[2]=0;
									if(connected_to==leader_id){
										MPI_Send(&temp_array,3,MPI_INT,leader_id,VERSION_CHECK,MPI_COMM_WORLD);
									}else{
										MPI_Send(&temp_array,3,MPI_INT,left_neighbor,VERSION_CHECK,MPI_COMM_WORLD);
									}
									break;
								}else if(server_file_array[i][0]!=-1 && (temp_array[0]!=server_file_array[i][0] || temp_array[1]>=server_file_array[i][1])){
									MPI_Send(&temp_array,3,MPI_INT,left_neighbor,VERSION_CHECK,MPI_COMM_WORLD);
									break;
								}
							}
						}

						
					}else{
						if(rank==leader_id){
							struct record* node=searchHashTable(temp_array[0],server_leader);

							struct queue_node * temp=node->front;

							MPI_Send(&temp_array[0],1,MPI_INT,temp->client_id,VERSION_OUTDATED,MPI_COMM_WORLD);
							dequeue(node);

						}else{
							if(connected_to==leader_id){
								MPI_Send(&temp_array,3,MPI_INT,leader_id,VERSION_CHECK,MPI_COMM_WORLD);
							}else{
								MPI_Send(&temp_array,3,MPI_INT,left_neighbor,VERSION_CHECK,MPI_COMM_WORLD);
							}
						}
					}
						
				}else if(status.MPI_TAG==REQUEST_SHUTDOWN && type==CLIENT_TYPE){
					int temp=1;
					if(active_requests==0){
						MPI_Send(&temp,1,MPI_INT,0,SHUTDOWN_OK,MPI_COMM_WORLD);
						break;
					}else{
						flagReq=1;
						MPI_Send(&temp,1,MPI_INT,0,SHUTDOWN_OK,MPI_COMM_WORLD);
						break;
					}
					
				}else if(status.MPI_TAG==REQUEST_SHUTDOWN && type==SERVER){
					int flagExit=0;
					if(rank==leader_id){
						counter++;
						
						if(counter<2){
							MPI_Send(&rank,1,MPI_INT,left_neighbor,REQUEST_SHUTDOWN,MPI_COMM_WORLD);
						}else{
							MPI_Send(&rank,1,MPI_INT,0,SHUTDOWN_OK,MPI_COMM_WORLD);
							break;
						}
					}else{
						MPI_Send(&rank,1,MPI_INT,left_neighbor,REQUEST_SHUTDOWN,MPI_COMM_WORLD);
						break;
					}
					
				}else if(status.MPI_TAG==SHUTDOWN){
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
					break;
			
				}else if(status.MPI_TAG==CLIENT ){
					if(type!=SERVER){
						type=CLIENT_TYPE;

						leader_id=temp_array[0];
						MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
					}else{
						int temp_num=-1;
						MPI_Send(&temp_num,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
					}
					

				}else if(status.MPI_TAG==UPLOAD && type==CLIENT_TYPE){
					for(i=0; i<100; i++){
						if(temp_array[0]==client_file_array[i][0]){
							client_file_array[i][1]++;
							break;
						}else if(client_file_array[i][0]==-1){
							client_file_array[i][0]=temp_array[0];
							client_file_array[i][1]++;
							break;
						}
					}
					temp_array[1]=rank;
					temp_array[2]=0;
					active_requests++;
					int success=MPI_Send(&temp_array,3,MPI_INT,leader_id,UPLOAD,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==UPLOAD_FAILED){
					printf("CLIENT %d FAILED TO UPLOAD %d\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==UPLOAD_OK){
					printf("CLIENT %d UPLOADED %d\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==RETRIEVE && type==CLIENT_TYPE){
					temp_array[1]=rank;
					temp_array[2]=0;
					active_requests++;
					MPI_Send(&temp_array,3,MPI_INT,leader_id,RETRIEVE,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==UPDATE && type==CLIENT_TYPE){
					temp_array[1]=rank;
					temp_array[2]=0;
					temp_array[3]=0;

					for(i=0; i<100; i++){
						if(temp_array[0]==client_file_array[i][0]){
							temp_array[3]=client_file_array[i][1];
							break;
						}
					}
					active_requests++;
					MPI_Send(&temp_array,4,MPI_INT,leader_id,UPDATE,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==UPDATE_FAILED && type==CLIENT_TYPE){
					printf("CLIENT %d FAILED TO UPDATE %d\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==UPDATE_OK && type==CLIENT_TYPE){
					for(i=0; i<100; i++){
						if(temp_array[0]==client_file_array[i][0]){
							client_file_array[i][1]++;
							break;
						}
					}
					printf("CLIENT %d UPDATED %d\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==VERSION_OUTDATED && type==CLIENT_TYPE){
					printf("CLIENT %d CANNOT UPDATE UPDATE %d WITHOUT MOST RECENT VERSION\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==RETRIEVE_FAILED){
					printf("CLIENT %d FAILED TO RETRIEVE %d\n",rank,temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}else if(status.MPI_TAG==RETRIEVE_OK){
					printf("CLIENT %d RETRIEVED VERSION %d OF %d\n",rank,temp_array[2],temp_array[0]);
					active_requests--;
					MPI_Send(&rank,1,MPI_INT,0,ACK,MPI_COMM_WORLD);
				}
		}
	
	}
	MPI_Finalize();
	return 0;
}

/******************************************************************************
* 
* Name: 	Zaid Albirawi
* Email: 	zalbiraw@uwo.ca
*
* scheduler.c 
*
******************************************************************************/

#include "scheduler.h"
#include "pthread.h"

#define FCFS 0
#define LIFO 1
#define SJF 2
#define RR 3

job_t shortestJob;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


//Declarations for scheduling functions 
job_t *firstComeFirstServe(d_linked_list_t*);
job_t *lastInFirstOut(d_linked_list_t*);
job_t *shortestFirst(d_linked_list_t*);
job_t *roundRobin(d_linked_list_t*);

job_t *get_next_job(int mode, d_linked_list_t* jobs) {
	job_t *j;

	//Lock critical section so threads don't access the same job
	pthread_mutex_lock(&mutex2);

	//calls appropriate scheduling algorithm
	//based on provided mode
	switch (mode){
		case FCFS:
		j = firstComeFirstServe(jobs);
		break; 

		case LIFO:
		j = lastInFirstOut(jobs);
		break;

		case SJF:
		if (jobs->head != NULL){
			j = shortestFirst(jobs);
		}else{
			j = NULL;
		}
			
		break;

		case RR:
		j = roundRobin(jobs);
		break; 
	}

	//unlock critical section
	pthread_mutex_unlock(&mutex2);
	
	return j;
}

//Method for retunring the top job on the stack
job_t* firstComeFirstServe(d_linked_list_t* jobsList){
	job_t *topJob;
	topJob = dequeue(jobsList);

	return (topJob);
}

//Method for returning last job in the stack 
job_t* lastInFirstOut(d_linked_list_t* jobsList){
	job_t *lastJob;
	lastJob = pop(jobsList);

	return (lastJob);
}

//Method for Shortest Job FIrst 
job_t* shortestFirst(d_linked_list_t* jobsList){
	

	//currently the shortest job is the first one untill we find something shorter
	struct d_node *shortestNode = jobsList->head;
	struct d_node *current = jobsList->head;

	shortestJob = *((job_t*)jobsList->head->value);

	int shortest = ((job_t*)current->value)->required_time;

	//loop through the list to find the shortest element 
	for (int i = 1; i < jobsList->size; i++){
		
		//traverse one further in the linked list
		current = current->next;
		
		//we update the shortest job if we find a shorter job
		if(shortest > ((job_t*)(current->value))->required_time){
			shortestNode = current;
			shortestJob = *(job_t*)current->value;
			shortest = ((job_t*)current->value)->required_time;
		}
	}

	//we have found the shortest job erase it out of the queue and return the value 
	erase(jobsList, shortestNode);

	return &shortestJob;
}

//Method for Round Robin
job_t* roundRobin(d_linked_list_t* jobsList){
	job_t* robinJob;


	return (robinJob);
}
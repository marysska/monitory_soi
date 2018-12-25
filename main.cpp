#include "mymonitor.h"
#include "randmon.h"
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#define N_PRODUCERS 3

using namespace std;

Mymonitor queues[N_CONSUMERS];
Randmon randmon; 
int sleep_time_consumer[N_CONSUMERS]={1, 2,3,4, 5};
int sleep_time_producer[N_PRODUCERS]={2, 2, 2};

void *f_consumer(void *nr){ //od 0 do 4 nr
	int number;
    	int*  data = reinterpret_cast<int*>(nr);
	number=*data;
	while(1){
		queues[number].getItem(number);
		sleep(sleep_time_consumer[number]);
	}

}

void *f_producer(void *nr){ //od 0 do 2 nr
	int number;
    	int*  data = reinterpret_cast<int*>(nr);
	number=*data;
	int num2put;
	num2put=100*number;
	int quenr;
	while(1){
		quenr=randmon.randMonitor();
		queues[quenr].putItem(num2put, number);
		randmon.done(quenr);
		num2put++;
		sleep(sleep_time_producer[number]);

	}

}


int main(int argv, char * argc[]){
	pthread_t consumer[N_CONSUMERS];
	pthread_t producer[N_PRODUCERS];
	int result;
	int i;
	for(i=0; i<N_CONSUMERS; ++i){
		result=pthread_create(&consumer[i], NULL, f_consumer, (void *)i);
		if (result){
			printf("SOMETHING WENT WRONG \n");
			exit(-22);
		}
	}
	for(i=0; i<N_PRODUCERS; ++i){
		result=pthread_create(&producer[i], NULL, f_producer, (void *)i);
		if (result){
			printf("SOMETHING WENT WRONG \n");
			exit(-33);
		}
	}

	return 0;

}

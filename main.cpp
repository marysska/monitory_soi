#include "mymonitor.h"
#include "randmon.h"
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define N_PRODUCERS 3

using namespace std;

Mymonitor queues[N_CONSUMERS];
Randmon randmon; 
int sleep_time_consumer[N_CONSUMERS]={10, 10,10,10, 10};
int sleep_time_producer[N_PRODUCERS]={1, 1, 1};

void *f_consumer(void *nr){ //od 0 do 4 nr
	long number1;
	int number;
	//cout<<"konsument"<<nr<<3<<endl;
    	//int*  data = reinterpret_cast<int*>(nr);
	number1=(long)nr;
	number=(int)number1;
	//number=(int)nr;
	//printf("Konsument %d\n", (int)number);
	while(1){
		queues[number].getItem(number);
		sleep(sleep_time_consumer[number]);
	}

}

void *f_producer(void *nr){ //od 0 do 2 nr
	long number;
	int number1;
	//cout<<"producent "<<nr<<endl;
    	//int*  data = reinterpret_cast<int*>(nr);
	//cout<<"ok"<<endl;
	number1=(long)nr;
	number=(int)number1;
	//number=(int)nr;
	int num2put;
	num2put=100*number;
	int quenr;
	//printf("Producent %d\n", (int)number);
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
	printf("WITAM \n");
	int result;
	int i;
	for(i=0; i<N_CONSUMERS; i++){
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
	for(i=0; i<N_CONSUMERS; ++i){
		result=pthread_join(consumer[i], NULL);
		if (result){
			printf("SOMETHING WENT WRONG \n");
			exit(-22);
		}
	}
	for(i=0; i<N_PRODUCERS; ++i){
		result=pthread_join(producer[i], NULL);
		if (result){
			printf("SOMETHING WENT WRONG \n");
			exit(-33);
		}
	}

	return 0;

}

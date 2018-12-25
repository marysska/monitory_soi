#include "monitor.h"
#include <stdio.h>

#define SIZE 10


class Mymonitor : private Monitor{

	private:
		int head;
		int tail;
		int count;
		int buffer[SIZE];
		Condition full, empty;
	
	public:
		Mymonitor(): head(0), tail(0), count(0) {
			//printf("inicjalizuje mymon \n");
		}
		
		void putItem(int item, int id){
			enter();
			//printf("wkladam \n");
			if (count==SIZE) wait(full);
			printf("Input %d , producer id %d \n", item, id);
			buffer[tail]=item;
			++tail;
			if (tail==SIZE) tail=0;
			++count;
			if (count==1) signal(empty);
			leave();

		}
		void getItem(int id){
			enter();
			//printf("wyciagam \n");
			if (count==0) wait(empty);
			int item;
			item=buffer[head];
			++head;
			if (head==SIZE) head=0;
			--count;
			printf("Output %d, consumer id %d\n", item, id);
			if (count==SIZE-1) signal(full);
			leave();

		}

};

#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymonitor.h"


#define N_CONSUMERS 5
using namespace std;

class Randmon : private Monitor{

	private:
		int ready[N_CONSUMERS];
	
	public:
		Randmon(){
			int i;
			//printf("inicjalizuje randmon \n");
			for(i=0; i<N_CONSUMERS; ++i){
				ready[i]=0;
			}
			srand(time(NULL));
		}
		
		int randMonitor(Mymonitor tablica[], int nr){
			enter();
			//printf("losowanko \n");
			int number;
			int liczba;
			number=-1;
			while(number==-1){
				number=(rand())%5;
				liczba=tablica[number].getCircaCount();
				printf("producent nr %d losuje, jest ok %d w kolejce %d \n",nr, liczba, number);
				if (ready[number]==0 && liczba!=10){
					ready[number]=1;
				}
				else {
					number=-1;
				}				
			}
			leave();
			return number;
		}

		
		void done(int number){
			//enter();
			ready[number]=0;
			//leave();

		}

};

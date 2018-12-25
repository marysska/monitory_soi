#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N_CONSUMERS 5
using namespace std;

class Randmon : private Monitor{

	private:
		int ready[N_CONSUMERS];
	
	public:
		Randmon(){
			int i;
			for(i=0; i<N_CONSUMERS; ++i){
				ready[i]=0;
			}
			srand(time(NULL));
		}
		
		int randMonitor(){
			enter();
			int number;
			number=-1;
			while(number==-1){
				number=(rand())%5;
				if (ready[number]==0){
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
			enter();
			ready[number]=0;
			leave();

		}

};

#include "walls.h"
Wall::Wall(int c1,int c2){
	if(c1 < c2){
		cell1_=c1;
		cell2_=c2;
	}
	else{
		cell1_=c2;
		cell2_=c1;
	}
}

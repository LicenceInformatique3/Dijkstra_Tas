#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "tas.h"


int FilsG(int i) {
	return (2*i+1);
}

int FilsD(int i) {
	return (2*i+2);
}

int Pere(int i) {
	if(i%2 == 0)
		return (i/2)-1;
	return i/2;
}

void entasserVersLeBas(int i, int * tab, int * position, int * distance, int n) {
	int iMax = i;

	if((FilsG(i) < n) && (distance[tab[FilsG(i)]]!= -1 && (distance[tab[FilsG(i)]] < distance[tab[iMax]] || distance[tab[iMax]]==-1)))
		iMax = FilsG(i);

	if((FilsD(i) < n) && (distance[tab[FilsD(i)]]!= -1 && (distance[tab[FilsD(i)]] < distance[tab[iMax]] || distance[tab[iMax]]==-1)))
		iMax = FilsD(i);

	if (iMax != i){
		swap_tab_int(tab,i,iMax);
        swap_tab_int(position,tab[i],tab[iMax]);
		entasserVersLeBas(iMax,tab,position,distance,n);
		entasserVersLeBas(i,tab,position,distance,n);
	}
}


void entasserVersLeHaut(int i, int * tab, int * position, int * distance, int n) {
	int iMax = i;
	if((Pere(i) >= 0) && (distance[tab[iMax]]!=1 && (distance[tab[Pere(i)]] > distance[tab[iMax]] || distance[tab[Pere(i)]]==-1)))
		iMax = Pere(i);

	if (iMax != i){
		swap_tab_int(tab,i,iMax);
        swap_tab_int(position,tab[i],tab[iMax]);
		entasserVersLeHaut(iMax,tab,position,distance,n);
	}
}

void construire_tas(int * tab, int * position, int * distance, int n) {

	int i;
	for(i = (n/2)-1;i >= 0;i--)
		entasserVersLeBas(i,tab,position,distance,n);
}

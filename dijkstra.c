#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "trace.h"
#include "tas.h"
#include "railwayNetwork.h"
#include "dijkstra.h"

#define INFINI -1
#define JOUR 1440
#define HEURE 60

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr){
 	ville * ville1 = &RRInstance->villes[villeDep], * ville2 = &RRInstance->villes[villeArr];
 	int min=-1;
 	heure=heure%JOUR;
 	for (int i = 0; i < RRInstance->nblignes; ++i){
 		int rankvilleDep = ville1->lignesInVille[i];
 		int rankvilleArr = ville2->lignesInVille[i];
		if (rankvilleDep !=-1 && rankvilleArr == rankvilleDep+1){
			ligne * ligne = &RRInstance->lignes[i];
			for (int j = 0; j < ligne->nbhoraires; ++j){
				int tmp1=ligne->horaires[rankvilleArr][j]-ligne->horaires[rankvilleDep][j];
				if (tmp1<0){
					tmp1 +=JOUR;
				}
				if (tmp1<0){
					trace("temps d'atente négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				int tmp2=ligne->horaires[rankvilleDep][j]-heure;
				if (tmp2<0){
					tmp2 +=JOUR;
				}
				if (tmp2<0){
					trace("temps trajet négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				int tmp=tmp1+tmp2;
				if (tmp<0){
					trace("temps total négatif !",__FILE__,__LINE__);
					exit(EXIT_FAILURE);
				}
				if(min==-1){
					min=tmp;
				}
				else if(tmp < min){
					min=tmp;
				}
			}
		}
	}
	if (min < 0){
		trace("min negatif ! ville inaccessible ?",__FILE__,__LINE__);
	}
	return min;
}

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS) {	//Recherche du minimum
	int min = T[0];
	nbS--;
	swap_tab_int(T,0,nbS);
	swap_tab_int(pos,T[0],T[nbS]);
	entasserVersLeBas(pos[T[0]],T,pos,d,nbS);
	return min;
}

void dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet, int * result){
	int tabSize=RRInstance->nbvilles;
	int T[tabSize], d[tabSize], pos[tabSize],precedent[tabSize];
	for(int s = 0; s < tabSize;s++){ 								// on initialise les s (sommets) autres que villeDepart à infini 
		d[s] = INFINI;
		T[s] = s;
		pos[s] = s;
		precedent[s]=-1;
	}
	d[trajet->villeDep] = trajet->horaireDep;
	construire_tas(T,pos,d,tabSize);
	int nbS = RRInstance->nbvilles;
	while(nbS > 0) {
		int min = extraireLeMin_tas(T, d, pos, nbS);						
		nbS--;
		if(d[min] != INFINI) {
			int voisinMin[RRInstance->nblignes];
			int nbvoisin = get_voisin(RRInstance,min,voisinMin);
			for(int i = 0; i < nbvoisin; i++){
				int dureeTrajet  = calcul_dureeTrajet(RRInstance,d[min],min,voisinMin[i]);
				if(d[voisinMin[i]] > (d[min] + dureeTrajet)){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
				else if (d[voisinMin[i]]==-1){
					d[voisinMin[i]] = d[min] + dureeTrajet;
					precedent[voisinMin[i]]=min;
					entasserVersLeHaut(pos[voisinMin[i]],T,pos,d,nbS);
				}
			}
		}
	}
  //Tableau du résultat
	for (int i = 0; i < tabSize; ++i){
		result[i*2]=precedent[i];
		result[i*2+1]=d[i];
	}
}

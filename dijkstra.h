#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct trajet{
	int horaireDep;
	int villeDep;
	int villeArr;
}Trajet;

int calcul_dureeTrajet(RailwayNetwork * RRInstance,int heure,int villeDep, int villeArr);

int extraireLeMin_tas(int * T, int * d,int * pos, int nbS);

void dijkstra_tas(RailwayNetwork * RRInstance,Trajet * trajet, int * result);

#endif

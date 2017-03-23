#ifndef TAS_H
#define TAS_H

int FilsG(int i);

int FilsD(int i);

int Pere(int i);

void entasserVersLeBas(int i, int * tab, int * position, int * distance, int n);

void entasserVersLeHaut(int i, int * tab, int * position, int * distance, int n);

void construire_tas(int * tab, int * position, int * distance, int n);

#endif

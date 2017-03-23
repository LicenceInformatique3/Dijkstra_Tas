#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void swap_tab_int(int * tab, int i, int j){
	int temp;
	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

//
//  load1dVeloSubModel.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"

velo_mod_1d_data *load1dVeloSubModel(char *fileName)
/*
 Purpose:   load a 1D velocity submodel into memory
 
 Input variables:
 *fileName  - pointer to the filename to open and read
 
 Output variables:
 velo1D     - (malloc'd) pointer to the velocity sub-model
 */
{
    velo_mod_1d_data *VELO_MOD_1D_DATA = NULL;
    VELO_MOD_1D_DATA = malloc(sizeof(velo_mod_1d_data));
    FILE *file;
    file = fopen(fileName, "r");
    char tempA[10], tempB[10];
    fscanf(file, "%s %s", tempA, tempB); // header line (discard)
    int i = 0;
    while(!feof(file))
    {
        fscanf(file, "%lf %lf %lf %s %s %lf", &VELO_MOD_1D_DATA->Vp[i], &VELO_MOD_1D_DATA->Vs[i], &VELO_MOD_1D_DATA->Rho[i], tempA, tempB, &VELO_MOD_1D_DATA->Dep[i]);
        i += 1;
    }
    VELO_MOD_1D_DATA->nDep = i;
    fclose(file);
    return VELO_MOD_1D_DATA;
}

//
//  v1DsubMod.c
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


void v1DsubMod(int zInd, double dep, qualities_vector *QUALITIES_VECTOR, velo_mod_1d_data *VELO_MOD_1D_DATA)
/*
 Purpose:   calculate the rho vp and vs values at a single lat long point for all the depths within this velocity submodel
 
 Input variables:
 depths         - pointer to a struct containing the references to which points lie within this velocity sub-model layer
 veloSubModNum  - the reference number of this velocity sub-model
 subModel1D     - pointer to the 1D velocity sub-model data
 
 Output variables:
 values         - struct containing the vp vs and rho values for all points within this velo sub-model
 
 
 */
{
    // loop over depth values and assign qualities from the sub-model
    for(int j = 0; j < VELO_MOD_1D_DATA->nDep; j++)
    {
        if(dep >= VELO_MOD_1D_DATA->Dep[j]*-1000) // convert to meters, -ve being downwards
        {
            QUALITIES_VECTOR->Rho[zInd] = VELO_MOD_1D_DATA->Rho[j];
            QUALITIES_VECTOR->Vp[zInd] = VELO_MOD_1D_DATA->Vp[j];
            QUALITIES_VECTOR->Vs[zInd] = VELO_MOD_1D_DATA->Vs[j];
            break;
        }
        if(j == VELO_MOD_1D_DATA->nDep)
        {
            printf("Error: Depth point below the extent represented in the 1D velocity model file.\n");
        }
    }
}



void load1dVeloSubModel(char *fileName, velo_mod_1d_data *VELO_MOD_1D_DATA)
/*
 Purpose:   load a 1D velocity submodel into memory
 
 Input variables:
 *fileName  - pointer to the filename to open and read
 
 Output variables:
 velo1D     - (malloc'd) pointer to the velocity sub-model
 */
{
    FILE *file;
    
    char fNameDir[128];
    sprintf(fNameDir,"Data/1D_Velocity_Model/%s",fileName);
    
    file = fopen(fNameDir, "r");
    if (file == NULL)
    {
        perror("Error");
    }
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

}


//velo1D *loadv1DsubMod(void)
///*
// Purpose:   read in the 1D velocity model dataset
//
// Input variables:
// N.A.
//
// Output variables:
// subModel1D - (malloc'd) pointer to the 1D velocity sub-model data
//
// */
//{
//    char *fileName;
//    fileName = "Data/1D_Velocity_Model/Cant1D_v1.fd_modfile";
//    velo1D *subModel1D = NULL;
//    subModel1D = load1dVeloSubModel(fileName);
//    printf("Completed Read of 1D Velocity Model Data\n");
//    return subModel1D;
//}



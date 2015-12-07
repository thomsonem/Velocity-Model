//
//  divideDepths.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 23/06/14.
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

int findGlobalSubVeloModelInd(double depth, partial_global_surface_depths *PARTIAL_GLOBAL_SURFACE_DEPTHS)
/*
 Purpose:   divide the depths at a given lat lon point into processing by the various velocity sub-functions
 
 
 Output variables:
 nVeloInd   - the indice of the sub velocity model the point lies within
 */
{
    int nVeloInd = 1e6; // large value, sub model inds should be <10
    
    for(int j = 0; j < PARTIAL_GLOBAL_SURFACE_DEPTHS->nSurfDep-1; j++)
    {
        if((depth < PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[j]) && (depth > PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[j+1]))        {
            nVeloInd = j;
            break;
        }
    }
    
    if(nVeloInd == 1e6)
    {
        printf("Error.\n"); 
    }
    
    return nVeloInd;
    
}

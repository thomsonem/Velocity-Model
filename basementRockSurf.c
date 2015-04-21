//
//  basementRockSurf.c
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


surfDepValues *basementRockSurf(gridStruct *location)
/*
 Purpose:   obtain the surface data for the basesment rock
 
 Input variables:
 location  - structure containing lat lon grid
 
 Output variables:
 surfDep   - (malloc'd) pointer to structure containing the surface data
 */
{
//    // load the surface file
//    char *fileName;
//    fileName = "QSSurface.in";
//    
//    // IDW settings
//    double power = -4;
//    double radius = 0.01;
//    
//    surfDepValues *surfDep;
//    surfDep = determineSurfaceDepths(location, fileName, power, radius);
//    
//    return surfDep;
    // TEMP SURFACE AT -10km to trial EP Tomo data
    surfDepValues *surfDep;
    surfDep = malloc(sizeof(surfDepValues));
    double infValue = -10000; // negative value in m (-10km) T
    // assign a constant large value for the entire surface
    for(int i = 0; i < location->nX; i++)
    {
        for(int j = 0; j < location->nY; j++)
        {
            surfDep->dep[i][j] = infValue;
        }
    }
    return surfDep;
    
}

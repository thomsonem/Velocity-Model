//
//  loadSurface.c
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

global_surf_read *loadGlobalSurface(char *fileName)
/*
 Purpose:   load a surface into memory
 
 Input variables:
 *fileName  - pointer to the filename to open and read
 
 Output variables:
 surfRead  - (malloc'd) pointer to loaded surface data
 */
{
    double firstLat;
    double firstLon;
    double lastLat;
    double lastLon;
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
    	perror("Error");
    }
    global_surf_read *GLOBAL_SURF_READ;
    GLOBAL_SURF_READ = malloc(sizeof(global_surf_read));
    
    int nLat, nLon;
    // read and assign the number of latitude and longitude values
    fscanf(file, "%d %d", &nLat, &nLon);
    GLOBAL_SURF_READ->nLat = nLat;
    GLOBAL_SURF_READ->nLon = nLon;
    
    // assure the preallocation of the surface struct is not exceeded
    assert(nLat<=GLOBAL_SURF_IN_DIM_MAX);
    assert(nLon<=GLOBAL_SURF_IN_DIM_MAX);
    
    // read lat values
    for(int i = 0; i < nLat; i++)
    {
        fscanf(file, "%lf",&GLOBAL_SURF_READ->lati[i]);
    }
    
    // read lon values
    for(int i = 0; i < nLon; i++)
    {
        fscanf(file, "%lf",&GLOBAL_SURF_READ->loni[i]);
    }
    
    // read in the surface raster data
    for(int i = 0; i < nLat; i++)
    {
        for(int j = 0; j < nLon; j++)
        {
            fscanf(file, "%lf",&GLOBAL_SURF_READ->raster[j][i]);
        }
    }
    
    fclose(file);
    
    firstLat = GLOBAL_SURF_READ->lati[0];
    lastLat = GLOBAL_SURF_READ->lati[GLOBAL_SURF_READ->nLat-1];
    
    if (firstLat >= lastLat)
    {
        GLOBAL_SURF_READ->maxLat = firstLat;
        GLOBAL_SURF_READ->minLat = lastLat;
    }
    else if (lastLat >= firstLat)
    {
        GLOBAL_SURF_READ->maxLat = lastLat;
        GLOBAL_SURF_READ->minLat = firstLat;
    }
    else
    {
        printf("Error.\n");
    }
    
    firstLon = GLOBAL_SURF_READ->loni[0];
    lastLon = GLOBAL_SURF_READ->loni[GLOBAL_SURF_READ->nLon-1];

    if (firstLon >= lastLon)
    {
        GLOBAL_SURF_READ->maxLon = firstLon;
        GLOBAL_SURF_READ->minLon = lastLon;
    }
    else if (lastLon >= firstLon)
    {
        GLOBAL_SURF_READ->maxLon = lastLon;
        GLOBAL_SURF_READ->minLon = firstLon;
    }
    else
    {
        printf("Error.\n");
    }

    return GLOBAL_SURF_READ;
    
}



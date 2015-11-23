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

basin_surf_read *loadBasinSurface(char *fileName)
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
    basin_surf_read *BASIN_SURF_READ;
    BASIN_SURF_READ = malloc(sizeof(basin_surf_read));
    
    int nLat, nLon;
    // read and assign the number of latitude and longitude values
    fscanf(file, "%d %d", &nLat, &nLon);
    BASIN_SURF_READ->nLat = nLat;
    BASIN_SURF_READ->nLon = nLon;
    
    // assure the preallocation of the surface struct is not exceeded
    assert(nLat<=BASIN_SURF_IN_DIM_MAX);
    assert(nLon<=BASIN_SURF_IN_DIM_MAX);
    
    // read lat values
    for(int i = 0; i < nLat; i++)
    {
        fscanf(file, "%lf",&BASIN_SURF_READ->lati[i]);
    }
    
    // read lon values
    for(int i = 0; i < nLon; i++)
    {
        fscanf(file, "%lf",&BASIN_SURF_READ->loni[i]);
    }
    
    // read in the surface raster data
    for(int i = 0; i < nLat; i++)
    {
        for(int j = 0; j < nLon; j++)
        {
            fscanf(file, "%lf",&BASIN_SURF_READ->raster[j][i]);
        }
    }
    
    fclose(file);
    
    firstLat = BASIN_SURF_READ->lati[0];
    lastLat = BASIN_SURF_READ->lati[BASIN_SURF_READ->nLat-1];
    
    if (firstLat >= lastLat)
    {
        BASIN_SURF_READ->maxLat = firstLat;
        BASIN_SURF_READ->minLat = lastLat;
    }
    else if (lastLat >= firstLat)
    {
        BASIN_SURF_READ->maxLat = lastLat;
        BASIN_SURF_READ->minLat = firstLat;
    }
    else
    {
        printf("Error.\n");
    }
    
    firstLon = BASIN_SURF_READ->loni[0];
    lastLon = BASIN_SURF_READ->loni[GLOBAL_SURF_READ->nLon-1];
    
    if (firstLon >= lastLon)
    {
        BASIN_SURF_READ->maxLon = firstLon;
        BASIN_SURF_READ->minLon = lastLon;
    }
    else if (lastLon >= firstLon)
    {
        BASIN_SURF_READ->maxLon = lastLon;
        BASIN_SURF_READ->minLon = firstLon;
    }
    else
    {
        printf("Error.\n");
    }
    
    return BASIN_SURF_READ;
    
}


global_surfaces *loadGlobalSurfaceData(global_model_parameters *GLOBAL_MODEL_PARAMETERS)
/*
 Purpose:   obtain the depths for all lat lon points for all desired surfaces
 
 Input variables:
 location        - structure containing lat lon grid
 surfSubModNames - structure containing all surface keywords
 
 Output variables:
 surfDep   - (malloc'd) pointer to structure containing surface depths for all lat lon points and surfaces
 */
{
    // place global surfaces into struct
    global_surfaces *GLOBAL_SURFACES;
    GLOBAL_SURFACES = malloc(sizeof(global_surfaces));
    
    global_surf_read *GLOBAL_SURF_READ;
    GLOBAL_SURF_READ = NULL;
    
    for(int i = 0; i < GLOBAL_MODEL_PARAMETERS->nSurf; i++)
    {
        // load surface and transfer data into global struct
        GLOBAL_SURF_READ = loadGlobalSurface(GLOBAL_MODEL_PARAMETERS->globalSurfFilenames[i]);
        
        // place in surfGlob struct
        GLOBAL_SURFACES->nLat[i] =  GLOBAL_SURF_READ->nLat;
        GLOBAL_SURFACES->nLon[i] =  GLOBAL_SURF_READ->nLon;
        GLOBAL_SURFACES->maxLat[i] =  GLOBAL_SURF_READ->maxLat;
        GLOBAL_SURFACES->minLat[i] =  GLOBAL_SURF_READ->minLat;
        GLOBAL_SURFACES->maxLon[i] =  GLOBAL_SURF_READ->maxLon;
        GLOBAL_SURFACES->minLon[i] =  GLOBAL_SURF_READ->minLon;
        
        // latitude
        for( int nLat = 0; nLat < GLOBAL_SURF_READ->nLat; nLat++)
        {
            GLOBAL_SURFACES->lati[i][nLat] = GLOBAL_SURF_READ->lati[nLat];
        }
        
        // longitude
        for( int nLon = 0; nLon < GLOBAL_SURF_READ->nLon; nLon++)
        {
            GLOBAL_SURFACES->loni[i][nLon] = GLOBAL_SURF_READ->loni[nLon];
        }
        
        // depth
        for( int nnLat = 0; nnLat < GLOBAL_SURF_READ->nLat; nnLat++)
        {
            for( int nnLon = 0; nnLon < GLOBAL_SURF_READ->nLon; nnLon++)
            {
                GLOBAL_SURFACES->dep[i][nnLon][nnLat] =  GLOBAL_SURF_READ->raster[nnLon][nnLat];
            }
        }
        
    }
    return GLOBAL_SURFACES;
}




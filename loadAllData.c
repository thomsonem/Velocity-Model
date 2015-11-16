//
//  loadAllData.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/10/15.
//  Copyright (c) 2015 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "constants.h"
#include "structs.h"
#include "functions.h"


void loadAllData(surfNames *surfSubModNames)
{
    // determine the depths of each surface for each lat lon point
    surfaceDepthsGlobal *surfGlob = NULL;
    surfGlob = getSurfaceValues(surfSubModNames);
    
    // read in velo subfunction plots
    velo1D *v1DsubModData = NULL;
    depInterpVals *EPtomo2010subModData = NULL;
    for(int i = 0; i < surfSubModNames->nVeloSubMod; i++)
    {
        if(strcmp(surfSubModNames->veloSubMod[i], "v1DsubMod") == 0)
        {
            v1DsubModData = loadv1DsubMod();
        }
        else if(strcmp(surfSubModNames->veloSubMod[i], "EPtomo2010subMod") == 0)
        {
            EPtomo2010subModData = loadEPtomo2010subModSurfaces();
        }
    }
    
    // read in basin data
    globalBasinData *basinData;
    basinData = malloc(sizeof(globalBasinData));
    if(basinData == NULL)
    {
        printf("Memory allocation failed for basin data array.\n");
    }
    
    for(int i = 0; i < surfSubModNames.nBasin; i++)
    {
        if(strcmp(surfSubModNames.basin[i], "CANTERBURY_BASIN") == 0)
        {
            loadCanterburyBasinData(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "PREQ_CANTERBURY_BASIN") == 0)
        {
            loadPreQCanterburyBasinData(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "PREQ_CANTERBURY_BASIN_1D") == 0)
        {
            loadPreQCanterburyBasinData1D(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "Q_CANTERBURY_BASIN") == 0)
        {
            loadQCanterburyBasinData(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "PALEO_CANTERBURY_BASIN") == 0)
        {
            loadPreQCanterburyBasinDataPaleogene(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "PALEO_MIO_CANTERBURY_BASIN") == 0)
        {
            loadPreQCanterburyBasinDataPaleogeneMiocene(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "BPV_BASIN") == 0)
        {
            loadBPVBasinData(location, i, basinData);
        }
        if(strcmp(surfSubModNames.basin[i], "BPV_BASIN_WHEATHERED") == 0)
        {
            loadBPVWheatheredBasinData(location, i, basinData);
        }
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

surfaceDepthsGlobal *getSurfaceValues(surfNames *surfSubModNames)
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
    surfaceDepthsGlobal *surfGlob;
    surfGlob = malloc(sizeof(surfaceDepthsGlobal));
    
    surfRead *tempSurf = NULL;
    char *fileName;
    for(int i = 0; i < surfSubModNames->nSurf; i++)
    {
        if(strcmp(surfSubModNames->surf[i], "posInfSurf")==0)
        {
            fileName = "Data/Global_Surfaces/posInf.in";
        }
        else if(strcmp(surfSubModNames->surf[i], "negInfSurf") == 0)
        {
            fileName = "Data/Global_Surfaces/negInf.in";
        }
        else if(strcmp(surfSubModNames->surf[i], "basementRockSurf") == 0)
        {
            fileName ="Data/Canterbury_Basin/Pre_Quaternary/BasementTop.in";
        }
        else if(strcmp(surfSubModNames->surf[i], "demSurf") == 0)
        {
            fileName = "Data/DEM/DEM.in";
        }
        else
        {
            printf("Error.\n");
        }
        // load surface and transfer data into global struct
        tempSurf = loadSurface(fileName);
        
        // place in surfGlob struct
        surfGlob->nLat[i] =  tempSurf->nLat;
        surfGlob->nLon[i] =  tempSurf->nLon;
        surfGlob->maxLat[i] =  tempSurf->maxLat;
        surfGlob->minLat[i] =  tempSurf->minLat;
        surfGlob->maxLon[i] =  tempSurf->maxLon;
        surfGlob->minLon[i] =  tempSurf->minLon;
        
        // latitude
        for( int nLat = 0; nLat < tempSurf->nLat; nLat++)
        {
            surfGlob->lati[i][nLat] = tempSurf->lati[nLat];
        }
        
        // longitude
        for( int nLon = 0; nLon < tempSurf->nLon; nLon++)
        {
            surfGlob->loni[i][nLon] = tempSurf->loni[nLon];
        }
        
        // depth
        for( int nnLat = 0; nnLat < tempSurf->nLat; nnLat++)
        {
            for( int nnLon = 0; nnLon < tempSurf->nLon; nnLon++)
            {
                surfGlob->dep[i][nnLon][nnLat] =  tempSurf->raster[nnLon][nnLat];
            }
        }
        
    }
    return surfGlob;
}

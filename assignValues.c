//
//  assignValues.c
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


global_qualitites *assignQualities(model_extent MODEL_EXTENT, global_model_parameters *GLOBAL_MODEL_PARAMETERS, partial_global_mesh *PARTIAL_GLOBAL_MESH, calculation_log *CALCULATION_LOG, int latInd)
/*
 Purpose:   obtain vp vs and rho for all points within the model grid
 
 Input variables:
 location        - pointer to structure containing lat lon grid
 surfSubModNames - structure containing all surface keywords
 surfDepsGlob    - pointer to structure containing the depths of all surfaces for all lat long gridpoints
 
 Output variables:
 globalValues    - (malloc'd) pointer to structure containing vp vs and rho for all gridpoints
 */
{
    velo_mod_1d_data *VELO_MOD_1D_DATA;
    VELO_MOD_1D_DATA = NULL;
    nz_tomography_data *NZ_TOMOGRAPHY_DATA;
    NZ_TOMOGRAPHY_DATA = NULL;
    global_surfaces *GLOBAL_SURFACES;
    GLOBAL_SURFACES = NULL;
    
    if( latInd == 0 ) // if first time, read all data required into memory
    {
        // read in sub velocity models
        for( int i = 0; i < GLOBAL_MODEL_PARAMETERS->nVeloSubMod; i++)
        {
            if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "v1DsubMod") == 0)
            {
                VELO_MOD_1D_DATA = load1dVeloSubModel(GLOBAL_MODEL_PARAMETERS->veloMod1dFileName[0]);
            }
            else if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "EPtomo2010subMod") == 0)
            {
                 NZ_TOMOGRAPHY_DATA = loadEPtomoSurfaceData();
            }
            else if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "NaNsubMod") == 0)
            {
                // no data required for NaN velocity sub model
            }
        }
        // read in global surfaces
        GLOBAL_SURFACES = 
        
    }
    
    
    

    
    
    
    surfaceDepthsGlobal *surfDepsGlob = NULL;
   

    

    determineIfWithinBasinLatLon(location, basinNum, basinData);
    enforceBasinSurfaceDepths(location, basinNum, basinData);
    assignBasinProperties(location, basinNum, basinData);

    surfDeps = determineSurfaceDepthsBasin(basinData, location, fileName, basinNum, i);

    
    
    for (int nP = 0; nP < location->nX; nP++)
    {
        // loop over gridpoints and assign quantities
        globalDataValues *globalValues;
        globalValues = malloc(sizeof(globalDataValues));
        if( globalValues == NULL)
        {
            printf("Memory allocation failed for global data array.\n");
        }
        int nVeloModInd;
        int flagInABasin = 0;
        
        //    printf("%i %i %i\n", location->nX, location->nY, location->nZ);
        
        // add in basin qualities
        for(int i = 0; i < location->nX; i++)
        {
            for(int j = 0; j < location->nY; j++)
            {
                for(int k = 0; k < location->nZ; k++)
                {
                    for(int m = 0; m < surfSubModNames.nBasin; m++) // loop over number of basins
                    {
                        if((basinData->inBasinLatLon[m][basinData->nBoundaries[m]-1][i][j] == 1) && (basinData->inBasinDep[m][i][j][k] == 1)) // in basin lat lon (wider boundary)
                        {
                            flagInABasin = 1; // flag as in a basin
                            globalValues->Rho[i][j][k] = basinData->Rho[m][i][j][k];
                            globalValues->Vp[i][j][k] = basinData->Vp[m][i][j][k];
                            globalValues->Vs[i][j][k] = basinData->Vs[m][i][j][k];
                        }
                    }
                    if(flagInABasin == 0) // if point is not flagged as within the basin assign based off sub-velocity models
                    {
                        // determine which sub velocity model the point lies within
                        nVeloModInd = findSubVeloModelInd(location, i, j, k, surfSubModNames.nVeloSubMod, surfDepsGlob);
                        
                        // call the respective sub velocity model
                        if(strcmp(surfSubModNames.veloSubMod[nVeloModInd], "v1DsubMod") == 0)
                        {
                            v1DsubMod(i, j, k, globalValues, location, v1DsubModData);
                        }
                        else if(strcmp(surfSubModNames.veloSubMod[nVeloModInd], "EPtomo2010subMod") == 0)
                        {
                            EPtomo2010subMod(i, j, k, globalValues, location, EPtomo2010subModData);
                        }
                        else if(strcmp(surfSubModNames.veloSubMod[nVeloModInd], "NaNsubMod") == 0)
                        {
                            NaNsubMod(i, j, k, globalValues);
                        }
                    }

                    flagInABasin = 0; // reassign flag
                }
            }
            //        printf("Completed calculation of properties at latitude %i of %i.\n", i+1, location->nX);

        }
        
    }
    
//    if((location->nX == 1)&&(location->nY==1))
//        // if grid only contains a single point save the surface depths to a text file
//    {
//        int basinNum = 0;
//        writeBasinSurfaceDepths(basinData, basinNum, location, outputDirectory);
//    }
//    if (location->saveSurfaceDepths == 1)
//    {
//        writeAllBasinSurfaceDepths(basinData, location, outputDirectory);
//    }
//    
//    free(basinData);
//    free(v1DsubModData);
//    free(EPtomo2010subModData);
//    
//    return globalValues;
//    
    
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
    global_surfaces = malloc(sizeof(global_surfaces));
    
    surf_read *SURF_DATA = NULL;
    char *fileName;
    for(int i = 0; i < surfSubModNames->nSurf; i++)
    {
        if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "posInfSurf")==0)
        {
            fileName = "Data/Global_Surfaces/posInf.in";
        }
        else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "negInfSurf") == 0)
        {
            fileName = "Data/Global_Surfaces/negInf.in";
        }
        else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "basementRockSurf") == 0)
        {
            fileName ="Data/Canterbury_Basin/Pre_Quaternary/BasementTop.in";
        }
        else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "demSurf") == 0)
        {
            fileName = "Data/DEM/DEM.in";
        }
        else
        {
            printf("Error.\n");
        }
        // load surface and transfer data into global struct
        SURF_DATA = loadSurface(fileName);
        
        // place in surfGlob struct
        GLOBAL_SURFACES->nLat[i] =  SURF_DATA->nLat;
        GLOBAL_SURFACES->nLon[i] =  SURF_DATA->nLon;
        GLOBAL_SURFACES->maxLat[i] =  SURF_DATA->maxLat;
        GLOBAL_SURFACES->minLat[i] =  SURF_DATA->minLat;
        GLOBAL_SURFACES->maxLon[i] =  SURF_DATA->maxLon;
        GLOBAL_SURFACES->minLon[i] =  SURF_DATA->minLon;
        
        // latitude
        for( int nLat = 0; nLat < SURF_DATA->nLat; nLat++)
        {
            GLOBAL_SURFACES->lati[i][nLat] = SURF_DATA->lati[nLat];
        }
        
        // longitude
        for( int nLon = 0; nLon < SURF_DATA->nLon; nLon++)
        {
            GLOBAL_SURFACES->loni[i][nLon] = SURF_DATA->loni[nLon];
        }
        
        // depth
        for( int nnLat = 0; nnLat < SURF_DATA->nLat; nnLat++)
        {
            for( int nnLon = 0; nnLon < SURF_DATA->nLon; nnLon++)
            {
                GLOBAL_SURFACES->dep[i][nnLon][nnLat] =  SURF_DATA->raster[nnLon][nnLat];
            }
        }
        
    }
    return surfGlob;
}

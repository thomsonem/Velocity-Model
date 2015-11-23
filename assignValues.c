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

    
    if( latInd == 0 ) // if first time, read all data required into memory
    {
        velo_mod_1d_data *VELO_MOD_1D_DATA;
        VELO_MOD_1D_DATA = NULL;
        nz_tomography_data *NZ_TOMOGRAPHY_DATA;
        NZ_TOMOGRAPHY_DATA = NULL;
        global_surfaces *GLOBAL_SURFACES;
        GLOBAL_SURFACES = NULL;
        basin_data *BASIN_DATA;
        BASIN_DATA = NULL;
        
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
        GLOBAL_SURFACES = loadGlobalSurfaceData(GLOBAL_MODEL_PARAMETERS);
        
        // read in basin surfaces and boundaries
        BASIN_DATA = loadBasinData(GLOBAL_MODEL_PARAMETERS);
        
    }
    
    
    

    
    
    
   

    

//    determineIfWithinBasinLatLon(location, basinNum, basinData);
//    enforceBasinSurfaceDepths(location, basinNum, basinData);
//    assignBasinProperties(location, basinNum, basinData);
//
//    surfDeps = determineSurfaceDepthsBasin(basinData, location, fileName, basinNum, i);

    
    
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


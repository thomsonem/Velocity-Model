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


globalDataValues *assignValues(modVersion modelVersion, gridStruct *location, surfNames surfSubModNames, surfaceDepthsGlobal *surfDepsGlob, char *outputDirectory)
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
    // read in velo subfunction plots
    velo1D *v1DsubModData = NULL;
    depInterpVals *EPtomo2010subModData = NULL;
    for(int i = 0; i < surfSubModNames.nVeloSubMod; i++)
    {
        if(strcmp(surfSubModNames.veloSubMod[i], "v1DsubMod") == 0)
        {
            v1DsubModData = loadv1DsubMod();
        }
        else if(strcmp(surfSubModNames.veloSubMod[i], "EPtomo2010subMod") == 0)
        {
            EPtomo2010subModData = loadEPtomo2010subMod(location);
        }
    }

    // read in basin data
    globalBasinData *basinData = NULL;
    basinData = malloc(sizeof(globalBasinData));
    for(int i = 0; i < surfSubModNames.nBasin; i++)
    {
        if(strcmp(surfSubModNames.basin[i], "CANTERBURY_BASIN") == 0)
        {
            loadCanterburyBasinData(location, i, basinData);
        }
    }

    // loop over gridpoints and assign quantities
    globalDataValues *globalValues;
    globalValues = malloc(sizeof(globalDataValues));
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
        printf("Completed calculation of properties at latitude %i of %i.\n", i+1, location->nX);
    }
    
    if((location->nX == 1)&&(location->nY==1))
       // if grid only contains a single point save the surface depths to a text file
       {
           writeBasinSurfaceDepths(basinData, location, outputDirectory);
       }
	if (modelVersion.saveSurfaceDepths == 1)
	{
		writeAllBasinSurfaceDepths(basinData, location, outputDirectory);
	}

    free(basinData);
    free(v1DsubModData);
    free(EPtomo2010subModData);
   
    return globalValues;
    
    
}

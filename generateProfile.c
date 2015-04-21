//
//  generateProfile.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 19/12/14.
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

void generateProfile(modOrigin modelOrigin)
{
    // Model extent struct
    modExtent modelExtent;
    modelExtent.Ymax = 0.5;
    modelExtent.Xmax = 0.5;
    modelExtent.Zmax = 10; // max depth (km)
    modelExtent.Zmin = -0.0;
    modelExtent.hDep = .01;
    modelExtent.hLatLon = 1;
    
    
    // Model version struct
    modVersion modelVersion;
    modelVersion.version = 1.2;
    printf("Generating model version %f.\n", modelVersion.version);
    
    // generate the model grid
    gridStruct *location = NULL;
    location = generateModelGrid(modelOrigin,modelExtent);
    
    // obtain surface filenames based off version number
    surfNames surfSubModNames;
    surfSubModNames = getSurfSubModNames(modelVersion);
    
    // determine the depths of each surface for each lat lon point
    surfaceDepthsGlobal *surfDepsGlob = NULL;
    surfDepsGlob = getSurfaceValues(location, surfSubModNames);
    
    // assign values
    globalDataValues *globDataVals = NULL;
    globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob);
    
    // write profile to file
    writeIndividualProfile(globDataVals, location);
    
    // free allocated memory
    free(surfDepsGlob);
    free(globDataVals);
    free(location);
    
    
    
}

void writeBasinSurfaceDepths(globalBasinData *basinData, gridStruct *location)
{
    FILE *fp;
    
    fp = fopen("SurfacesAtIndividualLocation.txt", "wb");
    fprintf(fp,"Basin Surface Depths at Lat: %lf Lon: %lf\n",location->Lat[0][0], location->Lon[0][0]);
    
    for(int i = 0; i < basinData->nSurf[0]; i++)
    {
        if(isnan(basinData->surfVals[0][0][0][i]) !=1)
        {
            fprintf(fp,"%s \t %lf\n",basinData->surf[0][i], basinData->surfVals[0][0][0][i]);
        }
    }
    fclose(fp);
    printf("Completed write of surface depths at the location\n");

}

void writeAllBasinSurfaceDepths(globalBasinData *basinData, gridStruct *location)
{
	FILE *fp;

	fp = fopen("/home/ethan/share/veloModelSliceSurfaceDepths.txt", "w");

	for (int i = 0; i < location->nX; i++)
	{
		fprintf(fp, "%lf,%lf", location->Lon[i][0], location->Lat[i][0]);
		for (int j = 0; j < basinData->nSurf[0]; j++) 
		{
				fprintf(fp, ",%lf", basinData->surfVals[0][i][0][j]);
		}
		fprintf(fp, "\n");

	}
	fclose(fp);
	printf("Completed write of surface depths at the all locations.\n");

}



void writeIndividualProfile(globalDataValues *globalValues, gridStruct *location)
{
    FILE *fp;
    
    fp = fopen("ProfileAtIndividualLocation.txt", "wb");
    fprintf(fp,"Properties at Lat: %lf Lon: %lf\n",location->Lat[0][0], location->Lon[0][0]);
    fprintf(fp,"Depth \t Vp \t Vs \t Rho\n");

    
    for(int i = 0; i < location->nZ; i++)
    {
        fprintf(fp,"%lf \t %lf \t %lf \t %lf\n",location->Z[i], globalValues->Vp[0][0][i],globalValues->Vs[0][0][i],globalValues->Rho[0][0][i]);
    }
    fclose(fp);
    printf("Completed write of profiles at the location\n");

}

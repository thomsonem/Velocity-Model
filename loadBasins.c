//
//  loadBasins.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 4/08/14.
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

basin_data *loadBasinData(global_model_parameters *GLOBAL_MODEL_PARAMETERS)
{
    basin_data *BASIN_DATA;
    BASIN_DATA = malloc(sizeof(basin_data));
    
    for( int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasins; i++)
    {
        loadAllBasinSurfaces(i, BASIN_DATA, GLOBAL_MODEL_PARAMETERS);
    }
    loadBoundaries(basinData, basinNum);
    loadAllBasinSurfaces(basinNum, basinData);
    
}

void loadAllBasinSurfaces(int basinNum, basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
{
    for(int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[basinNum]; i++)
    {
        // load surface and transfer data into global struct
        basin_surf_read *BASIN_SURF_READ;
        BASIN_SURF_READ = loadBasinSurface(GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[basinNum][i]);
        
        // place in surfGlob struct
        BASIN_DATA->nLat[basinNum][i] =  BASIN_SURF_READ->nLat;
        BASIN_DATA->nLon[basinNum][i] =  BASIN_SURF_READ->nLon;
        BASIN_DATA->maxLat[basinNum][i] =  BASIN_SURF_READ->maxLat;
        BASIN_DATA->minLat[basinNum][i] =  BASIN_SURF_READ->minLat;
        BASIN_DATA->maxLon[basinNum][i] =  BASIN_SURF_READ->maxLon;
        BASIN_DATA->minLon[basinNum][i] =  BASIN_SURF_READ->minLon;
        
        // latitude
        for( int nLat = 0; nLat < BASIN_SURF_READ->nLat; nLat++)
        {
            BASIN_DATA->lati[basinNum][i][nLat] = BASIN_SURF_READ->lati[nLat];
        }
        
        // longitude
        for( int nLon = 0; nLon < BASIN_SURF_READ->nLon; nLon++)
        {
            BASIN_DATA->loni[basinNum][i][nLon] = BASIN_SURF_READ->loni[nLon];
        }
        
        // depth
        for( int nnLat = 0; nnLat < BASIN_SURF_READ->nLat; nnLat++)
        {
            for( int nnLon = 0; nnLon < BASIN_SURF_READ->nLon; nnLon++)
            {
                BASIN_DATA->dep[basinNum][i][nnLon][nnLat] =  BASIN_SURF_READ->raster[nnLon][nnLat];
            }
        }
    }
}



void determineBasinProperties(globalBasinData *basinData, int basinNum, int xInd, int yInd, int zInd, gridStruct *location, velo1D *subModel1D)
{
    
    //find surfaces adjacent to the point
    
    double upperSurf, lowerSurf;
    char *upperSurfName = NULL, *lowerSurfName = NULL;
    for(int i = 0; i < basinData->nSurf[basinNum]; i++)
    {
        lowerSurf = basinData->surfVals[basinNum][xInd][yInd][i];
        if(lowerSurf<=location->Z[zInd] && isnan(lowerSurf) !=1)
        {
            lowerSurfName = basinData->surf[basinNum][i];
            break;
        }
        if (i == basinData->nSurf[basinNum])
        {
            printf("Error\n");
        }
    }
    
    for(int i = basinData->nSurf[basinNum]; i > 0; i--)
    {
        upperSurf = basinData->surfVals[basinNum][xInd][yInd][i-1];
        //printf("%lf %lf %i\n",upperSurf,location->Z[zInd],i-1);
        if(upperSurf>location->Z[zInd] && isnan(upperSurf) !=1)
        {
            upperSurfName = basinData->surf[basinNum][i-1];
            break;
        }
        if( (i-1) == 0)
        {
            printf("Error\n");
        }
    }
    

    // call upon the respective layer specific velocity model
    
    valStructLocal *values = NULL;
    if((strcmp(upperSurfName, "DEM") == 0) && strcmp(lowerSurfName, "RiccartonTop") == 0)
    {
        values = christchurchSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "RiccartonTop") == 0) && strcmp(lowerSurfName, "BromleyTop") == 0)
    {
        values = riccartonSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "BromleyTop") == 0) && strcmp(lowerSurfName, "LinwoodTop") == 0)
    {
        values = bromleySubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "LinwoodTop") == 0) && strcmp(lowerSurfName, "HeathcoteTop") == 0)
    {
        values = linwoodSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "HeathcoteTop") == 0) && strcmp(lowerSurfName, "BurwoodTop") == 0)
    {
        values = heathcoteSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "BurwoodTop") == 0) && strcmp(lowerSurfName, "ShirleyTop") == 0)
    {
        values = burwoodSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "ShirleyTop") == 0) && strcmp(lowerSurfName, "WainoniTop") == 0)
    {
        values = shirleySubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "WainoniTop") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
    {
        values = wainoniSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "DEM") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
    {
        values = DEMtoPlioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "DEM_1D") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
    {
        values = v1DBasinSubMod(location, zInd, subModel1D);
    }
    else if((strcmp(upperSurfName, "PlioceneTop") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
    {
        values = plioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "MioceneTop") == 0) && strcmp(lowerSurfName, "PaleogeneTop") == 0)
    {
        values = mioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "PaleogeneTop") == 0) && strcmp(lowerSurfName, "BasementTop") == 0)
    {
        values = paleogeneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "BPVTop") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
    {
        values = BPVSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else if((strcmp(upperSurfName, "BPVTopWheathered") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
    {
        values = WheatheredBPVSubModel(location, basinData, xInd, yInd, zInd, basinNum);
    }
    else
    {
        printf("error\n");
    }
    
    basinData->Vp[basinNum][xInd][yInd][zInd] = values->Vp;
    basinData->Vs[basinNum][xInd][yInd][zInd] = values->Vs;
    basinData->Rho[basinNum][xInd][yInd][zInd] = values->Rho;
    free(values);
}



void assignBasinProperties(gridStruct *location, int basinNum, globalBasinData *basinData)
{
    // load 1D velo model
    velo1D *velocityModel1DBasinData = NULL;
    velocityModel1DBasinData = loadv1DsubMod();
    
    // calculate the properties for all points inside the basin
    for(int i = 0; i < location->nX; i++)
    {
        for(int j = 0; j < location->nY; j++)
        {
            if(basinData->inBasinLatLon[basinNum][basinData->nBoundaries[basinNum]-1][i][j] == 1) // in basin lat lon (wider boundary)
            {
                for(int k = 0; k < location->nZ; k++)
                {
                    if(basinData->inBasinDep[basinNum][i][j][k] == 1) // in basin Z limits
                    {
                        determineBasinProperties(basinData, basinNum, i, j, k, location, velocityModel1DBasinData);
                    }
                }
            }
        }
//        printf("Completed calculation of basin properties at latitude %i of %i.\n", i+1, location->nX);
        printf("\rAssigning basin properties %d%% complete.", i*100/location->nX);
        fflush(stdout);
    }
    printf("\rAssigning basin properties 100%% complete.");
    fflush(stdout);
    printf("\n");
    printf("Basin data successfully calculated.\n");
    free(velocityModel1DBasinData);
}


void enforceBasinSurfaceDepths(gridStruct *location, int basinNum, globalBasinData *basinData)
{
    // enforce basin surface depths for all points in the within the lat lon poly (ignore others)
    double topLim, botLim;
    for(int i = 0; i < location->nX; i++)
    {
        for(int j = 0; j < location->nY; j++)
        {
            if(basinData->inBasinLatLon[basinNum][basinData->nBoundaries[basinNum]-1][i][j] == 1)
                // enforce depths based on the larger (or final) boundary
            {
                // enforce
                enforceSurfaceDepths(basinData, i, j, basinNum);
                
                // check if depth is within the top and bottom basin layers
                topLim = basinData->surfVals[basinNum][i][j][0];
                botLim = basinData->surfVals[basinNum][i][j][basinData->nSurf[basinNum]-1];
                for(int k  = 0; k < location->nZ; k++)
                {
                    if(location->Z[k] > topLim)
                    {
                        basinData->inBasinDep[basinNum][i][j][k] = 0;
                    }
                    else if (location->Z[k] < botLim)
                    {
                        basinData->inBasinDep[basinNum][i][j][k] = 0;
                    }
                    else
                    {
                        basinData->inBasinDep[basinNum][i][j][k] = 1; // in the basin Z limits
                    }
                }
            }
        }
    }
    printf("Basin surfaces depths enforced.\n");
}



























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

void loadBasinData(basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
{
    
    for( int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasins; i++)
    {
        loadAllBasinSurfaces(i, BASIN_DATA, GLOBAL_MODEL_PARAMETERS);
        loadBasinBoundaries(i, BASIN_DATA, GLOBAL_MODEL_PARAMETERS);
    }
    
    
}

void interpolateBasinSurfaceDepths(basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS, in_basin *IN_BASIN, partial_basin_surface_depths *PARTIAL_BASIN_SURFACE_DEPTHS, mesh_vector *MESH_VECTOR)
{
    determineIfWithinBasinLatLon(BASIN_DATA, GLOBAL_MODEL_PARAMETERS, IN_BASIN, *MESH_VECTOR->Lat, *MESH_VECTOR->Lon);
    determineBasinSurfaceDepths(BASIN_DATA, GLOBAL_MODEL_PARAMETERS, IN_BASIN, PARTIAL_BASIN_SURFACE_DEPTHS, *MESH_VECTOR->Lat, *MESH_VECTOR->Lon);
    
    
    
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



void determineBasinSurfaceDepths(basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS, in_basin *IN_BASIN, partial_basin_surface_depths *PARTIAL_BASIN_SURFACE_DEPTHS, double Lat, double Lon)
{
    /*
     Purpose:   obtain the depths for all lat lon points within the  for a given surface file
     
     Input variables:
     location  - structure containing lat lon grid
     fileName  - filename of the surface file for reading
     
     Output variables:
     surfDep   - (malloc'd) pointer to structure containing surface depths for all lat lon points
     */
    
    adjacent_points *ADJACENT_POINTS;

    for(int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasins; i++)
    {
        for(int j = 0; j < GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[i]; j++)
        {
            if(IN_BASIN->inBasinLatLon[i][i] == 1)
            {
                // find adjacent points
                ADJACENT_POINTS = findBasinAdjacentPoints(BASIN_DATA->surf[i][j], Lat, Lon);
                if (ADJACENT_POINTS->inSurfaceBounds == 1)
                {
                    // interpolate
                    PARTIAL_BASIN_SURFACE_DEPTHS->dep[i][j] = biLinearInterpolation( BASIN_DATA->surf[i][j]->loni[ADJACENT_POINTS->lonInd[0]], BASIN_DATA->surf[i][j]->loni[ADJACENT_POINTS->lonInd[1]], BASIN_DATA->surf[i][j]->lati[ADJACENT_POINTS->latInd[0]], BASIN_DATA->surf[i][j]->lati[ADJACENT_POINTS->latInd[1]], BASIN_DATA->surf[i][j]->raster[ADJACENT_POINTS->lonInd[0]][ADJACENT_POINTS->latInd[0]], BASIN_DATA->surf[i][j]->raster[ADJACENT_POINTS->lonInd[0]][ADJACENT_POINTS->latInd[1]], BASIN_DATA->surf[i][j]->raster[ADJACENT_POINTS->lonInd[1]][ADJACENT_POINTS->latInd[0]], BASIN_DATA->surf[i][j]->raster[ADJACENT_POINTS->lonInd[1]][ADJACENT_POINTS->latInd[1]], Lon, Lat);
                    free(ADJACENT_POINTS);
                }
                else
                {
                    printf("Error, point lies outside basin surface domain.\n");
                }
            }
            else
            {
                PARTIAL_BASIN_SURFACE_DEPTHS->dep[i][j] = NAN; // define as NAN if surface is outside of the boundary
            }
        }
    }
}

adjacent_points *findBasinAdjacentPoints(basin_surf_read *BASIN_SURF_READ, double lat, double lon)
{
    adjacent_points *ADJACENT_POINTS;
    ADJACENT_POINTS = malloc(sizeof(adjacent_points));
    
    int latAssignedFlag = 0;
    int lonAssignedFlag = 0;
    ADJACENT_POINTS->inSurfaceBounds = 0;
    
    for( int i = 0; i < BASIN_SURF_READ->nLat; i++)
    {
        if(BASIN_SURF_READ->lati[i] >= lat)
        {
            if (i==0)
            {
                break;
            }
            ADJACENT_POINTS->latInd[0]= i-1;
            ADJACENT_POINTS->latInd[1] = i;
            latAssignedFlag = 1;
            break;
            
        }
    }
    if(latAssignedFlag == 0) // to account for some surface file vectors of lat long being ascending not descending
    {
        for(int i = BASIN_SURF_READ->nLat-1; i >= 0; i--)
        {
            if(BASIN_SURF_READ->lati[i] >= lat)
            {
                if (i==BASIN_SURF_READ->nLat-1)
                {
                    break;
                }
                ADJACENT_POINTS->latInd[0]= i;
                ADJACENT_POINTS->latInd[1] = i+1;
                latAssignedFlag = 1;
                break;
                
            }
        }
    }
    for( int j = 0; j < BASIN_SURF_READ->nLon; j++)
    {
        if(BASIN_SURF_READ->loni[j] >= lon)
        {
            if (j==0)
            {
                break;
            }
            ADJACENT_POINTS->lonInd[0] = j-1;
            ADJACENT_POINTS->lonInd[1] = j;
            lonAssignedFlag = 1;
            break;
        }
    }
    if (lonAssignedFlag == 0)
    {
        for( int j = BASIN_SURF_READ->nLon-1; j >= 0; j--)
        {
            if(BASIN_SURF_READ->loni[j] >= lon)
            {
                if (j==BASIN_SURF_READ->nLon-1)
                {
                    break;
                }
                ADJACENT_POINTS->lonInd[0] = j;
                ADJACENT_POINTS->lonInd[1] = j+1;
                lonAssignedFlag = 1;
                break;
            }
        }
    }
    
    if((latAssignedFlag != 1)||(lonAssignedFlag !=1)) // if any indicies are unassigned
    {
        printf("Error, basin point lies outside of the extent of the basin surface.\n");
    }
    else
    {
        ADJACENT_POINTS->inSurfaceBounds = 1;
    }
    
    return ADJACENT_POINTS;
}


void determineIfWithinBasinLatLon(basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS, in_basin *IN_BASIN, double Lat, double Lon)
{
    int basinFlag = 0;
    int inPoly;
    
    for( int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasins; i++)
    {
        for( int j = 0; j < GLOBAL_MODEL_PARAMETERS->nBasinBoundaries[i]; j++)
        {
            if(Lon >= BASIN_DATA->maxLonBoundary[i][j])
            {
                basinFlag = 0;
            }
            else if(Lon <= BASIN_DATA->minLonBoundary[i][j])
            {
                basinFlag = 0;
            }
            else if(Lat >= BASIN_DATA->maxLatBoundary[i][j])
            {
                basinFlag = 0;
            }
            else if(Lat <= BASIN_DATA->minLatBoundary[i][j])
            {
                basinFlag = 0;
            }
            else
            {
                basinFlag = 1; // possibly in basin
            }
    
            // assign flag to indicate if point is inside(1) or outside(0) basin
            if(basinFlag == 0)
            {
                IN_BASIN->inBasinLatLon[i][j] = 0; // not in rectangle
            }
            else if(basinFlag == 1)
            {
                inPoly = pointInPoly(BASIN_DATA, i, j, Lon, Lat); // check if in poly
                if(inPoly == 1) // inside poly, check depth points at a later stage
                {
                    IN_BASIN->inBasinLatLon[i][j] = 1; // in lat lon poly
                }
                else if(inPoly == 0) // outside poly
                {
                    IN_BASIN->inBasinLatLon[i][j] = 1;
                }
                basinFlag = 0;
            }
        }
    }
}

void loadAllBasinSurfaces(int basinNum, basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
{
    for(int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[basinNum]; i++)
    {
        // load surface and transfer data into global struct
        BASIN_DATA->surf[basinNum][i] = loadBasinSurface(GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[basinNum][i]);
    }
 }


void loadBasinBoundaries(int basinNum, basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
/*
 Purpose:   load a boundary file into memory
 
 */
{
    for (int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasinBoundaries[basinNum]; i++)
    {
        FILE *file;
        file = fopen(GLOBAL_MODEL_PARAMETERS->basinBoundaryFilenames[basinNum][i], "r");
        
        int count = 0;
        BASIN_DATA->minLonBoundary[basinNum][i] = 180; // starting points to refine the encompassing rectangle
        BASIN_DATA->maxLonBoundary[basinNum][i] = -180;
        BASIN_DATA->minLatBoundary[basinNum][i] = 180;
        BASIN_DATA->maxLatBoundary[basinNum][i] = -180;
        
        while(!feof(file))
        {
            fscanf(file, "%lf %lf", &BASIN_DATA->boundaryLon[basinNum][i][count], &BASIN_DATA->boundaryLat[basinNum][i][count]);
            
            BASIN_DATA->minLonBoundary[basinNum][i] = fmin(BASIN_DATA->minLonBoundary[basinNum][i],BASIN_DATA->boundaryLon[basinNum][i][count]);
            BASIN_DATA->minLatBoundary[basinNum][i] = fmin(BASIN_DATA->minLatBoundary[basinNum][i],BASIN_DATA->boundaryLat[basinNum][i][count]);
            
            BASIN_DATA->maxLonBoundary[basinNum][i] = fmax(BASIN_DATA->maxLonBoundary[basinNum][i],BASIN_DATA->boundaryLon[basinNum][i][count]);
            BASIN_DATA->maxLatBoundary[basinNum][i] = fmax(BASIN_DATA->maxLatBoundary[basinNum][i],BASIN_DATA->boundaryLat[basinNum][i][count]);
            
            count += 1;
        }
        fclose(file);
        
        BASIN_DATA->boundaryNumPoints[basinNum][i] = count;
        assert(count<=MAX_DIM_BOUNDARY_FILE);
        assert(BASIN_DATA->boundaryLon[basinNum][i][count] == BASIN_DATA->boundaryLon[basinNum][i][0]);
        assert(BASIN_DATA->boundaryLat[basinNum][i][count] == BASIN_DATA->boundaryLat[basinNum][i][0]);
    }
}

void determineBasinProperties(void)
{
    
}


//
//
//void determineBasinProperties(globalBasinData *basinData, int basinNum, int xInd, int yInd, int zInd, gridStruct *location, velo1D *subModel1D)
//{
//    
//    //find surfaces adjacent to the point
//    
//    double upperSurf, lowerSurf;
//    char *upperSurfName = NULL, *lowerSurfName = NULL;
//    for(int i = 0; i < basinData->nSurf[basinNum]; i++)
//    {
//        lowerSurf = basinData->surfVals[basinNum][xInd][yInd][i];
//        if(lowerSurf<=location->Z[zInd] && isnan(lowerSurf) !=1)
//        {
//            lowerSurfName = basinData->surf[basinNum][i];
//            break;
//        }
//        if (i == basinData->nSurf[basinNum])
//        {
//            printf("Error\n");
//        }
//    }
//    
//    for(int i = basinData->nSurf[basinNum]; i > 0; i--)
//    {
//        upperSurf = basinData->surfVals[basinNum][xInd][yInd][i-1];
//        //printf("%lf %lf %i\n",upperSurf,location->Z[zInd],i-1);
//        if(upperSurf>location->Z[zInd] && isnan(upperSurf) !=1)
//        {
//            upperSurfName = basinData->surf[basinNum][i-1];
//            break;
//        }
//        if( (i-1) == 0)
//        {
//            printf("Error\n");
//        }
//    }
//    
//
//    // call upon the respective layer specific velocity model
//    
//    valStructLocal *values = NULL;
//    if((strcmp(upperSurfName, "DEM") == 0) && strcmp(lowerSurfName, "RiccartonTop") == 0)
//    {
//        values = christchurchSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "RiccartonTop") == 0) && strcmp(lowerSurfName, "BromleyTop") == 0)
//    {
//        values = riccartonSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "BromleyTop") == 0) && strcmp(lowerSurfName, "LinwoodTop") == 0)
//    {
//        values = bromleySubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "LinwoodTop") == 0) && strcmp(lowerSurfName, "HeathcoteTop") == 0)
//    {
//        values = linwoodSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "HeathcoteTop") == 0) && strcmp(lowerSurfName, "BurwoodTop") == 0)
//    {
//        values = heathcoteSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "BurwoodTop") == 0) && strcmp(lowerSurfName, "ShirleyTop") == 0)
//    {
//        values = burwoodSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "ShirleyTop") == 0) && strcmp(lowerSurfName, "WainoniTop") == 0)
//    {
//        values = shirleySubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "WainoniTop") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
//    {
//        values = wainoniSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "DEM") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
//    {
//        values = DEMtoPlioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "DEM_1D") == 0) && strcmp(lowerSurfName, "PlioceneTop") == 0)
//    {
//        values = v1DBasinSubMod(location, zInd, subModel1D);
//    }
//    else if((strcmp(upperSurfName, "PlioceneTop") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
//    {
//        values = plioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "MioceneTop") == 0) && strcmp(lowerSurfName, "PaleogeneTop") == 0)
//    {
//        values = mioceneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "PaleogeneTop") == 0) && strcmp(lowerSurfName, "BasementTop") == 0)
//    {
//        values = paleogeneSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "BPVTop") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
//    {
//        values = BPVSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else if((strcmp(upperSurfName, "BPVTopWheathered") == 0) && strcmp(lowerSurfName, "MioceneTop") == 0)
//    {
//        values = WheatheredBPVSubModel(location, basinData, xInd, yInd, zInd, basinNum);
//    }
//    else
//    {
//        printf("error\n");
//    }
//    
//    basinData->Vp[basinNum][xInd][yInd][zInd] = values->Vp;
//    basinData->Vs[basinNum][xInd][yInd][zInd] = values->Vs;
//    basinData->Rho[basinNum][xInd][yInd][zInd] = values->Rho;
//    free(values);
//}
//
//
//
//void assignBasinProperties(gridStruct *location, int basinNum, globalBasinData *basinData)
//{
//    // load 1D velo model
//    velo1D *velocityModel1DBasinData = NULL;
//    velocityModel1DBasinData = loadv1DsubMod();
//    
//    // calculate the properties for all points inside the basin
//    for(int i = 0; i < location->nX; i++)
//    {
//        for(int j = 0; j < location->nY; j++)
//        {
//            if(basinData->inBasinLatLon[basinNum][basinData->nBoundaries[basinNum]-1][i][j] == 1) // in basin lat lon (wider boundary)
//            {
//                for(int k = 0; k < location->nZ; k++)
//                {
//                    if(basinData->inBasinDep[basinNum][i][j][k] == 1) // in basin Z limits
//                    {
//                        determineBasinProperties(basinData, basinNum, i, j, k, location, velocityModel1DBasinData);
//                    }
//                }
//            }
//        }
////        printf("Completed calculation of basin properties at latitude %i of %i.\n", i+1, location->nX);
//        printf("\rAssigning basin properties %d%% complete.", i*100/location->nX);
//        fflush(stdout);
//    }
//    printf("\rAssigning basin properties 100%% complete.");
//    fflush(stdout);
//    printf("\n");
//    printf("Basin data successfully calculated.\n");
//    free(velocityModel1DBasinData);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

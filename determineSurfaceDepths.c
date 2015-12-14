//
//  determineSurfaceDepths.c
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


partial_global_surface_depths *interpolateGlobalSurfaceDepths(global_surfaces *GLOBAL_SURFACES, mesh_vector *MESH_VECTOR ,calculation_log *CALCULATION_LOG)
/*
 Purpose:   obtain the depths for all lat lon points for a given surface file
 
 Input variables:
 location  - structure containing lat lon grid
 fileName  - filename of the surface file for reading
 
 Output variables:
 surfDep   - (malloc'd) pointer to structure containing surface depths for all lat lon points
 */
{
    adjacent_points *ADJACENT_POINTS;
    global_surf_read *GLOBAL_SURF_READ;
    partial_global_surface_depths *PARTIAL_GLOBAL_SURFACE_DEPTHS;
    PARTIAL_GLOBAL_SURFACE_DEPTHS = malloc(sizeof(partial_global_surface_depths));
    
    double p1, p2, p3, v1, v2;
    double X1, X2, Y1, Y2, Q11, Q12, Q21, Q22, X, Y;


    
    for(int i = 0; i < GLOBAL_SURFACES->nSurf; i++)
    {
        GLOBAL_SURF_READ = GLOBAL_SURFACES->surf[i];
        ADJACENT_POINTS = findGlobalAdjacentPoints(GLOBAL_SURF_READ, *MESH_VECTOR->Lat, *MESH_VECTOR->Lon);
        
        if (ADJACENT_POINTS->inSurfaceBounds == 1)
        {
            // interpolate
            X1 = GLOBAL_SURF_READ->loni[ADJACENT_POINTS->lonInd[0]];
            X2 = GLOBAL_SURF_READ->loni[ADJACENT_POINTS->lonInd[1]];
            Y1 = GLOBAL_SURF_READ->lati[ADJACENT_POINTS->latInd[0]];
            Y2 = GLOBAL_SURF_READ->lati[ADJACENT_POINTS->latInd[1]];
            Q11 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[0]][ADJACENT_POINTS->latInd[0]];
            Q12 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[0]][ADJACENT_POINTS->latInd[1]];
            Q21 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[1]][ADJACENT_POINTS->latInd[0]];
            Q22 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[1]][ADJACENT_POINTS->latInd[1]];
            X = *MESH_VECTOR->Lon;
            Y = *MESH_VECTOR->Lat;
            PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i] =  biLinearInterpolation(X1, X2, Y1, Y2, Q11, Q12, Q21, Q22, X, Y);
            
        }
        else if (ADJACENT_POINTS->inLatExtensionZone == 1)
        {
            p1 = GLOBAL_SURF_READ->loni[ADJACENT_POINTS->lonInd[0]];
            p2 = GLOBAL_SURF_READ->loni[ADJACENT_POINTS->lonInd[1]];
            v1 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[0]][ADJACENT_POINTS->latEdgeInd];
            v2 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonInd[1]][ADJACENT_POINTS->latEdgeInd];
            p3 = *MESH_VECTOR->Lon;
            PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i] = linearInterpolation(p1, p2, v1, v2, p3);
            CALCULATION_LOG->nPointsInGlobalLatSurfaceExtensionZone += 1;
        }
        else if (ADJACENT_POINTS->inLonExtensionZone == 1)
        {
            p1 = GLOBAL_SURF_READ->lati[ADJACENT_POINTS->latInd[0]];
            p2 = GLOBAL_SURF_READ->lati[ADJACENT_POINTS->latInd[1]];
            v1 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonEdgeInd][ADJACENT_POINTS->latInd[0]];
            v2 = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->lonEdgeInd][ADJACENT_POINTS->latInd[1]];
            p3 = *MESH_VECTOR->Lat;
            PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i] = linearInterpolation(p1, p2, v1, v2, p3);
            CALCULATION_LOG->nPointsInGlobalLonSurfaceExtensionZone += 1;
        }
        else if (ADJACENT_POINTS->inCornerZone == 1)
        {
            PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i] = GLOBAL_SURF_READ->raster[ADJACENT_POINTS->cornerLonInd][ADJACENT_POINTS->cornerLatInd];
            CALCULATION_LOG->nPointsInGlobalCornerSurfaceExtensionZone += 1;
        }

        free(ADJACENT_POINTS);
    }
    double topVal, botVal;
    
    PARTIAL_GLOBAL_SURFACE_DEPTHS->nSurfDep = GLOBAL_SURFACES->nSurf;
    for(int i = GLOBAL_SURFACES->nSurf -1 ; i > 0; i--)
    {
        // enforce surface depths from bottom down
        
        topVal = PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i-1];
        botVal = PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i];
        
        if(topVal < botVal)
        {
            PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i] = PARTIAL_GLOBAL_SURFACE_DEPTHS->dep[i-1];
            CALCULATION_LOG->nPointsGlobalSurfacesEnforced += 1;

        }
        
    }
        
    return PARTIAL_GLOBAL_SURFACE_DEPTHS;
}

//surfDepValues *determineSurfaceDepthsBasin(globalBasinData *basinData ,gridStruct *location, char *fileName, int basinNum, int surfNum)
///*
// Purpose:   obtain the depths for all lat lon points within the  for a given surface file
// 
// Input variables:
// location  - structure containing lat lon grid
// fileName  - filename of the surface file for reading
// 
// Output variables:
// surfDep   - (malloc'd) pointer to structure containing surface depths for all lat lon points
// */
//{
//    // read in the filename
//    surfRead *currentSurface;
//    currentSurface = loadSurface(fileName);
//    
//    surfDepValues *surfDep;
//    surfDep = malloc(sizeof(surfDepValues));
//    adjacentPointsStruct *points;
//    
//    // loop over values and find the depth of the surface at all points (2D interpolation)
//    for(int i = 0; i < location->nX; i++)
//    {
//        for(int j = 0; j < location->nY; j++)
//        {
//            if(basinData->inBasinLatLon[basinNum][basinData->boundaryType[basinNum][surfNum]][i][j] == 1)
//            {
//                // find adjacent points
//                points = findAdjacentPoints(currentSurface, location->Lat[i][j], location->Lon[i][j]);
//                //                printf("%lf %lf\n",location->Lat[i][j], location->Lon[i][j]);
//                //                printf("%i\n",basinData->inBasinLatLon[basinNum][basinData->boundaryType[basinNum][surfNum]][i][j]);
//                
//                if (points->inSurfaceBounds == 1)
//                {
//                    // interpolate
//                    surfDep->dep[i][j] = biLinearInterpolation( currentSurface->loni[points->lonInd[0]], currentSurface->loni[points->lonInd[1]], currentSurface->lati[points->latInd[0]], currentSurface->lati[points->latInd[1]], currentSurface->raster[points->lonInd[0]][points->latInd[0]], currentSurface->raster[points->lonInd[0]][points->latInd[1]], currentSurface->raster[points->lonInd[1]][points->latInd[0]], currentSurface->raster[points->lonInd[1]][points->latInd[1]], location->Lon[i][j], location->Lat[i][j]);
//                    free(points);
//                }
//                else
//                {
//                    printf("%lf %lf\n",location->Lat[i][j], location->Lon[i][j]);
//
//                    printf("Error, point lies outside basin surface domain.\n");
//                }
//            }
//            else
//            {
//                surfDep->dep[i][j] = NAN; // define as NAN if surface is outside of the boundary
//            }
//        }
//    }
//    free(currentSurface);
//    
//    return surfDep;
//}

//
//  IDW.c
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

adjacentPointsStruct *findAdjacentPoints(surfRead *surface, double lat, double lon)
{
    adjacentPointsStruct *points;
    points = malloc(sizeof(adjacentPointsStruct));
    
    int latAssignedFlag = 0;
    int lonAssignedFlag = 0;
    for( int i = 0; i < surface->nLat; i++)
    {
        if(surface->lati[i] >= lat)
        {
            if (i==0)
            {
                break;
            }
            points->latInd[0]= i-1;
            points->latInd[1] = i;
            latAssignedFlag = 1;
            //printf("%lf %lf %lf\n",surface->lati[points.latInd[0]],lat,surface->lati[points.latInd[1]]);
            break;
            
        }
    }
    if(latAssignedFlag == 0) // to account for some surface file vectors of lat long being ascending not descending
    {
        for(int i = surface->nLat-1; i > 0; i--)
        {
            if(surface->lati[i] >= lat)
            {
                if (i==surface->nLat-1)
                {
                    break;
                }
                points->latInd[0]= i;
                points->latInd[1] = i+1;
                latAssignedFlag = 1;
                //printf("%lf %lf %lf\n",surface->lati[points.latInd[0]],lat,surface->lati[points.latInd[1]]);
                break;
                
            }
        }
    }
    for( int j = 0; j < surface->nLon; j++)
    {
        if(surface->loni[j] >= lon)
        {
            if (j==0)
            {
                break;
            }
            points->lonInd[0] = j-1;
            points->lonInd[1] = j;
            lonAssignedFlag = 1;
            //printf("%lf %lf %lf\n",surface->loni[points.lonInd[0]],lon,surface->loni[points.lonInd[1]]);
            break;
        }
    }
    if (lonAssignedFlag == 0)
    {
        //printf("%i\n",surface->nLon-1);
        for( int j = surface->nLon-1; j > 0; j--)
        {
           //printf("%lf %i\n",surface->loni[j],j);
            if(surface->loni[j] >= lon)
            {
                if (j==surface->nLon-1)
                {
                    break;
                }
                points->lonInd[0] = j;
                points->lonInd[1] = j+1;
                lonAssignedFlag = 1;
//                printf("%lf %lf %lf\n",surface->loni[points.lonInd[0]],lon,surface->loni[points.lonInd[1]]);
                break;
            }
        }
    }
    
    
    
//    if((surface->loni[points.lonInd[0]] >= lon) && (surface->loni[points.lonInd[1]] <= lon))
//    {
//        
//    }
//    else if((surface->loni[points.lonInd[1]] >= lon) && (surface->loni[points.lonInd[0]] <= lon))
//    {
//        
//    }
//    else if((surface->lati[points.latInd[1]] >= lat) && (surface->lati[points.latInd[0]] <= lat))
//    {
//        
//    }
//    else if((surface->lati[points.latInd[0]] >= lat) && (surface->lati[points.latInd[1]] <= lat))
//    {
//        
//    }
//    else
//    {
//        printf("Error.\n");
//    }
    
//    printf("%i %i %i %i\n",points.latInd[0], points.latInd[1], points.lonInd[0], points.lonInd[1] );
//    printf ("%lf %lf\n",lat,lon);
    if((points->lonInd[0]==-1)||(points->latInd[0]==-1)||(latAssignedFlag != 1)||(lonAssignedFlag !=1)) // if any indicies are unassigned
    {
        points->inLatExtensionZone = 0;
        points->inLonExtensionZone = 0;
        if((lonAssignedFlag == 1) && (latAssignedFlag == 0)) // longitude assigned
        {
            // check if point is within extended latitude limits
            if((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION)
            {
                points->inLatExtensionZone = 1;
                findEdgeInds(surface, points,1);
            }
            else if((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION)
            {
                points->inLatExtensionZone = 1;
                findEdgeInds(surface, points,3);
            }
        }
        
        if((latAssignedFlag == 1) && (lonAssignedFlag == 0)) // latitude assigned
        {
            // check if the point is within extended longitude limits
            if((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION)
            {
                points->inLonExtensionZone = 1;
                findEdgeInds(surface, points,4);

            }
            else if((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION)
            {
                points->inLonExtensionZone = 1;
                findEdgeInds(surface, points,2);

            }
        }
        
        // four cases for corner zones
        //printf("%lf %lf\n", lat, lon);
        if(((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= surface->minLon) && (lat >= surface->maxLat))
        {
            // top left
            findCornerInds(surface, surface->maxLat, surface->minLon, points);
        }
        else if (((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= surface->maxLon) && (lat >= surface->maxLat) )
        {
            // top right
            findCornerInds(surface, surface->maxLat, surface->maxLon, points);
        }
        else if (((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= surface->minLon) && (lat <= surface->minLat))
        {
            // bottom left
            findCornerInds(surface, surface->minLat, surface->minLon, points);
        }
        else if (((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= surface->maxLon) && (lat <= surface->minLat))
        {
            // bottom right
            findCornerInds(surface, surface->minLat, surface->maxLon, points);
        }

//        if((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION)
//        {
//            int k = surface->minLat - lat ;
//        }
//        
//        if ((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION)
//        {
//            int g = 1;
//        }
//        
//        if (lon > surface->maxLon)
//        {
//            int hh = 1;
//        }
//        if (lat < surface->minLat)
//        {
//            int kk = 10;
//        }
//        
    }
    else
    {
        points->inSurfaceBounds = 1;
    }
    
    
//    printf("Error, adjacent points incorrect\n");
    
    

    return points;
}


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

adjacent_points *findGLobalAdjacentPoints(surfRead *surface, double lat, double lon)
{
    adjacent_points *ADJACENT_POINTS;
    ADJACENT_POINTS = malloc(sizeof(adjacent_points));
    
    int latAssignedFlag = 0;
    int lonAssignedFlag = 0;
    ADJACENT_POINTS->inSurfaceBounds = 0;
    for( int i = 0; i < surface->nLat; i++)
    {
        if(surface->lati[i] >= lat)
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
        for(int i = surface->nLat-1; i > 0; i--)
        {
            if(surface->lati[i] >= lat)
            {
                if (i==surface->nLat-1)
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
    for( int j = 0; j < surface->nLon; j++)
    {
        if(surface->loni[j] >= lon)
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
        for( int j = surface->nLon-1; j > 0; j--)
        {
            if(surface->loni[j] >= lon)
            {
                if (j==surface->nLon-1)
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
        ADJACENT_POINTS->inLatExtensionZone = 0;
        ADJACENT_POINTS->inLonExtensionZone = 0;
        ADJACENT_POINTS->inCornerZone = 0;
        if((lonAssignedFlag == 1) && (latAssignedFlag == 0)) // longitude assigned
        {
            // check if point is within extended latitude limits
            if((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION && (lat >= surface->maxLat))
            {
                ADJACENT_POINTS->inLatExtensionZone = 1;
                findEdgeInds(surface, ADJACENT_POINTS,1);
            }
            else if((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION && (lat <= surface->minLat))
            {
                ADJACENT_POINTS->inLatExtensionZone = 1;
                findEdgeInds(surface, ADJACENT_POINTS,3);
            }
        }
        
        if((latAssignedFlag == 1) && (lonAssignedFlag == 0)) // latitude assigned
        {
            // check if the point is within extended longitude limits
            if((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION && (lon <= surface->minLon))
            {
                ADJACENT_POINTS->inLonExtensionZone = 1;
                findEdgeInds(surface, ADJACENT_POINTS,4);

            }
            else if((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION && (lon >=surface->maxLon))
            {
                ADJACENT_POINTS->inLonExtensionZone = 1;
                findEdgeInds(surface, ADJACENT_POINTS,2);

            }
        }
        
        // four cases for corner zones
        if(((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= surface->minLon) && (lat >= surface->maxLat))
        {
            // top left
            findCornerInds(surface, surface->maxLat, surface->minLon, ADJACENT_POINTS);
        }
        else if (((lat - surface->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= surface->maxLon) && (lat >= surface->maxLat) )
        {
            // top right
            findCornerInds(surface, surface->maxLat, surface->maxLon, ADJACENT_POINTS);
        }
        else if (((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((surface->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= surface->minLon) && (lat <= surface->minLat))
        {
            // bottom left
            findCornerInds(surface, surface->minLat, surface->minLon, ADJACENT_POINTS);
        }
        else if (((surface->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - surface->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= surface->maxLon) && (lat <= surface->minLat))
        {
            // bottom right
            findCornerInds(surface, surface->minLat, surface->maxLon, ADJACENT_POINTS);
        }
    }
    else
    {
        ADJACENT_POINTS->inSurfaceBounds = 1;
    }
    
    return ADJACENT_POINTS;
}


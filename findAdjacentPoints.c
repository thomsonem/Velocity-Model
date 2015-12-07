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

adjacent_points *findGlobalAdjacentPoints(surface_pointer *SURFACE_POINTER, double lat, double lon)
{
    adjacent_points *ADJACENT_POINTS;
    ADJACENT_POINTS = malloc(sizeof(adjacent_points));
    
    int latAssignedFlag = 0;
    int lonAssignedFlag = 0;
    ADJACENT_POINTS->inSurfaceBounds = 0;
    for( int i = 0; i < *SURFACE_POINTER->nLat; i++)
    {
        if(*SURFACE_POINTER->lati[i] >= lat)
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
        for(int i = *SURFACE_POINTER->nLat-1; i > 0; i--)
        {
            if(*SURFACE_POINTER->lati[i] >= lat)
            {
                if (i==*SURFACE_POINTER->nLat-1)
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
    for( int j = 0; j < *SURFACE_POINTER->nLon; j++)
    {
        if(*SURFACE_POINTER->loni[j] >= lon)
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
        for( int j = *SURFACE_POINTER->nLon-1; j > 0; j--)
        {
            if(*SURFACE_POINTER->loni[j] >= lon)
            {
                if (j==*SURFACE_POINTER->nLon-1)
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
            if((lat - *SURFACE_POINTER->maxLat) <= MAX_LAT_SURFACE_EXTENSION && (lat >= *SURFACE_POINTER->maxLat))
            {
                ADJACENT_POINTS->inLatExtensionZone = 1;
                findEdgeInds(SURFACE_POINTER, ADJACENT_POINTS,1);
            }
            else if((*SURFACE_POINTER->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION && (lat <= *SURFACE_POINTER->minLat))
            {
                ADJACENT_POINTS->inLatExtensionZone = 1;
                findEdgeInds(SURFACE_POINTER, ADJACENT_POINTS,3);
            }
        }
        
        if((latAssignedFlag == 1) && (lonAssignedFlag == 0)) // latitude assigned
        {
            // check if the point is within extended longitude limits
            if((*SURFACE_POINTER->minLon - lon) <= MAX_LON_SURFACE_EXTENSION && (lon <= *SURFACE_POINTER->minLon))
            {
                ADJACENT_POINTS->inLonExtensionZone = 1;
                findEdgeInds(SURFACE_POINTER, ADJACENT_POINTS,4);

            }
            else if((lon - *SURFACE_POINTER->maxLon) <= MAX_LON_SURFACE_EXTENSION && (lon >=*SURFACE_POINTER->maxLon))
            {
                ADJACENT_POINTS->inLonExtensionZone = 1;
                findEdgeInds(SURFACE_POINTER, ADJACENT_POINTS,2);

            }
        }
        
        // four cases for corner zones
        if(((lat - *SURFACE_POINTER->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((*SURFACE_POINTER->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= *SURFACE_POINTER->minLon) && (lat >= *SURFACE_POINTER->maxLat))
        {
            // top left
            findCornerInds(SURFACE_POINTER, *SURFACE_POINTER->maxLat, *SURFACE_POINTER->minLon, ADJACENT_POINTS);
        }
        else if (((lat - *SURFACE_POINTER->maxLat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - *SURFACE_POINTER->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= *SURFACE_POINTER->maxLon) && (lat >= *SURFACE_POINTER->maxLat) )
        {
            // top right
            findCornerInds(SURFACE_POINTER, *SURFACE_POINTER->maxLat, *SURFACE_POINTER->maxLon, ADJACENT_POINTS);
        }
        else if (((*SURFACE_POINTER->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((*SURFACE_POINTER->minLon - lon) <= MAX_LON_SURFACE_EXTENSION) && (lon <= *SURFACE_POINTER->minLon) && (lat <= *SURFACE_POINTER->minLat))
        {
            // bottom left
            findCornerInds(SURFACE_POINTER, *SURFACE_POINTER->minLat, *SURFACE_POINTER->minLon, ADJACENT_POINTS);
        }
        else if (((*SURFACE_POINTER->minLat - lat) <= MAX_LAT_SURFACE_EXTENSION) && ((lon - *SURFACE_POINTER->maxLon) <= MAX_LON_SURFACE_EXTENSION) && (lon >= *SURFACE_POINTER->maxLon) && (lat <= *SURFACE_POINTER->minLat))
        {
            // bottom right
            findCornerInds(SURFACE_POINTER, *SURFACE_POINTER->minLat, *SURFACE_POINTER->maxLon, ADJACENT_POINTS);
        }
    }
    else
    {
        ADJACENT_POINTS->inSurfaceBounds = 1;
    }
    
    return ADJACENT_POINTS;
}




void findEdgeInds(surface_pointer *SURFACE_POINTER, adjacent_points *ADJACENT_POINTS, int edgeType)
{
    if (edgeType == 1)
    {
        if(*SURFACE_POINTER->maxLat == *SURFACE_POINTER->lati[0])
        {
            ADJACENT_POINTS->latEdgeInd = 0;
        }
        else if (*SURFACE_POINTER->maxLat == *SURFACE_POINTER->lati[*SURFACE_POINTER->nLat-1])
        {
            ADJACENT_POINTS->latEdgeInd = *SURFACE_POINTER->nLat-1;
        }
        else
        {
            printf("Error.\n");
        }
    }
    else if (edgeType == 3)
    {
        if(*SURFACE_POINTER->minLat == *SURFACE_POINTER->lati[0])
        {
            ADJACENT_POINTS->latEdgeInd = 0;
        }
        else if (*SURFACE_POINTER->minLat == *SURFACE_POINTER->lati[*SURFACE_POINTER->nLat-1])
        {
            ADJACENT_POINTS->latEdgeInd = *SURFACE_POINTER->nLat-1;
        }
        else
        {
            printf("Error.\n");
        }
    }
    else if (edgeType == 2)
    {
        if(*SURFACE_POINTER->maxLon == *SURFACE_POINTER->loni[0])
        {
            ADJACENT_POINTS->lonEdgeInd = 0;
        }
        else if (*SURFACE_POINTER->maxLon == *SURFACE_POINTER->loni[*SURFACE_POINTER->nLon-1])
        {
            ADJACENT_POINTS->lonEdgeInd = *SURFACE_POINTER->nLon-1;
        }
        else
        {
            printf("Error.\n");
        }
    }
    else if (edgeType == 4)
    {
        if(*SURFACE_POINTER->minLon == *SURFACE_POINTER->loni[0])
        {
            ADJACENT_POINTS->lonEdgeInd = 0;
        }
        else if (*SURFACE_POINTER->minLon == *SURFACE_POINTER->loni[*SURFACE_POINTER->nLon-1])
        {
            ADJACENT_POINTS->lonEdgeInd = *SURFACE_POINTER->nLon-1;
        }
        else
        {
            printf("Error.\n");
        }
    }
    else
    {
        printf("Error.\n");
    }
    
}

void findCornerInds(surface_pointer *SURFACE_POINTER, double latPt, double lonPt, adjacent_points *ADJACENT_POINTS)
{
    if(latPt == *SURFACE_POINTER->lati[0])
    {
        ADJACENT_POINTS->cornerLatInd = 0;
    }
    else if (latPt == *SURFACE_POINTER->lati[*SURFACE_POINTER->nLat-1])
    {
        ADJACENT_POINTS->cornerLatInd = *SURFACE_POINTER->nLat-1;
    }
    else
    {
        printf("Error.\n");
    }
    
    if(lonPt == *SURFACE_POINTER->loni[0])
    {
        ADJACENT_POINTS->cornerLonInd = 0;
    }
    else if (lonPt == *SURFACE_POINTER->loni[*SURFACE_POINTER->nLon-1])
    {
        ADJACENT_POINTS->cornerLonInd = *SURFACE_POINTER->nLon-1;
    }
    else
    {
        printf("Error.\n");
    }
    
    ADJACENT_POINTS->inCornerZone = 1;
    
}



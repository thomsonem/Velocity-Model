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

adjacentPointsStruct findAdjacentPoints(surfRead *surface, double lat, double lon)
{
    adjacentPointsStruct points;
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
            points.latInd[0]= i-1;
            points.latInd[1] = i;
            latAssignedFlag = 1;
            //printf("%lf %lf %lf\n",surface->lati[points.latInd[0]],lat,surface->lati[points.latInd[1]]);
            break;
            
        }
    }
    if(latAssignedFlag == 0) // to account for some surface file vectors of lat long being ascending not descending
    {
        for( int i = surface->nLat-1; i > 0; i--)
        {
            if(surface->lati[i] >= lat)
            {
                points.latInd[0]= i;
                points.latInd[1] = i+1;
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
            points.lonInd[0] = j-1;
            points.lonInd[1] = j;
            lonAssignedFlag = 1;
            //printf("%lf %lf %lf\n",surface->loni[points.lonInd[0]],lon,surface->loni[points.lonInd[1]]);
            break;
        }
    }
    if (lonAssignedFlag == 0)
    {
        for( int j = surface->nLon-1; j > surface->nLon; j--)
        {
            if(surface->loni[j] >= lon)
            {
                points.lonInd[0] = j;
                points.lonInd[1] = j+1;
                lonAssignedFlag = 1;
//                printf("%lf %lf %lf\n",surface->loni[points.lonInd[0]],lon,surface->loni[points.lonInd[1]]);
                break;
            }
        }
    }
    
    if((points.lonInd[0]==-1)||(points.latInd[0]==-1)||(latAssignedFlag != 1)||(lonAssignedFlag !=1))
    {
        printf("Error, lat lon point outside the bounds of the surface file\n");
    }
    return points;
}


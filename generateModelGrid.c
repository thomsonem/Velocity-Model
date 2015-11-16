//
//  generateModelGrid.c
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

global_mesh *generateFullModelGrid(model_extent MODEL_EXTENT)
/*
 Purpose:   generate the grid of lat long and dep points
 
 Input variables:
 modelOrigin        - struct containing the origin and rotation of the model
 MODEL_EXTENT        - struct containing the extent, spacing and version of the model.
 
 Output variables:
 GLOBAL_MESH      - (malloc'd) pointer to structure containing lat lon and dep points
 
 */
{
    global_mesh *GLOBAL_MESH;
    GLOBAL_MESH = malloc(sizeof(global_mesh));
    // determine number of points in each orthogonal direction
	int nX = 2*MODEL_EXTENT.Xmax/MODEL_EXTENT.hLatLon;
	int nY = 2*MODEL_EXTENT.Ymax/MODEL_EXTENT.hLatLon;
	int nZ = (MODEL_EXTENT.Zmax-MODEL_EXTENT.Zmin)/MODEL_EXTENT.hDep;
    GLOBAL_MESH->maxLat = -180;
    GLOBAL_MESH->minLat = 0;
    GLOBAL_MESH->maxLon = 0;
    GLOBAL_MESH->minLon = 180;
    
    // esnure the number of points does not exceed that of the struct preallocation
	printf("nx: %i, ny: %i, nz: %i.\n", nX, nY, nZ);
    assert(nX<=LON_GRID_DIM_MAX);
    assert(nY<=LAT_GRID_DIM_MAX);
    assert(nZ<=DEP_GRID_DIM_MAX);
    
    //write values to the struct
    GLOBAL_MESH->nX = nX;
    GLOBAL_MESH->nY = nY;
    GLOBAL_MESH->nZ = nZ; 
    
	double X[LON_GRID_DIM_MAX], Y[LAT_GRID_DIM_MAX], Z[DEP_GRID_DIM_MAX];
    
    // loop over x y z arrays to insert values
	for(int i = 0; i < nX; i++)
	{
		X[i] = -1*MODEL_EXTENT.Xmax + MODEL_EXTENT.hLatLon*(i+0.5);
        GLOBAL_MESH->X[i] = X[i];
	}
    
    for(int i = 0; i < nY; i++)
	{
		Y[i] = -1*MODEL_EXTENT.Ymax + MODEL_EXTENT.hLatLon*(i+0.5);
        GLOBAL_MESH->Y[i] = Y[i];
	}
    
    for(int i = 0; i < nZ; i++)
	{
		Z[i] = MODEL_EXTENT.Zmin + MODEL_EXTENT.hDep*(i+0.5);
	}
    
    double locationXY[2];
    // calculate and insert values into struct
    singleGridPoint points;
    for(int ix = 0; ix < nX; ix++) //nX
    {
        for(int iy = 0; iy < nY; iy++) //xY
        {
            locationXY[0] = X[ix];
            locationXY[1] = Y[iy];
            
            points = XYtoLatLon(locationXY, MODEL_EXTENT.originLat, MODEL_EXTENT.originLon, MODEL_EXTENT.originRot);
            // determin the maximum lat long points of the model grid
            if( GLOBAL_MESH->maxLat < points.lat)
            {
                GLOBAL_MESH->maxLat = points.lat;
            }
            if( GLOBAL_MESH->maxLon < points.lon)
            {
                GLOBAL_MESH->maxLon = points.lon;
            }
            if( GLOBAL_MESH->minLat > points.lat)
            {
                GLOBAL_MESH->minLat = points.lat;
            }
            if( GLOBAL_MESH->minLon > points.lon)
            {
                GLOBAL_MESH->minLon = points.lon;
            }
            GLOBAL_MESH->Lat[ix][iy] = points.lat;
            GLOBAL_MESH->Lon[ix][iy] = points.lon;
        }
    }
    
    for(int iz = 0; iz < nZ; iz++)
    {
        GLOBAL_MESH->Z[iz] = -1000*Z[iz]; // convert to m (below ground is negative)
    }
    printf("Completed Generation of Model Grid.\n");
    return *GLOBAL_MESH;
}



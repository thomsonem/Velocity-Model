//
//  extractPartialMesh.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 16/11/15.
//  Copyright (c) 2015 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"


partial_global_mesh *extractPartialMesh(global_mesh *GLOBAL_MESH, int latInd)
{
    partial_global_mesh *PARTIAL_GLOBAL_MESH;
    PARTIAL_GLOBAL_MESH = malloc(sizeof(partial_global_mesh));
    if(PARTIAL_GLOBAL_MESH == NULL)
    {
        printf("Memory allocation failed partial global data array.\n");
    }
    
    int i;
    
    PARTIAL_GLOBAL_MESH->nX = GLOBAL_MESH->nX;
    PARTIAL_GLOBAL_MESH->nY = GLOBAL_MESH->nY;
    PARTIAL_GLOBAL_MESH->nZ = GLOBAL_MESH->nZ;
    PARTIAL_GLOBAL_MESH->Y = GLOBAL_MESH->Y[latInd];

    for(i = 0; i < GLOBAL_MESH->nZ; i ++)
    {
        PARTIAL_GLOBAL_MESH->Z[i] = GLOBAL_MESH->Z[i];
    }
    for(i = 0; i < GLOBAL_MESH->nX; i ++)
    {
        PARTIAL_GLOBAL_MESH->Lon[i] = GLOBAL_MESH->Lon[i][latInd];
        PARTIAL_GLOBAL_MESH->Lat[i] = GLOBAL_MESH->Lat[i][latInd];
        PARTIAL_GLOBAL_MESH->X[i] = GLOBAL_MESH->X[i];
    }
    return PARTIAL_GLOBAL_MESH;
}

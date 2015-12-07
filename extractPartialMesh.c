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
    PARTIAL_GLOBAL_MESH->nY = 1;//GLOBAL_MESH->nY;
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

mesh_vector *extractMeshVector(partial_global_mesh *PARTIAL_GLOBAL_MESH, int lonInd)
{
    mesh_vector *MESH_VECTOR;
    MESH_VECTOR = malloc(sizeof(mesh_vector));
    
    MESH_VECTOR->Lat = &PARTIAL_GLOBAL_MESH->Lat[lonInd];
    MESH_VECTOR->Lon = &PARTIAL_GLOBAL_MESH->Lon[lonInd];
    
    for(int i = 0; i < PARTIAL_GLOBAL_MESH->nZ; i++)
    {
        MESH_VECTOR->Z[i] = &PARTIAL_GLOBAL_MESH->Z[i];
    }
    MESH_VECTOR->nZ = &PARTIAL_GLOBAL_MESH->nZ;
    
    return MESH_VECTOR;
}

surface_pointer *getGlobalSurfacePointer(global_surfaces *GLOBAL_SURFACES, int surfaceNumber)
{
    surface_pointer *SURFACE_POINTER;
    SURFACE_POINTER = malloc(sizeof(surface_pointer));
    
    for(int i = 0; i < GLOBAL_SURFACES->nLon[surfaceNumber]; i++)
    {
        for(int j = 0; j < GLOBAL_SURFACES->nLat[surfaceNumber]; j++)
        {
            SURFACE_POINTER->dep[i][j] = &GLOBAL_SURFACES->dep[surfaceNumber][i][j];
        }
    }
    
    for(int j = 0; j < GLOBAL_SURFACES->nLat[surfaceNumber]; j++)
    {
        SURFACE_POINTER->lati[j] = &GLOBAL_SURFACES->lati[surfaceNumber][j];
    }
    for(int i = 0; i < GLOBAL_SURFACES->nLon[surfaceNumber]; i++)
    {
        SURFACE_POINTER->loni[i] = &GLOBAL_SURFACES->loni[surfaceNumber][i];
    }
    
    SURFACE_POINTER->nLat = &GLOBAL_SURFACES->nLat[surfaceNumber];
    SURFACE_POINTER->nLon = &GLOBAL_SURFACES->nLon[surfaceNumber];
    SURFACE_POINTER->maxLat = &GLOBAL_SURFACES->maxLat[surfaceNumber];
    SURFACE_POINTER->maxLon = &GLOBAL_SURFACES->maxLon[surfaceNumber];
    SURFACE_POINTER->minLat = &GLOBAL_SURFACES->minLat[surfaceNumber];
    SURFACE_POINTER->minLon = &GLOBAL_SURFACES->minLon[surfaceNumber];

    
    return SURFACE_POINTER;
}

surface_pointer *getTomographySurfacePointer(nz_tomography_data *NZ_TOMOGRAPHY_DATA, int surfaceNumber, char *quality)
{
    surface_pointer *SURFACE_POINTER;
    SURFACE_POINTER = malloc(sizeof(surface_pointer));
    
    for(int i = 0; i < NZ_TOMOGRAPHY_DATA->nLon[surfaceNumber]; i++)
    {
        for(int j = 0; j < NZ_TOMOGRAPHY_DATA->nLat[surfaceNumber]; j++)
        {
            if (strcmp(quality, "Vp") == 0)
            {
                SURFACE_POINTER->dep[i][j] = &NZ_TOMOGRAPHY_DATA->Vp[surfaceNumber][i][j];

            }
            else if (strcmp(quality, "Vs") == 0)
            {
                SURFACE_POINTER->dep[i][j] = &NZ_TOMOGRAPHY_DATA->Vs[surfaceNumber][i][j];

            }
            else if (strcmp(quality, "Rho") == 0)
            {
                SURFACE_POINTER->dep[i][j] = &NZ_TOMOGRAPHY_DATA->Rho[surfaceNumber][i][j];
            }
        }
    }
    
    for(int j = 0; j < NZ_TOMOGRAPHY_DATA->nLat[surfaceNumber]; j++)
    {
        SURFACE_POINTER->lati[j] = &NZ_TOMOGRAPHY_DATA->lati[surfaceNumber][j];
    }
    for(int i = 0; i < NZ_TOMOGRAPHY_DATA->nLon[surfaceNumber]; i++)
    {
        SURFACE_POINTER->loni[i] = &NZ_TOMOGRAPHY_DATA->loni[surfaceNumber][i];
    }
    
    SURFACE_POINTER->nLat = &NZ_TOMOGRAPHY_DATA->nLat[surfaceNumber];
    SURFACE_POINTER->nLon = &NZ_TOMOGRAPHY_DATA->nLon[surfaceNumber];
    SURFACE_POINTER->maxLat = &NZ_TOMOGRAPHY_DATA->maxLat[surfaceNumber];
    SURFACE_POINTER->maxLon = &NZ_TOMOGRAPHY_DATA->maxLon[surfaceNumber];
    SURFACE_POINTER->minLat = &NZ_TOMOGRAPHY_DATA->minLat[surfaceNumber];
    SURFACE_POINTER->minLon = &NZ_TOMOGRAPHY_DATA->minLon[surfaceNumber];
    
    
    return SURFACE_POINTER;
}






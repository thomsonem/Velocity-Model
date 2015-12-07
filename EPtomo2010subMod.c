//
//  EPtomo2010subMod.c
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

void EPtomo2010subMod(int zInd, double dep, mesh_vector *MESH_VECTOR, qualities_vector *QUALITIES_VECTOR, nz_tomography_data *NZ_TOMOGRAPHY_DATA)
/*
 Purpose:   calculate the rho vp and vs values at a single lat long point for all the depths within this velocity submodel
 
 Input variables:
 depths         - pointer to a struct containing the references to which points lie within this velocity sub-model layer
 veloSubModNum  - the reference number of this velocity sub-model
 xInd           - the indice of the longitude point
 yInd           - the indice of the latitude point
 EPtomoData     - pointer to the Eberhart-Phillips 2010 tomography data
 
 Output variables:
 values         - struct containing the vp vs and rho values for all points within this velo sub-model
 
 */
{
    int count = 0;
    
    // find the indice of the first "surface" above the data point in question
    while(dep < NZ_TOMOGRAPHY_DATA->surfDeps[count]*1000)
    {
        count += 1;
    }
    int indAbove = count - 1;
    int indBelow = count;
    
    
    
    // loop over the depth points and obtain the vp vs and rho values using interpolation between "surfaces"
    adjacent_points *ADJACENT_POINTS_ABOVE;
    surface_pointer *SURFACE_POINTER_ABOVE;
    
    adjacent_points *ADJACENT_POINTS_BELOW;
    surface_pointer *SURFACE_POINTER_BELOW;
    
    char *quality = NULL;
    
    double X1b, X2b, Y1b, Y2b, Q11b, Q12b, Q21b, Q22b, X, Y;
    double X1a, X2a, Y1a, Y2a, Q11a, Q12a, Q21a, Q22a;
    double valAbove, valBelow;
    double depAbove, depBelow;
    double val;
    
    for( int i = 0; i < 3; i++)
    {
        if (i == 1)
        {
            quality = "Vp";

        }
        else if ( i == 2)
        {
            quality = "Vs";

        }
        else if (i == 3)
        {
            quality = "Rho";

        }
        SURFACE_POINTER_ABOVE = getTomographySurfacePointer(NZ_TOMOGRAPHY_DATA, indAbove, quality);
        ADJACENT_POINTS_ABOVE = findGlobalAdjacentPoints(SURFACE_POINTER_ABOVE, *MESH_VECTOR->Lat, *MESH_VECTOR->Lon);
        
        SURFACE_POINTER_BELOW = getTomographySurfacePointer(NZ_TOMOGRAPHY_DATA, indBelow, quality);
        ADJACENT_POINTS_BELOW = findGlobalAdjacentPoints(SURFACE_POINTER_BELOW, *MESH_VECTOR->Lat, *MESH_VECTOR->Lon);
        
        X1b = *SURFACE_POINTER_BELOW->loni[ADJACENT_POINTS_BELOW->lonInd[0]];
        X2b = *SURFACE_POINTER_BELOW->loni[ADJACENT_POINTS_BELOW->lonInd[1]];
        Y1b = *SURFACE_POINTER_BELOW->lati[ADJACENT_POINTS_BELOW->latInd[0]];
        Y2b = *SURFACE_POINTER_BELOW->lati[ADJACENT_POINTS_BELOW->latInd[1]];
        Q11b = *SURFACE_POINTER_BELOW->dep[ADJACENT_POINTS_BELOW->lonInd[0]][ADJACENT_POINTS_BELOW->latInd[0]];
        Q12b = *SURFACE_POINTER_BELOW->dep[ADJACENT_POINTS_BELOW->lonInd[0]][ADJACENT_POINTS_BELOW->latInd[1]];
        Q21b = *SURFACE_POINTER_BELOW->dep[ADJACENT_POINTS_BELOW->lonInd[1]][ADJACENT_POINTS_BELOW->latInd[0]];
        Q22b = *SURFACE_POINTER_BELOW->dep[ADJACENT_POINTS_BELOW->lonInd[1]][ADJACENT_POINTS_BELOW->latInd[1]];
        X = *MESH_VECTOR->Lon;
        Y = *MESH_VECTOR->Lat;
        
        
        X1a = *SURFACE_POINTER_ABOVE->loni[ADJACENT_POINTS_ABOVE->lonInd[0]];
        X2a = *SURFACE_POINTER_ABOVE->loni[ADJACENT_POINTS_ABOVE->lonInd[1]];
        Y1a = *SURFACE_POINTER_ABOVE->lati[ADJACENT_POINTS_ABOVE->latInd[0]];
        Y2a = *SURFACE_POINTER_ABOVE->lati[ADJACENT_POINTS_ABOVE->latInd[1]];
        Q11a = *SURFACE_POINTER_ABOVE->dep[ADJACENT_POINTS_ABOVE->lonInd[0]][ADJACENT_POINTS_ABOVE->latInd[0]];
        Q12a = *SURFACE_POINTER_ABOVE->dep[ADJACENT_POINTS_ABOVE->lonInd[0]][ADJACENT_POINTS_ABOVE->latInd[1]];
        Q21a = *SURFACE_POINTER_ABOVE->dep[ADJACENT_POINTS_ABOVE->lonInd[1]][ADJACENT_POINTS_ABOVE->latInd[0]];
        Q22a = *SURFACE_POINTER_ABOVE->dep[ADJACENT_POINTS_ABOVE->lonInd[1]][ADJACENT_POINTS_ABOVE->latInd[1]];
        
        valAbove = biLinearInterpolation(X1a, X2a, Y1a, Y2a, Q11a, Q12a, Q21a, Q22a, X, Y);
        valBelow = biLinearInterpolation(X1b, X2b, Y1b, Y2b, Q11b, Q12b, Q21b, Q22b, X, Y);
        
        
        depAbove = NZ_TOMOGRAPHY_DATA->surfDeps[indAbove]*1000;
        depBelow = NZ_TOMOGRAPHY_DATA->surfDeps[indBelow]*1000;
        val = linearInterpolation(depAbove, depBelow, valAbove, valBelow, dep);
        if (i == 1)
        {
            QUALITIES_VECTOR->Vp[zInd] = val;
            
        }
        else if ( i == 2)
        {
            QUALITIES_VECTOR->Vs[zInd] = val;
            
        }
        else if (i == 3)
        {
            QUALITIES_VECTOR->Rho[zInd] = val;
            
        }
        
    }
    
}

nz_tomography_data *loadEPtomoSurfaceData(char *tomoType)
/*
 Purpose:   read in the Eberhart-Phillips 2010 tomography dataset
 
 Input variables:
 location       - struct containing the lat lon and dep points
 
 Output variables:
 surfDepVals    - (malloc'd) pointer to a struct containing the values of the "surfaces" at each lat lon value 
 
 */
{
    const char *varNames[3];
    const char *directoryName;
    varNames[0] = "vp", varNames[1] = "vs", varNames[2] = "rho";
    int elev[30];
    
    int nElev;
    if(strcmp(tomoType, "2010_Full_South_Island") == 0)
    {
        nElev = 14;
        int elev[17] = {15, 1, -3, -8, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275};
        directoryName = "2010_Full_South_Island";

    }
    else if(strcmp(tomoType, "2010_Update_Canterbury") == 0)
    {
//        nElev = 21;
//        int elev[21] = {15, 1, -3, -5, -8, -11, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275, -370, -630};
//        directoryName = "2010_Update_Canterbury";

    }
    else if (strcmp(tomoType, "2010_Update_Hybrid") == 0)
    {
//        int nElev = 20;
//        int elev[20] = {10, 1, -5, -8, -11, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275, -370, -620};
//        directoryName = "2010_Update_Hybrid";

    }
    
    char baseFilename[256];
    
    nz_tomography_data *NZ_TOMOGRAPHY_DATA;
    NZ_TOMOGRAPHY_DATA = malloc(sizeof(nz_tomography_data));
    NZ_TOMOGRAPHY_DATA->nSurf = nElev;
    assert(NZ_TOMOGRAPHY_DATA->nSurf<=MAX_NUM_TOMO_SURFACES);
    
    global_surf_read *TOMO_TEMP_SURF;
    
    for(int i = 0; i < nElev; i++)
    {
        NZ_TOMOGRAPHY_DATA->surfDeps[i] = elev[i]; // depth in km
        for(int j = 0; j < 3; j++)
        {
            sprintf(baseFilename,"Data/Tomography/%s/surf_tomography_%s_elev%i.in",directoryName,varNames[j],elev[i]);
            // read the surface
            TOMO_TEMP_SURF = loadGlobalSurface(baseFilename);
            if (j == 0) // assume all surfaces for vp vs and rho have the same coordinates
            {
                // place in NZ_TOMOGRAPHY_DATA struct
                NZ_TOMOGRAPHY_DATA->nLat[i] =  TOMO_TEMP_SURF->nLat;
                NZ_TOMOGRAPHY_DATA->nLon[i] =  TOMO_TEMP_SURF->nLon;
                NZ_TOMOGRAPHY_DATA->maxLat[i] =  TOMO_TEMP_SURF->maxLat;
                NZ_TOMOGRAPHY_DATA->minLat[i] =  TOMO_TEMP_SURF->minLat;
                NZ_TOMOGRAPHY_DATA->maxLon[i] =  TOMO_TEMP_SURF->maxLon;
                NZ_TOMOGRAPHY_DATA->minLon[i] =  TOMO_TEMP_SURF->minLon;
                
                for( int nLat = 0; nLat < TOMO_TEMP_SURF->nLat; nLat++)
                {
                    NZ_TOMOGRAPHY_DATA->lati[i][nLat] = TOMO_TEMP_SURF->lati[nLat];
                }
                for( int nLon = 0; nLon < TOMO_TEMP_SURF->nLon; nLon++)
                {
                    NZ_TOMOGRAPHY_DATA->loni[i][nLon] = TOMO_TEMP_SURF->loni[nLon];
                }
            }
            for( int nnLat = 0; nnLat < TOMO_TEMP_SURF->nLat; nnLat++)
            {
                for( int nnLon = 0; nnLon < TOMO_TEMP_SURF->nLon; nnLon++)
                {
                    if (j == 0)
                    {
                        NZ_TOMOGRAPHY_DATA->Vp[i][nnLon][nnLat] =  TOMO_TEMP_SURF->raster[nnLon][nnLat];
                    }
                    else if (j == 1)
                    {
                        NZ_TOMOGRAPHY_DATA->Vs[i][nnLon][nnLat] =  TOMO_TEMP_SURF->raster[nnLon][nnLat];
                        
                    }
                    else if (j == 3)
                    {
                        NZ_TOMOGRAPHY_DATA->Rho[i][nnLon][nnLat] =  TOMO_TEMP_SURF->raster[nnLon][nnLat];
                        
                    }
                }
            }
            free(TOMO_TEMP_SURF);
        }
//        printf("\rReading tomography data %d%% complete.", i*100/nElev);
//        fflush(stdout);
    }
    return NZ_TOMOGRAPHY_DATA;
}


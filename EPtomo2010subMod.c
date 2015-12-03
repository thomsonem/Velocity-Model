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

//void EPtomo2010subMod(int xInd, int yInd, int zInd, globalDataValues *globalValues, gridStruct *location, depInterpVals *EPtomoData)
///*
// Purpose:   calculate the rho vp and vs values at a single lat long point for all the depths within this velocity submodel
// 
// Input variables:
// depths         - pointer to a struct containing the references to which points lie within this velocity sub-model layer
// veloSubModNum  - the reference number of this velocity sub-model
// xInd           - the indice of the longitude point
// yInd           - the indice of the latitude point
// EPtomoData     - pointer to the Eberhart-Phillips 2010 tomography data
// 
// Output variables:
// values         - struct containing the vp vs and rho values for all points within this velo sub-model
// 
// */
//{
//    int count = 0;
//    double p1, p2;
//    double Rho1, Rho2, Vp1, Vp2, Vs1, Vs2;
//    
//    // find the indice of the first "surface" above the data point in question
//    while(location->Z[zInd]<EPtomoData->deps[count]*1000)
//    {
//        count += 1;
//    }
//    
//    // loop over the depth points and obtain the vp vs and rho values using interpolation between "surfaces"
//
//    p1 = EPtomoData->deps[count-1]*1000;
//    p2 = EPtomoData->deps[count]*1000;
//    Rho1 = EPtomoData->Rho[count-1][xInd][yInd];
//    Rho2 = EPtomoData->Rho[count][xInd][yInd];
//    Vs1 = EPtomoData->Vs[count-1][xInd][yInd];
//    Vs2 = EPtomoData->Vs[count][xInd][yInd];
//    Vp1 = EPtomoData->Vp[count-1][xInd][yInd];
//    Vp2 = EPtomoData->Vp[count][xInd][yInd];
//    
//    globalValues->Rho[xInd][yInd][zInd] = linearInterpolation(p1, p2, Rho1, Rho2, location->Z[zInd]);
//    globalValues->Vs[xInd][yInd][zInd] = linearInterpolation(p1, p2, Vs1, Vs2, location->Z[zInd]);
//    globalValues->Vp[xInd][yInd][zInd] = linearInterpolation(p1, p2, Vp1, Vp2, location->Z[zInd]);
//    
//}

nz_tomography_data *loadEPtomoSurfaceData(void)
/*
 Purpose:   read in the Eberhart-Phillips 2010 tomography dataset
 
 Input variables:
 location       - struct containing the lat lon and dep points
 
 Output variables:
 surfDepVals    - (malloc'd) pointer to a struct containing the values of the "surfaces" at each lat lon value 
 
 */
{
    const char *varNames[3];
    varNames[0] = "vp", varNames[1] = "vs", varNames[2] = "rho";
    int nElev = 14; // only read first 14 for efficiency
    int elev[17] = {15, 1, -3, -8, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275};
    //    int elev[21] = {15, 1, -3, -5, -8, -11, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275, -370, -630};
    //int elev[20] = {10, 1, -5, -8, -11, -15, -23, -30, -38, -48, -65, -85, -105, -130, -155, -185, -225, -275, -370, -620};
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
            sprintf(baseFilename,"Data/Tomography/surf_tomography_%s_elev%i.in",varNames[j],elev[i]);
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


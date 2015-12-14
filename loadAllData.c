//
//  loadAllData.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/10/15.
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


void loadAllGlobalData(global_model_parameters *GLOBAL_MODEL_PARAMETERS,calculation_log *CALCULATION_LOG, velo_mod_1d_data *VELO_MOD_1D_DATA, nz_tomography_data *NZ_TOMOGRAPHY_DATA, global_surfaces *GLOBAL_SURFACES, basin_data *BASIN_DATA)
{
        // read in sub velocity models
        for( int i = 0; i < GLOBAL_MODEL_PARAMETERS->nVeloSubMod; i++)
        {
            if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "v1DsubMod") == 0)
            {
                load1dVeloSubModel(GLOBAL_MODEL_PARAMETERS->veloMod1dFileName[0], VELO_MOD_1D_DATA);
            }
            else if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "EPtomo2010subMod") == 0)
            {
                loadEPtomoSurfaceData(GLOBAL_MODEL_PARAMETERS->tomographyName, NZ_TOMOGRAPHY_DATA );
            }
            else if(strcmp(GLOBAL_MODEL_PARAMETERS->veloSubMod[i], "NaNsubMod") == 0)
            {
                // no data required for NaN velocity sub model, leave as placeholder
            }
        }
        // read in global surfaces
        loadGlobalSurfaceData(GLOBAL_SURFACES, GLOBAL_MODEL_PARAMETERS);

        // read in basin surfaces and boundaries
        loadBasinData(BASIN_DATA, GLOBAL_MODEL_PARAMETERS);
    
    printf("All data loaded.\n");

    
    
//    // read in basin data
//    globalBasinData *basinData;
//    basinData = malloc(sizeof(globalBasinData));
//    if(basinData == NULL)
//    {
//        printf("Memory allocation failed for basin data array.\n");
//    }
//    
//    for(int i = 0; i < surfSubModNames.nBasin; i++)
//    {
//        if(strcmp(surfSubModNames.basin[i], "CANTERBURY_BASIN") == 0)
//        {
//            loadCanterburyBasinData(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "PREQ_CANTERBURY_BASIN") == 0)
//        {
//            loadPreQCanterburyBasinData(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "PREQ_CANTERBURY_BASIN_1D") == 0)
//        {
//            loadPreQCanterburyBasinData1D(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "Q_CANTERBURY_BASIN") == 0)
//        {
//            loadQCanterburyBasinData(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "PALEO_CANTERBURY_BASIN") == 0)
//        {
//            loadPreQCanterburyBasinDataPaleogene(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "PALEO_MIO_CANTERBURY_BASIN") == 0)
//        {
//            loadPreQCanterburyBasinDataPaleogeneMiocene(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "BPV_BASIN") == 0)
//        {
//            loadBPVBasinData(location, i, basinData);
//        }
//        if(strcmp(surfSubModNames.basin[i], "BPV_BASIN_WHEATHERED") == 0)
//        {
//            loadBPVWheatheredBasinData(location, i, basinData);
//        }
//        
//    }
//    
    
}



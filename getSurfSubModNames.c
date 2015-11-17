//
//  getGLOBAL_MODEL_PARAMETERS->c
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

global_model_parameters *getGlobalModelParameters(double modelVersion)
/*
 Purpose:   obtain the names of the surfaces and sub velocity models to be used
 
 Input variables:
 modelVersion -  structure containing the version of the model for generation
 
 Output variables:
 surfNames    -  structure containing the names of the surfaces and sub velocity models to be used
 */
{
    global_model_parameters *GLOBAL_MODEL_PARAMETERS;
    GLOBAL_MODEL_PARAMETERS = malloc(sizeof(global_model_parameters));

    
//    fileName = "Data/Global_Surfaces/posInf.in";
//}
//else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "negInfSurf") == 0)
//{
//    fileName = "Data/Global_Surfaces/negInf.in";
//}
//else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "basementRockSurf") == 0)
//{
//    fileName ="Data/Canterbury_Basin/Pre_Quaternary/BasementTop.in";
//}
//else if(strcmp(GLOBAL_MODEL_PARAMETERS->surf[i], "demSurf") == 0)
//{
//    fileName = "Data/DEM/DEM.in";
//}
//else

//    char *basin[MAX_NUM_BASINS];
//    char *basinSurfFilenames[MAX_NUM_BASINS][MAX_NUM_BASIN_SURFACES];
//    char *basinSurfaceNames[MAX_NUM_BASINS][MAX_NUM_BASIN_SURFACES];
//    int nBasinSurfaces[MAX_NUM_BASINS];
//    int nBasinBoundaries[MAX_NUM_BASINS][MAX_NUM_BASIN_BOUNDARIES];
//    char *basinBoundaryFilenames[MAX_NUM_BASINS][MAX_NUM_BASIN_BOUNDARIES];
//    char *basinBoundaryNames[MAX_NUM_BASINS][MAX_NUM_BASIN_BOUNDARIES];
//    int nBasin;

    // Model Version 0.1, 1D velocity sub Model
    if(modelVersion == 0.1)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 2;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 1;
        
        // insert surface surface keywords and filenames
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->globalSurfFilenames[0] = "Data/Global_Surfaces/posInf.in";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "negInfSurf";
        GLOBAL_MODEL_PARAMETERS->globalSurfFilenames[1] = "Data/Global_Surfaces/negInf.in";
        
        // insert velocity submodel keywords and filenames (if necessary)
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloMod1dFileName[0] = "Cant1D_v1.fd_modfile";
        
        
        GLOBAL_MODEL_PARAMETERS->nBasins = 2;

        // CANTERBURY Basin
        GLOBAL_MODEL_PARAMETERS->basin[0] = "CANTERBURY_BASIN";
        GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[0] = 12;
        GLOBAL_MODEL_PARAMETERS->nBasinBoundaries[0] = 2;
        GLOBAL_MODEL_PARAMETERS->basinBoundaryFilenames[0][0] = "Data/Boundaries/QuaternarySurfacesBoundary.txt";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryFilenames[0][1] = "Data/Boundaries/CanterburyBasinBoundary.txt";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][0] = "DEM";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][0] = "Data/DEM/DEM.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][0] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][0] = "Above_RIC";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][1] = "RiccartonTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][1] = "Data/Canterbury_Basin/Quaternary/RiccartonTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][1] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][1] = "Riccarton";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][2] = "BromleyTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][2] = "Data/Canterbury_Basin/Quaternary/BromleyTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][2] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][2] = "Bromley";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][3] = "LinwoodTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][3] = "Data/Canterbury_Basin/Quaternary/LinwoodTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][3] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][3] = "Linwood";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][4] = "HeathcoteTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][4] = "Data/Canterbury_Basin/Quaternary/HeathcoteTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][5] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][4] = "Heathcote";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][5] = "BurwoodTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][5] = "Data/Canterbury_Basin/Quaternary/BurwoodTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][5] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][5] = "Burwood";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][6] = "ShirleyTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][6] = "Data/Canterbury_Basin/Quaternary/ShirleyTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][6] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][6] = "Shirley";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][7] = "WainoniTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][7] =  "Data/Canterbury_Basin/Quaternary/WainoniTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][7] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][7] = "Wainoni";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][8] = "PlioceneTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][8] = "Data/Canterbury_Basin/Pre_Quaternary/PlioceneTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][8] = 8;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][8] = "Pliocene";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][9] = "MioceneTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][9] = "Data/Canterbury_Basin/Pre_Quaternary/MioceneTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][9] = 1;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][9] = "Miocene";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][10] = "PaleogeneTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][10] = "Data/Canterbury_Basin/Pre_Quaternary/PaleogeneTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][10] = 1;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[0][10] = "Paleogene";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[0][11] = "BasementTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[0][11] = "Data/Canterbury_Basin/Pre_Quaternary/BasementTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[0][11] = 1;
        
        
        // BPV Basin
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN";
        GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[1] = 2;
        GLOBAL_MODEL_PARAMETERS->nBasinBoundaries[1] = 1;
        GLOBAL_MODEL_PARAMETERS->basinBoundaryFilenames[1][0] = "Data/Boundaries/BPVBoundary.txt";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[1][0] = "BPVTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[1][0] = "Data/Canterbury_Basin/BPV/BPVTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[1][0] = 0;
        GLOBAL_MODEL_PARAMETERS->basinSubModelNames[1][0] = "BPV_Standard";
        
        GLOBAL_MODEL_PARAMETERS->basinSurfaceNames[1][1] = "MioceneTop";
        GLOBAL_MODEL_PARAMETERS->basinSurfaceFilenames[1][1] = "Data/Canterbury_Basin/Pre_Quaternary/MioceneTop.in";
        GLOBAL_MODEL_PARAMETERS->basinBoundaryNumber[1][1] = 0;

        
        
        
    }
    // Model Version 0.2, EP Tomography
    if(modelVersion == 0.2)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 2;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 1;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "EPtomo2010subMod";
        
//        GLOBAL_MODEL_PARAMETERS->nBasin = 0;
        
    }
    
    //  Model Version 0.3  CHCH BASIN
    else if(modelVersion == 0.3)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    //  Model Version 0.4  w/ CHCH BASIN and 1D velocity model
    else if(modelVersion == 0.4)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "v1DsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    //  Model Version 0.5  w/ CHCH BASIN and EP Tomo
    else if(modelVersion == 0.5)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "v1DsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    
    //  Model Version 0.6  w/ CHCH BASIN of preQ
    else if(modelVersion == 0.6)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    
    
    //  Model Version 0.11  w/ CHCH BASIN of Q
    else if(modelVersion == 0.11)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "Q_CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    
    //  Model Version 0.12  w/ CHCH BASIN of preQ
    else if(modelVersion == 0.12)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
    }
    
    //  Model Version 0.13  w/ CHCH BASIN
    else if(modelVersion == 0.13)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    //  Model Version 0.141  w/ PREQ + Q + BPV
    else if(modelVersion == 0.141)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 4;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 3;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[3] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[2] = "EPtomo2010subMod";
        
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    else if(modelVersion == 0.14)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 4;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 3;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[3] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[2] = "EPtomo2010subMod";

        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
        
    }
    //  Model Version 0.15  w/ PREQ + Q + BPV
    else if(modelVersion == 0.15)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 4;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 3;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "demSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[3] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "NaNsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[2] = "EPtomo2010subMod";
        
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN";
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 2;
        
    }
    
    //==========================================================
    
    //          FINALIZED VERSIONS
    
    //==========================================================
    
    //  Model Version 1.0  w/ 1D velo mod (Cant. 1D)
    else if(modelVersion == 1.01)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 2;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 1;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        
//        GLOBAL_MODEL_PARAMETERS->nBasin = 0;
        
    }
    //  Model Version 1.1  w/ Tomography
    else if(modelVersion == 1.11)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 2;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 1;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "EPtomo2010subMod";
        
//        GLOBAL_MODEL_PARAMETERS->nBasin = 0;
    }
    //  Model Version 1.2  w/ 1D to basement w/ Tomography
    else if(modelVersion == 1.21)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
        
//        GLOBAL_MODEL_PARAMETERS->nBasin = 0;
    }
    //  Model Version 1.3  w/ 1D to basement w/ Tomography w/ Pliocene Basin layer
    else if(modelVersion == 1.31)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PALEO_CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
    }
    //  Model Version 1.4  w/ 1D to basement w/ Tomography w/ Paleogene + Miocene Basin layers
    else if(modelVersion == 1.41)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
    
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PALEO_MIO_CANTERBURY_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 1;
    }
    //  Model Version 1.5  w/ 1D to basement w/ Tomography w/ Paleogene + Miocene Basin layers w/ BPV Basin
    else if(modelVersion == 1.51)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PALEO_MIO_CANTERBURY_BASIN";
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 2;
    }
    
    //  Model Version 1.6  w/ 1D to basement w/ Tomography w/ Paleogene + Miocene + Pliocene Basin layers (full PreqQ basin)
    else if(modelVersion == 1.62)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN";
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 2;
    }
    else if(modelVersion == 1.63)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 3;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 2;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "basementRockSurf";
        GLOBAL_MODEL_PARAMETERS->surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "v1DsubMod";
        GLOBAL_MODEL_PARAMETERS->veloSubMod[1] = "EPtomo2010subMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN";
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN_WHEATHERED";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 2;
    }
    //  Model Version 1.6  w/ 1D to basement w/ Tomography w/ Paleogene + Miocene + Pliocene Basin layers (full PreqQ basin)
    else if(modelVersion == 1.64)
    {
        // define the number of surfaces and sub models
        GLOBAL_MODEL_PARAMETERS->nSurf = 2;
        GLOBAL_MODEL_PARAMETERS->nVeloSubMod = 1;
        
        // insert surface surface keywords
        GLOBAL_MODEL_PARAMETERS->surf[0] = "posInfSurf";
        GLOBAL_MODEL_PARAMETERS->surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        GLOBAL_MODEL_PARAMETERS->veloSubMod[0] = "EPtomo2010subMod";
        
        // insert basin name / number
        GLOBAL_MODEL_PARAMETERS->basin[0] = "PREQ_CANTERBURY_BASIN_1D";
        GLOBAL_MODEL_PARAMETERS->basin[1] = "BPV_BASIN";
//        GLOBAL_MODEL_PARAMETERS->nBasin = 2;
    }
    else
    {
        printf("Invalid velocity model version number.\n");
    }
    
    assert(GLOBAL_MODEL_PARAMETERS->nSurf==(GLOBAL_MODEL_PARAMETERS->nVeloSubMod+1));
    assert(GLOBAL_MODEL_PARAMETERS->nSurf<=(MAX_NUM_GLOBAL_SURFACES));
    assert(GLOBAL_MODEL_PARAMETERS->nBasins<=(MAX_NUM_BASINS));
    for (int i = 0; i < GLOBAL_MODEL_PARAMETERS->nBasins; i++)
    {
        assert(GLOBAL_MODEL_PARAMETERS->nBasinSurfaces[i]<=(MAX_NUM_BASIN_SURFACES));
    }
    printf("Global Model Parameters Obtained.\n");
    return GLOBAL_MODEL_PARAMETERS;
    
}

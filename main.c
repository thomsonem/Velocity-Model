
//
//  main.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 19/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "constants.h"
#include "structs.h"
#include "functions.h"

int main(void)//(int argc, char *argv[])
{
    ///*
     int argc = 14;
     char *argv[20];
     argv[1] = "GENERATE_VELOCITY_MOD";
     argv[2] = "1.01";
     argv[3] = "v1.01";
     argv[4] = "-43.6";
     argv[5] = "170.75";
     argv[6] = "-50.00";
     argv[7] = "1";
     argv[8] = "1";
     argv[9] = "1";
     argv[10] = "0";
     argv[11] = "0.5";
     argv[12] = "1";
     argv[13] = "0.5";
     //*/
    
    
    /*
    int argc = 15;
    char *argv[15];
    argv[1] = "EXTRACT_VELOCITY_SLICES";
    argv[2] = "1.01";
    argv[3] = "v1.01";
    argv[4] = "-43.6";
    argv[5] = "172.3";
    argv[6] = "-10";
    argv[7] = "70";
    argv[8] = "60";
    argv[9] = "46";
    argv[10] = "0";
    argv[11] = "0.1";
    argv[12] = "1";
    argv[13] = "0.6";
    argv[14] = "SliceParameters";
    */
    
    /*
    int argc = 5;
    char *argv[5];
    argv[1] = "GENERATE_VELOCITY_SLICES";
    argv[2] = "1.63";
    argv[3] = "v1.63";
    argv[4] = "SliceParametersBPV";
    */ //./CVM GENERATE_VELOCITY_SLICES 1.62 v1.62 SliceParameters
    
    
    /*
    int argc = 9;
    char *argv[9];
    argv[1] = "GENERATE_INDIVIDUAL_PROFILE";
    argv[2] = "1.62";
    argv[3] = "ProfileV1.62";
    argv[4] = "-44.3968";
    argv[5] = "171.5";
    argv[6] = "2";
    argv[7] = "-1";
    argv[8] = "0.05";
    */

    char *generateType = argv[1];
    model_extent MODEL_EXTENT;
    global_mesh *GLOBAL_MESH = NULL;
    

    //=============================================================
    
    // Generate velocity model "GENERATE_VELOCITY_MOD" or "EXTRACT_VELOCITY_SLICES"
     
    //=============================================================
    if ((strcmp(generateType, "GENERATE_VELOCITY_MOD") == 0) || (strcmp(generateType,"EXTRACT_VELOCITY_SLICES")== 0))
    {
        if (strcmp(generateType, "GENERATE_VELOITY_MOD") == 0 && argc != 14)
        {
            printf("Incorrect number of inputs: Recieved %i, require 13.\n",argc-1);
            exit(0);
        }
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICES") == 0 && argc != 15)
        {
            printf("Incorrect number of inputs: Recieved %i, require 14.\n",argc-1);
            exit(0);
        }
        // Model Version
        char *tempPointA;
        MODEL_EXTENT.version = strtod(argv[2],&tempPointA);
        printf("========================================\n");
        printf("Generating velocity model version %f.2\n", MODEL_EXTENT.version);
        printf("========================================\n");

        // Model origin paremeters
        MODEL_EXTENT.originLat = atof(argv[4]);
        MODEL_EXTENT.originLon = atof(argv[5]);
        MODEL_EXTENT.originRot = atof(argv[6]);
        
        // Model extent parameters
        MODEL_EXTENT.Xmax = atoi(argv[7]);
        MODEL_EXTENT.Ymax = atoi(argv[8]);
        MODEL_EXTENT.Zmax = atof(argv[9]); // max depth (positive downwards)
        MODEL_EXTENT.Zmin = atof(argv[10]);
        MODEL_EXTENT.hDep = atof(argv[11]);
        MODEL_EXTENT.hLatLon = atof(argv[12]);
        
        // generate the model grid
        GLOBAL_MESH = generateFullModelGrid(MODEL_EXTENT);
        
        // obtain surface filenames based off version number
        global_model_parameters *GLOBAL_MODEL_PARAMETERS;
        GLOBAL_MODEL_PARAMETERS = getGlobalModelParameters(MODEL_EXTENT.version);
        
        // generate the log file struct
        calculation_log *CALCULATION_LOG;
        CALCULATION_LOG = malloc(sizeof(calculation_log));
        CALCULATION_LOG->minVs = atof(argv[13]);
        CALCULATION_LOG->outputDirectory = argv[2];
        
        partial_global_mesh *PARTIAL_GLOBAL_MESH;
        global_qualitites *GLOBAL_QUALITIES;
        
        // read in velocity model data (surfaces, 1D models, tomography etc)
        for(int j = 0; j < GLOBAL_MESH->nY; j++)
        {
            PARTIAL_GLOBAL_MESH = extractPartialMesh(GLOBAL_MESH, j);
            GLOBAL_QUALITIES = assignQualities(MODEL_EXTENT, GLOBAL_MODEL_PARAMETERS, PARTIAL_GLOBAL_MESH, CALCULATION_LOG, j);

            writeGlobalQualities(PARTIAL_GLOBAL_MESH, GLOBAL_QUALITIES, CALCULATION_LOG, j);

            free(PARTIAL_GLOBAL_MESH);
            free(GLOBAL_QUALITIES);
        }
        
        
        
        // create output directory and the velocity model
        mkdir(outputDirectory, 0700);
        printf("Output directory created.\n");
        

        
        
//        // write log to file
//        writeVeloModLogFile(argc, argv, logStruct);
//        
//        if (strcmp(generateType,"GENERATE_VELOCITY_MOD") == 0)
//        {
//            // write log file
//            writeVeloModInputsLogFile(argc, argv);
//            
//            printf("GENERATE_VELO_MOD routine complete.\n");
//            printf("========================================\n\n");
//        }
//        
//        

        
        // create directory to output files to
        outputDirectory = argv[3];
        struct stat st = {0};
        if (stat(outputDirectory, &st) == -1)
        {
        }
        else
        {
            // if the output directory exists assume velocity model exists
            printf("Output directory already exists.\n");

        }
        
        free(globDataVals);
        free(location);

        
//        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICES") == 0)
//        {
//            sliceParams *sliceParameters;
//            sliceParameters = readExtractedSliceParametersFile(argv[14]);
//            
//            globalDataValues *globDataValsRead;
//            globDataValsRead = loadCvmDataAll(location, outputDirectory);
//            
//            for( int i = 0; i < sliceParameters->nSlices; i++)
//            {
//                // slice extent struct
//                sliceBounds.nSections = 1; // can do arbitary transects, restricted here to 1 slice between 2 points.
//                sliceBounds.resXY = sliceParameters->LatLonRes[i]; // hard coded number of points to take along the slice
//                sliceBounds.latPtsSlice[0] = sliceParameters->latA[i];
//                sliceBounds.latPtsSlice[1] = sliceParameters->latB[i];
//                sliceBounds.lonPtsSlice[0] = sliceParameters->lonA[i];
//                sliceBounds.lonPtsSlice[1] = sliceParameters->lonB[i];
//                
//                // extract slice from data
//                extractSlice(location, modelOrigin, sliceBounds, globDataValsRead, outputDirectory,i+1);
//                
//                sliceBounds.zMax = 1; // positive downwards
//                sliceBounds.zMin = 0;
//                sliceBounds.resZ = 1;
//                sliceBounds.saveSlices = 0;
//                generateSlice(modelOrigin, sliceBounds, modelVersion, outputDirectory);
//
//                printf("Slice %i of %i complete.\n",i+1, sliceParameters->nSlices);
//            }
//            char *type = "EXTRACTED";
//            writeSliceParametersLogFile(sliceParameters, modelVersion, location, outputDirectory, type);
//            
//            free(sliceParameters);
//            free(globDataValsRead);
//            
//            // write log file
//            writeVeloModInputsLogFile(argc, argv);
//
//            printf("EXTRACT_VELOCITY_SLICE routine complete.\n");
//            printf("========================================\n\n");
//            
//        }
    
        // free allocated memory
//        free(surfDepsGlob);
        
    }
    
    //=============================================================
    
    // Generate profile "GENERATE_INDIVIDUAL_PROFILE"
    
    //=============================================================
//    else if (strcmp(generateType, "GENERATE_INDIVIDUAL_PROFILE") == 0)
//    {
//        if (argc != 9)
//        {
//            printf("Incorrect number of inputs: Recieved %i, require 8.\n",argc-1);
//            exit(0);
//        }
//        
//        // Model Version
//        modelVersion.version = atof(argv[2]);
//        printf("========================================\n\n");
//        printf("Generating velocity model version %f.\n", modelVersion.version);
//        printf("========================================\n");
//        
//        // create directory to output files to
//        outputDirectory = argv[3];
//        struct stat st = {0};
//        if (stat(outputDirectory, &st) == -1)
//        {
//            mkdir(outputDirectory, 0700);
//            printf("Output directory created.\n");
//        }
//        else
//        {
//            printf("Output directory already exists.\n");
//        }
//        
//        // Model origin struct - used as the point where the profile is desired
//        modelOrigin.mlat = atof(argv[4]);
//        modelOrigin.mlon = atof(argv[5]);
//        modelOrigin.mrot = 0;
//        
//        // Model extent struct
//        modelExtent.Ymax = 0.5;
//        modelExtent.Xmax = 0.5;
//        modelExtent.Zmax = atof(argv[6]); // max depth (positive downwards)
//        modelExtent.Zmin = atof(argv[7]);
//        modelExtent.hDep = atof(argv[8]);
//        modelExtent.hLatLon = 1;
//        
//        // Generate profile
//        generateProfile(modelOrigin, modelVersion, modelExtent, outputDirectory);
//        
//        // write log file
//        writeVeloModInputsLogFile(argc, argv);
//        
//        printf("GENERATE_INDIVIDUAL_PROFILE routine complete.\n");
//        printf("========================================\n\n");
//
//    }
//    
//    
//    //=============================================================
//    
//    // Generate high resolution velocity slice "GENERATE_VELOCITY_SLICES"
//    
//    //=============================================================
//    else if (strcmp(generateType, "GENERATE_VELOCITY_SLICES") == 0)
//    {
//        if (argc != 5)
//        {
//            printf("Incorrect number of inputs: Recieved %i, require 4.\n",argc-1);
//            exit(0);
//        }
//        
//        // Model Version
//        modelVersion.version = atof(argv[2]);
//        printf("Generating velocity model version %f.\n", modelVersion.version);
//        
//        // create directory to output files to
//        outputDirectory = argv[3];
//        struct stat st = {0};
//        if (stat(outputDirectory, &st) == -1)
//        {
//            mkdir(outputDirectory, 0700);
//            printf("Output directory created.\n");
//        }
//        else
//        {
//            printf("Output directory already exists.\n");
//        }
//        
//        sliceParams *sliceParameters;
//        sliceParameters = readGeneratedSliceParametersFile(argv[4]);
//
//        
//        for( int i = 0; i < sliceParameters->nSlices; i++)
//        {
//            // slice extent struct
//            sliceBounds.nSections = 1;
//            sliceBounds.zMax = sliceParameters->depMax[i]; // positive downwards
//            sliceBounds.zMin = sliceParameters->depMin[i];
//            sliceBounds.resZ = (sliceParameters->depMax[i] - sliceParameters->depMin[i])/sliceParameters->DepRes[i];
//            sliceBounds.resXY = sliceParameters->LatLonRes[i];
//            sliceBounds.latPtsSlice[0] = sliceParameters->latA[i];
//            sliceBounds.latPtsSlice[1] = sliceParameters->latB[i];
//            sliceBounds.lonPtsSlice[0] = sliceParameters->lonA[i];
//            sliceBounds.lonPtsSlice[1] = sliceParameters->lonB[i];
//            sliceBounds.saveSlices = 1;
//
//            
//            modelOrigin.mlat = sliceBounds.latPtsSlice[0];
//            modelOrigin.mlon = sliceBounds.lonPtsSlice[0];
//            modelOrigin.mrot = 0;
//            
//            generateSlice(modelOrigin, sliceBounds, modelVersion, outputDirectory);
//            
//            printf("Slice %i of %i complete.\n",i+1, sliceParameters->nSlices);
//        }
//
//        char *type = "GENERATED";
//        writeSliceParametersLogFile(sliceParameters, modelVersion, location, outputDirectory, type);
//        
//        free(sliceParameters);
//
//        // write log file
//        writeVeloModInputsLogFile(argc, argv);
//        
//        printf("GENERATE_VELOCITY_SLICES routine complete.\n");
//        printf("========================================\n\n");
//
//        
//
//
//    }
}




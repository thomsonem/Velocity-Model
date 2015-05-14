
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

int main(int argc, char *argv[])
{
    /*
    int argc = 18;
    char *argv[18];
    argv[1] = "EXTRACT_VELOCITY_SLICE";
    argv[2] = "1.2";
    argv[3] = "ExtractedSliceV1.3";
    argv[4] = "-43.6";
    argv[5] = "172.3";
    argv[6] = "-10.00";
    argv[7] = "70";
    argv[8] = "60";
    argv[9] = "40";
    argv[10] = "0";
    argv[11] = "10";
    argv[12] = "10";
    argv[13] = "250";
    argv[14] = "-43.0";
    argv[15] = "-43.0";
    argv[16] = "171.0";
    argv[17] = "173.0";
    */

    
    
    /*
    int argc = 13;
    char *argv[13];
    argv[1] = "GENERATE_VELOCITY_MOD";
    argv[2] = "1.2";
    argv[3] = "ExtractedSliceV1.3";
    argv[4] = "-43.6";
    argv[5] = "172.3";
    argv[6] = "-10.00";
    argv[7] = "70";
    argv[8] = "60";
    argv[9] = "46";
    argv[10] = "0";
    argv[11] = ".25";
    argv[12] = ".25";
    */
    
    /*
    int argc = 9;
    char *argv[12];
    argv[1] = "GENERATE_INDIVIDUAL_PROFILE";
    argv[2] = "0.3";
    argv[3] = "GeneratedProfileV0.3";
    argv[4] = "-43.7471";
    argv[5] = "171.765";
    argv[6] = "1";
    argv[7] = "-0.3";
    argv[8] = "0.001";
    */
    
    
    char *generateType = argv[1];
        
    modOrigin modelOrigin;
    modVersion modelVersion;
    char *outputDirectory;
    modExtent modelExtent;
    sliceExtent sliceBounds;
    globalDataValues *globDataVals = NULL;
    surfaceDepthsGlobal *surfDepsGlob = NULL;
    gridStruct *location = NULL;
    

    //=============================================================
    
    // Generate velocity model "GENERATE_VELOCITY_MOD" or "EXTRACT_VELOCITY_SLICE"
     
    //=============================================================
    if ((strcmp(generateType, "GENERATE_VELOCITY_MOD") == 0) || (strcmp(generateType,"EXTRACT_VELOCITY_SLICE")== 0))
    {
        printf("Entered.\n");
        if (strcmp(generateType, "GENERATE_VELOITY_MOD") == 0 && argc != 13)
        {
            printf("Incorrect number of inputs: Recieved %i, require 12.\n",argc-1);
            exit(0);
        }
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICE") == 0 && argc != 18)
        {
            printf("Incorrect number of inputs: Recieved %i, require 17.\n",argc-1);
            exit(0);
        }
        
        
        // Model Version
        modelVersion.version = atof(argv[2]);
        printf("Generating velocity model version %f.\n", modelVersion.version);
        
        // create directory to output files to
        outputDirectory = argv[3];
        struct stat st = {0};
        if (stat(outputDirectory, &st) == -1)
        {
            mkdir(outputDirectory, 0700);
            printf("Output directory created.\n");
        }
        else
        {
            printf("Output directory already exists.\n");
        }

        // Model origin struct
        modelOrigin.mlat = atof(argv[4]);
        modelOrigin.mlon = atof(argv[5]);
        modelOrigin.mrot = atof(argv[6]);
        
        // Model extent struct
        modelExtent.Xmax = atoi(argv[7]);
        modelExtent.Ymax = atoi(argv[8]);
        modelExtent.Zmax = atof(argv[9]); // max depth (positive downwards)
        modelExtent.Zmin = atof(argv[10]);
        modelExtent.hDep = atof(argv[11]);
        modelExtent.hLatLon = atof(argv[12]);
        
        // generate the model grid
        location = generateModelGrid(modelOrigin, modelExtent);
//        writeGridPoints(location, outputDirectory);
        
        // obtain surface filenames based off version number
        surfNames surfSubModNames;
        surfSubModNames = getSurfSubModNames(modelVersion);
        
        // determine the depths of each surface for each lat lon point
        surfDepsGlob = getSurfaceValues(location, surfSubModNames);
        
        // assign values
        globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob, outputDirectory);
        
        // write data to file
        writeCVMData(location, globDataVals, outputDirectory);
        
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICE") == 0)
        {
            // slice extent struct
            sliceBounds.nSections = 1; // can do arbitary transects, restricted here to 1 slice between 2 points.
            sliceBounds.resXY = atoi(argv[13]);
            sliceBounds.latPtsSlice[0] = atof(argv[14]);
            sliceBounds.latPtsSlice[1] = atof(argv[15]);
            sliceBounds.lonPtsSlice[0] = atof(argv[16]);
            sliceBounds.lonPtsSlice[1] = atof(argv[17]);
            
            // extract slice from data
            extractSlice(location, modelOrigin, sliceBounds, outputDirectory);
            printf("EXTRACT_VELOCITY_SLICE routine complete.\n");

        }
        else
        {
            printf("GENERATE_VELO_MOD routine complete.\n");
        }
        
        // write log file
        writeVeloModLogFile(argc, argv);
        
        // free allocated memory
        free(surfDepsGlob);
        free(globDataVals);
        free(location);
        
        
    }
    
    //=============================================================
    
    // Generate profile "GENERATE_INDIVIDUAL_PROFILE"
    
    //=============================================================
    else if (strcmp(generateType, "GENERATE_INDIVIDUAL_PROFILE") == 0)
    {
        if (argc != 9)
        {
            printf("Incorrect number of inputs: Recieved %i, require 8.\n",argc-1);
            exit(0);
        }
        
        // Model Version
        modelVersion.version = atof(argv[2]);
        printf("Generating velocity model version %f.\n", modelVersion.version);
        
        // create directory to output files to
        outputDirectory = argv[3];
        struct stat st = {0};
        if (stat(outputDirectory, &st) == -1)
        {
            mkdir(outputDirectory, 0700);
            printf("Output directory created.\n");
        }
        else
        {
            printf("Output directory already exists.\n");
        }
        
        // Model origin struct - used as the point where the profile is desired
        modelOrigin.mlat = atof(argv[4]);
        modelOrigin.mlon = atof(argv[5]);
        modelOrigin.mrot = 0;
        
        // Model extent struct
        modelExtent.Ymax = 0.5;
        modelExtent.Xmax = 0.5;
        modelExtent.Zmax = atof(argv[6]); // max depth (positive downwards)
        modelExtent.Zmin = atof(argv[7]);
        modelExtent.hDep = atof(argv[8]);
        modelExtent.hLatLon = 1;
        
        // Generate profile
        generateProfile(modelOrigin, modelVersion, modelExtent, outputDirectory);
        
        printf("GENERATE_INDIVIDUAL_PROFILE routine complete.\n");
        
        // write log file
        writeVeloModLogFile(argc, argv);

    }
    
    
    //=============================================================
    
    // Generate high resolution velocity slice "GENERATE_VELOCITY_SLICE"
    
    //=============================================================
    else if (strcmp(generateType, "GENERATE_VELOCITY_SLICE") == 0)
    {
        if (argc != 12)
        {
            printf("Incorrect number of inputs: Recieved %i, require 11.\n",argc-1);
            exit(0);
        }
        
        // Model Version
        modelVersion.version = atof(argv[2]);
        printf("Generating velocity model version %f.\n", modelVersion.version);
        
        // create directory to output files to
        outputDirectory = argv[3];
        struct stat st = {0};
        if (stat(outputDirectory, &st) == -1)
        {
            mkdir(outputDirectory, 0700);
            printf("Output directory created.\n");
        }
        else
        {
            printf("Output directory already exists.\n");
        }
        
        modelVersion.saveSurfaceDepths = 1;
        
        // slice extent struct
        sliceBounds.nSections = 1;
        sliceBounds.zMax = atof(argv[4]); // positive downwards
        sliceBounds.zMin = atof(argv[5]);
        sliceBounds.resZ = atof(argv[6]);
        sliceBounds.resXY = atoi(argv[7]);
        sliceBounds.latPtsSlice[0] = atof(argv[8]);
        sliceBounds.latPtsSlice[1] = atof(argv[9]);
        sliceBounds.lonPtsSlice[0] = atof(argv[10]);
        sliceBounds.lonPtsSlice[1] = atof(argv[11]);
        
        modelOrigin.mlat = sliceBounds.latPtsSlice[0];
        modelOrigin.mlon = sliceBounds.lonPtsSlice[0];
        modelOrigin.mrot = 0;
        
        generateSlice(modelOrigin, sliceBounds, modelVersion, outputDirectory);
        
        printf("GENERATE_VELOCITY_SLICE routine complete.\n");
        
        // write log file
        writeVeloModLogFile(argc, argv);

    }
}




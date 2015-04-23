
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
    
    // Generate velocity model "GENERATE_VELO_MOD" or "EXTRACT_VELOCITY_SLICE"
     
    //=============================================================
    if (strcmp(generateType, "GENERATE_VELO_MOD") == 0 || strcmp(generateType,"EXTRACT_VELOCITY_SLICE"))
    {
        if (strcmp(generateType, "GENERATE_VELO_MOD") == 0 && argc != 13)
        {
            printf("Incorrect number of inputs: Recieved %i, require 12.\n",argc-1);
            exit(0);
        }
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICE") && argc != 18)
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
        
        // obtain surface filenames based off version number
        surfNames surfSubModNames;
        surfSubModNames = getSurfSubModNames(modelVersion);
        
        // determine the depths of each surface for each lat lon point
        surfDepsGlob = getSurfaceValues(location, surfSubModNames);
        
        // assign values
        globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob, outputDirectory);
        
        // write data to file
        writeCVMData(location, globDataVals, outputDirectory);
        
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICE"))
        {
            // slice extent struct
            sliceBounds.nSections = 1; // can do arbitary transects, restricted here to 1 slice between 2 points.
            sliceBounds.resXY = atoi(argv[13]);
            sliceBounds.latPtsSlice[0] = atof(argv[14]);
            sliceBounds.latPtsSlice[1] = atof(argv[16]);
            sliceBounds.lonPtsSlice[0] = atof(argv[17]);
            sliceBounds.lonPtsSlice[1] = atof(argv[15]);
            
            // extract slice from data
            extractSlice(location, modelOrigin, sliceBounds, outputDirectory);
        }
        
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

    }
}




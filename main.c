
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
    int argc = 14;
    char *argv[14];
    argv[1] = "EXTRACT_VELOCITY_SLICES";
    argv[2] = "1.3";
    argv[3] = "VelocityModel1.3";
    argv[4] = "-43.6"; //-43.75
    argv[5] = "172.3"; //172.25
    argv[6] = "-10";
    argv[7] = "70"; //130
    argv[8] = "60";//120
    argv[9] = "46";
    argv[10] = "0";
    argv[11] = ".1";
    argv[12] = ".1";
    argv[13] = "SliceParameters";
    */
    
    /*
    int argc = 12;
    char *argv[12];
    argv[1] = "GENERATE_VELOCITY_SLICE";
    argv[2] = "1.3";
    argv[3] = "GeneratedSliceV1.3";
    argv[4] = "46";
    argv[5] = "0";
    argv[6] = "1";
    argv[7] = "10";
    argv[8] = "-42.6";
    argv[9] = "-43.0";
    argv[10] = "172.7";
    argv[11] = "172.7";
    */
    
    
    /*
    int argc = 9;
    char *argv[12];
    argv[1] = "GENERATE_INDIVIDUAL_PROFILE";
    argv[2] = "1.1";
    argv[3] = "GeneratedProfileV1.3";
    argv[4] = "-44.6";
    argv[5] = "170.5";
    argv[6] = "1";
    argv[7] = "-0.0";
    argv[8] = "0.01";
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
    if ((strcmp(generateType, "GENERATE_VELOCITY_MOD") == 0) || (strcmp(generateType,"EXTRACT_VELOCITY_SLICES")== 0))
    {
        if (strcmp(generateType, "GENERATE_VELOITY_MOD") == 0 && argc != 13)
        {
            printf("Incorrect number of inputs: Recieved %i, require 12.\n",argc-1);
            exit(0);
        }
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICES") == 0 && argc != 14)
        {
            printf("Incorrect number of inputs: Recieved %i, require 13.\n",argc-1);
            exit(0);
        }
        // Model Version
        modelVersion.version = atof(argv[2]);
        printf("Generating velocity model version %f.\n", modelVersion.version);
        
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
        
        // create directory to output files to
        outputDirectory = argv[3];
        struct stat st = {0};
        if (stat(outputDirectory, &st) == -1)
        {
            // create output directory and the velocity model
            mkdir(outputDirectory, 0700);
            printf("Output directory created.\n");
            
            // obtain surface filenames based off version number
            surfNames surfSubModNames;
            surfSubModNames = getSurfSubModNames(modelVersion);
            
            // determine the depths of each surface for each lat lon point
            surfDepsGlob = getSurfaceValues(location, surfSubModNames, outputDirectory);
            
            // assign values
            globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob, outputDirectory);
            
            // write data to file
            writeCVMData(location, globDataVals, outputDirectory);
            
            if (strcmp(generateType,"GENERATE_VELO_MOD") == 0)
            {
                printf("GENERATE_VELO_MOD routine complete.\n");
            }

            
        }
        else
        {
            // if the output directory exists assume velocity model exists
            printf("Output directory already exists.\n");

        }
        
        free(globDataVals);
        
        if (strcmp(generateType,"EXTRACT_VELOCITY_SLICES") == 0)
        {
            sliceParams *sliceParameters;
            sliceParameters = readSliceParametersFile(argv[13]);
            
            globalDataValues *globDataValsRead;
            globDataValsRead = loadCvmDataAll(location, outputDirectory);
            
            for( int i = 0; i < sliceParameters->nSlices; i++)
            {
                // slice extent struct
                sliceBounds.nSections = 1; // can do arbitary transects, restricted here to 1 slice between 2 points.
                sliceBounds.resXY = 250; // hard coded number of points to take along the slice
                sliceBounds.latPtsSlice[0] = sliceParameters->latA[i];
                sliceBounds.latPtsSlice[1] = sliceParameters->latB[i];
                sliceBounds.lonPtsSlice[0] = sliceParameters->lonA[i];
                sliceBounds.lonPtsSlice[1] = sliceParameters->lonB[i];
                
                // extract slice from data
                extractSlice(location, modelOrigin, sliceBounds, globDataValsRead, outputDirectory,i+1);
                printf("Slice %i of %i complete.\n",i+1, sliceParameters->nSlices);
            }
            writeSliceParametersLogFile(sliceParameters, modelVersion, location, outputDirectory);
            
            free(sliceParameters);
            free(globDataValsRead);
            printf("EXTRACT_VELOCITY_SLICE routine complete.\n");
            
        }
        
        
        // write log file
        writeVeloModLogFile(argc, argv);
        
        // free allocated memory
        free(surfDepsGlob);
        
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




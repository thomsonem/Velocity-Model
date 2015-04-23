
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
    printf("Begin.\n");
    char *generateType = argv[1];
    
    modOrigin modelOrigin;
    modVersion modelVersion;
    char *outputDirectory;
    modExtent modelExtent;


    if (strcmp(generateType, "GENERATE_VELO_MOD") == 0)
    {
        // Model Version
        modelVersion.version = atof(argv[2]);

        // Model origin struct
        modelOrigin.mlat = atof(argv[3]);
        modelOrigin.mlon = atof(argv[4]);
        modelOrigin.mrot = atof(argv[5]);
        outputDirectory = argv[6];
        
        // Model extent struct
        modelExtent.Xmax = atoi(argv[7]);
        modelExtent.Ymax = atoi(argv[8]);
        modelExtent.Zmax = atof(argv[9]); // max depth (positive downwards)
        modelExtent.Zmin = atof(argv[10]);
        modelExtent.hDep = atof(argv[11]);
        modelExtent.hLatLon = atof(argv[12]);
        
    }
    else if (strcmp(generateType, "GENERATE_INDIVIDUAL_PROFILE") == 0)
    {
        
    }
    else if (strcmp(generateType, "EXTRACT_VELOCITY_SLICE") == 0)
    {
        
    }
    else if (strcmp(generateType, "GENERATE_VELOCITY_SLICE") == 0)
    {
        
    }

    printf("Generating velocity model version %f.\n", modelVersion.version);

    int profileRequired = 0; // set as 1 if a velocity profile is requires at this location, else set to 0
    int modelInterrogation = 0; // set as 1 if a velocity slice extraction is required from the generated model
    int figureGeneration = 0; // set as 1 if high resolution figure is to be generated
    
    // create directory to output files to
    struct stat st = {0};
    
    if (stat(outputDirectory, &st) == -1)
    {
        mkdir(outputDirectory, 0700);
    }
    
    globalDataValues *globDataVals = NULL;
    surfaceDepthsGlobal *surfDepsGlob = NULL;
    gridStruct *location = NULL;


    if(profileRequired == 1)
    {
        // Model extent struct
        modExtent modelExtent;
        modelExtent.Ymax = 0.5;
        modelExtent.Xmax = 0.5;
        modelExtent.Zmax = 10; // max depth (km)
        modelExtent.Zmin = -0.0;
        modelExtent.hDep = .01;
        modelExtent.hLatLon = 1;
        
        generateProfile(modelOrigin, modelVersion, modelExtent, outputDirectory);
    }
	else
    {
		// generate the model grid
		location = generateModelGrid(modelOrigin, modelExtent);
		// printf("%lf %lf %lf %lf\n", location->maxLat, location->minLat, location->maxLon, location->minLon);

        // obtain surface filenames based off version number
        surfNames surfSubModNames;
        surfSubModNames = getSurfSubModNames(modelVersion);
        
        // determine the depths of each surface for each lat lon point
        surfDepsGlob = getSurfaceValues(location, surfSubModNames);
        
        // assign values
        globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob, outputDirectory);
        
        // write data to file
        writeCVMData(location, globDataVals, outputDirectory);
        

    }
    if (modelInterrogation == 1)
    {
        // slice extent struct
        sliceExtent sliceBounds;
        sliceBounds.nSections = 1;
        sliceBounds.resXY = 5;
        
        sliceBounds.lonPtsSlice[0] = 172.6;
        sliceBounds.lonPtsSlice[1] = 172.6;
        sliceBounds.latPtsSlice[0] = -43.4;
        sliceBounds.latPtsSlice[1] = -43.9;
        
        extractSlice(location, modelOrigin, modelExtent, sliceBounds, outputDirectory);

    }
    if( figureGeneration == 1)
    {
		modelVersion.saveSurfaceDepths = 1;
        // slice extent struct
        sliceExtent sliceBounds;
        sliceBounds.nSections = 1;
        sliceBounds.resXY = 100;
        sliceBounds.resZ = .01;
        sliceBounds.zMin = -.15;
        sliceBounds.zMax = .20; // positive downwards
        sliceBounds.lonPtsSlice[0] = 172.6;
        sliceBounds.lonPtsSlice[1] = 172.6;
        sliceBounds.latPtsSlice[0] = -43.4;
        sliceBounds.latPtsSlice[1] = -43.9;

        generateSlice(modelOrigin, modelExtent, sliceBounds, modelVersion, outputDirectory);
    }
    
    // free allocated memory
    free(surfDepsGlob);
	free(globDataVals);
    free(location);

    
    
}




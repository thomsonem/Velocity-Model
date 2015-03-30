
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


#include "constants.h"
#include "structs.h"
#include "functions.h"

int main(void)
{
    // Model origin struct
    modOrigin modelOrigin;
    modelOrigin.mlat = -43.65;
    modelOrigin.mlon = 172.6;
    modelOrigin.mrot = 1.0;
    modVersion modelVersion;

	// Model extent struct
	modExtent modelExtent;
	modelExtent.Ymax = 30;
	modelExtent.Xmax = 20;
	modelExtent.Zmax = 0.20; // max depth (positive downwards)
	modelExtent.Zmin = -0.10; //
	modelExtent.hDep = .1; // can assign different grid spacing in z to that in the horizontal plane
	modelExtent.hLatLon = 10;
    
	// Model version struct
	modelVersion.version = 1.2;
	printf("Generating model version %f.\n", modelVersion.version);

    int profileRequired = 0; // set as 1 if a velocity profile is requires at this location, else set to 0
    int modelInterrogation = 0; // set as 1 if a velocity slice extraction is required from the generated model
    int figureGeneration = 1; // set as 1 if high resolution figure is to be generated
    
    globalDataValues *globDataVals = NULL;
    surfaceDepthsGlobal *surfDepsGlob = NULL;
    gridStruct *location = NULL;


    if( profileRequired == 1)
    {
        generateProfile(modelOrigin);
    }
	else if (modelInterrogation == 1)
    {
		// generate the model grid
		location = generateModelGrid(modelOrigin, modelExtent);
		printf("%lf %lf %lf %lf\n", location->maxLat, location->minLat, location->maxLon, location->minLon);

        // obtain surface filenames based off version number
        surfNames surfSubModNames;
        surfSubModNames = getSurfSubModNames(modelVersion);
        
        // determine the depths of each surface for each lat lon point
        surfDepsGlob = getSurfaceValues(location, surfSubModNames);
        
        // assign values
        globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob);
        
        // write data to file
        //writeCVMData(location, globDataVals);
        

        // slice extent struct
        sliceExtent sliceBounds;
        sliceBounds.nSections = 1;
        sliceBounds.resXY = 5;
        
        sliceBounds.lonPtsSlice[0] = 172.6;
        sliceBounds.lonPtsSlice[1] = 172.6;
        sliceBounds.latPtsSlice[0] = -43.4;
        sliceBounds.latPtsSlice[1] = -43.9;
        
        extractSlice(location, modelOrigin, modelExtent, sliceBounds);
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

        generateSlice(modelOrigin, modelExtent, sliceBounds, modelVersion);
    }
    
    // free allocated memory
    free(surfDepsGlob);
	free(globDataVals);
    free(location);

    
    
}




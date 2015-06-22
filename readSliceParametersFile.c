//
//  readSliceParametersFile.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 14/06/15.
//  Copyright (c) 2015 Dept. Civil Engineering. All rights reserved.
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

sliceParams *readSliceParametersFile(char *sliceParametersDirectory)
{
    sliceParams *sliceParameters;
    sliceParameters = malloc(sizeof(sliceParams));
    
    char sliceFileName[64];
    sprintf(sliceFileName,"%s/SliceParameters.txt", sliceParametersDirectory);
    FILE *file;
    
    file = fopen(sliceFileName, "r");
    
    if (file == NULL) {
        perror("Error");
    }
    
    fscanf(file, "%d", &sliceParameters->nSlices);
    
    assert(sliceParameters->nSlices<=MAX_NUM_SLICES);
    
    for(int i = 0; i < sliceParameters->nSlices; i++)
    {
        fscanf(file, "%lf %lf %lf %lf", &sliceParameters->latA[i], &sliceParameters->latB[i], &sliceParameters->lonA[i], &sliceParameters->lonB[i]);
    }
    
    return sliceParameters;
}
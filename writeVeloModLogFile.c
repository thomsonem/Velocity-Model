//
//  writeVeloModLogFile.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 24/04/15.
//  Copyright (c) 2015 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

void writeVeloModLogFile(int argc, char *argv[])
{
    FILE *logFile;
    const char *inputVector[18];
    char logFileName[64];
    sprintf(logFileName,"%s/log.txt", argv[3]);
    logFile = fopen(logFileName,"w");
    
    
    inputVector[1] = "Sub routine name";
    inputVector[2] = "MODEL_VERSION";
    inputVector[3] = "OUTPUT_DIR";
    
    if (strcmp(argv[1], "GENERATE_VELOCITY_MOD") == 0)
    {
        inputVector[4] = "ORIGIN_LAT";
        inputVector[5] = "ORIGIN_LON";
        inputVector[6] = "ORIGIN_ROT";
        inputVector[7] = "EXTENT_X";
        inputVector[8] = "EXTENT_Y";
        inputVector[9] = "EXTENT_ZMAX";
        inputVector[10] = "EXTENT_ZMIN";
        inputVector[11] = "EXTENT_Z_SPACING";
        inputVector[12] = "EXTENT_LATLON_SPACING";
    }
    else if(strcmp(argv[1],"EXTRACT_VELOCITY_SLICE")== 0)
    {
        inputVector[4] = "ORIGIN_LAT";
        inputVector[5] = "ORIGIN_LON";
        inputVector[6] = "ORIGIN_ROT";
        inputVector[7] = "EXTENT_X";
        inputVector[8] = "EXTENT_Y";
        inputVector[9] = "EXTENT_ZMAX";
        inputVector[10] = "EXTENT_ZMIN";
        inputVector[11] = "EXTENT_Z_SPACING";
        inputVector[12] = "EXTENT_LATLON_SPACING";
        inputVector[13] = "SLICE_NPTS_XY";
        inputVector[14] = "SLICE_LAT_1";
        inputVector[15] = "SLICE_LAT_2";
        inputVector[16] = "SLICE_LON_1";
        inputVector[17] = "SLICE_LON_2";
    }
    else if (strcmp(argv[1], "GENERATE_VELOCITY_SLICE") == 0)
    {
        inputVector[4] = "SLICE_ZMAX";
        inputVector[5] = "SLICE_ZMIN";
        inputVector[6] = "SLICE_Z_SPACING";
        inputVector[7] = "SLICE_NPTS_XY";
        inputVector[8] = "SLICE_LAT_1";
        inputVector[9] = "SLICE_LAT_2";
        inputVector[10] = "SLICE_LON_1";
        inputVector[11] = "SLICE_LON_2";
    }
    else if (strcmp(argv[1], "GENERATE_INDIVIDUAL_PROFILE") == 0)
    {
        inputVector[4] = "PROFILE_LAT";
        inputVector[5] = "PROFILE_LON";
        inputVector[6] = "PROFILE_ZMAX";
        inputVector[7] = "PROFILE_ZMIN";
        inputVector[8] = "EXTENT_Z_SPACING";
    }
    else
    {
        printf("Error.\n");
    }
    
    fprintf(logFile,"Code called with the following inputs.\n");
    
    for( int i = 1; i < argc; i ++)
    {
        fprintf(logFile,"%s\t%s\n",inputVector[i],argv[i]);
//        printf("%s\t%s\n",inputVector[i],argv[i]);
    }

    fclose(logFile);
    printf("Log file write complete.\n");
    
    
}


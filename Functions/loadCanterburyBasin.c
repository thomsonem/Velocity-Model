//
//  loadCanterburyBasin.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 28/11/14.
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

void loadCanterburyBasinData(gridStruct *location, int basinNum, globalBasinData *basinData)
{
    basinData->surf[basinNum][0] = "DEM";
    basinData->surf[basinNum][1] = "RiccartonTop";
    basinData->surf[basinNum][2] = "BromleyTop";
    basinData->surf[basinNum][3] = "LinwoodTop";
    basinData->surf[basinNum][4] = "HeathcoteTop";
    basinData->surf[basinNum][5] = "BurwoodTop";
    basinData->surf[basinNum][6] = "ShirleyTop";
    basinData->surf[basinNum][7] = "PlioceneTop";
    basinData->surf[basinNum][8] = "MioceneTop";
    basinData->surf[basinNum][9] = "PaloegeneTop";
    basinData->surf[basinNum][10] = "CretaceousTop";
    basinData->surf[basinNum][11] = "BasementTop";
    basinData->nSurf[basinNum] = 12;
    
    
    // basin boundaries must be completly encompassed within higher level boundaries
    // ie basin [0] must be completely within basin [0] in order to enforce the depths properley
    
    basinData->nBoundaries[basinNum] = 2;
    basinData->boundaryFileName[basinNum][0] = "QuaternarySurfacesBoundary.txt";
    basinData->boundaryFileName[basinNum][1] = "CanterburyBasinBoundary.txt";
    
    basinData->boundaryType[basinNum][0] = 1; // dem utilizes the largest boundary
    basinData->boundaryType[basinNum][1] = 0;
    basinData->boundaryType[basinNum][2] = 0;
    basinData->boundaryType[basinNum][3] = 0;
    basinData->boundaryType[basinNum][4] = 0;
    basinData->boundaryType[basinNum][5] = 0;
    basinData->boundaryType[basinNum][6] = 0; // 6 surfaces utilize boundary #0 (small boundary)
    basinData->boundaryType[basinNum][7] = 1; // other surfaces utilize boundary #1
    basinData->boundaryType[basinNum][8] = 1;
    basinData->boundaryType[basinNum][9] = 1;
    basinData->boundaryType[basinNum][10] = 1;
    basinData->boundaryType[basinNum][11] = 1;
    
    // load the basin data
    loadBasin(location, basinNum, basinData);

    
}




//
//  writeLatLonData.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 15/07/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "constants.h"
#include "structs.h"

void writeLatLonData(gridStruct *location, globalDataValues *globDataVals)
/*
 Purpose:   write the velocity profile for the previously specified lat lon points
 
 Input variables:
 location        - pointer to structure containing lat lon points
 globalValues    - pointer to structure containing vp vs and rho for the lat lon points
 Output variables:
 N/A.
 */
{
    // generate files for writing
    FILE *fRho, *fVp, *fVs;

    fRho = fopen("E:\veloProfilesRho.xy","w");
    fVp = fopen("E:\veloProfilesVp.xy","w");
    fVs = fopen("E:\veloProfilesVs.xy","w");
    
    double currRho, currVp, currVs;
    for(int i = 0; i < location->nY; i++)
    {
        if(i != 0)
        {
            fprintf(fVp,">\n");
            fprintf(fVs,">\n");
            fprintf(fRho,">\n");
        }
        for(int m = 0; m < location->nZ; m++)
        {
            currVp = globDataVals->Vp[i][i][m];
            currRho = globDataVals->Rho[i][i][m];
            currVs = globDataVals->Vs[i][i][m];
            if(m != 0 && currVp < globDataVals->Vp[i][i][m-1])
            {
                printf("%lf %lf \n", location->Lon[i][i], location->Lat[i][i]);
            }
        
            fprintf(fVs, "%lf\t%lf \n", currVs, location->Z[m]);
            fprintf(fVp, "%lf\t%lf \n", currVp, location->Z[m]);
            fprintf(fRho, "%lf\t%lf \n", currRho, location->Z[m]);
        }
    }
    fclose(fVp);
    fclose(fVs);
    fclose(fRho);
    //printf("Completed writing data to file.\n");
    
}

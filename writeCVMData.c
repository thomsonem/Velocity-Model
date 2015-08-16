//
//  writeCVMData.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 24/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"

void writeCVMData(gridStruct *location, globalDataValues *globDataVals, char *outputDirectory)
/*
 Purpose:   write the full velocity model to file
 
 Input variables:
 location        - pointer to structure containing lat lon grid
 globalValues    - pointer to structure containing vp vs and rho for all gridpoints
 
 Output variables:
 N/A.
 */
{
    char veloModDir[128];
    sprintf(veloModDir,"%s/Velocity_Model",outputDirectory);
    
    struct stat st = {0};
    if (stat(veloModDir, &st) == -1)
    {
        // create output directory and the velocity model
        mkdir(veloModDir, 0700);
    }
    
    
    
    FILE *fvp, *fvs, *frho; //*fp
    char vp3dfile[64];
    sprintf(vp3dfile,"%s/vp3dfile.p",veloModDir);

    char vs3dfile[64];
    sprintf(vs3dfile,"%s/vs3dfile.s",veloModDir);

	char rho3dfile[64];
    sprintf(rho3dfile,"%s/rho3dfile.d",veloModDir);

    float *vp, *vs, *rho;
    int bsize, ip;
    
	fvp = fopen(vp3dfile,"w");
	fvs = fopen(vs3dfile,"w");
	frho = fopen(rho3dfile,"w");
    
	//determine the number of x,y,z layers
    printf("Starting binary file write.\n");
    printf("Number of grid points, ");
	printf("nx: %d ",location->nX);
	printf("ny: %d ",location->nY);
	printf("nz: %d ",location->nZ);
	printf("\n");
    
	bsize = location->nX*location->nZ*sizeof(float);
	vp = (float*) malloc(bsize);
	vs = (float*) malloc(bsize);
	rho = (float*) malloc(bsize);
    
	for(int iy = 0; iy < location->nY; iy++)
    {
		for(int iz = 0; iz < location->nZ; iz++)
        {
			for (int ix = 0; ix < location->nX; ix++)
            {
				ip = ix + iz * location->nX;  //index counter
				vp[ip] = globDataVals->Vp[ix][iy][iz];
				vs[ip] = globDataVals->Vs[ix][iy][iz];
				rho[ip] = globDataVals->Rho[ix][iy][iz];
			}
		}
		//increment a counter
//		printf("Completed write of properties at longitude %i of %i.\n",iy+1,location->nY);
        printf("\rWriting velocity model to file %d%% complete.", iy*100/location->nY);
        fflush(stdout);
        
		//now write the obtained file in binary
		fwrite(vp,sizeof(vp[0]),location->nX*location->nZ,fvp);
		fwrite(vs,sizeof(vs[0]),location->nX*location->nZ,fvs);
		fwrite(rho,sizeof(rho[0]),location->nX*location->nZ,frho);
	}
    printf("\rWriting velocity model to file 100%% complete.");
    fflush(stdout);
    printf("\n");
    
    free(vp);
    free(vs);
    free(rho);
	fclose(fvp);
	fclose(fvs);
	fclose(frho);
    printf("Binary file write complete.\n");

    
}

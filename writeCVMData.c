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
#include <stdint.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"

void writeGlobalQualities(partial_global_mesh *PARTIAL_GLOBAL_MESH, partial_global_qualities *PARTIAL_GLOBAL_QUALITIES, calculation_log *CALCULATION_LOG, int latInd)

/*
 Purpose:   write the full velocity model to file
 
 Input variables:
 PARTIAL_GLOBAL_MESH        - pointer to structure containing lat lon grid
 globalValues    - pointer to structure containing vp vs and rho for all gridpoints
 
 Output variables:
 N/A.
 */
{
    // perform endian check
    int endianInt;
    endianInt = endian();
    
    char veloModDir[128];
    sprintf(veloModDir,"%s/Velocity_Model",CALCULATION_LOG->outputDirectory);
    
    
    FILE *fvp, *fvs, *frho;
    char vp3dfile[64];
    sprintf(vp3dfile,"%s/vp3dfile.p",veloModDir);
    
    char vs3dfile[64];
    sprintf(vs3dfile,"%s/vs3dfile.s",veloModDir);
    
    char rho3dfile[64];
    sprintf(rho3dfile,"%s/rho3dfile.d",veloModDir);
    
    float *vp, *vs, *rho;
    float vpTemp, vsTemp, rhoTemp;
    float vpWrite, vsWrite, rhoWrite;
    
    int bsize, ip;
    
    
    if( latInd == 0) // if first time, generate binary files
    {
        struct stat st = {0};
        if (stat(veloModDir, &st) == -1)
        {
            // create output directory and the velocity model
            mkdir(veloModDir, 0700);
        }
        fvp = fopen(vp3dfile,"w");
        fvs = fopen(vs3dfile,"w");
        frho = fopen(rho3dfile,"w");
        
    }
    else // append to existing binary files
    {
        fvp = fopen(vp3dfile,"a");
        fvs = fopen(vs3dfile,"a");
        frho = fopen(rho3dfile,"a");
    }

	bsize = PARTIAL_GLOBAL_MESH->nX*PARTIAL_GLOBAL_MESH->nZ*sizeof(float);
	vp = (float*) malloc(bsize);
	vs = (float*) malloc(bsize);
	rho = (float*) malloc(bsize);
    
		for(int iz = 0; iz < PARTIAL_GLOBAL_MESH->nZ; iz++)
        {
			for (int ix = 0; ix < PARTIAL_GLOBAL_MESH->nX; ix++)
            {
				ip = ix + iz * PARTIAL_GLOBAL_MESH->nX;  //index counter
                if (PARTIAL_GLOBAL_QUALITIES->Vs[ix][iz] < CALCULATION_LOG->minVs) // enforce min Vs
                {
                    vsTemp = CALCULATION_LOG->minVs;
                    CALCULATION_LOG->nPointsExceedingMinVelo += 1;
                }
                else
                {
                    vsTemp = PARTIAL_GLOBAL_QUALITIES->Vs[ix][iz]; // else assign from global structure
                }
                vpTemp = PARTIAL_GLOBAL_QUALITIES->Vp[ix][iz];
                rhoTemp = PARTIAL_GLOBAL_QUALITIES->Rho[ix][iz];
                
                
                if (endianInt == 1) // big endian
                {
                    vsWrite = float_swap(vsTemp);
                    vpWrite = float_swap(vpTemp);
                    rhoWrite = float_swap(rhoTemp);
                }
                else if (endianInt == 0) // little endian
                {
                    vsWrite = vsTemp;
                    vpWrite = vpTemp;
                    rhoWrite = rhoTemp;
                }

                fwrite(&vpWrite,sizeof(float),1,fvp);
                fwrite(&vsWrite,sizeof(float),1,fvs);
                fwrite(&rhoWrite,sizeof(float),1,frho);
			}
		}
    
    
    free(vp);
    free(vs);
    free(rho);
	fclose(fvp);
	fclose(fvs);
	fclose(frho);

    
}



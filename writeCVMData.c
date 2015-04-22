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
    FILE *fvp, *fvs, *frho; //*fp
	FILE *fvpdebug, *fvsdebug, *frhodebug;
    char vp3dfile[64];
    sprintf(vp3dfile,"%s/vp3dfile.bin",outputDirectory);

    char vs3dfile[64];
    sprintf(vs3dfile,"%s/vs3dfile.bin",outputDirectory);

	char rho3dfile[64];
    sprintf(rho3dfile,"%s/rho3dfile.bin",outputDirectory);

    char vpdebug3dfile[64];
    sprintf(vpdebug3dfile,"%s/vpdebug3dfile.txt",outputDirectory);

    char vsdebug3dfile[64];
    sprintf(vsdebug3dfile,"%s/vsdebug3dfile.txt",outputDirectory);

    char rhodebug3dfile[64];
    sprintf(rhodebug3dfile,"%s/rhodebug3dfile.txt",outputDirectory);

    float *vp, *vs, *rho;
    int bsize, ip;
    
	fvp = fopen(vp3dfile,"w");
	fvs = fopen(vs3dfile,"w");
	frho = fopen(rho3dfile,"w");
    fvpdebug = fopen(vpdebug3dfile,"w");
    fvsdebug = fopen(vsdebug3dfile,"w");
    frhodebug = fopen(rhodebug3dfile,"w");
    
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
                
				//now write the obtained file to text - this is for debugging purposes
                fprintf(fvpdebug," %f \n",vp[ip]);
                fprintf(fvsdebug," %f \n",vs[ip]);
                fprintf(frhodebug," %f \n",rho[ip]);
			}
		}
		//increment a counter
		printf("Completed write of properties at latitude %i of %i.\n",iy+1,location->nY);
        
		//now write the obtained file in binary
		fwrite(vp,sizeof(vp[0]),location->nX*location->nZ,fvp);
		fwrite(vs,sizeof(vs[0]),location->nX*location->nZ,fvs);
		fwrite(rho,sizeof(rho[0]),location->nX*location->nZ,frho);
	}
	fclose(fvp);
	fclose(fvs);
	fclose(frho);
    printf("Binary file write complete.\n");
    
    /*
    // generate file for writing
    fp = fopen("E:\\veloModel.txt","w");
//    fprintf(fp, "Longitude Depth Latitude Vp Vs Rho\n");


    double currRho, currVp, currVs;
    for(int i = 0; i < location->nX; i++)
    {
        for(int j = 0; j < location->nY; j++)
        {
            for(int m = 0; m < location->nZ; m++)
            {
                currVp = globDataVals->Vp[i][j][m];
                currRho = globDataVals->Rho[i][j][m];
                currVs = globDataVals->Vs[i][j][m];

                if( i == (location->nX-1) && j == (location->nY-1) && m == (location->nZ-1))
                {
					if (currVp != currVp) // used only for Visual studio code
					{
						fprintf(fp, "%i,%i,%lf,NAN,NAN,NAN", i, j, location->Z[m]);
						//                    fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf",location->Lat[i][j],location->Lon[i][j],location->Z[m], currVp, currVs, currRho);

					}
					else
					{
						fprintf(fp, "%i,%i,%lf,%lf,%lf,%lf", i, j, location->Z[m], currVp, currVs, currRho);
						//                    fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf",location->Lat[i][j],location->Lon[i][j],location->Z[m], currVp, currVs, currRho);
					}
                }
				else
				{
					if (currVp != currVp) // used only for Visual studio code
					{
						fprintf(fp, "%i,%i,%lf,NAN,NAN,NAN\n", i, j, location->Z[m]);
						//                    fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf",location->Lat[i][j],location->Lon[i][j],location->Z[m], currVp, currVs, currRho);

					}
					else
					{
					
					fprintf(fp, "%i,%i,%lf,%lf,%lf,%lf\n", i, j, location->Z[m], currVp, currVs, currRho);
					//                    fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf\n",location->Lat[i][j],location->Lon[i][j],location->Z[m], currVp, currVs, currRho);
					}
                }

//                fprintf(fp, "%lf,%lf,%lf,%lf,%lf,%lf\n",location->Lon[i][j], location->Z[m], location->Lat[i][j], currVp, currVs, currRho);
                
            }
        }
    }
  
     fclose(fp);
    

     printf("Completed writing data to file.\n");
     
     // generate file for writing
     FILE *fp2;
     fp2 = fopen("/Users/EthanT/Desktop/veloModelLatSlice.txt","w");
     //fprintf(fp2, "Longitude Depth Latitude Vp Vs Rho\n");
     
     int j = location->nY/2;
     printf("%i",j);
     for(int i = 0; i < location->nX; i++)
     {
     for(int m = 0; m < location->nZ; m++)
     {
     currVp = globDataVals->Vp[i][j][m];
     currRho = globDataVals->Rho[i][j][m];
     currVs = globDataVals->Vs[i][j][m];
     fprintf(fp2, "%lf, %lf, %lf, %lf, %lf\n",location->Lon[i][j], location->Z[m], currVp, currVs, currRho);
     
     }
     
     }
     
     fclose(fp2);
     
     // generate file for writing
     FILE *fp3;
     fp3 = fopen("/Users/EthanT/Desktop/veloModelLonSlice.txt","w");
     //fprintf(fp3, "Longitude Depth Latitude Vp Vs Rho\n");
     
     int i = location->nX/2;
     for(int j = 0; j < location->nY; j++)
     {
     for(int m = 0; m < location->nZ; m++)
     {
     currVp = globDataVals->Vp[i][j][m];
     currRho = globDataVals->Rho[i][j][m];
     currVs = globDataVals->Vs[i][j][m];
     fprintf(fp3,"%lf, %lf, %lf, %lf, %lf\n",location->Lat[i][j], location->Z[m], currVp, currVs, currRho);
     }
     }
     fclose(fp3);
     */
    
}

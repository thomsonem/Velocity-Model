//
//  sliceFunctions.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 1/03/15.
//  Copyright (c) 2015 Dept. Civil Engineering. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"


void generateSlice(modOrigin modelOrigin, modExtent modelExtent, sliceExtent sliceBounds, modVersion modelVersion)
{
    globalDataValues *globDataVals = NULL;
    surfaceDepthsGlobal *surfDepsGlob = NULL;
    sliceExtractData *sliceData;
    sliceData = malloc(sizeof(sliceExtractData));
    generateSliceXYpoints(sliceData, modelOrigin, modelExtent, sliceBounds);
    
    
    // generate the model grid
    gridStruct *location;
    location = malloc(sizeof(gridStruct));
    int nZ = (sliceBounds.zMax-sliceBounds.zMin)/sliceBounds.resZ + 1;
    
    location->nX = sliceData->nPts;
    location->nY = 1;
    location->nZ = nZ;
    
    // ensure the number of points does not exceed that of the struct preallocation
    assert(location->nX<=LON_GRID_DIM_MAX);
    assert(location->nY<=LAT_GRID_DIM_MAX);
    assert(location->nZ<=DEP_GRID_DIM_MAX);
    for(int i = 0; i < sliceData->nPts; i++)
    {
        location->Lat[i][0] = sliceData->latPts[i];
        location->Lon[i][0] = sliceData->lonPts[i];
    }
    for(int j = 0; j < nZ; j++)
    {
        location->Z[j] = -1000*(sliceBounds.zMin + sliceBounds.resZ*(j+0.5));
    }

    
    // obtain surface filenames based off version number
    surfNames surfSubModNames;
    surfSubModNames = getSurfSubModNames(modelVersion);
    
    // determine the depths of each surface for each lat lon point
    
    surfDepsGlob = getSurfaceValues(location, surfSubModNames);
    
    // assign values
    globDataVals = assignValues(modelVersion, location, surfSubModNames, surfDepsGlob);
    
    
    
    
    // loop over points and extract values
    for(int i = 0; i < sliceData->nPts; i++)
    {
        for(int k = 0; k < location->nZ; k++)
        {
            sliceData->Vp[i][k] = globDataVals->Vp[i][0][k];
            sliceData->Vs[i][k] = globDataVals->Vs[i][0][k];
            sliceData->Rho[i][k] = globDataVals->Rho[i][0][k];

        }
    }
    
    // generate file for writing
    FILE *fp2;
	double currRho, currVp, currVs; 
	fp2 = fopen("/home/ethan/share/veloModelSliceGenerated.txt", "w");

    for(int i = 0; i < sliceData->nPts; i++)
    {
        for(int m = 0; m < location->nZ; m++)
        {
            currVp = sliceData->Vp[i][m];
            currRho = sliceData->Rho[i][m];
            currVs = sliceData->Vs[i][m];
			if (currVp != currVp) // used only for Visual studio code
			{
				//printf("%lf,%lf,%lf,NAN,NAN,NAN\n", sliceData->lonPts[i], sliceData->latPts[i], location->Z[m]);
				fprintf(fp2, "%lf,%lf,%lf,NAN,NAN,NAN\n", sliceData->lonPts[i], sliceData->latPts[i], location->Z[m]);
			}
			else
			{
				//printf("%lf,%lf,%lf,%lf,%lf,%lf\n", sliceData->lonPts[i], sliceData->latPts[i], location->Z[m], currVp, currVs, currRho);
				fprintf(fp2, "%lf,%lf,%lf,%lf,%lf,%lf\n", sliceData->lonPts[i], sliceData->latPts[i], location->Z[m], currVp, currVs, currRho);
			}
            //            fprintf(fp2, "%lf\t%lf\t%lf\n",sliceData->latPts[i], location->Z[m], currVp);
            
//            fprintf(fp2, "%lf\t%lf\t%lf\n",sliceData->latPts[i], location->Z[m], currVp);
            
        }
        
    }
   
	fclose(fp2);
	//free(location);
	//free(sliceData);
}

void extractSlice(gridStruct *location, modOrigin modelOrigin, modExtent modelExtent, sliceExtent sliceBounds)
{
    
    sliceExtractData *sliceData;
    sliceData = malloc(sizeof(sliceExtractData));
    generateSliceXYpoints(sliceData, modelOrigin, modelExtent, sliceBounds);
    
    globalDataValues *globDataVals;
    globDataVals = loadCvmDataAll(location);
    
    // loop over points
    int xInd = 0;
    int yInd = 0;
    double X1, X2, Y1, Y2;
    double Q11Vp, Q12Vp, Q21Vp, Q22Vp;
    double Q11Vs, Q12Vs, Q21Vs, Q22Vs;
    double Q11Rho, Q12Rho, Q21Rho, Q22Rho;
    
    for(int i = 0; i < sliceData->nPts; i++)
    {
        // if x or y value is outside of the bound of the dataset return NaNs.
        if(sliceData->xPts[i]<location->X[0] || sliceData->xPts[i]>location->X[location->nX-1] || sliceData->yPts[i]>location->Y[location->nY-1] || sliceData->yPts[i]<location->Y[0] )
        {
            for(int k = 0; k < location->nZ; k++)
            {
                sliceData->Vp[i][k] = NAN;
                sliceData->Vs[i][k] = NAN;
                sliceData->Rho[i][k] = NAN;
            }
        }
        else  // get indice of nearby points
        {
            for(int k = 0; k < location->nX; k++)
            {
                if(location->X[k]>=sliceData->xPts[i])
                {
                    xInd = k-1;
                    break;
                }
            }
            for(int j = 0; j < location->nY; j++)
            {
                if(location->Y[j]>=sliceData->yPts[i])
                {
                    yInd = j-1;
                    break;
                }
            }
            // interpolate points
            X1 = location->X[xInd];
            X2 = location->X[xInd+1];
            Y1 = location->Y[yInd];
            Y2 = location->Y[yInd+1];
            for(int k = 0; k < location->nZ; k++)
            {
                // Vs
                Q11Vs = globDataVals->Vs[xInd][yInd][k];
                Q12Vs = globDataVals->Vs[xInd][yInd+1][k];
                Q21Vs = globDataVals->Vs[xInd+1][yInd][k];
                Q22Vs = globDataVals->Vs[xInd+1][yInd+1][k];
                
                sliceData->Vs[i][k] = biLinearInterpolation(X1, X2, Y1, Y2, Q11Vs, Q12Vs, Q21Vs, Q22Vs, sliceData->xPts[i], sliceData->yPts[i]);
                
                // Vp
                Q11Vp = globDataVals->Vp[xInd][yInd][k];
                Q12Vp = globDataVals->Vp[xInd][yInd+1][k];
                Q21Vp = globDataVals->Vp[xInd+1][yInd][k];
                Q22Vp = globDataVals->Vp[xInd+1][yInd+1][k];
                
                sliceData->Vp[i][k] = biLinearInterpolation(X1, X2, Y1, Y2, Q11Vp, Q12Vp, Q21Vp, Q22Vp, sliceData->xPts[i], sliceData->yPts[i]);
                
                // Rho
                Q11Rho = globDataVals->Rho[xInd][yInd][k];
                Q12Rho = globDataVals->Rho[xInd][yInd+1][k];
                Q21Rho = globDataVals->Rho[xInd+1][yInd][k];
                Q22Rho = globDataVals->Rho[xInd+1][yInd+1][k];
                
                sliceData->Rho[i][k] = biLinearInterpolation(X1, X2, Y1, Y2, Q11Rho, Q12Rho, Q21Rho, Q22Rho, sliceData->xPts[i], sliceData->yPts[i]);
            }
        }
        
    }
    
    // generate file for writing
    FILE *fp2;
    double currRho, currVp, currVs;
    fp2 = fopen("E:\veloModelSliceExtracted.txt","w");
	printf("File opened for writing.\n");
    for(int i = 0; i < sliceData->nPts; i++)
    {
        for(int m = 0; m < location->nZ; m++)
        {
            currVp = sliceData->Vp[i][m];
            currRho = sliceData->Rho[i][m];
            currVs = sliceData->Vs[i][m];
            //            fprintf(fp2, "%lf\t%lf\t%lf\n",sliceData->latPts[i], location->Z[m], currVp);
            fprintf(fp2, "%lf,%lf,%lf,%lf,%lf,%lf\n",sliceData->lonPts[i],sliceData->latPts[i], location->Z[m], currVp, currVs, currRho);
            
        }
        
    }
    
    fclose(fp2);
    
}




globalDataValues* loadCvmDataAll(gridStruct *location)
{
    globalDataValues *globDataVals;
    globDataVals = malloc(sizeof(globalDataValues));
    FILE *fvp, *fvs, *frho;
    char vp3dfile[] = "E:\\vp3dfile.p";
    char vs3dfile[] = "E:\\vs3dfile.s";
    char rho3dfile[] = "E:\\rho3dfile.d";
    float *vp, *vs, *rho;
    int bsize, ip;
    
    fvp = fopen(vp3dfile,"r");
    fvs = fopen(vs3dfile,"r");
    frho = fopen(rho3dfile,"r");
    
    bsize = location->nX*location->nZ*sizeof(float);
    vp = (float*) malloc(bsize);
    vs = (float*) malloc(bsize);
    rho = (float*) malloc(bsize);
    
    for(int iy = 0; iy < location->nY; iy++)
    {
        //increment a counter
        printf("%d / %d complete \n",iy+1,location->nY);
        
        //now read the obtained file in binary
        fread(vp,sizeof(vp[0]),location->nX*location->nZ,fvp);
        fread(vs,sizeof(vs[0]),location->nX*location->nZ,fvs);
        fread(rho,sizeof(rho[0]),location->nX*location->nZ,frho);
        for(int iz = 0; iz < location->nZ; iz++)
        {
            for (int ix = 0; ix < location->nX; ix++)
            {
                ip = ix + iz * location->nX;  //index counter
                globDataVals->Vp[ix][iy][iz] = vp[ip];
                globDataVals->Vs[ix][iy][iz] = vs[ip];
                globDataVals->Rho[ix][iy][iz] = rho[ip];
            }
        }
    }
    fclose(fvp);
    fclose(fvs);
    fclose(frho);
    
    return globDataVals;
}





void generateSliceXYpoints(sliceExtractData *sliceData, modOrigin modelOrigin, modExtent modelExtent, sliceExtent sliceBounds)
{
    int nBranches = sliceBounds.nSections;
    int nGrdPts;
    double deltaLat;
    double deltaLon;
    int count = 0;
    double distX, distY;
    double locationXY[2];
    double dLatRot, dLonRot;
    singleGridPoint rotatedGridPoint;
    
    
    for(int i = 0; i < nBranches; i++)
    {
        nGrdPts = sliceBounds.resXY;
        deltaLat = (sliceBounds.latPtsSlice[i]-sliceBounds.latPtsSlice[i+1])/nGrdPts;
        deltaLon = (sliceBounds.lonPtsSlice[i]-sliceBounds.lonPtsSlice[i+1])/nGrdPts;
        for(int j = 0; j < nGrdPts+1; j++)
        {
            sliceData->lonPts[count] = sliceBounds.lonPtsSlice[i]-j*deltaLon;
            sliceData->latPts[count] = sliceBounds.latPtsSlice[i]-j*deltaLat;
            
            locationXY[0] = modelOrigin.mlat;
            locationXY[1] = sliceData->lonPts[count];
            
            distX = LatLonToDistance(locationXY, modelOrigin);
            
            locationXY[0] =sliceData->latPts[count];
            locationXY[1] = modelOrigin.mlon;
            
            distY = LatLonToDistance(locationXY, modelOrigin);
            
            dLatRot = modelOrigin.mlat - sliceData->latPts[count];
            dLonRot = modelOrigin.mlon - sliceData->lonPts[count];
            
            
            if(dLatRot < 0)
            {
                distY = -distY;
            }
            
            if (dLonRot < 0)
            {
                distX = - distX;
            }
            
            rotatedGridPoint = rotateGrid(modelOrigin.mrot, distX, distY);
            
            sliceData->xPts[count] = rotatedGridPoint.X;
            sliceData->yPts[count] = rotatedGridPoint.Y;
            
            count += 1;
        }
    }
    sliceData->nPts = count;
    assert(sliceData->nPts<=MAX_NUM_SLICE_GRIDPTS);
}







 //
//  functions.h
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#ifndef functions_h
#define functions_h

// extraction and file I/O
extern void generateProfile(modOrigin modelOrigin, modVersion modelVersion, modExtent modelExtent, char *outputDirectory);
extern void writeAllBasinSurfaceDepths(globalBasinData *basinData, gridStruct *location, char *outputDirectory);
extern void writeBasinSurfaceDepths(globalBasinData *basinData, gridStruct *location, char *outputDirectory);
extern void writeIndividualProfile(globalDataValues *globalValues, gridStruct *location, char *outputDirectory);

// slice functions
extern void generateSlice(modOrigin modelOrigin, sliceExtent sliceBounds, modVersion modelVersion,  char *outputDirectory);
extern void extractSlice(gridStruct *location, modOrigin modelOrigin, sliceExtent sliceBounds, char *outputDirectory);
extern void generateSliceXYpoints(sliceExtractData *sliceData, modOrigin modelOrigin, sliceExtent sliceBounds);
extern globalDataValues* loadCvmDataAll(gridStruct *location, char *outputDirectory);



// primary functions
extern surfNames getSurfSubModNames(modVersion modelVersion);
extern surfaceDepthsGlobal *getSurfaceValues(gridStruct *location, surfNames surfSubModNames);
extern gridStruct *generateModelGrid(modOrigin modelOrigin, modExtent modelExtent);
extern globalDataValues *assignValues(modVersion modelVersion, gridStruct *location, surfNames surfSubModNames, surfaceDepthsGlobal *surfDepsGlob, char *outputDirectory);
extern void writeCVMData(gridStruct *location, globalDataValues *globDataVals, char *outputDirectory);
extern gridStruct *generateLatLonForPlotting(modOrigin modelOrigin, modExtent modelExtent, double latPts[], double lonPts[], int nPts);
extern void writeLatLonData(gridStruct *location, globalDataValues *globDataVals, char *outputDirectory);
extern void writeGridPoints(gridStruct *location, char *outputDirectory);




// secondary functions
extern void writeVeloModLogFile(int argc, char *argv[]);
extern surfRead *loadSurface(char *fileName);
extern indexStruct calculateSurfaceLatLonIndex(surfRead currentSurface, double x, double y);
extern double IDW(surfVec *depVec, double x, double y, double power, double radius);
extern double linearInterpolation(double p1, double p2, double v1, double v2, double p3);
extern double biLinearInterpolation(double X1, double X2, double Y1, double Y2, double Q11, double Q12, double Q21, double Q22, double X, double Y);
extern velo1D *load1dVeloSubModel(char *fileName);
extern int findSubVeloModelInd(gridStruct *location, int lonInd, int latInd, int depInd, int nVeloSubMod, surfaceDepthsGlobal *surfDepsGlob);
extern depInterpVals generateSurfaceValuesAllDepths(surfVecGlobal *vector, gridStruct location, int elev[], int nElev, double power, double radius);
extern void loadBoundary(globalBasinData *basinData, int basinNum);
extern int pointInPoly(globalBasinData *basinData, int basinNum, int boundaryNum, double xLoc, double yLoc);
extern void plotExtracts(void);
extern adjacentPointsStruct findAdjacentPoints(surfRead *surface, double lat, double lon);
extern void determineIfWithinBasinLatLon(gridStruct *location, int basinNum, globalBasinData *basinData);


// surface functions
extern void enforceSurfaceDepths(globalBasinData *basinData, int xInd, int yInd, int basinNum);
extern surfVec *generateSurfaceVectors(surfRead *surfStruct);
extern surfDepValues *determineSurfaceDepths(gridStruct *location, char *fileName);
extern surfDepValues *determineSurfaceDepthsBasin(globalBasinData *basinData ,gridStruct *location, char *fileName, int basinNum, int surfNum);
extern surfDepValues *negInfSurf(gridStruct *location);
extern surfDepValues *posInfSurf(gridStruct *location);
extern surfDepValues *basementRockSurf(gridStruct *location);
extern surfDepValues *demSurf(gridStruct *location);


// basin velocity submodel functions CHCH
extern valStructLocal *christchurchSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *riccartonSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *bromleySubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *linwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *heathcoteSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *burwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *shirleySubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *DEMtoPlioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *plioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *mioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *paloegeneSubMod(gridStruct *location, int xInd, int yInd, int zInd);
extern valStructLocal *cretaceousSubMod(gridStruct *location, int xInd, int yInd, int zInd);




// sub velocity functions 
extern void v1DsubMod(int xInd, int yInd, int zInd, globalDataValues *golbalValues, gridStruct *location, velo1D *subModel1D);
extern velo1D *loadv1DsubMod(void);

extern void EPtomo2010subMod(int xInd, int yInd, int zInd, globalDataValues *globalValues, gridStruct *location, depInterpVals *EPtomoData);
extern depInterpVals *loadEPtomo2010subMod(gridStruct *location);

extern void NaNsubMod(int xInd, int yInd, int zInd, globalDataValues *golbalValues);


// Basin data
extern void loadCanterburyBasinData(gridStruct *location, int basinNum, globalBasinData *basinData);

extern void determineBasinProperties(globalBasinData *basinData, int basinNum, int xInd, int yInd, int zInd, gridStruct *location);
extern void loadBasinSurfaces(gridStruct *location, int basinNum, globalBasinData *basinData);
extern void enforceBasinSurfaceDepths(gridStruct *location, int basinNum, globalBasinData *basinData);
extern void assignBasinProperties(gridStruct *location, int basinNum, globalBasinData *basinData);
extern void loadBasin(gridStruct *location, int basinNum, globalBasinData *basinData);

// math functions
extern double LatLonToDistance(double locationLatLon[], modOrigin modelOrigin);
extern singleGridPoint XYtoLatLon(double locationXY[],  modOrigin modelOrigin);
extern singleGridPoint pointRadialDistance(double refLatLon[],double bearing, double distance);
extern double rad2deg(double angRad);
extern double deg2rad(double angDeg);
extern singleGridPoint rotateGrid(double rotAngle, double X, double Y);








#endif

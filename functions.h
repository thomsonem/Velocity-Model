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
//extern void generateProfile(modOrigin modelOrigin, modVersion modelVersion, modExtent modelExtent, char *outputDirectory);
//extern void writeAllBasinSurfaceDepths(globalBasinData *basinData, gridStruct *location, char *outputDirectory);
//extern void writeBasinSurfaceDepths(globalBasinData *basinData,  int basinNum, gridStruct *location, char *outputDirectory);
//extern void writeIndividualProfile(globalDataValues *globalValues, gridStruct *location, char *outputDirectory);

// slice functions
//extern void generateSlice(modOrigin modelOrigin, sliceExtent sliceBounds, modVersion modelVersion,  char *outputDirectory);
//extern void extractSlice(gridStruct *location, modOrigin modelOrigin, sliceExtent sliceBounds, globalDataValues *globDataVals, char *outputDirectory, int sliceNumber);
//extern void generateSliceXYpoints(sliceExtractData *sliceData, modOrigin modelOrigin, sliceExtent sliceBounds);
//extern globalDataValues* loadCvmDataAll(gridStruct *location, char *outputDirectory);



// primary functions
extern global_model_parameters *getGlobalModelParameters(double modelVersion);
//extern surfaceDepthsGlobal *getSurfaceValues(surfNames *surfSubModNames);
extern void loadAllGlobalData(global_model_parameters *GLOBAL_MODEL_PARAMETERS,calculation_log *CALCULATION_LOG, velo_mod_1d_data *VELO_MOD_1D_DATA, nz_tomography_data *NZ_TOMOGRAPHY_DATA, global_surfaces *GLOBAL_SURFACES, basin_data *BASIN_DATA);
extern global_mesh *generateFullModelGrid(model_extent MODEL_EXTENT);
extern qualities_vector *assignQualities(global_model_parameters *GLOBAL_MODEL_PARAMETERS, velo_mod_1d_data *VELO_MOD_1D_DATA, nz_tomography_data *NZ_TOMOGRAPHY_DATA, global_surfaces *GLOBAL_SURFACES, basin_data *BASIN_DATA, mesh_vector *MESH_VECTOR,calculation_log *CALCULATION_LOG);
extern mesh_vector *extractMeshVector(partial_global_mesh *PARTIAL_GLOBAL_MESH, int lonInd);
extern void writeGlobalQualities(partial_global_mesh *PARTIAL_GLOBAL_MESH, partial_global_qualities *PARTIAL_GLOBAL_QUALITIES, calculation_log *CALCULATION_LOG, int latInd);
//extern gridStruct *generateLatLonForPlotting(modOrigin modelOrigin, modExtent modelExtent, double latPts[], double lonPts[], int nPts);
extern void loadGlobalSurfaceData(global_surfaces *GLOBAL_SURFACES, global_model_parameters *GLOBAL_MODEL_PARAMETERS);
extern global_surf_read *loadGlobalSurface(char *fileName);
extern basin_surf_read *loadBasinSurface(char *fileName);
//void loadBasinBoundaries(int basinNum, basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
extern partial_global_surface_depths *interpolateGlobalSurfaceDepths(global_surfaces *GLOBAL_SURFACES, mesh_vector *MESH_VECTOR ,calculation_log *CALCULATION_LOG);





//extern void writeLatLonData(gridStruct *location, globalDataValues *globDataVals, char *outputDirectory);
//extern void writeGridPoints(gridStruct *location, char *outputDirectory);




// secondary functions
extern void writeVeloModInputsLogFile(int argc, char *argv[]);
//extern void writeVeloModLogFile(int argc, char *argv[],calculationLogStruct *logStruct);
//extern void writeSliceParametersLogFile(sliceParams *sliceParameters, modVersion modelVersion, gridStruct *location, char *outputDirectory, char *type);
//extern indexStruct calculateSurfaceLatLonIndex(surfRead currentSurface, double x, double y);
//extern double IDW(surfVec *depVec, double x, double y, double power, double radius);
extern double linearInterpolation(double p1, double p2, double v1, double v2, double p3);
extern double biLinearInterpolation(double X1, double X2, double Y1, double Y2, double Q11, double Q12, double Q21, double Q22, double X, double Y);
extern int findGlobalSubVeloModelInd(double depth, partial_global_surface_depths *PARTIAL_GLOBAL_SURFACE_DEPTHS);



//extern depInterpVals generateSurfaceValuesAllDepths(surfVecGlobal *vector, gridStruct location, int elev[], int nElev, double power, double radius);
//extern int pointInPoly(globalBasinData *basinData, int basinNum, int boundaryNum, double xLoc, double yLoc);
extern void plotExtracts(void);
extern adjacent_points *findGlobalAdjacentPoints(global_surf_read *GLOBAL_SURF_READ, double lat, double lon);
extern void findCornerInds(global_surf_read *GLOBAL_SURF_READ, double latPt, double lonPt, adjacent_points *ADJACENT_POINTS);
extern void findEdgeInds(global_surf_read *GLOBAL_SURF_READ, adjacent_points *ADJACENT_POINTS, int edgeType);
//extern void writeAllSurfaceDepths(gridStruct *location, surfDepValues *surfDep, char *outputDirectory);
//extern void determineIfWithinBasinLatLon(gridStruct *location, int basinNum, globalBasinData *basinData);
extern sliceParams *readExtractedSliceParametersFile(char *sliceParametersDirectory);
extern sliceParams *readGeneratedSliceParametersFile(char *sliceParametersDirectory);
//extern void writeGlobalSurfaceDepths(surfaceDepthsGlobal *surfDepGlob, gridStruct *location, surfNames *surfSubModNames, char *outputDirectory);
//extern void writeAllGlobalSurfaceDepths(surfaceDepthsGlobal *surfDepGlob, gridStruct *location, surfNames *surfSubModNames, char *outputDirectory);
extern partial_global_mesh *extractPartialMesh(global_mesh *GLOBAL_MESH, int latInd);



// surface functions
//extern void enforceSurfaceDepths(globalBasinData *basinData, int xInd, int yInd, int basinNum);
//extern surfVec *generateSurfaceVectors(surfRead *surfStruct);
//extern surfDepValues *determineSurfaceDepths(gridStruct *location, char *fileName);
//extern surfDepValues *determineSurfaceDepthsBasin(globalBasinData *basinData ,gridStruct *location, char *fileName, int basinNum, int surfNum);
//extern surfDepValues *negInfSurf(gridStruct *location);
//extern surfDepValues *posInfSurf(gridStruct *location);
//extern surfDepValues *basementRockSurf(gridStruct *location);
//extern surfDepValues *demSurf(gridStruct *location);



// basin velocity submodel functions CHCH
//extern valStructLocal *christchurchSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *riccartonSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *bromleySubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *linwoodSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *heathcoteSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *burwoodSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *shirleySubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *wainoniSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *DEMtoPlioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *plioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *mioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *paleogeneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *cretaceousSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *BPVSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);
//extern valStructLocal *v1DBasinSubMod(gridStruct *location, int zInd, velo1D *subModel1D);
//extern valStructLocal *WheatheredBPVSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum);





// sub velocity functions 
extern void v1DsubMod(int zInd, double dep, qualities_vector *QUALITIES_VECTOR, velo_mod_1d_data *VELO_MOD_1D_DATA);
extern void load1dVeloSubModel(char *fileName, velo_mod_1d_data *VELO_MOD_1D_DATA);

extern void EPtomo2010subMod(int zInd, double dep, mesh_vector *MESH_VECTOR, qualities_vector *QUALITIES_VECTOR, nz_tomography_data *NZ_TOMOGRAPHY_DATA);
extern void loadEPtomoSurfaceData(char *tomoType, nz_tomography_data *NZ_TOMOGRAPHY_DATA);
extern void NaNsubMod(int zInd, qualities_vector *QUALITIES_VECTOR);


// Basin data
//extern void loadCanterburyBasinData(int basinNum, globalBasinData *basinData);
//extern void loadPreQCanterburyBasinData(int basinNum, globalBasinData *basinData);
//extern void loadPreQCanterburyBasinData1D(int basinNum, globalBasinData *basinData);
//extern void loadQCanterburyBasinData(int basinNum, globalBasinData *basinData);
//extern void loadPreQCanterburyBasinDataPaleogeneMiocene(int basinNum, globalBasinData *basinData);
//extern void loadPreQCanterburyBasinDataPaleogene(int basinNum, globalBasinData *basinData);
//extern void loadBPVBasinData(int basinNum, globalBasinData *basinData);
//extern void loadBPVWheatheredBasinData(int basinNum, globalBasinData *basinData);

extern void loadBasinData(basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS);


//extern void determineBasinProperties(globalBasinData *basinData, int basinNum, int xInd int yInd, int zInd, gridStruct *location, velo1D *subModel1D);
//extern void loadAllBasinSurfaces(int basinNum, basin_data *BASIN_DATA, global_model_parameters *GLOBAL_MODEL_PARAMETERS)
//extern void enforceBasinSurfaceDepths(gridStruct *location, int basinNum, globalBasinData *basinData);
//extern void assignBasinProperties(gridStruct *location, int basinNum, globalBasinData *basinData);
//extern basin_data *loadBasinData(global_model_parameters *GLOBAL_MODEL_PARAMETERS);

// math functions
extern double LatLonToDistance(double locationLatLon[], double originLat, double originLon);
extern singleGridPoint XYtoLatLon(double locationXY[], double originLat, double originLon, double originRot);
extern singleGridPoint pointRadialDistance(double refLatLon[],double bearing, double distance);
extern double rad2deg(double angRad);
extern double deg2rad(double angDeg);
extern singleGridPoint rotateGrid(double rotAngle, double X, double Y);
extern float float_swap(const float inFloat);
extern int endian(void);




extern calculation_log *initializeCalculationLog(int argc, char *argv[]);





#endif

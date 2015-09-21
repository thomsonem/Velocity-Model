//
//  basinSubModels.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 4/08/14.
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

// Christchurch formation sub-model
valStructLocal *christchurchSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_silt * pow((effectiveStress/P_a),ns_marine);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971; // in kg/m3
    values->Vp = 1.6; // in km/s
//    values->Vs = 0.17; // in km/s
    
    return values;
}

// Riccarton gravels sub-model
valStructLocal *riccartonSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_gravel * pow((effectiveStress/P_a),ns_gravel);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.4;
    
    return values;
}

// Bromley formation sub-model
valStructLocal *bromleySubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_silt * pow((effectiveStress/P_a),ns_marine);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.3;
    
    return values;
}

// Linwood gravel sub-model
valStructLocal*linwoodSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_gravel * pow((effectiveStress/P_a),ns_gravel);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.5;
    
    return values;
}

// Heathcote formation sub-model
valStructLocal *heathcoteSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_silt * pow((effectiveStress/P_a),ns_marine);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.4;
    
    return values;
}

// Burwood gravel sub-model
valStructLocal *burwoodSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_gravel * pow((effectiveStress/P_a),ns_gravel);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.6;
    
    return values;
}

// Shirley formation sub-model
valStructLocal *shirleySubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_silt * pow((effectiveStress/P_a),ns_marine);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.4;
    
    return values;
}

// Wainoni gravels sub-model
valStructLocal *wainoniSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
    valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_gravel * pow((effectiveStress/P_a),ns_gravel);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.6;
    
    return values;
}

//  DEM to pliocene surface sub-model (same as shirley formation)
valStructLocal *DEMtoPlioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    double Z, totalStress, effectiveStress, Vs;
    Z = basinData->surfVals[basinNum][xInd][yInd][0] - location->Z[zInd]; // zero indice represents the first surface, should always be the DEM
    totalStress = Z * rho_const; // kPa
    effectiveStress = totalStress - Z * 9.81; // kPa
    Vs = As_silt * pow((effectiveStress/P_a),ns_marine);
    values->Vs = Vs; // in km/s
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
//    values->Vs = 0.4;
    
    return values;
}


//=================================================================

//          PRE QUATERNARY MODELS

//=================================================================

// Pliocene sub-model
valStructLocal *plioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.905;
    values->Vp = 2;
    values->Vs = 0.6086;
    
    return values;
}

// Miocene sub-model
valStructLocal *mioceneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 2.0931;
    values->Vp = 2.5;
    values->Vs = 0.98355;
    
    return values;
}

// Paleogene sub-model
valStructLocal *paleogeneSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 2.151;
    values->Vp = 2.7;
    values->Vs = 1.1511;
    
    return values;
}

//=================================================================

//          BPV MODEL

//=================================================================

// BPV sub-model
valStructLocal *BPVSubModel(gridStruct *location, globalBasinData *basinData, int xInd, int yInd, int zInd, int basinNum)
{
    valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Vp = 3.5;
    values->Rho = 2.3184;
    values->Vs = 1.8554;
    
    return values;
}




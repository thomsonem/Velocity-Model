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
valStructLocal *christchurchSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971; // in kg/m3
    values->Vp = 1.6; // in km/s
    values->Vs = 0.17; // in km/s
    
    return values;
}

// Riccarton gravels sub-model
valStructLocal *riccartonSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.4;
    
    return values;
}

// Bromley formation sub-model
valStructLocal *bromleySubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.3;
    
    return values;
}

// Linwood gravel sub-model
valStructLocal*linwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.5;
    
    return values;
}

// Heathcote formation sub-model
valStructLocal *heathcoteSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.4;
    
    return values;
}

// Burwood gravel sub-model
valStructLocal *burwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.6;
    
    return values;
}

// Shirley formation sub-model
valStructLocal *shirleySubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.4;
    
    return values;
}

// Wainoni gravels sub-model
valStructLocal *wainoniSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
    valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.4;
    
    return values;
}

//  DEM to pliocene surface sub-model (same as shirley formation)
valStructLocal *DEMtoPlioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.6971;
    values->Vp = 1.6;
    values->Vs = 0.4;
    
    return values;
}

// Pliocene sub-model
valStructLocal *plioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 1.905;
    values->Vp = 2;
    values->Vs = 0.6086;
    
    return values;
}

// Miocene sub-model
valStructLocal *mioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 2.0931;
    values->Vp = 2.5;
    values->Vs = 0.98355;
    
    return values;
}

// Paleogene sub-model
valStructLocal *paleogeneSubMod(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 2.151;
    values->Vp = 2.7;
    values->Vs = 1.1511;
    
    return values;
}





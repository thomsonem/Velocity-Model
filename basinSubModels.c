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
    
    values->Rho = 1; // in kg/m3
    values->Vp = 1; // in km/s
    values->Vs = 1; // in km/s
    
    return values;
}

// Riccarton gravels sub-model
valStructLocal *riccartonSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 2;
    values->Vp = 2;
    values->Vs = 2;
    
    return values;
}

// Bromley formation sub-model
valStructLocal *bromleySubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 3;
    values->Vp = 3;
    values->Vs = 3;
    
    return values;
}

// Linwood gravel sub-model
valStructLocal*linwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 4;
    values->Vp = 4;
    values->Vs = 4;
    
    return values;
}

// Heathcote formation sub-model
valStructLocal *heathcoteSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 5;
    values->Vp = 5;
    values->Vs = 5;
    
    return values;
}

// Burwood gravel sub-model
valStructLocal *burwoodSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 6;
    values->Vp = 6;
    values->Vs = 6;
    
    return values;
}

// Shirley formation sub-model
valStructLocal *shirleySubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 7;
    values->Vp = 7;
    values->Vs = 7;
    
    return values;
}

//  DEM to pliocene surface sub-model (same as shirley formation)
valStructLocal *DEMtoPlioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 7.5;
    values->Vp = 7.5;
    values->Vs = 7.5;
    
    return values;
}

// Pliocene sub-model
valStructLocal *plioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 8;
    values->Vp = 8;
    values->Vs = 8;
    
    return values;
}

// Miocene sub-model
valStructLocal *mioceneSubModel(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 9;
    values->Vp = 9;
    values->Vs = 9;
    
    return values;
}

// Paleogene sub-model
valStructLocal *paloegeneSubMod(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 10;
    values->Vp = 10;
    values->Vs = 10;
    
    return values;
}

// Cretaceous sub-model
valStructLocal *cretaceousSubMod(gridStruct *location, int xInd, int yInd, int zInd)
{
	valStructLocal *values = NULL;
    values = malloc(sizeof(valStructLocal));
    
    values->Rho = 11;
    values->Vp = 11;
    values->Vs = 11;
    
    return values;
}



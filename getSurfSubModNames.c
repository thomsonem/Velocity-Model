//
//  getSurfSubModNames.c
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/06/14.
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

surfNames getSurfSubModNames(modVersion modelVersion)
/*
 Purpose:   obtain the names of the surfaces and sub velocity models to be used
 
 Input variables:
 modelVersion -  structure containing the version of the model for generation
 
 Output variables:
 surfNames    -  structure containing the names of the surfaces and sub velocity models to be used
 */
{
    surfNames surfSubModNames;
    
    // Model Version 0.1, 1D velocity sub Model
    if(modelVersion.version == 0.1)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 2;
        surfSubModNames.nVeloSubMod = 1;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "v1DsubMod";
        
        surfSubModNames.nBasin = 0;
        
    }
    // Model Version 0.2, EP Tomography
    if(modelVersion.version == 0.2)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 2;
        surfSubModNames.nVeloSubMod = 1;

        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "negInfSurf";

        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "EPtomo2010subMod";

        surfSubModNames.nBasin = 0;

    }

    //  Model Version 0.3  CHCH BASIN
    else if(modelVersion.version ==0.3)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 3;
        surfSubModNames.nVeloSubMod = 2;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "demSurf";
        surfSubModNames.surf[2] = "negInfSurf";

        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "NaNsubMod";
        surfSubModNames.veloSubMod[1] = "NaNsubMod";
        
        // insert basin name / number
        surfSubModNames.basin[0] = "CANTERBURY_BASIN";
        surfSubModNames.nBasin = 1;

    }
    //  Model Version 0.4  w/ CHCH BASIN and 1D velocity model
    else if(modelVersion.version == 0.4)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 3;
        surfSubModNames.nVeloSubMod = 2;

        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "demSurf";
        surfSubModNames.surf[2] = "negInfSurf";

        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "NaNsubMod";
        surfSubModNames.veloSubMod[1] = "v1DsubMod";

        // insert basin name / number
        surfSubModNames.basin[0] = "CANTERBURY_BASIN";
        surfSubModNames.nBasin = 1;

    }
    //  Model Version 0.5  w/ CHCH BASIN and EP Tomo
    else if(modelVersion.version == 0.5)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 3;
        surfSubModNames.nVeloSubMod = 2;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "demSurf";
        surfSubModNames.surf[2] = "negInfSurf";
        
        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "NaNsubMod";
        surfSubModNames.veloSubMod[1] = "v1DsubMod";
        
        // insert basin name / number
        surfSubModNames.basin[0] = "CANTERBURY_BASIN";
        surfSubModNames.nBasin = 1;
        
    }
    //  Model Version 1.1  w/ 1D velo mod (Cant. 1D)
    else if(modelVersion.version == 1.1)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 2;
        surfSubModNames.nVeloSubMod = 1;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "v1DsubMod";
        
        surfSubModNames.nBasin = 0;

    }
    //  Model Version 1.2  w/ Tomography
    else if(modelVersion.version == 1.2)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 2;
        surfSubModNames.nVeloSubMod = 1;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "negInfSurf";
        
        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "EPtomo2010subMod";
        
        surfSubModNames.nBasin = 0;
    }
    //  Model Version 1.3  w/ 1D + basement w/ Tomography
    else if(modelVersion.version == 1.3)
    {
        // define the number of surfaces and sub models
        surfSubModNames.nSurf = 3;
        surfSubModNames.nVeloSubMod = 2;
        
        // insert surface surface keywords
        surfSubModNames.surf[0] = "posInfSurf";
        surfSubModNames.surf[1] = "basementRockSurf";
        surfSubModNames.surf[2] = "negInfSurf";

        // insert velocity submodel names
        surfSubModNames.veloSubMod[0] = "v1DsubMod";
        surfSubModNames.veloSubMod[1] = "EPtomo2010subMod";
        
        surfSubModNames.nBasin = 0;
    }
    
    assert(surfSubModNames.nSurf==(surfSubModNames.nVeloSubMod+1));
    printf("Surface Submodel Names Successfully Obtained.\n");
    return surfSubModNames;
    
}

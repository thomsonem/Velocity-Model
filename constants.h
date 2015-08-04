//
//  constants.h
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#ifndef constants_h
#define constants_h

#define SURF_IN_DIM_MAX 1022 // maximum dimension of surface input files (used in main and here)
#define LON_GRID_DIM_MAX 1501 // X
#define LAT_GRID_DIM_MAX 1201 // Y
#define DEP_GRID_DIM_MAX 1501 // Z
#define NUM_SURF_DIM_MAX 15 // the maximum number of surfaces
#define SURF_VEC_DIM_MAX 8442 // maximum length of surface vector // obsolete
#define SUB_MOD_DIM_MAX 50 // maximum number of entries in the 1d sub model arrays
#define MAX_NUM_BASINS 1 // the maxinum number of basins
#define MAX_DIM_BOUNDARY_FILE 1000 // naximum number of points to define a basin boundary
#define MAX_NUM_VELOSUBMOD 15 // max number of velo sub models in the basin
#define MAX_NUM_SLICE_GRIDPTS 5000 // the maximum number of grid points for slice extraction
#define MAX_NUM_SLICE_PIVOTS 4
#define MAX_NUM_BOUNDARIES 2 // the maximum number of boundaries per velocity model
#define EARTH_RADIUS_MEAN 6371.0071
#define MAX_NUM_SLICES 15 // the maximum number of slices
#define MAX_LAT_SURFACE_EXTENSION 1 // value in degrees the surface files may be extended by
#define MAX_LON_SURFACE_EXTENSION 1 // value in degrees the surface files may be extended by

#define P_a 101.325 // kPa
#define ns_marine 0.331
#define ns_gravel 0.273
#define rho_const 19.0 // t/m3
#define As_gravel 0.312 // m/s
#define As_silt 0.192 // m/s





#endif

#if !defined(M_PI)
    #define M_PI 3.14159

#endif
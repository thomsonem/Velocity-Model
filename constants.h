//
//  constants.h
//  CVMversions
//
//  Created by Ethan M. Thomson on 20/06/14.
//  Copyright (c) 2014 Dept. Civil Engineering. All rights reserved.
//

#ifndef constants_h
#define constants_h

#define GLOBAL_SURF_IN_DIM_MAX 1022 // maximum dimension of global surface input files
//#define BASIN_SURF_IN_DIM_MAX 1000 // maximum dimension of basin surface input files
#define LON_GRID_DIM_MAX 1401 // X
#define LAT_GRID_DIM_MAX 1201 // Y
#define DEP_GRID_DIM_MAX 561 // Z
#define SUB_MOD_DIM_MAX 50 // maximum number of entries in the 1d sub model arrays
#define MAX_NUM_BASINS 2 // the maxinum number of basins
#define MAX_NUM_GLOBAL_SURFACES 4 // the maxinum number of global (Full domain) surfaces
#define MAX_NUM_BASIN_SURFACES 9 // the maximum number of basin surfaces
#define MAX_NUM_1D_VELOCITY_MODELS 1 // the maximum number of 1D velocity models
#define MAX_NUM_BASIN_BOUNDARIES 3 // the maximum number of boundaries per velocity model



#define MAX_DIM_BOUNDARY_FILE 1500 // maximum number of points to define a basin boundary
//#define MAX_NUM_VELOSUBMOD 15 // max number of velo sub models in the basin
#define MAX_NUM_SLICE_GRIDPTS 5000 // the maximum number of grid points for slice extraction
#define MAX_NUM_SLICE_PIVOTS 4
#define MAX_NUM_TOMO_SURFACES 21 // the maximun number of Tomography surfaces able to be loaded
#define MAX_NUM_GLOBAL_SURFACES 4 // the maximum number of full domain (global) surfaces
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

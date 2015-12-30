/*
 * Copyright Ahnaf Siddiqui and Sameer Varma.
 */

#ifndef LLT_TRI_H
#define LLT_TRI_H

#include "triangle.h"
#include "vec.h"
#ifdef GRO_V5
#include "pargs.h"
#else
#include "statutil.h"
#endif


// Flags
enum {
	LLT_CORRECT = 1, // Correct areas for periodic bounding conditions
	LLT_PRINT = 2 // Print triangle data that can be visualized using, for example, the 'showme' program
};

// Struct for area output data.
// These are total surface area, divide a given area by natoms to get area per particle.
struct tri_area {
	real *area; // Triangulated areas indexed by [frame #]. *area are corrected areas for periodic bounds if LLT_CORRECT was used.
	real *area1; // Uncorrected areas, NULL if LLT_CORRECT wasn't used.
	real *area2; // Triangulated areas of combination of input points with their translated image. NULL if LLT_CORRECT wasn't used.
	int natoms, nframes; // Number of atoms and number of frames, respectively, that were triangulated.
};

void llt_tri_area(const char *traj_fname, const char *ndx_fname, output_env_t *oenv, 
	struct tri_area *areas, unsigned char flags);

real tri_surface_area(rvec *x, int natoms, unsigned char flags);

void print_areas(const char *fname, struct tri_area *areas);

void print_trifiles(struct triangulateio *tio, const char *node_name, const char *ele_name);

void free_tri_area(struct tri_area *areas);


inline real area_tri(rvec a, rvec b, rvec c) {
	rvec ab, ac, cpr;
	rvec_sub(b, a, ab);
	rvec_sub(c, a, ac);
	cprod(ab, ac, cpr);
	return norm(cpr) / 2.0;
}


#endif // LLT_TRI_H
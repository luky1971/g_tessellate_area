/*
 * Copyright Ahnaf Siddiqui
 */

#ifndef GKUT_IO_H
#define GKUT_IO_H

#include "vec.h"
#ifdef GRO_V5
#include "pargs.h"
#else
#include "statutil.h"
#endif

#define FRAMESTEP 500 // The number of new frames by which to reallocate an array of length # trajectory frames

void read_traj(const char *traj_fname, rvec ***x, int *nframes, int *natoms, output_env_t *oenv);
/* Reads a trajectory file. rvec **x is position coordinates indexed x[frame #][atom #]
 * 2D memory is allocated for x.
 */

void print_traj(rvec **x, int nframes, int natoms, const char *fname);
/* Prints the given 2D array of vectors to a text file with the given name.
 */

void ndx_get_indx(const char *ndx_fname, int numgroups, atom_id ***indx, int **isize);
/* Get indexes for a given number of groups from a given index file.
 * Indexes are put in 2D array **indx and number of indexes per group are put in 1D array *isize.
 * 2D memory is allocated for indx and 1D memory is allocated for isize.
 */

void filter_vecs(atom_id *indx, int isize, rvec *pre_x, rvec **new_x);
/* Creates a new 1D array of vectors new_x with only the coordinates from pre_x that are specified by the indexes in indx.
 * 1D memory is allocated for new_x.
 */

void ndx_filter_traj(const char *ndx_fname, rvec **pre_x, rvec ***new_x, int nframes, int *natoms);
/* Creates a new trajectory with only the coordinates from the old trajectory (pre_x) that are specified by the index file.
 * 2D memory is allocated for new_x.
 */

#endif // GKUT_IO_H
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "Molecule.hpp"
#include "Constants.hpp"

long double LJ_potential(Molecule mi, Molecule mj);

inline long double LJ_potential(Molecule mi, Molecule mj)
{
        double dx, dy, dz;
	long double r2, r6, r12, u;
	// distance between i-j
	dx = mj.qx - mi.qx;
	dy = mj.qy - mi.qy;
	dz = mj.qz - mi.qz;
	r2 = dx * dx + dy * dy + dz * dz;
	if (r2 > cutoff_distance^2) return 0;
	r6 = r2 * r2 * r2; 
	r12 = r6 * r6;
	// LJ potential (sigma and epsilon = 1.0 for simplicity.)
	u = 4.0 * (1.0 / r12 - 1.0 / r6) + C0;
	return u;
}
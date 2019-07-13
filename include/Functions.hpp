#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <math>
#include <random>
#include <vector>
#include "Molecule.hpp"
#include "Constants.hpp"

long double LJ_potential(Molecule& mi, Molecule& mj);
void init_MB_velosity(Molecule& m);

inline long double LJ_potential(Molecule& mi, Molecule& mj)
{
        double dx, dy, dz;
	long double r2, r6, r12, u;
	// distance between i-j
	dx = mj.qx - mi.qx;
	dy = mj.qy - mi.qy;
	dz = mj.qz - mi.qz;
	r2 = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);
	// the force from molecule mj to molecule mi will be ignored when r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3); 
	r12 = pow(r6, 2);
	// LJ potential (sigma and epsilon = 1.0 for simplicity.)
	u = 4.0 * (1.0 / r12 - 1.0 / r6) + U0;
	return u;
}

inline void init_MB_velosity(Molecule& m)
{
	// Maxwell-Boltzmann distribution 
	double sigma;
	random_device seed_gen;
	default_random_engine engine(seed_gen());
	sigma = sqrt(kB * T0 / m.mass);
	normal_distribution<> dist(0.0, sigma);
	m.px = m.mass * dist(engine);
	m.py = m.mass * dist(engine);
	m.pz = m.mass * dist(engine);
}

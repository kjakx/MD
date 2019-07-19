#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <math>
#include <random>
#include <vector>
#include "Molecule.hpp"
#include "Constants.hpp"

double LJ_potential(Molecule& mi, Molecule& mj);
void init_MB_velocity(Molecule& m);
void correct_distance(double &dx, double &dy, double &dz);
void correct_position(double &qx, double &qy, double &qz);

inline double LJ_potential(Molecule& mi, Molecule& mj)
{
        double dx, dy, dz;
	double r2, r6, r12, u;
	// distance between i-j
	dx = mj.qx - mi.qx;
	dy = mj.qy - mi.qy;
	dz = mj.qz - mi.qz;
	correct_distance(dx, dy, dz);
	r2 = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);
	// the force from molecule mj to molecule mi will be ignored when r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3); 
	r12 = pow(r6, 2);
	// LJ potential
	u = 4.0 * (1.0 / r12 - 1.0 / r6) + U0;
	return u;
}

inline void init_MB_velocity(Molecule& m)
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

inline void correct_distance(double &dx, double &dy, double &dz)
{
	if (dx > 0.5 * Lx)
	{
		dx -= Lx;
	}
	else if (dx < -0.5 * Lx)
	{
		dx += Lx;
	}
	if (dy > 0.5 * Ly)
	{
		dy -= Ly;
	}
	else if (dy < -0.5 * Ly)
	{
		dy += Ly;
	}
	if (dz > 0.5 * Lz)
	{
		dz -= Lz;
	}
	else if (dz < -0.5 * Lz)
	{
		dz += Lz;
	}
}

inline void correct_position(double &qx, double &qy, double &qz)
{
	if (qx > Lx)
	{
		qx -= Lx;
	}
	else if (qx < 0)
	{
		qx += Lx;
	}
	if (qy > Ly)
	{
		qy -= Ly;
	}
	else if (qy < 0)
	{
		qy += Ly;
	}
	if (qz > Lz)
	{
		qz -= Lz;
	}
	else if (qz < 0)
	{
		qz += Lz;
	}
}

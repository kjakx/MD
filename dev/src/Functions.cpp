#include "Functions.hpp"

double LJ_potential_between(Molecule* mi, Molecule* mj)
{
	double r2, r6, r12, u;
	// distance^2 between i-j
	r2 = mi->r2_to(mj);
	// the force between mi and mj will be ignored (= 0) if r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3); 
	r12 = pow(r6, 2);
	// LJ potential
	u = 4.0 * (1.0 / r12 - 1.0 / r6) + U0;
	return u;
}

double VDW_forces_between(Molecule* mi, Molecule* mj)
{
	double r2, r6, r14;
	double f;
	r2 = mi->r2_to(mj);
	// the force from molecule mj to molecule mi will be ignored when r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3);
	r14 = r6 * r6 * r2;
	// calculate force between i-j with derivative of LJ potential
	f = (24 * r6 - 48) / r14;
	/*--- memo
		本来はLJ potential の微分 f = (24 * r6 - 48) / r13 とすべき所だが、
		f はそのまま使うわけではなく、続くx,y,z成分の計算で、
		fx = f * rx / r などとして各成分の単位ベクトルを掛けて分解するので、
		先にr14で割ってrxを掛ける、という順序でも問題ないと理解。
	end memo ---*/
	return f;
}

void init_MB_velocity(Molecule* m)
{
	// Maxwell-Boltzmann distribution
	double sigma;
	random_device seed_gen;
	default_random_engine engine(seed_gen());
	sigma = sqrt(kB * T0);
	normal_distribution<> dist(0.0, sigma);
	m->px = dist(engine);
	m->py = dist(engine);
	m->pz = dist(engine);
}

void correct_distance(double& rx, double& ry, double& rz)
{
	if (rx > 0.5 * Lx)
	{
		rx -= Lx;
	}
	else if (rx < -0.5 * Lx)
	{
		rx += Lx;
	}
	if (ry > 0.5 * Ly)
	{
		ry -= Ly;
	}
	else if (ry < -0.5 * Ly)
	{
		ry += Ly;
	}
	if (rz > 0.5 * Lz)
	{
		rz -= Lz;
	}
	else if (rz < -0.5 * Lz)
	{
		rz += Lz;
	}
}

void correct_position(double& qx, double& qy, double& qz)
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

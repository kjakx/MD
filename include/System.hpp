#ifndef	SYSTEM_HPP
#define SYSTEM_HPP

#include <cmath>
#include <tuple>
#include <vector>
#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

#endif

using namespace std;

class System
{
private:
	vector<Molecule> molecules;
	//double E;
	//double T;
	double time;
	void update_position();
	void update_velocity();
	tuple<double, double, double> calculate_force(Molecule mi, Molecule mj);
public:
	System();
	~System();
	// setter
	void set_molecule(double qx, double qy, double qz);
	//void set_energy(long double E);
	//void set_temp(long double T);
	// getter
	//vector<Molecule>& get_molecules();
	double get_kinetic_energy();
	double get_potential_energy();
	double get_energy();
	double get_time();
	unsigned long int get_num_of_mol();
	// functions
	void tick();
	void update();
}

inline void System::update_position()
{
	for (Molecule &m : molecules)
	{
		m.qx += m.px * dt;
		m.qy += m.py * dt;
		m.qz += m.pz * dt;
		// periodic boundary condition
		correct_position(m.qx, m.qy, m.qz);
	}
	
}

inline void System::update_velocity()
{
	double fx, fy, fz;
	for (int i = 0; i < molecules.size() - 1; i++)
	{
		for (int j = i + 1; j < molecules.size(); j++)
		{
			// calculate force between i-j
			tie(fx, fy, fz) = calculate_force(molecules[i], molecules[j]);
			molecules[i].px += fx * dt * 0.5;
			molecules[i].py += fy * dt * 0.5;
			molecules[i].pz += fz * dt * 0.5;
			molecules[j].px -= fx * dt * 0.5;
			molecules[j].py -= fy * dt * 0.5;
			molecules[j].pz -= fz * dt * 0.5;
		}
	}
}

inline System()
{
	time = 0;
}	

inline ~System()
{
	delete molecules;
}

inline void System::set_molecule(double qx, double qy, double qz);
{	
	Molecule m;
	m.qx = qx;
	m.qy = qy;
	m.qz = qz;
	init_MB_verocity(m);
	molecules.push_back(m);
}
/*
inline void System::set_energy(long double E)
{
	this->E = E;
}

inline void System::set_temp(long double T)
{
	this->T = T;
}

inline vector<Molecule>& System::get_molecules()
{
	return molecules;
}
*/
inline double System::get_kinetic_energy()
{
	double K = 0;
	for (Molecule &m : molecules)
	{
		// sum up kinetic energies of all molecules.
		K += m.get_kinetic_energy();
	}
	return K;
}
	
inline double System::get_potential_energy()
{
	double U = 0;
	for (int i = 0; i < molecules.size() - 1; i++)
	{
		for (int j = i + 1; j < molecules.size(); j++)
		{
			// calculate LJ potential between i-j
			U += LJ_potential(molecules[i], molecules[j]);
		}
	}
	return U;
}

inline double System::get_energy()
{
	double K, U, E;
	K = get_kinetic_energy();
	U = get_potential_energy();
	E = K + U;
	return E;
}

inline double System::get_time()
{
	retuen time;
}

inline unsigned long int System::get_num_of_mol()
{
	return molecules.size();
}

inline void System::tick()
{
	time += dt;
}

inline void System::update()
{
	// velocity Verlet integration
	// 1. update(1) velocity on t + dt.
	update_velocity();
	// 2. update position on t + dt.
	update_position();
	// 3. update(2) velocity on t + dt.
	update_velocity();
}

inline tuple<double, double, double> System::calculate_force(Molecule mi, Molecule mj)
{
        double rx, ry, rz;
	double r2, r6, r14;
	double f, fx, fy, fz;
	// distance between i-j
	rx = mj.qx - mi.qx;
	ry = mj.qy - mi.qy;
	rz = mj.qz - mi.qz;
	// periodic boundary condition
	correct_distance(rx, ry, rz);
	r2 = pow(rx, 2) + pow(ry, 2) + pow(rz, 2);
	// the force from molecule mj to molecule mi will be ignored when r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3);	
	r14 = r6 * r6 * r2;
	// calculate force between i-j with derivative of LJ potential
	/*--- memo
		本来はLJ potential の微分 f = (24 * r6 - 48) / r13 とすべき所だが、
		f はそのまま使うわけではなく、続くx,y,z成分の計算で、
		fx = f * rx / r などとして各成分の単位ベクトルを掛けて分解するので、
		先にr14で割ってrxを掛ける、という順序でも問題ないと理解。
	end memo ---*/
	f = (24 * r6 - 48) / r14;
	fx = f * rx;
	fy = f * ry;
	fz = f * rz;
	return forward_as_tuple(fx, fy, fz);
}

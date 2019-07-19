#ifndef	SYSTEM_HPP
#define SYSTEM_HPP

#include <tuple>
#include <vector>
#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

class System
{
private:
	vector<Molecule> molecules;
	unsigned long double t;
	//long double E;
	long double T;
	double time;
	void update_position();
	void update_velocity();
	tuple<double, double, double> calculate_force();
public:
	System();
	~System();
	// setter
	void set_molecule(double qx, double qy, double qz);
	//void set_energy(long double E);
	void set_temp(long double T);
	// getter
	vector<Molecule>& get_molecules();
	//Molecule get_molecule(unsigned long int id);
	long double get_kinetic_energy();
	long double get_potential_energy();
	long double get_energy();
	long double get_temp();
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
	}
}

inline void System::update_velocity()
{
	double dfx, dfy, dfz;
	for (int i = 0; i < molecules.size() - 1; i++)
	{
		for (int j = i + 1; j < molecules.size(); j++)
		{
			// calculate force between i-j
			tie(dfx, dfy, dfz) = calculate_force(molecules[i], molecules[j]);
			molecules[i].px += dfx * dt * 0.5;
			molecules[i].py += dfy * dt * 0.5;
			molecules[i].pz += dfz * dt * 0.5;
			molecules[j].px -= dfx * dt * 0.5;
			molecules[j].py -= dfy * dt * 0.5;
			molecules[j].pz -= dfz * dt * 0.5;
		}
	}
}

inline System()
{
	this->T = T0;
	this->time = 0;
}	

inline void System::set_molecule(double qx, double qy, double qz);
{	
	Molecule m;
	m.set_q(qx, qy, qz);
	init_MB_verocity(m);
	molecules.push_back(m);
}
/*
inline void System::set_energy(long double E)
{
	this->E = E;
}
*/
inline void System::set_temp(long double T)
{
	this->T = T;
}

inline vector<Molecule>& System::get_molecules()
{
	return molecules;
}
/*
inline Molecule System::get_molecule(unsigned long int id)
{
	return molecules[id];
}
*/
inline long double System::get_kinetic_energy()
{
	long double K = 0;
	for (Molecule &m : molecules)
	{
		// sum up kinetic energies of all molecules.
		K += m.get_kinetic_energy();
	}
	return K;
}
	
inline long double System::get_potential_energy()
{
	long double U = 0;
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

inline long double System::get_energy()
{
	long double K, U, E;
	K = get_kinetic_energy();
	U = get_potential_energy();
	E = K + U;
	return E;
}

inline long double System::get_temp()
{
	retuen T;
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

inline tuple<double, double, double> System::calculate_force(molecules[i], molecules[j])
{
        double rx, ry, rz, dfx, dfy, dfz;
	long double r2, r6, r12, r14;
	// distance between i-j
	rx = mj.qx - mi.qx;
	ry = mj.qy - mi.qy;
	rz = mj.qz - mi.qz;
	r2 = pow(rx, 2) + pow(ry, 2) + pow(rz, 2);
	// the force from molecule mj to molecule mi will be ignored when r2 > CUTOFF_R2.
	if (r2 > CUTOFF_R2) return 0;
	r6 = pow(r2, 3);
	r12 = pow(r6, 2);
	r14 = r12 * r2;
	// calculate force between i-j with derivative of LJ potential
	/* ---memo
	本来はLJ potential の微分 df = (24 * r6 - 48) / r13 とすべき所だが、
	df はそのまま使うわけではなく、続くx,y,z成分の計算で、
	dfx = df * rx / r などとして各成分の単位ベクトルを掛けて分解するので、
	先にr14で割ってrxを掛ける、という計算でも問題ないと理解。
	end memo--- */
	df = (24 * r6 - 48) / r14;
	dfx = df * rx;
	dfy = df * ry;
	dfz = df * rz;
	return forward_as_tuple(dfx, dfy, dfz);
}

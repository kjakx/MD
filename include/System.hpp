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
			// interaction between i-j
			molecules[i].interact_with(molecules[j]);
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
			U += LJ_potential_between(molecules[i], molecules[j]);
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

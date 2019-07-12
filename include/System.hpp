#ifndef	SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

class System
{
private:
	vector<Molecule> molecules;
	long double E = 0;
	long double T = 0;
public:
	System();
	~System();
	// setter
	void set_molecule(double qx, double qy, double qz, 
			  double px, double py, double pz);
	void set_energy(long double E);
	void set_temp(long double T);
	//void set_num_of_mol(unsigned long int N);

	// getter
	vector<Molecule>& get_molecules();
	Molecule get_molecule(unsigned long int id);
	long double get_kinetic_energy();
	long double get_potential_energy();
	long double get_energy();
	long double get_temp();
	unsigned long int get_num_of_mol();

	// utils
	// to be continued...
}

inline System()
{
	
}

inline ~System()
{
	
}	

inline void System::set_molecule(double qx, double qy, double qz,
				 double px, double py, double pz);
{	
	// new molecule
	Molecule m;
	// coodinate and power
	m.set_q(qx, qy, qz);
	m.set_p(px, py, pz);
	// add new molecule to System
	molecules.push_back(m);
}

inline void System::set_energy(long double E)
{
	this->E = E;
}

inline void System::set_temp(long double T)
{
	this->T = T;
}

inline void System::set_num_of_mol(unsigned long int N)
{
	this->N = N;
}

inline vector<Molecule>& System::get_molecules()
{
	return molecules;
}

inline Molecule System::get_molecule(unsigned long int id)
{
	return molecules[id];
}

inline long double System::get_kinetic_energy()
{
	long double K = 0;
	for (Molecule &m : molecules)
	{
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

inline long double System::get_temp()
{
	retuen T;
}

inline unsigned long int System::get_num_of_mol()
{
	return molecules.size();
}

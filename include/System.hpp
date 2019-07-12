#ifndef	SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <tuple>
#include "Molecule.hpp"

class System
{
private:
	vector<Molecule> molecules;
	long double E, T;
	unsigned long int N;
public:
	// setter
	void set_molecule(double qx, double qy, double qz, 
			  double px, double py, double pz);
	void set_energy(long double E);
	void set_temp(long double T);
	void set_num_of_mol(unsigned long int N);

	// getter
	vector<Molecule>& get_molecule();
	Molecule get_molecule(unsigned long int id);
	long double get_energy();
	long double get_temp();
	unsigned long int get_num_of_mol();

	// utils
	// to be continued...
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
	return this->molecules;

inline Molecule System::get_molecule(unsigned long int id)
{
	return this->molecules[id];

inline long double System::get_energy()
{
	return this->E;
}

inline long double System::get_temp()
{
	retuen this->T;
}

inline unsigned long int System::get_num_of_mol()
{
	return this->N;
}

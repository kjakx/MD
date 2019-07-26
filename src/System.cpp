#include "System.hpp"

using namespace std;

void System::update_position()
{
	for (Molecule &m : molecules)
	{
		m.qx += m.px * dt;
		m.qy += m.py * dt;
		m.qz += m.pz * dt;
	}
}

void System::update_velocity()
{
	for (int i = 0; i < molecules.size() - 1; i++)
	{
		for (int j = i + 1; j < molecules.size(); j++)
		{
			// interaction between i-j
			molecules[i].interact_with(*molecules[j]);
		}
	}
}

System()
{
	time = 0;
}	

~System()
{
	delete molecules;
}

void System::add_molecule(double qx, double qy, double qz);
{	
	Molecule m;
	m.qx = qx;
	m.qy = qy;
	m.qz = qz;
	init_MB_verocity(m);
	molecules.push_back(m);
}

double System::get_kinetic_energy()
{
	double K = 0;
	for (Molecule &m : molecules)
	{
		// sum up kinetic energies of all molecules.
		K += m.get_kinetic_energy();
	}
	return K;
}
	
double System::get_potential_energy()
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

double System::get_energy()
{
	double K, U, E;
	K = get_kinetic_energy();
	U = get_potential_energy();
	E = K + U;
	return E;
}

double System::get_time()
{
	retuen time;
}

unsigned long int System::get_num_of_mol()
{
	return molecules.size();
}

void System::tick()
{
	time += dt;
}

void System::update()
{
	// velocity Verlet integration
	// 1. update(1) velocity on t + dt.
	update_velocity();
	// 2. update position on t + dt.
	update_position();
	// 3. update(2) velocity on t + dt.
	update_velocity();
	// 4. consider periodic boundary condition.
	correct_position();
	// 5. increase time by dt.
	tick();
}

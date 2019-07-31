#include "System.hpp"

using namespace std;

void System::update_position()
{
	for (Molecule *m : molecules)
	{
		m->qx += m->px * dt;
		m->qy += m->py * dt;
		m->qz += m->pz * dt;
		correct_position(m->qx, m->qy, m->qz);
	}
}

void System::update_velocity()
{
	for (size_t i = 0; i < molecules.size() - 1; i++)
	{
		for (size_t j = i + 1; j < molecules.size(); j++)
		{
			// interaction between i-j
			molecules[i]->interact_with(molecules[j]);
		}
	}
}

void System::control_temperature()
{
	double T = get_temperature();
	if (abs(T0 - T) / T0 > 0.05)
	{
		for (Molecule *m : molecules)
		{
			// velocity scaling method
			m->px *= sqrt(T0 / T);
			m->py *= sqrt(T0 / T);
			m->pz *= sqrt(T0 / T);
		}
	}
}

System::System()
{
	time = 0;
}

System::~System()
{
	for (Molecule *m : molecules)
	{
		delete m;
	}
}

void System::add_molecule(double qx, double qy, double qz)
{	
	Molecule* m = new Molecule(qx, qy, qz);
	molecules.push_back(m);
}

Molecule* System::get_molecule(size_t index)
{
	return molecules[index];
}

double System::get_kinetic_energy()
{
	double K = 0;
	for (Molecule *m : molecules)
	{
		// sum up kinetic energies of all molecules.
		K += m->get_kinetic_energy();
	}
	return K;
}
	
double System::get_potential_energy()
{
	double U = 0;
	for (size_t i = 0; i < molecules.size() - 1; i++)
	{
		for (size_t j = i + 1; j < molecules.size(); j++)
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

double System::get_temperature()
{
	double T = 0;
	for (Molecule *m : molecules)
	{
		T += pow(m->px, 2) + pow(m->py, 2) + pow(m->pz, 2);
	}
	T /= 3 * molecules.size();
	return T;
}

double System::get_time()
{
	return time;
}

size_t System::get_num_of_mol()
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
	// 4. control temperature (for NVT ensemble).
	control_temperature();
	// 5. increase time by dt.
	tick();
}

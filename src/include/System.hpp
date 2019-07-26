#pragma	once

#include <cmath>
#include <tuple>
#include <vector>
#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

using namespace std;

class System
{
private:
	vector<Molecule> molecules;
	double time;
	void update_position();
	void update_velocity();
public:
	System();
	~System();
	void add_molecule(double qx, double qy, double qz);
	// getter
	double get_kinetic_energy();
	double get_potential_energy();
	double get_energy();
	double get_time();
	unsigned long int get_num_of_mol();
	// functions
	void tick();
	void update();
};

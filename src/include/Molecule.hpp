#pragma once

#include <cmath>
#include <tuple>

using namespace std;

class Molecule
{
public:
// property:
	double qx, qy, qz;
	double px, py, pz;
// method:
	Molecule();
	Molecule(double qx, double qy, double qz);
	double get_kinetic_energy();
	double r2_to(Molecule* that);
	tuple<double, double, double> r_xyz_to(Molecule* that);
	void interact_with(Molecule* that);
};

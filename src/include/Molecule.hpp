#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <cmath>
#include <tuple>
#include "Functions.hpp"
#include "Constant.hpp"

#endif

using namespace std;

class Molecule
{
public:
// property:
	double mass;
	double qx, qy, qz;
	double px, py, pz;
// method:
	Molecule(double qx, double qy, double qz);
	double get_kinetic_energy();
	double r2_to(Molecule& that);
	tuple<double, double, double> r_xyz_to(Molecule& that);
	void interact_with(Molecule& that);
}

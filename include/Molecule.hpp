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

inline Molecule(double qx, double qy, double qz)
{
	mass = m0 / u_m;
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
	init_MB_velocity(this);
}

inline tuple<double, double, double> Md::r_xyz_to(Molecule& that)
{
	double rx, ry, rz;
	// components of distance between i-j
	rx = that.qx - this.qx;
	ry = that.qy - this.qy;
	rz = that.qz - this.qz;
	// periodic boundary condition
	correct_distance(rx, ry, rz);
	return forward_as_tuple(rx, ry, rz);
}

inline double Molecule::r2_to(Molecule& that)
{
	double rx, ry, rz;
	tie(rx, ry, rz) = this->r_xyz_to(that);
	r2 = pow(rx, 2) + pow(ry, 2) + pow(rz, 2);
	return r2;
}

inline double Molecule::get_kinetic_energy()
{
	double k = 0;
	k += pow(px, 2);
	k += pow(py, 2);
	k += pow(pz, 2);
	return k * 0.5;
}

inline void Molecule::interact_with(Molecule& that)
{
        double rx, ry, rz;
	double f, fx, fy, fz;
	// components of distance between i-j
	tie(rx, ry, rz) = this->r_xyz_to(that);
	// calculate force between i-j with derivative of LJ potential
	f = VDW_forces_between(this, that);
	// components of forces between i-j
	fx = f * rx;
	fy = f * ry;
	fz = f * rz;
	// interaction!
	// action
	this.px += fx * dt * 0.5;
	this.py += fy * dt * 0.5;
	this.pz += fz * dt * 0.5;
	// reaction
	that.px -= fx * dt * 0.5;
	that.py -= fy * dt * 0.5;
	that.pz -= fz * dt * 0.5;
}

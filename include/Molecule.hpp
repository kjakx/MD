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
	~Molecule();
	// setter
	//void set_q(double qx, double qy, double qz);
	//void set_p(double px, double py, double pz);

	// getter
	//tuple<double, double, double> get_q();
	//tuple<double, double, double> get_p();
	double get_kinetic_energy();
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
/*
inline void Molecule::set_q(double qx, double qy, double qz)
{
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
}

inline void Molecule::set_p(double px, double py, double pz)
{
	this->px = px;
	this->py = py;
	this->pz = pz;
}
inline tuple<double, double, double> Molecule::get_q()
{
	// Since I would like to write in a line, I used tuple.
	return forward_as_tuple(qx, qy, qz);
}

inline tuple<double, double, double> Molecule::get_p()
{
	return forward_as_tuple(px, py, pz);
}
*/
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
	tie(rx, ry, rz) = r_xyz_between(this, that);
	// calculate force between i-j with derivative of LJ potential
	f = VDW_forces_between(this, that);
	// components of forces between i-j
	fx = f * rx;
	fy = f * ry;
	fz = f * rz;
	// interaction!
	this.px += fx * dt * 0.5;
	this.py += fy * dt * 0.5;
	this.pz += fz * dt * 0.5;
	that.px -= fx * dt * 0.5;
	that.py -= fy * dt * 0.5;
	that.pz -= fz * dt * 0.5;
}

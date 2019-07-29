#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

using namespace std;

Molecule::Molecule()
{
	Molecule(0, 0, 0);
}

Molecule::Molecule(double qx, double qy, double qz)
{
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
	init_MB_velocity(this);
}

tuple<double, double, double> Molecule::r_xyz_to(Molecule* that)
{
	double rx, ry, rz;
	// components of distance between i-j
	rx = that->qx - this->qx;
	ry = that->qy - this->qy;
	rz = that->qz - this->qz;
	// periodic boundary condition
	correct_distance(rx, ry, rz);
	return forward_as_tuple(rx, ry, rz);
}

double Molecule::r2_to(Molecule* that)
{
	double rx, ry, rz, r2;
	tie(rx, ry, rz) = this->r_xyz_to(that);
	r2 = pow(rx, 2) + pow(ry, 2) + pow(rz, 2);
	return r2;
}

double Molecule::get_kinetic_energy()
{
	double k = 0;
	k += pow(px, 2);
	k += pow(py, 2);
	k += pow(pz, 2);
	return k * 0.5;
}

void Molecule::interact_with(Molecule* that)
{
	double rx, ry, rz;
	double f, fx, fy, fz;
	// components of distance between i-j
	tie(rx, ry, rz) = this->r_xyz_to(that);
	// calculate force between i-j with derivative of LJ potential
	f = VDW_forces_between(this, that);
	// preserve p for calculation of position
	this->px_prev = this->px;
	this->py_prev = this->py;
	this->pz_prev = this->pz;
	that->px_prev = that->px;
	that->py_prev = that->py;
	that->pz_prev = that->pz;
	// components of forces between i-j
	fx = f * rx;
	fy = f * ry;
	fz = f * rz;
	// interaction!
	// action
	this->px += fx * dt * 0.5;
	this->py += fy * dt * 0.5;
	this->pz += fz * dt * 0.5;
	// reaction
	that->px -= fx * dt * 0.5;
	that->py -= fy * dt * 0.5;
	that->pz -= fz * dt * 0.5;
}

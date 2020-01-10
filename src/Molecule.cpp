#include "Molecule.hpp"
#include "Functions.hpp"
#include "Constants.hpp"
#include <cmath>
#include <tuple>
#include <random>

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
	this->init_velocity();
}

Molecule::Molecule(double qx, double qy, double qz,
                   double px, double py, double pz)
{
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
	this->px = px;
	this->py = py;
	this->pz = pz;
}

void Molecule::init_velocity()
{
	// Maxwell-Boltzmann distribution
	double sigma;
	sigma = sqrt(kB * T0_R / m0_R);
	random_device seed_gen;
	default_random_engine engine(seed_gen());
	normal_distribution<> dist(0.0, sigma);
	this->px = dist(engine) / u_v;
	this->py = dist(engine) / u_v;
	this->pz = dist(engine) / u_v;
}

void Molecule::update_position()
{
    this->qx += this->px * dt;
	this->qy += this->py * dt;
	this->qz += this->pz * dt;
	correct_position(this->qx, this->qy, this->qz);
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
	double k;
	k = pow(px, 2) + pow(py, 2) + pow(pz, 2);
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

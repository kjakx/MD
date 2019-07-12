#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <tuple>

using namespace std;

class Molecule
{
private:
	double qx, qy, qz;
	double px, py, pz;
public:
	// setter
	void set_q(double qx, double qy, double qz);
	void set_p(double px, double py, double pz);

	// getter
	tuple<double, double, double> get_q();
	tuple<double, double, double> get_p();
	long double get_kinetic_energy();
}

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

inline long double Molecule::get_kinetic_energy()
{
	long double k = 0;
	k += px * px;
	k += py * py;
	k += pz * pz;
	return k * 0.5;
}

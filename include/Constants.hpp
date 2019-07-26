#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cmath>
#include <iostream>

#endif

using namespace std;

//--- define units of variables
const double kB = pow(1.380649, -23);		// Boltzmann constant [J/K]
const double eV = pow(1.602176634, -19);	// elementary charge [J]
const double u_d = pow(1.000, -10);		// distance [m]
const double u_m = pow(1.000, -26);		// mass [kg]
const double u_t = u_d * sqrt(u_m / eV);	// time [s]
const double u_v = sqrt(eV / u_m);		// velocity [m/s]
const double u_f = eV / u_d;			// force [kg*m/s2]
const double u_a = eV / (u_d * u_m);		// acceleration [m/s2]
const double u_T = eV / kB;			// temperature [K]
const double u_P = eV / pow(u_d, 3);		// pressure [kg/(m*s2)]
const double u_U = eV;				// energy [J]
//---

//--- variables in real value
const double T0_R = 273.15;			// initial temperature [K]
const double m0_R = u_m;			// mass of molecule [kg]
const double dt_R = 0.01;			// calculation time step [s]
//---

//--- variables in dimensionless
const double T0 = T0_R / u_T;			// initial temperature [-]
const double m0 = m0_R / u_m;			// mass of molecule [-]
const double dt = dt_R / u_t;			// calculation time step [-]
const double L = 10.0;
//---

//--- cutoff radius and potential U0
const double CUTOFF_R = 2.0;
const double CUTOFF_R2 = pow(CUTOFF_R, 2);
const double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const double U0 = - 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);
//---

int main()
{
	cout << "### unit of variables ###" << endl;
	cout << "kB\t=\t" << kB << "[J/K]" << endl;
	cout << "eV\t=\t" << eV << "[J]" << endl;
	cout << "d\t=\t" << u_d << "[m]" << endl;
	cout << "m\t=\t" << u_m << "[kg]" << endl;
	cout << "t\t=\t" << u_t << "[s]" << endl;
	cout << "v\t=\t" << u_v << "[m/s]" << endl;
	cout << "f\t=\t" << u_f << "[kg*m/s2]" << endl;
	cout << "a\t=\t" << u_a << "[m/s2]" << endl;
	cout << "T\t=\t" << u_T << "[K]" << endl;
	cout << "P\t=\t" << u_P << "[kg/(m*s2)]" << endl;
	cout << "U\t=\t" << u_U << "[J]" << endl;
  	return 0;
}

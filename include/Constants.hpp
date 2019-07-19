#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <math>
#include <iostream>

//--- define units of variables
const unsigned double kB = pow(1.380649, -23);  	// Boltzmann constant [J/K]
const unsigned double eV = pow(1.602176634, -19);	// elementary charge [J]
const unsigned double u_d = pow(1.000, -10);    	// distance [m]
const unsigned double u_m = pow(1.000, -26);		// mass [kg]
const unsigned double u_t = u_d * sqrt(u_m / eV);	// time [s]
const unsigned double u_v = sqrt(eV / u_m);		// velocity [m/s]
const unsigned double u_f = eV / u_d;			// force [kg*m/s2]
const unsigned double u_a = eV / (u_d * u_m);		// acceleration [m/s2]
const unsigned double u_T = eV / kB;			// temperature [K]
const unsigned double u_P = eV / pow(u_d, 3);		// pressure [kg/(m*s2)]
const unsigned double u_U = eV;				// energy [J]
//---

//--- variables in real value
const unsigned double T0_R = 273.15;			// initial temperature [K]
const unsigned double m0_R = u_m;			// mass of molecule [kg]
const unsigned double dt_R = 0.01;			// calculation time step [s]
//---

//--- variables in dimensionless
const unsigned double T0 = T0_R / u_T;			// initial temperature [-]
const unsigned double m0 = m0_R / u_m;			// mass of molecule [-]
const unsigned double dt = dt_R / u_t;			// calculation time step [-]
//---

//--- cutoff radius and potential U0
const unsigned double CUTOFF_R = 2.0;
const unsigned double CUTOFF_R2 = pow(CUTOFF_R, 2);
const unsigned double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const unsigned double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const double U0 = - 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);
//---

int main()
{
	cout << "### unit of variables ### << endl;
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

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <math>

//--- define units of variables
const unsigned double kB = pow(1.380649, -23);  	// Boltzmann constant [J/K]
const unsigned double eV = pow(1.602176634, -19);	// elementary charge [J]
const unsigned double u_d = pow(1.000, -10);    	// distance [m]
const unsigned double u_m = pow(1.000, -26);		// mass [kg]
const unsigned double u_t = u_d * sqrt(u_m / eV);	// time [s]
const unsigned double u_v = sqrt(eV / u_m);		// velosity [m/s]
const unsigned double u_f = eV / u_d;			// force [kg(m/s2)]
const unsigned double u_a = eV / (u_d * u_m);		// acceleration [m/s2]
const unsigned double u_T = eV / kB;			// temperature [K]
const unsigned double u_P = eV / pow(u_d, 3);		// pressure [kg/(ms2)]
const unsigned double u_U = eV;				// energy [J]
//---

//--- variables in real value
const unsigned double T0_R = 273.15;			// initial temperature [K]
const unsigned double m0_R = u_m;			// mass of molecule [kg]
//---

//--- variables in dimensionless
const unsigned double T0 = T0_R / u_T;			// initial temperature [-]
const unsigned double m0 = m0_R / u_m;			// mass of molecule [-]
//---

//--- cutoff radius and potential U0
const unsigned double CUTOFF_R = 2.0;
const unsigned double CUTOFF_R2 = pow(CUTOFF_R, 2);
const unsigned double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const unsigned double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const double U0 = - 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);
//---

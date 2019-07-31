#pragma once

#include <cmath>
#include <iostream>

using namespace std;

//--- define units of variables (Ar)
const static double kB = 1.380649 * pow(10, -23);	// Boltzmann constant [J/K]
const static double u_d = 3.4 * pow(10, -10);		// distance [m]
const static double u_e = 1.65 * pow(10, -21);		// energy [J]
const static double u_m = 6.69 * pow(10, -26);		// mass [kg]
const static double u_t = u_d * sqrt(u_m / u_e);	// time [s]
const static double u_v = sqrt(u_e / u_m);		// velocity [m/s]
const static double u_f = u_e / u_d;			// force [kg*m/s2]
const static double u_a = u_e / (u_d * u_m);		// acceleration [m/s2]
const static double u_T = u_e / kB;			// temperature [K]
const static double u_P = u_e / pow(u_d, 3);		// pressure [kg/(m*s2)]
const static double u_rho = u_m / pow(u_d, 3);		// density [kg/m3]
//---

//--- variables in real value
const static double T0_R = 300.0;			// initial temperature [K]
const static double m0_R = u_m;				// mass of molecule [kg]
const static double dt_R = 0.5 * pow(10, -15);		// calculation time step [s]
const static double LC_R = 5.43 * pow(10, -10);		// lattice constant [m]
const static double L_R = 5 * LC_R;
//---

//--- variables in dimensionless
const static double T0 = T0_R / u_T;			// initial temperature [-]
const static double m0 = m0_R / u_m;			// mass of molecule [-]
const static double dt = dt_R / u_t;			// calculation time step [-]
const static double LC = LC_R / u_d;			// lattice constant [-]
const static double L = L_R / u_d;			// size of system [-]
const static double Lx = L;
const static double Ly = L;
const static double Lz = L;
//---

//--- cutoff radius and potential U0
const static double CUTOFF_R = LC;
const static double CUTOFF_R2 = pow(CUTOFF_R, 2);
const static double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const static double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const static double U0 = - 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);
//---

/*
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
	cout << "e\t=\t" << u_e << "[J]" << endl;
	cout << "rho\t=\t" << u_rho << "[kg/m3]" << endl;
	cout << "T0\t=\t" << T0 << "[-]" << endl;
	cout << "m0\t=\t" << m0 << "[-]" << endl;
	cout << "dt\t=\t" << dt << "[-]" << endl;
	cout << "density\t=\t" << density << "[-]" << endl;
	return 0;
}
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <math>
// define units of variables
const double m0 = pow(1.000, -26); // mass [kg]
const double kB = pow(1.38064852, -23); // Boltzmann constant [J/K]
const double eV = pow(1.60217662, -19); // energy [J]
const double d = pow(1.000, -10); // distance [m]

// set variables in real value

// variables in units

// initial temperature [K]
const double T0 = 273.15;

// Boltzmann constant [J/K

const long double CUTOFF = 2.0;
const long double CUTOFF_R2 = pow(CUTOFF, 2);
const long double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const long double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const long double U0 = - 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);

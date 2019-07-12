#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <math>

const long double CUTOFF_R2 = 2.0;
const long double CUTOFF_R6 = pow(CUTOFF_R2, 3);
const long double CUTOFF_R12 = pow(CUTOFF_R6, 2);
const long double U0 = 4 * (1.0 / CUTOFF_R12 - 1.0 / CUTOFF_R6);

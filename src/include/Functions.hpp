#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cmath>
#include <tuple>
#include <random>
#include <vector>
#include "Molecule.hpp"
#include "Constants.hpp"

#endif

double LJ_potential_between(Molecule& mi, Molecule& mj);
double VDW_forces_between(Molecule& mi, Molecule& mj);
void init_MB_velocity(Molecule& m);
void correct_distance(double &dx, double &dy, double &dz);
void correct_position(double &qx, double &qy, double &qz);

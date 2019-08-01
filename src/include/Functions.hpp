#pragma once

#include "Molecule.hpp"

double LJ_potential_between(Molecule* mi, Molecule* mj);
double VDW_forces_between(Molecule* mi, Molecule* mj);
void correct_distance(double& rx, double& ry, double& rz);
void correct_position(double& qx, double& qy, double& qz);

#pragma once

#define STEPS 10000
#define SAMPLES 100

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "System.hpp"
#include "Constants.hpp"

class MD
{
private:
	System sys;
	void config_molecules();
	void export_cdview();
public:
	MD();
	void run();
};

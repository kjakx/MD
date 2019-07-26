#pragma once

#define STEPS 10000
#define SAMPLES 100

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "System.hpp"
#include "Constant.hpp"

class MD
{
private:
	System sys;
	void config_molecules();
public:
	MD();
	~MD();
	void run();
};

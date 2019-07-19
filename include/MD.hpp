#ifndef MD_HPP
#define MD_HPP

#define STEPS 10000
#define SAMPLES 100

#include <string>
#include <fstream>
#include <iostream>
#include "System.hpp"
#include "Constant.hpp"

using namespace std;

class MD
{
private:
	System sys;
	void config_molecules(istream& istr);
	void calculate();
public:
	MD();
	~MD();
	void run();
}

inline void MD::config_molecules(istream& istr)
{
	while (true)
	{
		istr >> qx >> qy >> qz;
		if (istr.eof()) break;
		sys.set_molecule(qx, qy, qz);
	}
}

inline MD::calculate();
{
	sys.update();
	sys.tick();
}

inline MD()
{
	sys = System();
	config_molecules(cin);
}

inline ~MD()
{
	delete sys;
}

inline void MD::run()
{
	
}

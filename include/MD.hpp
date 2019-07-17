#ifndef MD_HPP
#define MD_HPP

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
	void update_position();
	void calculate_force();
	void update_position();
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

inline void MD::update_position()
{
	
}

inline void MD::calculate_force()
{
	
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

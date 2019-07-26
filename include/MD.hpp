#ifndef MD_HPP
#define MD_HPP

#define STEPS 10000
#define SAMPLES 100

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "System.hpp"
#include "Constant.hpp"

#endif

using namespace std;

class MD
{
private:
	System sys;
	void config_molecules();
public:
	MD();
	~MD();
	void run();
}

inline void MD::config_molecules()
{
	/*--- いずれはファイルや標準ストリームから読み込めるようにする
	while (true)
	{
		istr >> qx >> qy >> qz;
		if (istr.eof()) break;
		sys.set_molecule(qx, qy, qz);
	}
	---*/
	const double density = 0.50;
	const double s = 1.0 / pow(density * 0.25, 1.0 / 3.0);
	const double hs = s * 0.5;
	const int is = static_cast<int>(L / s);
	for (int iz = 0; iz < is; iz++)
	{
		for (int iy = 0; iy < is; iy++)
		{
			for (int ix = 0; ix < is; ix++)
			{
				sys.add_molecules(ix * s, iy * s, iz * s);
				sys.add_molecules(ix * s + hs, iy * s, iz * s);
				sys.add_molecules(ix * s, iy * s + hs, iz * s);
				sys.add_molecules(ix * s, iy * s, iz * s + hs);
			}
		}
	}
}

inline MD()
{
	sys = System();
	config_molecules();
}

inline ~MD()
{
	delete sys;
}

inline void MD::run()
{
	cout << "### MD calculation ###" << endl;
	cout << "time\t";
	cout << "Kinetic Energy\t";
	cout << "Potential Energy\t";
	cout << "Energy" << endl;
	for (int i = 0; i <= STEPS; i++)
	{
		if (i % SAMPLES == 0)
		{
			cout << sys.get_time() << "\t";
			cout << sys.get_kinetic_energy() << "\t";
			cout << sys.get_potential_energy() << "\t";
			cout << sys.get_energy() << endl;
		}
		sys.update();
	}
}

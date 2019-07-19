#ifndef MD_HPP
#define MD_HPP

#define STEPS 10000
#define SAMPLES 100

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
	void config_molecules(istream& istr);
	void calculate();
public:
	MD();
	~MD();
	void run();
}

inline void MD::config_molecules(istream& istr)
{
	/*--- いずれはファイルや標準ストリームから読み込めるようにする
	while (true)
	{
		istr >> qx >> qy >> qz;
		if (istr.eof()) break;
		sys.set_molecule(qx, qy, qz);
	}
	---*/
}

inline void MD::calculate();
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
		calculate();
	}
}

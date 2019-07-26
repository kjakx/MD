#include "MD.hpp"

using namespace std;

void MD::config_molecules()
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

MD()
{
	sys = System();
	config_molecules();
}

~MD()
{
	delete sys;
}

void MD::run()
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

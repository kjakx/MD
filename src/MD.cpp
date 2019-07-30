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
	const double s = 1.0 / pow(density * 0.25, 1.0 / 3.0);
	const double hs = s * 0.5;
	const int is = static_cast<int>(L / s);
	for (int iz = 0; iz < is; iz++)
	{
		for (int iy = 0; iy < is; iy++)
		{
			for (int ix = 0; ix < is; ix++)
			{
				sys.add_molecule(ix * s, iy * s, iz * s);
				sys.add_molecule(ix * s + hs, iy * s + hs, iz * s);
				sys.add_molecule(ix * s + hs, iy * s, iz * s + hs);
				sys.add_molecule(ix * s, iy * s + hs, iz * s + hs);
			}
		}
	}
}

void MD::export_cdview()
{
	double x, y, z;
	ofstream output_file;
	ostringstream oss;
	// set filename
	ios::fmtflags curret_flag = cout.flags();
	oss << "./vis/" << setw(4) << std::setfill('0') << steps << ".cdv";
	string filename(oss.str());
	std::cout.flags(curret_flag);
	// open output file 
	output_file.open(filename, ios::out);
	for (size_t i = 0; i < sys.get_num_of_mol(); i++)
	{
		x = sys.get_molecule(i)->qx;
		y = sys.get_molecule(i)->qy;
		z = sys.get_molecule(i)->qz;
		output_file << i << " " << 0 << " " << x << " " << y << " " << z << endl;
	}
	output_file.close();
}

MD::MD()
{
	sys = System();
	config_molecules();
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
			steps = i / SAMPLES;
			export_cdview();
			cout << sys.get_time() << "\t";
			cout << sys.get_kinetic_energy() << "\t";
			cout << sys.get_potential_energy() << "\t";
			cout << sys.get_energy() << endl;
		}
		sys.update();
	}
}

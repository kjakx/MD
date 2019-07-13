#ifndef MD_HPP
#define MD_HPP

#include <fstream>
#include "System.hpp"

using namespace std;

class MD
{
private:
	System sys;
public:
	MD();
	~MD();
	init();
	run();
	
	config_molecules();
}

inline MD()
{
	sys = System();
	// input file stream
	ifstream fin("input.dat");

	// output file stream
	ofstream fout("output.dat"); 

	// file open error handling
	if(fin.fail())
	{
		cout << "cannot open input file" << endl;
    		return 1;
	}
	if(fout.fail())
	{
		cout << "cannot open output file" << endl;
		return 1;
	}

	while((fin >> qx >> qy >> qz)!=0)
	{
		sys.set_molecule(qx, qy, qz);
	}

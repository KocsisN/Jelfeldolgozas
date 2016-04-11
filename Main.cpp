#include<iostream>
#include<vector>
#include<fstream>
#include"EMD.h"

using namespace std;

int main()
{
	std::vector<double> signal, time;
	ifstream in("signal.dat");
	

	double dt0, DT, dt = 0, val;
	in >> dt0 >> DT;

	while (in >> val){
		signal.push_back(val);
		//time.push_back(dt);
		//dt += DT;
	}
	in.close();
/*
	vector<double> minima, maxima, minimaIndexes, maximaIndexes;*/

	EMD emd(1/20000);

	emd.compute(signal);


	system("pause");
	return 0;
}
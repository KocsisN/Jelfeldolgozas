#include<iostream>
#include<vector>
#include<fstream>
#include"EMD.h"

using namespace std;

int main()
{
	std::vector<double> signal, time;
	ifstream in("signal.dat");
	
	if (!in.is_open()){
		cout << "NINCS" << endl;
		system("pause");
		return 0;
	}

	double dt0, DT, val;
	in >> DT;

	while (in >> val){
		signal.push_back(val);
		//time.push_back(dt);
		//dt += DT;
	}
	cout << signal.size();
	in.close();
/*
	vector<double> minima, maxima, minimaIndexes, maximaIndexes;*/

	EMD emd((double)1/20000.0);

	emd.compute(signal);


	system("pause");
	return 0;
}
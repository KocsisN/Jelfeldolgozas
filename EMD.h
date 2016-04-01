#ifndef EMD_H
#define EMD_H

#include<vector>
#include<fstream>
#include<string>
#include<vector>
#include"spline3.h"
#include"Extrema.h"

#define EPSFORZERO 0.0004
#define EPSFORNONZERO 0.001

using namespace std;

class EMD
{
private:
	string inputFile, outputFile;
	Extrema extrema;
	double step;
	bool isIMF(vector<double> &potentialIMF, int numberOfExtremas, vector<double> &signalNew);
public:
	EMD(double step);
	EMD(string inputFile = "input.txt", string outputFile="output.txt", double step = 0.00005);
	~EMD();

	void compute(vector<double> &signal);
};

#endif
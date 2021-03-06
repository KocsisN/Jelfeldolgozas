#ifndef EMD_H
#define EMD_H

#include<vector>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<iostream>
#include<chrono>
#include"spline3.h"
#include"Extrema.h"

#define EPSFORZERO 0.0001
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
	EMD(string inputFile = "input.txt", string outputFile = "output.txt");
	~EMD();

	void compute(vector<double> &signal);
};

#endif
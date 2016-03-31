#ifndef EMD_H
#define EMD_H

#include<vector>
#include<fstream>
#include<string>
#include<vector>
#include"spline3.h"
#include"Extrema.h"

using namespace std;

class EMD
{
private:
	string inputFile, outputFile;
	Extrema extrema;
	bool isIMF(vector<double> &potentialIMF);
public:
	EMD(string inputFile = "input.txt", string outputFile="output.txt");
	~EMD();

	void compute(vector<double> signal);
};

#endif
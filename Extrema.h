#ifndef EXTREMA_H
#define EXTREMA_H

#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

class Extrema
{
public:
	Extrema();
	~Extrema();

	void getExtremas(vector<double> signal, vector<double> &minima, vector<double> &minimaIndexes,
		vector<double> &maxima, vector<double> &maximaIndexes, double step, bool only_minima = true,
		bool onlymaxima = true, bool cout = true);
	int numberOfZeroCross(vector<double> &signal);


	void printToFile(string filename, vector<double> &minima, vector<double> &minimaIndexes,
		vector<double> &maxima, vector<double> &maximaIndexes);
};

#endif